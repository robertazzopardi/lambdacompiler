# gcc
CC		:= g++
# CC		:= gcc
CFLAGS	:= -std=c++20 -Wall -Wextra -g

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:=

ifeq ($(OS),Windows_NT)
EXECUTABLE	:= main.exe
SOURCEDIRS	:= $(SRC)
INCLUDEDIRS	:= $(INCLUDE)
LIBDIRS		:= $(LIB)
else
EXECUTABLE	:= main
SOURCEDIRS	:= $(shell find $(SRC) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)
LIBDIRS		:= $(shell find $(LIB) -type d)
endif

CINCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))
CLIBS		:= $(patsubst %,-L%, $(LIBDIRS:%/=%))

SOURCES		:= $(wildcard $(patsubst %,%/*.cpp, $(SOURCEDIRS)))
OBJECTS		:= $(SOURCES:.cpp=.o)

all: $(BIN)/$(EXECUTABLE)

.PHONY: clean
clean:
	-$(RM) $(BIN)/$(EXECUTABLE)
	-$(RM) $(OBJECTS)

run: all
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(CINCLUDES) $(CLIBS) $^ -o $@ $(LIBRARIES)



# CREATE ASSEMBLY FILE AND OUTPUT FILE, LINK, AND RUN
# nasm assembly.asm -f elf64 -o assembly.o && gcc -no-pie -Wall -Wextra -Werror -o assembly assembly.o && ./assembly

# CREATE ASSEMBLY FILE AND OUTPUT FILE, LINK, REMOVE OUTPUT FILE, AND RUN
# nasm assembly.asm -f elf64 -o assembly.o && gcc -no-pie -Wall -Wextra -Werror -o assembly assembly.o && rm ./assembly.o && ./assembly