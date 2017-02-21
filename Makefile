OBJ = *.cpp

CFLAGS = -ansi -Wall -g -O0 -pedantic -lSDL2_image `pkg-config --cflags --libs sdl2 ` -std=c++11

all: test

test: $(OBJ)
		g++ $(OBJ) -o scarybird $(CFLAGS)
win_x86_64: 
	/opt/mingw/bin/x86_64-w64-mingw32-g++ $(OBJ) -o WinExecutable/scarybird.exe ./scarybird.o -LSDL2-2.0.4/lib/x64 -lSDL2main -lSDL2 $(CFLAGS)