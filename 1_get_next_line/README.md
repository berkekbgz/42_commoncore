*This project has been created as part of the 42 curriculum by bkabagoz.*

# get_next_line

## Description

`get_next_line` is a C programming project from the 42 Common Core curriculum.

The goal of the project is to implement a function:

```c
char	*get_next_line(int fd);
```

This function reads from a given file descriptor and returns one line at a time. Each call to `get_next_line()` returns the next available line until the end of the file is reached or an error occurs.

The returned line includes the trailing newline character `\n` when one exists. If the file ends without a final newline, the last line is still returned correctly. When there is nothing left to read, or if an error occurs, the function returns `NULL`.

This project focuses on understanding file descriptors, dynamic memory allocation, buffered reading, and especially the use of static variables in C.

## Project Requirements

Mandatory files:

```text
get_next_line.c
get_next_line.h
get_next_line_utils.c
```

Allowed external functions:

```text
read
malloc
free
```

Forbidden:

```text
libft
lseek
global variables
```

The project must compile with:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

The value of `BUFFER_SIZE` can be changed during evaluation, so the function must work with different buffer sizes such as `1`, `42`, `9999`, or larger values.

## Instructions

To compile a small test program with `get_next_line`, use:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

Example `main.c`:

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

Run it with:

```bash
./a.out
```

To test with another buffer size:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c main.c
./a.out
```

## Algorithm Explanation

The function uses a static variable to keep unread data between function calls.

Because `read()` may return more data than a single line requires, the extra characters after a newline must not be lost. They are stored in a static variable called the remainder or stash. On the next call to `get_next_line()`, the function continues from that saved content before reading more from the file descriptor.

The algorithm works as follows:

1. Validate the file descriptor and `BUFFER_SIZE`.
2. Allocate a temporary buffer of size `BUFFER_SIZE + 1`.
3. Check whether the saved remainder already contains a newline.
4. If it does, extract and return the next line from the remainder.
5. If not, read more data from the file descriptor.
6. Append the newly read data to the remainder.
7. Repeat until a newline is found, end-of-file is reached, or an error occurs.
8. When a line is extracted:

   * the line is returned to the caller;
   * the unused part after the newline is saved for the next call;
   * if there is no unused part, the remainder is freed.
9. When end-of-file is reached:

   * if the remainder still contains characters, return them as the final line;
   * otherwise free memory and return `NULL`.

This approach avoids reading the entire file at once. It only reads as much as necessary until a complete line can be returned.

## Memory Management

Every string returned by `get_next_line()` is allocated with `malloc()`. The caller is responsible for freeing each returned line.

Example:

```c
line = get_next_line(fd);
if (line)
{
	printf("%s", line);
	free(line);
}
```

Internal temporary buffers and saved remainders are freed when they are no longer needed, when an error occurs, or when the end of the file is reached.

## Mandatory Behavior

The mandatory implementation keeps one static remainder.

This means it is designed to read one file descriptor correctly through repeated calls. It does not independently track multiple file descriptors at the same time.

Example:

```c
char	*line;

line = get_next_line(fd);
while (line)
{
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
}
```

## Bonus Behavior

The bonus version, if implemented, must be placed in separate files:

```text
get_next_line_bonus.c
get_next_line_bonus.h
get_next_line_utils_bonus.c
```

The bonus version must still use only one static variable, but it must also manage multiple file descriptors independently.

A common solution is to use one static array, where each index stores the remainder for one file descriptor:

```c
static char	*remainder[MAX_OPEN_FD];
```

This allows calls such as:

```c
get_next_line(fd1);
get_next_line(fd2);
get_next_line(fd3);
get_next_line(fd1);
```

without losing the reading state of each file descriptor.

## Resources

Useful references for this project:

* `man 2 read`
* `man 3 malloc`
* `man 3 free`
* 42 subject PDF: Get Next Line
* C static variables
* File descriptors in Unix-like systems
* Dynamic memory allocation in C
* EOF and newline handling in text files

## AI Usage

AI assistance was used as a learning and review tool during this project.

It was used for:
* reviewing edge cases such as invalid file descriptors, end-of-file, and allocation failure;
* improving the explanation of the algorithm for this README.

The implementation itself was tested and verified manually with compiler flags, custom tests, and external testers such as Francinette. AI output was not accepted blindly: suggestions were reviewed, adapted, and checked against the subject requirements.
