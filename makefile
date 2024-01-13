CC = g++

SRC_DIR = ./src/
OBJ_DIR = ./obj/
BUILD_DIR = ./build/

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

compile:
	$(CC) -Iinclude -c $(SRCS) -o $(OBJS)
build:
	$(CC) $(OBJS) -o $(BUILD_DIR)/app.exe -Llib -lSDL2
run:
	$(BUILD_DIR)/app.exe
clean:
	rm -rf $(OBJ_DIR)
.PHONY: compile clean