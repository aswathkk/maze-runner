#Makefile for MazeRunner

CC = g++

LIBS = -framework OpenGL -framework GLUT -w

FILES = main.cpp camera.cpp maze.cpp human.cpp

OUTPUT = mazerunner

build: $(FILES)
	$(CC) $(FILES) $(LIBS) -o $(OUTPUT)
