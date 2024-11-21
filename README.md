# Get Next Line Bonus

This project provides an implementation of the `get_next_line` function, which reads a single line from a file descriptor, supporting multiple file descriptors simultaneously. It handles memory allocation dynamically and uses a linked list to store buffered content.

## Features

- Reads one line at a time from a file descriptor, up to `BUFFER_SIZE` bytes per call to `read`.
- Supports multiple file descriptors concurrently.
- Dynamically manages memory for large files and variable line lengths.
- Handles edge cases like empty files, EOF, or errors during reading.

---

## File Descriptions

### 1. `get_next_line_bonus.c`

Contains the main logic for the `get_next_line` function:
- **`get_next_line`**: Reads and returns the next line from a file descriptor.
- **`check_for_newline`**: Checks if a newline character exists in the buffer.
- **`read_and_store`**: Reads from the file descriptor and appends data to the stash.
- **`cat_content`**: Concatenates all buffered content into a single line.
- **`trim_tail`**: Removes the processed part of the buffer and keeps unprocessed data for subsequent calls.

### 2. `get_next_line_utils_bonus.c`

Utility functions for managing the linked list and memory:
- **`create_node`**: Creates a new linked list node for buffering data.
- **`get_tail`**: Retrieves the last node of the linked list.
- **`enqueue`**: Adds a new node to the end of the linked list.
- **`cleanup_on_error`**: Frees memory and clears the stash in case of an error.
- **`ft_memcpy`**: Copies memory safely between buffers.

---

## How to Use

1. **Clone the repository**:
   ```bash
   git clone https://github.com/your-username/get_next_line.git
   cd get_next_line
   ```

2. **Compile the code**:
   Include the necessary files and define the `BUFFER_SIZE`. Example:
   ```bash
   gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c -o get_next_line
   ```

3. **Include the header file**:
   Ensure your code includes the `get_next_line_bonus.h` header.

4. **Example usage**:
   ```c
   #include "get_next_line_bonus.h"
   #include <fcntl.h>
   #include <stdio.h>

   int main(void)
   {
       int fd = open("example.txt", O_RDONLY);
       char *line;

       while ((line = get_next_line(fd)) != NULL)
       {
           printf("%s", line);
           free(line);
       }
       close(fd);
       return 0;
   }
   ```

---

## Key Functions and Behavior

- **Memory Management**: Allocates memory dynamically for each line. Ensure to free returned lines after use.
- **Multifile Support**: Uses an array of static pointers to handle multiple file descriptors without interfering with one another.
- **Error Handling**: Properly frees allocated memory in case of an error or EOF.
