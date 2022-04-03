CXX=g++
CXXFLAGS=-arch arm64 -std=c++11

SOURCES=src/*.cpp src/*.o

all: sdl-conway make-dist

clean:
	rm -rf dist
	rm -f src/*.o

make-dist:
	mkdir -p dist
	cp grids/*.cwy dist/
	cp sdl-conway dist/

%.o: %.cpp *.hpp
	${CXX} -c $(CXXFLAGS) $< -o $@

sdl-conway: src/main.o src/ConwayGrid.o
	g++ $(CXXFLAGS) src/main.o src/ConwayGrid.o -o sdl-conway -lSDL2

