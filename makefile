all: cubic fractal-color fractal-pointbased

cubic : cubic.c
	gcc -lglut -lGL -lGLU -lGLEW cubic.c -o cubic

fractal-pointbased : fractal-pointbased.cpp
	g++ fractal-pointbased.cpp -o fractal-pointbased -lglut -lGLU -lGL -lm -std=c++11

fractal-color : triangle.cpp
	g++ -lglut -lGL -lGLU -lGLEW triangle.cpp -o fractal-color
