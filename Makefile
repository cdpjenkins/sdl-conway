CXX=g++
CXXFLAGS=-arch arm64 -std=c++11

SOURCES=*.cpp *.o

%.o: %.cpp *.hpp
	${CXX} -c $(CXXFLAGS) $< -o $@

sdl-conway: main.o ConwayGrid.o
	g++ $(CXXFLAGS) main.o ConwayGrid.o -o sdl-conway -lSDL2

