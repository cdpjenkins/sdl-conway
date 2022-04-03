#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ConwayGrid.hpp"

#define MAX_LINE_LENGTH 1000

ConwayGrid::ConwayGrid() {
    init_to_blank();
}

void ConwayGrid::init_to_blank() {
    current_grid = grid1;
    next_grid = grid2;
    width = GRID_WIDTH;
    height = GRID_HEIGHT;
    cell_width = CELL_WIDTH;
    cell_height = CELL_HEIGHT;
    running = false;

    memset(this->grid1, 0, sizeof(grid1));
    memset(this->grid2, 0, sizeof(grid2));
}

void ConwayGrid::load_from_file(const char* filename) {
    FILE *fp;
    char row_string[MAX_LINE_LENGTH];

    init_to_blank();

    fp = fopen(filename, "r");
    if (!fp) {
        printf("Failed to open %s\n", filename);
        exit(1);
    }

    for (int y = 0; fgets(row_string, MAX_LINE_LENGTH, fp) != NULL && y < height; y++) {
        int x;
        char* ptr;

        for (ptr = row_string, x = 0; ptr != NULL && x < width; ptr++, x++) {
            set_cell(current_grid, x, y, *ptr == 'x');
        }
    }

    fclose(fp);
}

void ConwayGrid::save_to_file(const char* filename) {
    FILE *fp;
    int x, y;

    fp = fopen(filename, "w");
    if (!fp) {
        printf("Failed to open %s for writing\n", filename);
        perror("arghghghgh");
        exit(1);
    }

    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            if (cell_alive_at(x, y)) {
                fprintf(fp, "x");
            } else {
                fprintf(fp, ".");
            }
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}

void ConwayGrid::print() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (cell_alive_at(x, y)) {
                printf("x");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int ConwayGrid::num_living_neighbours(int x, int y) {
    int a1 = cell_alive_at(x-1, y-1) ? 1 : 0;
    int a2 = cell_alive_at(x, y-1) ? 1 : 0;
    int a3 = cell_alive_at(x+1, y-1) ? 1 : 0;
    int a4 = cell_alive_at(x-1, y) ? 1 : 0;
    int a5 = cell_alive_at(x+1, y) ? 1 : 0;
    int a6 = cell_alive_at(x-1, y+1) ? 1 : 0;
    int a7 = cell_alive_at(x, y+1) ? 1 : 0;
    int a8 = cell_alive_at(x+1, y+1) ? 1 : 0;

    return a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8;
}

void ConwayGrid::step() {
    if (running) {
        for (int x = 1; x < width - 1; x++) {
            for (int y = 1; y < height - 1; y++) {
                bool new_value;
                int live_neighbours;
                
                live_neighbours = num_living_neighbours(x, y);
                if (cell_alive_at(x, y)) {
                    new_value = live_neighbours == 2 || live_neighbours == 3;
                } else {
                    new_value = live_neighbours == 3;
                }

                next_grid[grid_index(x, y)] = new_value;
            }
        }

        bool *temp_grid_ptr = next_grid;
        next_grid = current_grid;
        current_grid = temp_grid_ptr;

        generation++;
    }
}

void ConwayGrid::run() {
    running = true;
}

void ConwayGrid::pause() {
    running = false;
}

void ConwayGrid::screen_coords_to_grid_coords(int x, int y, int *grid_x, int *grid_y) {
    *grid_x = x / cell_width;
    *grid_y = y / cell_height;
}

void ConwayGrid::invert_cell(int grid_x, int grid_y) {
    if (!running) {
        bool cell_value = current_grid[grid_index(grid_x, grid_y)];
        current_grid[grid_index(grid_x, grid_y)] = !cell_value;
    }
}
