all:
	g++ -I src/include -I src/util -L src/lib -o main main.cpp src/util/vector2.cpp -lSDL2main -lSDL2 -lSDL2_ttf