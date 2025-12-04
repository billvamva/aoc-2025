#include "grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned concatenate(unsigned x, unsigned y)
{
    unsigned pow = 10;
    while (y >= pow)
        pow *= 10;
    return x * pow + y;
}

int get_highest_available_by_index(char* row, unsigned long start, unsigned long end)
{
    unsigned highest_index = start;
    for (unsigned long i = start; i < end; i++) {
        if (row[i] - '0' > row[highest_index] - '0') {
            highest_index = i;
        }
    }
    return highest_index;
}

void process_row_part_1(char* row, unsigned* running_total)
{
    unsigned long l = 0;
    unsigned long r = strlen(row) - 1;
    for (unsigned long i = 0; i < strlen(row) - 1; i++) {
        if (row[i] - '0' > row[l] - '0') {
            l = i;
        }
    }

    for (unsigned long i = strlen(row) - 1; i > l; i--) {
        if (row[i] - '0' > row[r] - '0') {
            r = i;
        }
    }

    unsigned current_num = concatenate(row[l] - '0', row[r] - '0');
    *running_total += current_num;
}

void print_array(unsigned long* arr, unsigned long len)
{
    for (unsigned long i = 0; i < len; i++) {
        printf("%ld", arr[i]);
    }
    printf("\n");
}

unsigned long combine(const unsigned long* a, int n)
{
    unsigned long result = 0;
    for (int i = 0; i < n; i++) {
        result = result * 10UL + a[i];
    }
    return result;
}

void process_row_part_2(char* row, unsigned long* running_total)
{
    unsigned long nums[12];
    int current_index = 0;

    for (unsigned long i = 0; i < 12; i++) {
        current_index = get_highest_available_by_index(row, current_index, strlen(row) - (12 - i - 1));
        nums[i] = row[current_index] - '0';
        current_index++;
    }

    unsigned long result = combine(nums, 12);
    printf("Result: %ld\n", result);
    *running_total += result;
}

int main()
{
    Grid* grid = read_grid("data.txt");

    unsigned long running_total = 0;
    for (unsigned long i = 0; i < grid->rows; i++) {
        process_row_part_2(grid->data[i], &running_total);
    }
    printf("Total: %ld\n", running_total);
}
