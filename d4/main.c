#include "grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int result = 0;

int directions[8][2] = {
    { 1, 0 }, // right
    { -1, 0 }, // left
    { 0, 1 }, // down
    { 0, -1 }, // up
    { 1, 1 }, // down-right
    { -1, -1 }, // up-left
    { 1, -1 }, // up-right
    { -1, 1 } // down-left
};

int get_surrounding_cells(Grid* grid, int row, int col)
{

    int count = 0;
    for (unsigned long i = 0; i < sizeof(directions) / sizeof(directions[0]); i++) {
        long new_col = col + directions[i][0];
        long new_row = row + directions[i][1];

        if (new_row < 0 || new_row >= grid->rows || new_col < 0 || new_col >= grid->cols) {
            continue;
        }
        if (grid->data[new_row][new_col] != '@') {
            continue;
        }
        count++;
        if (count == 4) {
            return 0;
        }
    }
    grid->data[row][col] = 'X';
    return 1;
}

void evaluate_neighbors(Grid* grid, int row, int col)
{
    for (unsigned long i = 0; i < sizeof(directions) / sizeof(directions[0]); i++) {
        long new_col = col + directions[i][0];
        long new_row = row + directions[i][1];
        if (new_row < 0 || new_row >= grid->rows || new_col < 0 || new_col >= grid->cols) {
            continue;
        }
        if (grid->data[new_row][new_col] != '@') {
            continue;
        }
        if (get_surrounding_cells(grid, new_row, new_col)) {
            result++;
            evaluate_neighbors(grid, new_row, new_col);
        }
    }
}

void traverse_grid_spiral(Grid* grid, char** visited)
{
    int dr[4] = { 0, 1, 0, -1 }; // right, down, left, up
    int dc[4] = { 1, 0, -1, 0 };

    long r = 0, c = 0, dir = 0;

    for (long step = 0; step < grid->rows * grid->cols; step++) {

        visited[r][c] = '1'; // mark AFTER arriving

        long new_r = r + dr[dir];
        long new_c = c + dc[dir];

        // If blocked, rotate direction
        if (new_r < 0 || new_r >= grid->rows || new_c < 0 || new_c >= grid->cols || visited[new_r][new_c] == '1') {

            dir = (dir + 1) % 4;
            new_r = r + dr[dir];
            new_c = c + dc[dir];
        }

        // If still invalid, traversal is finished
        if (new_r < 0 || new_r >= grid->rows || new_c < 0 || new_c >= grid->cols)
            break;

        r = new_r;
        c = new_c;

        // Process cell
        if (grid->data[r][c] == '@') {
            if (get_surrounding_cells(grid, r, c)) {
                result++;
                evaluate_neighbors(grid, r, c);
            }
        }
    }
}

char** create_zero_grid(int rows, int cols)
{
    char** grid = (char**)malloc(rows * sizeof(char*));
    for (int i = 0; i < rows; i++) {
        grid[i] = (char*)malloc(cols * sizeof(char));
        memset(grid[i], '0', cols * sizeof(char));
    }
    return grid;
}

void free_zero_grid(char** grid, int rows)
{
    for (int i = 0; i < rows; i++) {
        free(grid[i]);
    }
    free(grid);
}

int main()
{
    Grid* grid = read_grid("data.txt");
    char** visited = create_zero_grid(grid->rows, grid->cols);
    traverse_grid_spiral(grid, visited);
    printf("Result: %d\n", result);
}
