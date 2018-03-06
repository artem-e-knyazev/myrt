BINARY_DIR:=build
BINARY_NAME:=myrt
BINARY_PATH:=$(BINARY_DIR)/$(BINARY_NAME)

OUTPUT:=-o $(BINARY_PATH)

INCLUDE_MYRT_MATH:=-I submodules/myrt_math/include
INCLUDE_MYRT:=-I src
INCLUDE:=$(INCLUDE_MYRT_MATH) $(INCLUDE_MYRT)

CFLAGS:=-std=c++1z -O3 -Weffc++ -Wc++1z-extensions

SRC:=src/main.cpp

all: build

.PHONY: build
build:
	mkdir -p $(BINARY_DIR)
	g++ $(CFLAGS) $(INCLUDE) $(OUTPUT) $(SRC)

