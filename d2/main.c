#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int validate_pt_1(char* id_str, long i)
{
    char comp[256];
    char halfway_str[256];
    snprintf(id_str, 256, "%ld", i);
    if (strlen(id_str) % 2 != 0) {
        return 1;
    }
    memcpy(halfway_str, id_str, strlen(id_str) / 2);
    halfway_str[strlen(id_str) / 2] = '\0';
    snprintf(comp, 256, "%s%s", halfway_str, halfway_str);
    if (strcmp(id_str, comp) == 0) {
        return 0;
    }
    return 1;
}

char* get_first_n_chars(char* str, int n)
{
    static char buffer[256];
    strncpy(buffer, str, n);
    buffer[n] = '\0';
    return buffer;
}

char* repeat_str_n_times(char* str, int n)
{
    static char buffer[256];
    buffer[0] = '\0';
    for (int i = 0; i < n; i++) {
        strcat(buffer, str);
    }
    return buffer;
}

int validate_pt_2(char* id_str, long i)
{
    char* comp;
    char* part_str;
    snprintf(id_str, 256, "%ld", i);
    for (unsigned long part = 0; part < strlen(id_str) / 2; part++) {
        if (strlen(id_str) % (part + 1) != 0) {
            continue;
        }
        part_str = get_first_n_chars(id_str, part + 1);
        comp = repeat_str_n_times(part_str, strlen(id_str) / (part + 1));

        if (strcmp(id_str, comp) == 0) {
            return 0;
        }
    }
    return 1;
}

void find_invalid_ids(long start, long end, unsigned long* running_total)
{
    char* id_str = malloc(512);
    for (long i = start; i <= end; i++) {
        if (!validate_pt_2(id_str, i)) {
            *running_total += i;
        }
    }
    free(id_str);
}

int main()
{

    char* fileName = "data.txt";
    FILE* file = fopen(fileName, "r");

    char line[256];
    char* token;
    long start, end = 0;
    unsigned long running_total = 0;

    while (fgets(line, sizeof(line), file)) {
        token = strtok(line, ",");
        while (token != NULL) {
            parse_range(token, &start, &end);
            printf("Processing range: %ld - %ld\n", start, end);
            find_invalid_ids(start, end, &running_total);
            token = strtok(NULL, ",");
        }
    }
    printf("Total of invalid IDs: %lu\n", running_total);
}
