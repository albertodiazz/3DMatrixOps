CC = gcc
TARGET = app
SRC = app.cpp
LIBS = -lGL -lGLU -lglut -lm

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(LIBS)
