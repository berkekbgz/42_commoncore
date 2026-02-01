*This project has been created as part of the 42 curriculum by bkabagoz.*

## Description

Libft is the first project in the 42 curriculum. The goal is to create a personal C library containing re-implementations of standard libc functions, along with additional utility functions that will be useful throughout the 42 cursus.

This library includes:
- **Part 1**: Standard libc functions (memory, string, character manipulation)
- **Part 2**: Additional utility functions not in libc
- **Part 3**: Linked list manipulation functions

## Function List

### Part 1 - Libc Functions

| Function | Description |
|----------|-------------|
| `ft_isalpha` | Check if character is alphabetic |
| `ft_isdigit` | Check if character is a digit |
| `ft_isalnum` | Check if character is alphanumeric |
| `ft_isascii` | Check if character is ASCII |
| `ft_isprint` | Check if character is printable |
| `ft_strlen` | Calculate string length |
| `ft_memset` | Fill memory with a constant byte |
| `ft_bzero` | Zero a byte string |
| `ft_memcpy` | Copy memory area |
| `ft_memmove` | Copy memory area (handles overlap) |
| `ft_strlcpy` | Size-bounded string copy |
| `ft_strlcat` | Size-bounded string concatenation |
| `ft_toupper` | Convert to uppercase |
| `ft_tolower` | Convert to lowercase |
| `ft_strchr` | Locate character in string |
| `ft_strrchr` | Locate character from end of string |
| `ft_strncmp` | Compare strings up to n characters |
| `ft_memchr` | Scan memory for a character |
| `ft_memcmp` | Compare memory areas |
| `ft_strnstr` | Locate substring in string |
| `ft_atoi` | Convert string to integer |
| `ft_calloc` | Allocate and zero memory |
| `ft_strdup` | Duplicate a string |

### Part 2 - Additional Functions

| Function | Description |
|----------|-------------|
| `ft_substr` | Extract substring from string |
| `ft_strjoin` | Concatenate two strings |
| `ft_strtrim` | Trim characters from string |
| `ft_split` | Split string by delimiter |
| `ft_itoa` | Convert integer to string |
| `ft_strmapi` | Apply function to each character (new string) |
| `ft_striteri` | Apply function to each character (in-place) |
| `ft_putchar_fd` | Output character to file descriptor |
| `ft_putstr_fd` | Output string to file descriptor |
| `ft_putendl_fd` | Output string with newline to fd |
| `ft_putnbr_fd` | Output integer to file descriptor |

### Part 3 - Linked List Functions

| Function | Description |
|----------|-------------|
| `ft_lstnew` | Create new list node |
| `ft_lstadd_front` | Add node to beginning of list |
| `ft_lstsize` | Count nodes in list |
| `ft_lstlast` | Get last node of list |
| `ft_lstadd_back` | Add node to end of list |
| `ft_lstdelone` | Delete single node |
| `ft_lstclear` | Delete all nodes in list |
| `ft_lstiter` | Apply function to each node's content |
| `ft_lstmap` | Create new list by applying function |

## Instructions

### Compilation

```bash
make        # Compile the library
make clean  # Remove object files
make fclean # Remove object files and library libft.a
make re     # Force full recompile
```

This creates `libft.a` static library.

### Usage

1. Include the header in your source file:
```c
#include "libft.h"
```

2. Compile with the library:
```bash
cc your_program.c -L/path/to/libft -lft -I/path/to/libft
```

### Example

```c
#include "libft.h"
#include <stdio.h>

int main(void)
{
    char *str = ft_strjoin("Hello, ", "World!");
    printf("%s\n", str);
    free(str);
    return (0);
}
```

## Resources

### Documentation
- [C Standard Library Reference](https://en.cppreference.com/w/c)
- [GNU C Library Manual](https://www.gnu.org/software/libc/manual/)
- [Linux man pages](https://man7.org/linux/man-pages/)

### 42 Resources
- 42 Norm documentation
- 42 Libft Subject PDF

### AI Usage

AI was used as a learning assistant during this project for:
- **Code review**: Checking implementations for bugs, edge cases, and memory leaks
- **Debugging**: Understanding segmentation faults and undefined behavior
