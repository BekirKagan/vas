#pragma once

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifndef VASADEF
#ifdef VAS_ARRAY_STATIC
#define VASADEF static
#else
#define VASADEF extern
#endif // VAS_ARRAY_STATIC
#endif // !VASADEF

typedef struct VAS_Array {
    void* items;
    size_t isize;
    size_t count;
    size_t capacity;
} VAS_Array;

VASADEF void vas_array_init(VAS_Array* array, size_t item_size);
VASADEF void vas_array_deinit(VAS_Array* array);
VASADEF bool vas_array_append(VAS_Array* array, const void* item);
VASADEF bool vas_array_insert(VAS_Array* array, const void* item, size_t index);
VASADEF bool vas_array_remove(VAS_Array* array, size_t index);
VASADEF void vas_array_clear(VAS_Array* array);
VASADEF void* vas_array_get(VAS_Array* array, size_t index);

#ifdef __cplusplus
}
#endif // __cplusplus

#ifdef VAS_ARRAY_IMPLEMENTATION

#ifndef VASA_ASSERT
#include <assert.h>
#define VASA_ASSERT(x) assert(x)
#endif // !VASA_ASSERT

#ifndef VASA_MALLOC
#include <stdlib.h>
#include <string.h>
#define VASA_MALLOC(size) malloc(size)
#define VASA_REALLOC(block, size) realloc(block, size)
#define VASA_FREE(block) free(block)
#define VASA_MEMCPY(dst, src, size) memcpy(dst, src, size)
#define VASA_MEMMOVE(dst, src, size) memmove(dst, src, size)
#endif // !VASA_MALLOC

#define VAS_ARRAY_INITIAL_CAPACITY 1
#define VAS_ARRAY_MAXIMUM_CAPACITY 4096

VASADEF void vas_array_init(VAS_Array* array, size_t item_size) {
    VASA_ASSERT(array != NULL);
    VASA_ASSERT(item_size > 0);
    array->isize = item_size;
    array->count = 0;
    array->capacity = VAS_ARRAY_INITIAL_CAPACITY;
    array->items = VASA_MALLOC(item_size * VAS_ARRAY_INITIAL_CAPACITY);
    VASA_ASSERT(array->items != NULL);
}

VASADEF void vas_array_deinit(VAS_Array* array) {
    if (array == NULL) {
        return;
    }
    VASA_FREE(array->items);
    array->items = NULL;
    array->isize = 0;
    array->count = 0;
    array->capacity = 0;
}

static bool vas_array_grow(VAS_Array* array) {
    if (array->count < array->capacity) {
        return true;
    }
    size_t new_capacity = array->capacity * 2;
    if (new_capacity > VAS_ARRAY_MAXIMUM_CAPACITY) {
        return false;
    }
    void* new_items = VASA_REALLOC(array->items, array->isize * new_capacity);
    if (new_items == NULL) {
        return false;
    }
    array->capacity = new_capacity;
    array->items = new_items;
    return true;
}

VASADEF bool vas_array_append(VAS_Array* array, const void* item) {
    VASA_ASSERT(array != NULL);
    VASA_ASSERT(item != NULL);
    if (!vas_array_grow(array)) {
        return false;
    }
    VASA_MEMCPY((char*)array->items + array->isize * array->count, item, array->isize);
    array->count++;
    return true;
}

VASADEF bool vas_array_insert(VAS_Array* array, const void* item, size_t index) {
    VASA_ASSERT(array != NULL);
    VASA_ASSERT(item != NULL);
    VASA_ASSERT(index <= array->count);
    if (!vas_array_grow(array)) {
        return false;
    }
    VASA_MEMMOVE((char*)array->items + (array->isize * (index + 1)),
                 (char*)array->items + (array->isize * index),
                 array->isize * (array->count - index));
    VASA_MEMCPY((char*)array->items + (array->isize * index), item, array->isize);
    array->count++;
    return true;
}

VASADEF bool vas_array_remove(VAS_Array* array, size_t index) {
    VASA_ASSERT(array != NULL);
    VASA_ASSERT(index < array->count);
    VASA_MEMMOVE((char*)array->items + (array->isize * index),
                 (char*)array->items + (array->isize * (index + 1)),
                 array->isize * (array->count - index - 1));
    array->count--;
    return true;
}

VASADEF void vas_array_clear(VAS_Array* array) {
    VASA_ASSERT(array != NULL);
    array->count = 0;
}

VASADEF void* vas_array_get(VAS_Array* array, size_t index) {
    VASA_ASSERT(array != NULL);
    VASA_ASSERT(index < array->count);
    return (void*)((char*)array->items + (array->isize * index));
}

#endif // VAS_ARRAY_IMPLEMENTATION
