## Vas

A lightweight, single-header dynamic array library for C learning and general-purpose use.

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

Vas is a simple, educational implementation of a dynamic array (vector) in C. It is designed to be easy to read, easy to use, and compatible with modern C standards.

## 🚀 Features

- **Single Header**: No complex build systems; just include `vas_array.h`.
- **Type Agnostic**: Store any data type using `void*` and size tracking.
- **C23 Ready**: Tested with modern Clang compilers using the `-std=c23` flag.
- **Transparent**: Minimal code footprint, perfect for learning how dynamic memory works in C.

## 📦 Installation

Simply copy `vas_array.h` into your project directory.

## 🛠️ Usage

To use the library, define `VAS_ARRAY_IMPLEMENTATION` in **exactly one** C file before including the header.

```c
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
```

## 🏗️ Compilation

The project is developed using Clang. To build the provided example on Windows, run the included batch file:

```powershell
.\build.bat
```

Or use the command manually:

```powershell
clang example.c -o example.exe -Wall -Wextra -Werror -std=c23
.\example.exe
```

## 📚 API Reference

| Function         | Description                                           |
|------------------|-------------------------------------------------------|
| vas_array_init   | Allocates initial memory and sets the item size.      |
| vas_array_deinit | Frees all memory and resets the array struct.         |
| vas_array_append | Adds an item to the end, growing capacity if needed.  |
| vas_array_insert | Places an item at an index and shifts existing items. |
| vas_array_remove | Removes an item at an index and closes the gap.       |
| vas_array_clear  | Resets count to zero but keeps allocated memory.      |
| vas_array_get    | Returns a pointer to the element at the index.        |

## ⚖️ License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
