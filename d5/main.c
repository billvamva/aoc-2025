#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    long start;
    long end;
} range;

void parse_range(char* range_str, long* start, long* end)
{
    char* dash_pos = strchr(range_str, '-');
    if (dash_pos != NULL) {
        *dash_pos = '\0';
        *start = atol(range_str);
        *end = atol(dash_pos + 1);
    } else {
        *start = atol(range_str);
        *end = *start;
    }
}

int validate_input(long start, long end)
{
    if (start < 0 || end < 0 || start > end) {
        return 0; // invalid
    }
    return 1; // valid
}

int is_in_ranges(range* r, long ranges_length, long value)
{
    for (long i = 0; i < ranges_length; i++) {
        printf("Checking %ld against range %ld-%ld\n", value, r[i].start, r[i].end);
        if (value >= r[i].start && value <= r[i].end) {
            return 1; // found
        }
    }
    return 0;
}

void add_to_ranges(range** ranges_ptr, long* range_length, long start, long end)
{
    // merge or add new range in sorted order
    range* ranges = *ranges_ptr;
    for (long i = 0; i < *range_length; i++) {
        if (end < ranges[i].start - 1) {
            // insert before
            memmove(&ranges[i + 1], &ranges[i], (*range_length - i) * sizeof(range));
            ranges[i].start = start;
            ranges[i].end = end;
            (*range_length)++;
            return;
        } else if (start > ranges[i].end + 1) {
            continue; // check next
        } else {
            // overlap, merge
            if (start < ranges[i].start) {
                ranges[i].start = start;
            }
            if (end > ranges[i].end) {
                ranges[i].end = end;
            }
            // merge with subsequent ranges if necessary
            long j = i + 1;
            while (j < *range_length && ranges[j].start <= ranges[i].end + 1) {
                if (ranges[j].end > ranges[i].end) {
                    ranges[i].end = ranges[j].end;
                }
                j++;
            }
            // shift remaining ranges
            memmove(&ranges[i + 1], &ranges[j], (*range_length - j) * sizeof(range));
            *range_length -= (j - i - 1);
            return;
        }
    }
    ranges[*range_length].start = start;
    ranges[*range_length].end = end;
    (*range_length)++;
}

long get_num_values_in_range(range* r)
{
    return r->end - r->start + 1;
}

void print_ranges(range* ranges, long range_length)
{
    for (long i = 0; i < range_length; i++) {
        printf("%ld-%ld\n", ranges[i].start, ranges[i].end);
    }
}

int main()
{
    FILE* file = fopen("data.txt", "r");

    char line[256];
    long start, end = 0;

    range* ranges = malloc(1000 * sizeof(range));
    long range_length = 0;
    long current_value;
    long result = 0;

    // get ranges
    while (fgets(line, sizeof(line), file)) {
        if (strcmp(line, "\n") == 0) {
            break;
        } else if (strchr(line, '-')) {
            parse_range(line, &start, &end);
            add_to_ranges(&ranges, &range_length, start, end);
        } else {
            // current_value = atol(line);
            // if (is_in_ranges(ranges, range_length, current_value)) {
            //     continue;
            // }
        }
    }
    for (long i = 0; i < range_length; i++) {
        result += get_num_values_in_range(&ranges[i]);
    }
    printf("Result: %ld\n", result);
}
