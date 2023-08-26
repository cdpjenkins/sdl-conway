#ifndef CONWAY_GRID_H
#define CONWAY_GRID_H

#include <array>
#include <string>
using namespace std;
#include <cstring>

template<int GRID_WIDTH, int GRID_HEIGHT>
class ConwayGrid {
public:
    static constexpr int width = GRID_WIDTH;
    static constexpr int height = GRID_HEIGHT;
    bool running;

    ConwayGrid() :
            running(false),
            cell_array(){

        init_to_blank();
    }

    void init_to_blank() {
        running = false;

        cell_array.fill(0x00);

        for (int x = 0; x < width; x++) {
            cell_array[grid_index(x, 0)] = 0x20;
            cell_array[grid_index(x, height - 1)] = 0x20;
        }

        for (int y = 0; y < height; y++) {
            cell_array[grid_index(0, y)] = 0x20;
            cell_array[grid_index(width - 1 , y)] = 0x20;
        }
    }

    void load_from_file(const char* filename) {
        constexpr int MAX_LINE_LENGTH = 1000;

        FILE *fp;
        char row_string[MAX_LINE_LENGTH];
        memset(row_string, 0, sizeof(row_string));

        init_to_blank();

        fp = fopen(filename, "r");
        if (!fp) {
            printf("Failed to open %s\n", filename);
            exit(1);
        }

        for (int y = 0; fgets(row_string, MAX_LINE_LENGTH, fp) != nullptr && y < height; y++) {
            int x;
            char* ptr;

            for (ptr = row_string, x = 0; ptr != nullptr && x < width; ptr++, x++) {
                if (*ptr == 'x') {
                    transition_cell_from_dead_to_alive(x, y);
                }
            }
        }

        fclose(fp);
    }

    void save_to_file(const char* filename) {
        FILE *fp;
        int x, y;

        fp = fopen(filename, "w");
        if (!fp) {
            fprintf(stderr, "Failed to open %s for writing\n", filename);
            perror("Error");
            goto close_file;
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
close_file:
        fclose(fp);
    }

    void print() {
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

    void step() {
        if (running) {

            CellArray cell_array_copy;
            memcpy(&cell_array_copy, &cell_array, sizeof(cell_array));

            for (int index = 0; index < width*height; index += 4) {
                uint32_t* long_word_ptr = reinterpret_cast<uint32_t*>(&cell_array_copy[index]);
                if (*long_word_ptr) {
                    for (int i = 0; i < 4; i++) {
                        uint8_t &current_value = cell_array_copy[index + i];
                        if (current_value != 0) {
                            if (current_value == 0x03) {
                                transition_cell_from_dead_to_alive(index + i);
                            } else if ((current_value & 0x10) && (current_value != 0x12) && (current_value != 0x13)) {
                                transition_cell_from_alive_to_dead(index + i);
                            }
                        }
                    }
                }
            }
        }
    }

    void run() {
        running = true;
    }

    void pause() {
        running = false;
    }

    void screen_coords_to_grid_coords(int x, int y, int cell_size, int &out_grid_x, int &out_grid_y) const {
        out_grid_x = x / cell_size;
        out_grid_y = y / cell_size;
    }

    void invert_cell(int grid_x, int grid_y) {
        if (!running) {
            if (cell_alive_at(grid_x, grid_y)) {
                transition_cell_from_alive_to_dead(grid_x, grid_y);
            } else {
                transition_cell_from_dead_to_alive(grid_x, grid_y);
            }
        }
    }

    inline bool cell_alive_at(int x, int y) {
        return cell_array[grid_index(x, y)] & 0x10;
    }

    inline bool cell_is_buffer(int x, int y) {
        return cell_array[grid_index(x, y)] & 0x20;
    }

private:
    typedef array<uint8_t, GRID_WIDTH * GRID_HEIGHT> CellArray;

    CellArray cell_array;

    inline void transition_cell_from_dead_to_alive(int index) {
        cell_array[index] |= 0x10;

        cell_array[index - GRID_WIDTH - 1]++;
        cell_array[index - GRID_WIDTH]++;
        cell_array[index - GRID_WIDTH + 1]++;
        cell_array[index - 1]++;
        cell_array[index + 1]++;
        cell_array[index + GRID_WIDTH - 1]++;
        cell_array[index + GRID_WIDTH]++;
        cell_array[index + GRID_WIDTH + 1]++;
    }

    inline void transition_cell_from_dead_to_alive(int x, int y) {
        transition_cell_from_dead_to_alive(grid_index(x, y));
    }

    inline void transition_cell_from_alive_to_dead(int index) {
        cell_array[index] = cell_array[index] & (~0x10);

        cell_array[index - GRID_WIDTH - 1]--;
        cell_array[index - GRID_WIDTH]--;
        cell_array[index - GRID_WIDTH + 1]--;
        cell_array[index - 1]--;
        cell_array[index + 1]--;
        cell_array[index + GRID_WIDTH - 1]--;
        cell_array[index + GRID_WIDTH]--;
        cell_array[index + GRID_WIDTH + 1]--;
    }

    inline void transition_cell_from_alive_to_dead(int x, int y) {
        transition_cell_from_alive_to_dead(grid_index(x, y));
    }

    static inline int grid_index(int column, int row) {
        return row * width + column;
    }
};

#endif // CONWAY_GRID_H
