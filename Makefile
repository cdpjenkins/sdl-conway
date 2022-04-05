CXX=g++
CXXFLAGS=-arch arm64 -std=c++11 `sdl2-config --cflags | sed -e 's/include\/SDL2/include/'`
LDFLAGS=`sdl2-config --libs`

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
	g++ $(LDFLAGS) $(CXXFLAGS) src/main.o src/ConwayGrid.o -o sdl-conway

