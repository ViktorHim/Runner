CC = g++

SRC_DIR = ./src/
OBJ_DIR = ./obj/
BUILD_DIR = ./build/

SRCS = $(wildcard $(SRC_DIR)*.cpp)
OBJS = $(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)%.o, $(SRCS))

all: build run

build: $(OBJS)
	$(CC) $(OBJS) -o $(BUILD_DIR)app.exe -Llib -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_image

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(CC) -c $< -o $@ -Iinclude

run:
	$(BUILD_DIR)app.exe
clean:
	del /Q .\obj\*.o
	del /Q .\build\app.exe

.PHONY: compile clean build