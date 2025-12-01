
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node* prev;
    struct node* next;
    int value;
} node;

node* traverse(node* current, char dir, int distance, int* zero_count)
{
    for (int i = 0; i < distance; i++) {
        if (current->value == 0) {
            (*zero_count)++;
        }
        if (dir == 'L') {
            current = current->next;
        } else if (dir == 'R') {
            current = current->prev;
        }
    }
    return current;
}

node* create_doubly_circular_linked_list()
{
    node* head = NULL;
    node* tail = NULL;
    node* start = NULL;
    for (int i = 0; i <= 99; i++) {
        node* new_node = (node*)malloc(sizeof(node));
        new_node->value = i;
        if (head == NULL) {
            head = new_node;
            tail = new_node;
            new_node->next = new_node;
            new_node->prev = new_node;
        } else {
            tail->next = new_node;
            new_node->prev = tail;
            new_node->next = head;
            head->prev = new_node;
            tail = new_node;
            if (i == 50) {
                start = new_node;
            }
        }
    }
    return start;
}

int main()
{
    // populate doubly circular linked list

    FILE* file = fopen("data.txt", "r");

    char buffer[64];
    char dir;
    int distance;
    node* head = create_doubly_circular_linked_list();
    int result = 0;

    node* current = head;
    while (fgets(buffer, sizeof(buffer), file)) {
        dir = buffer[0];
        distance = atoi(&buffer[1]);
        current = traverse(current, dir, distance, &result);
    }

    printf("Result: %d\n", result);

    // free memory
    if (head != NULL) {
        node* current = head;
        do {
            node* next = current->next;
            free(current);
            current = next;
        } while (current != head);
    }
    return 0;
}
