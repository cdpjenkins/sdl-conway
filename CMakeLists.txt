cmake_minimum_required(VERSION 3.18)
project(sdl-conway)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set (CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(sdl-conway
    src/ConwayGrid.cpp
    src/Viewport.cpp
    src/main.cpp
)

target_link_libraries(sdl-conway ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

file(GLOB GRIDS ${PROJECT_SOURCE_DIR}/grids/*.cwy)
file(
    COPY ${GRIDS}
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB INSTALLABLE_GRIDS ${CMAKE_CURRENT_BINARY_DIR}/*.cwy)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist)
install(
    FILES ${INSTALLABLE_GRIDS} sdl-conway
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/dist
)
