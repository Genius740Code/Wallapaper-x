CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
DEBUG_FLAGS = -g
RELEASE_FLAGS = -O2

# SFML paths
SFML_INCLUDE = -I./code/include
SFML_LIB_DIR = -L./code/lib
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Directories
SRC_DIR = src
BUILD_DIR = build

# Files
SRC = $(SRC_DIR)/main.cpp
OBJ = $(BUILD_DIR)/main.o
EXECUTABLE = $(BUILD_DIR)/sfml_window

all: $(BUILD_DIR) $(EXECUTABLE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(EXECUTABLE): $(OBJ)
	$(CXX) $(CXXFLAGS) $(RELEASE_FLAGS) $(SFML_LIB_DIR) -o $@ $^ $(SFML_LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(RELEASE_FLAGS) $(SFML_INCLUDE) -c $< -o $@

debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: all

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all debug clean 