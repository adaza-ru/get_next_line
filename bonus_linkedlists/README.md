*This project has been created as part of the 42 curriculum by adaza-ru.*

# Description

**Get Next Line** is a project that consists of implementing a function capable of reading and returning a single line from a given file descriptor. The main goal of this project is to develop a solid understanding of file input/output in C, efficient dynamic memory management, and the use of static variables to preserve data between successive function calls.

The `get_next_line` function reads a file line by line, regardless of the buffer size defined at compile time. Through this project, key concepts such as string manipulation, memory allocation and deallocation, and the use of the `read()` system call are reinforced.

# Instructions

## Compilation

To compile the project, use the following commands:

### Mandatory version

`cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl`

### Bonus version

`cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c -o gnl_bonus`

## Execution

Create a text file in the project directory and test the function using a simple main, for example:

	#include "get_next_line.h"
	#include <fcntl.h>
	#include <stdio.h>
	#include <stdlib.h>

	int main(void)
	{
	    int fd = open("file.txt", O_RDONLY);
	    char *line;

	    while ((line = get_next_line(fd)) != NULL)
	    {
	        printf("%s", line);
	        free(line);
	    }
	    close(fd);
	    return (0);
	}

For the bonus part, multiple files can be opened simultaneously, and `get_next_line` can be called with different file descriptors within the same program.

# Algorithm

Each call to `get_next_line` returns exactly one line, including the newline character if it exists.

The core algorithm is based on repeatedly reading from a file descriptor into a buffer. The read data is appended to a static storage area (stash) each time the `read()` function is called. This process continues until a newline character (`'\n'`) or the end of the file is encountered. Then the complete line can be extracted and returned, and that information is eliminated from the stash.

Memory is dynamically allocated for all returned lines and intermediate buffers, and carefully freed to avoid memory leaks.

## Bonus – Multiple File Descriptors

For the bonus part, where the function must handle multiple file descriptors at the same time, there are two main possible approaches:

**Arrays**: Provide faster access times but require preallocating memory, which can lead to higher memory usage if many file descriptors are unused.

**Linked lists**: Allow dynamic memory allocation only when needed, resulting in better memory efficiency at the cost of slightly slower access.

In this implementation, linked lists were chosen to manage multiple file descriptors. Each node stores a file descriptor and its associated stash. This design allows the program to scale dynamically with the number of open file descriptors while minimizing unnecessary memory usage, prioritizing flexibility and memory efficiency over raw speed.

# Resources

- P2P.
- Stack Overflow.  
- Linux manual pages (man 2 read, man 2 open, man 2 close, man malloc).

## Use of AI in the Project

AI tools were used exclusively as learning and support aids for the following tasks:

- Clarifying theoretical concepts such as how `read()` works at a low level, file descriptors, static variables, and dangling pointers.
- Assisting with debugging by interpreting Valgrind reports to identify memory leaks and segmentation faults.  
- Diagnosing specific errors encountered during early implementations.
- Improving the clarity and structure of the README file.