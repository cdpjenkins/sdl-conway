#ifndef CONWAY_GRID_H
#define CONWAY_GRID_H

#define GRID_WIDTH 160
#define GRID_HEIGHT 120
#define CELL_WIDTH 4
#define CELL_HEIGHT 4

#define MAX_LINE_LENGTH 1000

class ConwayGrid {
public:
    int width = GRID_WIDTH;
    int height = GRID_HEIGHT;
    int cell_width;
    int cell_height;
    bool running;
    int generation = 0;

    ConwayGrid();
    void init_to_blank();
    void load_from_file(const char* filename);
    void save_to_file(const char* filename);
    void print();
    void step();
    void run();
    void pause();
    void screen_coords_to_grid_coords(int x, int y, int *grid_x, int *grid_y);
    void invert_cell(int grid_x, int grid_y);

    inline bool cell_alive_at(int x, int y) {
        return current_grid[grid_index(x, y)];
    }

private:
    bool grid1[GRID_WIDTH * GRID_HEIGHT];
    bool grid2[GRID_WIDTH * GRID_HEIGHT];
    bool* current_grid;
    bool* next_grid;

    int num_living_neighbours(int x, int y);

    inline void set_cell(bool* grid, int x, int y, bool value) {
        current_grid[grid_index(x, y)] = value;
    }

    inline int grid_index(int column, int row) {
        return row * width + column;
    }
};

#endif // CONWAY_GRID_H
