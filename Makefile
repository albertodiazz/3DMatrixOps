CC = gcc -g
TARGET = app
# SRC = app.cpp
SRC = rasterization.cpp
LIBS = -lGL -lGLU -lglut -lm -lstdc++


all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(LIBS)
