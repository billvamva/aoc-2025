#include "grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Grid* read_grid(const char* filename)
{
    unsigned long capacity = 16;
    char** data = malloc(capacity * sizeof(char*));
    char* line = malloc(COLS);

    FILE* file = fopen(filename, "r");
    if (!file)
        return NULL;

    unsigned long rows = 0;
    unsigned long cols = 0;

    while (fgets(line, COLS, file)) {

        size_t len = strlen(line);

        // strip newline
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
        }

        // grow row storage
        if (rows == capacity) {
            capacity *= 2;
            data = realloc(data, capacity * sizeof(char*));
        }

        // store line
        data[rows] = malloc(len + 1);
        memcpy(data[rows], line, len + 1);

        // track max column length
        if (len > cols)
            cols = len;

        rows++;
    }

    fclose(file);
    free(line);

    Grid* grid = malloc(sizeof(Grid));
    grid->data = data;
    grid->rows = rows;
    grid->cols = cols;

    return grid;
}

void free_grid(Grid* grid)
{
    for (unsigned long i = 0; i < grid->rows; i++) {
        free(grid->data[i]);
    }
    free(grid->data);
    free(grid);
}

void print_grid(Grid* grid)
{
    for (unsigned long i = 0; i < grid->rows; i++) {
        printf("%s\n", grid->data[i]);
    }
}
