#ifndef GRID_H
#define GRID_H

#define ROWS 256
#define COLS 256

typedef struct Grid {
    char** data;
    unsigned long rows;
    unsigned long cols;
} Grid;

Grid* read_grid(const char* filename);
void free_grid(Grid* grid);
void print_grid(Grid* grid);

#endif
