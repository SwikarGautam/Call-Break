all: compile link

compile:
	g++ -Isrc/include -c main.cpp Menu.cpp

link:
	g++ main.o Menu.o -o sfml-app -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system