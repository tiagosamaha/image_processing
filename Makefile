CC = g++

all: compile

compile:
	$(CC) src/main.cpp `pkg-config --cflags --libs opencv`
