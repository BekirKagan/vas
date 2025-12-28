#include <stdio.h>

#define VAS_ARRAY_IMPLEMENTATION
#include "vas_array.h"

int main() {
    // Initialize the array for 'int' types
    VAS_Array list;
    vas_array_init(&list, sizeof(int));

    // Append data
    int value = 100;
    vas_array_append(&list, &value);

    // Access data
    int* retrieved = (int*)vas_array_get(&list, 0);
    if (retrieved) {
        printf("Value: %d\n", *retrieved);
    }

    // Clean up
    vas_array_deinit(&list);
    return 0;
}
