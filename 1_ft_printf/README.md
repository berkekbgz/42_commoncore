_This project has been created as part of the 42 curriculum by bkabagoz._

# ft_printf

## Description

`ft_printf` is a 42 Common Core project whose goal is to recode a simplified version of the standard C `printf()` function.

The project focuses on variadic functions, formatted output, integer base conversion, pointer printing, and precise return values. The final deliverable is a static library named `libftprintf.a` that exposes this function:

```c
int	ft_printf(const char *format, ...);
```

Unlike the original libc `printf()`, this implementation does not reproduce internal buffer management. It writes output directly and returns the number of characters printed, or `-1` if a write error occurs.

## Supported Conversions

| Conversion | Output |
| --- | --- |
| `%c` | Single character |
| `%s` | String |
| `%p` | Pointer address in hexadecimal format |
| `%d` | Signed decimal integer |
| `%i` | Signed decimal integer |
| `%u` | Unsigned decimal integer |
| `%x` | Unsigned hexadecimal integer, lowercase |
| `%X` | Unsigned hexadecimal integer, uppercase |
| `%%` | Percent sign |

## Instructions

Build the static library from the project directory:

```sh
make
```

This creates:

```text
libftprintf.a
```

Available Makefile rules:

| Rule | Description |
| --- | --- |
| `make` or `make all` | Compile the project and create `libftprintf.a` |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and `libftprintf.a` |
| `make re` | Rebuild the library from scratch |

Compile a test program with the library:

```sh
cc -Wall -Wextra -Werror main.c -L. -lftprintf -o test_ft_printf
```

Example usage:

```c
#include "ft_printf.h"

int	main(void)
{
	ft_printf("Hello %s, value = %d, hex = %x\n", "42", 42, 42);
	return (0);
}
```

## Implementation Details

The implementation is organized around a direct format-string scan.

`ft_printf()` walks through the `format` string one character at a time. Ordinary characters are written immediately with `write(1, ...)`. When a `%` is found, the next character is interpreted as a conversion specifier and dispatched to the matching helper function.

The variadic arguments are managed with `va_list`, `va_start`, `va_arg`, and `va_end`. Each supported conversion extracts exactly the type expected by the C variadic calling convention, such as `int` for `%c`, `%d`, and `%i`, `char *` for `%s`, `void *` for `%p`, and `unsigned int` for `%u`, `%x`, and `%X`.

The project uses simple helper functions instead of a complex formatting structure because the mandatory subject only requires the basic conversions `cspdiuxX%`. This keeps the code small, readable, and aligned with the subject requirement to avoid reproducing libc `printf()` buffer management.

Integer and hexadecimal output are printed recursively. The recursion first prints the most significant digits, then writes the current digit. This avoids heap allocation and temporary buffers while preserving the correct digit order. The only persistent state needed during formatting is the current position in the format string, the active `va_list`, and the accumulated character count.

Pointer output casts the pointer value to an unsigned integer type large enough to hold the address, prints the `0x` prefix for non-null pointers, and then reuses the hexadecimal printer. Null strings are printed as `(null)`, and null pointers are printed as `(nil)`, matching common libc behavior used in typical `ft_printf` evaluations.

## Project Structure

```text
/
|-- Makefile
|-- README.md
|-- ft_printf.c
|-- ft_printf.h
|-- ft_put/
|   |-- ft_put.h
|   |-- ft_putcharstr.c
|   |-- ft_puthex.c
|   |-- ft_putint.c
|   `-- ft_putptr.c
`-- libft/
```

## Resources

- 42 ft_printf subject pdf
- C variadic arguments: https://en.cppreference.com/w/c/variadic
- `stdarg(3)` manual: https://man7.org/linux/man-pages/man3/stdarg.3.html
- `printf(3)` manual: https://man7.org/linux/man-pages/man3/printf.3.html
- `write(2)` manual: https://man7.org/linux/man-pages/man2/write.2.html
- Static libraries with `ar`: https://man7.org/linux/man-pages/man1/ar.1.html

AI was used to draft and structure this README from the subject PDF and the existing source files. It was not used in this task to modify the `ft_printf` implementation itself.
