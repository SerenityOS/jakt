LIBRARY = libak.so

OBJS = \
	AK/FlyString.o \
	AK/Format.o \
	AK/GenericLexer.o \
	AK/String.o \
	AK/StringBuilder.o \
	AK/StringImpl.o \
	AK/StringView.o \
	AK/Utf16View.o \
	AK/Utf8View.o \
	AK/kmalloc.o

CXX = clang++-14
CXXFLAGS = -std=c++20 -fPIC -O -g -I. -Wall -Wno-user-defined-literals

all: $(LIBRARY)

$(LIBRARY): $(OBJS)
	$(LD) -shared -o $(LIBRARY) $(OBJS)

clean:
	rm -f $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<
