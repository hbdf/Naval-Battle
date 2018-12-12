board.o: board.hpp board.cpp
	g++ --std=c++0x board.cpp -c

cell_representation.o: cell_representation.hpp cell_representation.cpp
	g++ cell_representation.cpp -c --std=c++0x

cube.o: cube.hpp cube.cpp
	g++ cube.cpp -c -std=c++0x

object.o: object.hpp object.cpp
	g++ object.cpp -c -std=c++0x

ship.o: ship.hpp ship.cpp
	g++ ship.cpp -c -std=c++0x

sphere.o: sphere.hpp sphere.cpp
	g++ sphere.cpp -c -std=c++0x

main.o: main.cpp
	g++ main.cpp -c -std=c++0x

main: board.o cell_representation.o cube.o object.o ship.o sphere.o main.o
	g++  -std=c++0x main.cpp board.o cell_representation.o cube.o object.o ship.o sphere.o -o main -lGL -lGLU -lglut -lpthread -pthread