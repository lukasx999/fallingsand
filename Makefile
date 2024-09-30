all: main.cc canvas.cc
	g++ $^ -Wall -Wextra -std=c++20 -pedantic -ggdb -o out -lraylib
