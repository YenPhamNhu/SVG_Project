all:
	g++ -I src/include -L src/lib main.cpp -o main.exe  -lmingw32 -lSDL2main -lSDL2