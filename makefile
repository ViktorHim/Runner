CC = g++

SRC_DIR = ./src/
OBJ_DIR = ./obj/
BUILD_DIR = ./build/

SRCS = $(wildcard $(SRC_DIR)*.cpp)
OBJS = $(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)%.o, $(SRCS))

all: build

build: $(OBJS)
	$(CC) $(OBJS) -o $(BUILD_DIR)app.exe -Llib -lSDL2 -lSDL2main

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(CC) -c $< -o $@ -Iinclude
	
run:
	$(BUILD_DIR)app.exe
clean:
	del /Q $(OBJ_DIR)*
	del /Q $(BUILD_DIR)*
.PHONY: compile clean build