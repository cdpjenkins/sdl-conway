CXX=g++
CXXFLAGS=-arch arm64 -std=c++11 `sdl2-config --cflags | sed -e 's/include\/SDL2/include/'`
LDFLAGS=`sdl2-config --libs`

all: sdl-conway make-dist

clean:
	rm -rf dist
	rm -f src/*.o

make-dist:
	mkdir -p dist
	cp grids/*.cwy dist/
	cp sdl-conway dist/

src/%.o: src/%.cpp src/*.hpp
	${CXX} -c $(CXXFLAGS) $< -o $@

sdl-conway: src/main.o src/ConwayGrid.o src/Viewport.o src/*.hpp
	g++ $(LDFLAGS) $(CXXFLAGS) src/main.o src/ConwayGrid.o src/Viewport.o -o sdl-conway

