all:
	# g++ -Isrc/Include -Lsrc/lib -o main main.cpp RectShape.cpp Circle.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_gfx
	g++ -Isrc/Include -Lsrc/lib -o main main.cpp RectShape.cpp -lmingw32 -lSDL2main -lSDL2
