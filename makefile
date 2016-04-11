all: cubic fractal-color fractal-pointbased

cubic : cubic.c
	gcc cubic.c -o cubic -lglut -lGL -lGLU -lm -lGLEW

fractal-pointbased : fractal-pointbased.cpp
	g++ fractal-pointbased.cpp -o fractal-pointbased -lglut -lGLU -lGL -lm -std=c++11

fractal-color : triangle.cpp
	g++ triangle.cpp -o fractal-color -lglut -lGL -lGLU -lGLEW 
