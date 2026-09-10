*This project has been created as part of the 42 curriculum by adaza-ru.*

<div align="center">

# Get Next Line — Two Approaches to Reading in Chunks

**A line-by-line file reader in C, implemented twice: an O(1) array-indexed version and an O(n) linked-list version — built to compare raw speed against memory footprint when tracking read state across multiple file descriptors.**

![C](https://img.shields.io/badge/language-C-00599C?logo=c&logoColor=white)
![Memory Management](https://img.shields.io/badge/focus-memory_management-blueviolet)

</div>

---

## Table of Contents

- [Overview](#overview)
- [Why Two Implementations?](#why-two-implementations)
- [Repository Structure](#repository-structure)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Algorithm](#algorithm)
- [Comparing the Two Approaches](#comparing-the-two-approaches)
- [Design Reflection](#design-reflection)
- [Resources](#resources)
- [Notes](#notes)

---

## Overview

`get_next_line` reads a file descriptor and returns exactly one line per call, newline included, regardless of the `BUFFER_SIZE` used to read from disk. Each call has to pick up exactly where the previous one left off — which means the function needs to persist state (whatever was read past the last newline) between calls, without any of that state living in the caller's scope.

The core exercise is in three parts: managing that persistent state safely, handling dynamic memory correctly (no leaks, no use-after-free), and working directly with the `read()` system call instead of buffered stdio.

## Why Two Implementations?

The 42 bonus requires the function to handle **multiple file descriptors in the same program** — call it with `fd_1`, then `fd_2`, then `fd_1` again, and each stream has to resume correctly. That means the persisted state can no longer be a single static variable; it has to be indexed per fd. There are two common ways to do that:

- **Array indexed by fd** — `static char *stash[1024]`, using the fd itself as the index. This is what most implementations use, since 1024 is the typical Unix soft limit on open file descriptors.
- **Linked list of `{fd, stash}` nodes** — allocates state only for file descriptors actually in use, creating and freeing nodes as fds are opened and exhausted.

Rather than pick one, this repo includes both, on purpose — see [Design Reflection](#design-reflection) for the reasoning and what the comparison actually showed.

The mandatory (single-fd) version isn't included here; this repo focuses on the bonus, where the interesting design decisions live.

## Repository Structure

```
.
├── gnl_array/
│   ├── gnl_arrays.c
│   ├── gnl_array_utils.c
│   └── gnl_array.h
└── gnl_linked_list/
    ├── gnl_linked_list.c
    ├── gnl_linked_list_utils.c
    └── gnl_linked_list.h
```

Both expose the exact same function signature — `char *get_next_line(int fd)` — so either folder is a drop-in replacement for the other.

## Getting Started

### Requirements

- A C compiler

### Build

```bash
# Array-based version
cd gnl_array
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 gnl_array.c gnl_array_utils.c main.c -o gnl_test
./gnl_test file1.txt file2.txt file3.txt
```

```bash
# Linked-list version
cd gnl_linked_list
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 gnl_linked_list.c gnl_linked_list_utils.c main.c -o gnl_test
./gnl_test file1.txt file2.txt file3.txt
```

`BUFFER_SIZE` can be set to any value at compile time — the function behaves identically regardless of how small or large the read chunks are.

## Usage

### Example of ``main.c``

```c
#include "gnl_array.h" // <gnl_array.h / gnl_linked_list.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

/*
** Opens every file passed as an argument and reads them in round-robin,
** one line at a time, to demonstrate that get_next_line keeps each file
** descriptor's state independent from the others.
**
** Usage: ./gnl_test file1.txt file2.txt file3.txt ...
*/

int	main(int argc, char **argv)
{
	int		*fds;
	char	*line;
	int		open_count;
	int		i;

	if (argc < 2)
		return (printf("Usage: %s <file1> [file2] ...\n", argv[0]), 1);
	fds = malloc(sizeof(int) * (argc - 1));
	if (!fds)
		return (perror("malloc"), 1);
	i = 0;
	while (i < argc - 1)
	{
		fds[i] = open(argv[i + 1], O_RDONLY);
		if (fds[i] < 0)
			perror(argv[i + 1]);
		i++;
	}
	open_count = argc - 1;
	while (open_count > 0)
	{
		i = 0;
		while (i < argc - 1)
		{
			if (fds[i] >= 0)
			{
				line = get_next_line(fds[i]);
				if (line)
				{
					printf("[fd %d | %s] %s", fds[i], argv[i + 1], line);
					free(line);
				}
				else
				{
					close(fds[i]);
					fds[i] = -1;
					open_count--;
				}
			}
			i++;
		}
	}
	free(fds);
	return (0);
}
```

The bonus version additionally supports interleaving reads across several open file descriptors within the same program — each keeps its own independent state.

## Algorithm

Each call reads from the file descriptor into a fixed-size buffer, appending the result to that fd's persisted stash, and repeats until a `'\n'` is found or `read()` returns 0 (EOF). The line up to and including the newline is then extracted and returned, and consumed from the stash.

All returned lines and intermediate buffers are dynamically allocated and explicitly freed to avoid leaks — including on EOF and error paths, where the stash itself must be released rather than left dangling.

## Comparing the Two Approaches

| Aspect | Array (`stash[1024]`) | Linked list |
|---|---|---|
| Access per fd | O(1) — direct indexing | O(n) — list traversal |
| Memory allocated | 1024 pointer slots reserved up front (a few KB, unused slots stay `NULL`) | One node allocated per fd actually in use |
| Fd ceiling | Bounded by the array size (1024, matching the Unix soft limit) | No ceiling tied to a fixed array size |
| Lifecycle | Slots persist for the program's lifetime | Nodes are created on first read and freed on EOF/close |
| Implementation complexity | Simpler — direct indexing | Slightly more — manual node lifecycle management |

## Design Reflection

The array is what nearly everyone uses for this bonus, and for good reason — O(1) access is hard to beat. My first instinct was that reserving 1024 pointers up front felt wasteful for a program that might only ever open two or three files, so I built the linked-list version to allocate state only for the fds actually in use, accepting O(n) lookups in exchange.

In practice, the memory difference turned out to be negligible — 1024 pointers is a few kilobytes, irrelevant on any machine built in the last couple of decades. What the linked-list version gives up is trivial O(1) access; what it gains is a cleaner lifecycle: state exists only as long as an fd is open, created and destroyed alongside it, with no dependency on Unix's fd limit. I kept both versions because that trade-off — a bit of extra complexity in exchange for a structure that doesn't reserve space for something it isn't using — felt like a more interesting exercise than optimizing for a memory cost that, at this scale, doesn't really matter.

## Resources

- Peer-to-peer discussion
- Stack Overflow
- Linux manual pages (`man 2 read`, `man 2 open`, `man 2 close`, `man malloc`)

## Notes

Originally built as part of the 42 curriculum. AI tools were used as a learning aid — clarifying low-level concepts (`read()`, file descriptors, static variables, dangling pointers), interpreting Valgrind output during debugging, and improving the structure of this README. All suggestions were reviewed and adapted by hand.
