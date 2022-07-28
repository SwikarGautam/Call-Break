all: compile link

compile:
g++ -Isrc/include -c main.cpp Menu.cpp Credits.cpp Cards.cpp Player.cpp Play.cpp

link:
g++ main.o Menu.o Credits.o Cards.o Player.o Play.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system