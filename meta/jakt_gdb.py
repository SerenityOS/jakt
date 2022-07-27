# Copyright (c) 2021, Gunnar Beutner <gunnar@beutner.name>
# Copyright (c) 2021-2022, Ali Mohammad Pur <mpfard@jakt.org>
#
# SPDX-License-Identifier: BSD-2-Clause

import gdb
import gdb.types
import re


def handler_class_for_type(type, re=re.compile('^([^<]+)(<.*>)?$')):
    typename = str(type.tag)

    match = re.match(typename)
    if not match:
        return UnhandledType

    klass = match.group(1)

    if klass == 'Jakt::Array':
        return JaktArray
    elif klass == 'Jakt::RefCounted':
        return JaktRefCounted
    elif klass == 'Jakt::RefPtr':
        return JaktRefPtr
    elif klass == 'Jakt::NonnullRefPtr':
        return JaktRefPtr
    elif klass == 'Jakt::String':
        return JaktString
    elif klass == 'Jakt::StringStorage':
        return JaktStringStorage
    elif klass == 'Jakt::Variant':
        return JaktVariant
    else:
        return UnhandledType


class UnhandledType:
    @classmethod
    def prettyprint_type(cls, type):
        return type.name


class JaktRefCounted:
    def __init__(self, val):
        self.val = val

    def to_string(self):
        return self.val["m_ref_count"]

    @classmethod
    def prettyprint_type(cls, type):
        contained_type = type.template_argument(0)
        return f'Jakt::RefCounted<{handler_class_for_type(contained_type).prettyprint_type(contained_type)}>'


class JaktString:
    def __init__(self, val):
        self.val = val

    def to_string(self):
        if int(self.val["m_storage"]["m_ptr"]) == 0:
            return '""'
        else:
            impl = JaktRefPtr(self.val["m_storage"]).get_pointee().dereference()
            return JaktStringStorage(impl).to_string()

    @classmethod
    def prettyprint_type(cls, type):
        return 'Jakt::String'


class JaktStringView:
    def __init__(self, val):
        self.val = val

    def to_string(self):
        if int(self.val["m_length"]) == 0:
            return '""'
        else:
            characters = self.val["m_characters"]
            str_type = characters.type.target().array(self.val["m_length"]).pointer()
            return str(characters.cast(str_type).dereference())

    @classmethod
    def prettyprint_type(cls, type):
        return 'Jakt::StringView'


def get_field_unalloced(val, member, type):
    # Trying to access a variable-length field seems to fail with
    # Python Exception <class 'gdb.error'> value requires 4294967296 bytes, which is more than max-value-size
    # This works around that issue.
    return gdb.parse_and_eval(f"*({type}*)(({val.type.name}*){int(val.address)})->{member}")


class JaktStringStorage:
    def __init__(self, val):
        self.val = val

    def to_string(self):
        if int(self.val["m_length"]) == 0:
            return '""'
        else:
            str_type = gdb.lookup_type("char").array(self.val["m_length"])
            return get_field_unalloced(self.val, "m_inline_buffer", str_type)

    @classmethod
    def prettyprint_type(cls, type):
        return 'Jakt::StringStorage'


class JaktRefPtr:
    def __init__(self, val):
        self.val = val

    def to_string(self):
        return JaktRefPtr.prettyprint_type(self.val.type)

    def get_pointee(self):
        inner_type = self.val.type.template_argument(0)
        inner_type_ptr = inner_type.pointer()
        return self.val["m_ptr"].cast(inner_type_ptr)

    def children(self):
        return [('*', self.get_pointee())]

    @classmethod
    def prettyprint_type(cls, type):
        contained_type = type.template_argument(0)
        return f'Jakt::RefPtr<{handler_class_for_type(contained_type).prettyprint_type(contained_type)}>'


class JaktVariant:
    def __init__(self, val):
        self.val = val
        self.index = int(self.val["m_index"])
        self.contained_types = self.resolve_types(self.val.type)

    def to_string(self):
        return JaktVariant.prettyprint_type(self.val.type)

    def children(self):
        data = self.val["m_data"]
        ty = self.contained_types[self.index]
        return [(JaktVariant.variant_name(ty), data.cast(ty.pointer()).referenced_value())]

    @classmethod
    def resolve_types(cls, ty):
        contained_types = []
        type_resolved = ty.strip_typedefs()
        index = 0
        while True:
            try:
                arg = type_resolved.template_argument(index)
                index += 1
                contained_types.append(arg)
            except RuntimeError:
                break
        return contained_types

    @classmethod
    def variant_name(cls, t, re=re.compile(r'^Jakt::.*?([^:]*)_Details::(\w+)$')):
        match = re.match(t.name)
        if match:
            klass = match.group(1)
            variant = match.group(2)
            return f'{klass}::{variant}'
        return handler_class_for_type(t).prettyprint_type(t)

    @classmethod
    def prettyprint_type(cls, ty):
        names = ", ".join(JaktVariant.variant_name(t) for t in JaktVariant.resolve_types(ty))
        return f'Jakt::Variant<{names}>'


class JaktArray:
    def __init__(self, val):
        self.val = val
        self.storage_type = self.val.type.template_argument(0)

    def to_string(self):
        impl = JaktRefPtr(self.val["m_storage"]).get_pointee().dereference()
        return JaktArrayStorage(impl).to_string()

    @classmethod
    def prettyprint_type(cls, type):
        t = type.template_argument(0)
        type_name = handler_class_for_type(t).prettyprint_type(t)
        return f'Jakt::Array<{type_name}>'

class JaktArrayStorage:
    def __init__(self, val):
        self.val = val
        self.storage_type = self.val.type.template_argument(0)

    def to_string(self):
        return JaktArrayStorage.prettyprint_type(self.val.type)

    def children(self):
        array_type = self.storage_type.array(self.val["m_length"])
        return get_field_unalloced(self.val, "m_elements", array_type)

    @classmethod
    def prettyprint_type(cls, type):
        t = type.template_argument(0)
        type_name = handler_class_for_type(t).prettyprint_type(t)
        return f'Jakt::ArrayStorage<{type_name}>'


class JaktPrettyPrinterLocator(gdb.printing.PrettyPrinter):
    def __init__(self):
        super(JaktPrettyPrinterLocator, self).__init__("jakt_pretty_printers", [])

    def __call__(self, val):
        type = gdb.types.get_basic_type(val.type)
        handler = handler_class_for_type(type)
        if handler is UnhandledType:
            return None
        return handler(val)


gdb.printing.register_pretty_printer(None, JaktPrettyPrinterLocator(), replace=True)
