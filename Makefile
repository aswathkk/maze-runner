#Makefile for MazeRunner

CC = g++

LIBS = -framework OpenGL -framework GLUT -w

FILES = main.cpp camera.cpp maze.cpp human.cpp

OUTPUT = a.out

build: $(FILES)
	$(CC) $(FILES) $(LIBS) -o $(OUTPUT)

detect: $(FILES)
	$(CC) detect.cpp camera.cpp $(LIBS) -o $(OUTPUT)