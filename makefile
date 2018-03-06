INCLUDE_MYRT_MATH:=-I submodules/myrt_math/include
INCLUDE:=$(INCLUDE_MYRT_MATH)

BINARY_DIR:=build
BINARY_NAME:=myrt
BINARY_PATH:=$(BINARY_DIR)/$(BINARY_NAME)

SRC:=src/main.cpp

all: build

CFLAGS:=-std=c++1z -O3 -Weffc++ -Wc++1z-extensions
OUTPUT:=-o $(BINARY_PATH)

.PHONY: build
build:
	mkdir -p $(BINARY_DIR)
	g++ $(CFLAGS) $(INCLUDE) $(OUTPUT) $(SRC)

