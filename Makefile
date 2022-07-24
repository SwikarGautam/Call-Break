all: compile link

compile:
	g++ -Isrc/include -c main.cpp Menu.cpp Credits.cpp

link:
	g++ main.o Menu.o Credits.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system