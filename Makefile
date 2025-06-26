CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -O2 -lm
CXXFLAGS = -Wall -Wextra -O2 `pkg-config --cflags Qt5Widgets`
LDFLAGS = `pkg-config --libs Qt5Widgets` -lm

SRC_C = src/pythagoras_tree.c
SRC_CPP = src/main.cpp
OBJ_C = $(SRC_C:.c=.o)
OBJ_CPP = $(SRC_CPP:.cpp=.o)
TARGET = src/pythagoras_tree

all: $(TARGET)

$(TARGET): $(OBJ_C) $(OBJ_CPP)
	$(CXX) $(OBJ_C) $(OBJ_CPP) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_C) $(OBJ_CPP) $(TARGET)

.PHONY: all clean
