from pathlib import Path
from LSP.plugin import LspPlugin, OnPreStartContext
from lsp_utils import NodeManager
from sublime_lib import ResourcePath

def plugin_loaded():
    LspYaktPlugin.register()

def plugin_unloaded():
    LspYaktPlugin.unregister()


class LspYaktPlugin(LspPlugin):
    @classmethod
    def on_pre_start_async(cls, context: OnPreStartContext) -> None:
        package_name = cls.plugin_storage_path.name
        NodeManager.on_pre_start_async(
            context,
            cls.plugin_storage_path,
            ResourcePath('Packages', package_name, 'server'),
            Path('src', 'server.js'),
            node_version_requirement='>=18',
        )
