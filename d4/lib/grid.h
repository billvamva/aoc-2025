#ifndef GRID_H
#define GRID_H

#define ROWS 512
#define COLS 512

typedef struct Grid {
    char** data;
    long rows;
    long cols;
} Grid;

Grid* read_grid(const char* filename);
void free_grid(Grid* grid);
void print_grid(Grid* grid);

#endif
