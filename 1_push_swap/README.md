_This project has been created as part of the 42 curriculum by bkabagoz, erearsla._

# push_swap

## Description

`push_swap` is a sorting algorithm project from the 42 curriculum. Given a list
of integers and two stacks `a` and `b`, the program prints to standard output
the shortest possible sequence of stack operations that sorts the integers of
stack `a` in ascending order, with the smallest value at the top.

The allowed operations form the *Push_swap language*:

| Operation | Effect                                                             |
|-----------|--------------------------------------------------------------------|
| `sa`      | Swap the first two elements of stack `a`.                          |
| `sb`      | Swap the first two elements of stack `b`.                          |
| `ss`      | `sa` and `sb` at the same time.                                    |
| `pa`      | Pop the top of `b` and push it on top of `a`.                      |
| `pb`      | Pop the top of `a` and push it on top of `b`.                      |
| `ra`      | Rotate `a` upwards (top goes to the bottom).                       |
| `rb`      | Rotate `b` upwards (top goes to the bottom).                       |
| `rr`      | `ra` and `rb` at the same time.                                    |
| `rra`     | Reverse rotate `a` (bottom goes to the top).                       |
| `rrb`     | Reverse rotate `b` (bottom goes to the top).                       |
| `rrr`     | `rra` and `rrb` at the same time.                                  |

The goal is not just to sort, but to sort *cheaply* — the fewer operations the
better. The subject pushes the cost analysis out of the classical RAM model and
into the Push_swap operation model, where complexity is measured in operations
emitted, not abstract steps.

## Instructions

### Build

The project ships with a `Makefile` that builds its own `libft` and `ft_printf`
sub-libraries before linking the binary.

```sh
make            # builds ./push_swap
make clean      # removes object files
make fclean     # removes object files and the binary
make re         # rebuilds from scratch
```

The build uses `cc -Wall -Wextra -Werror`. No external dependencies beyond the
two vendored libraries.

### Usage

```
./push_swap [--simple|--medium|--complex|--adaptive] [--bench] <int> <int> ...
```

Arguments are integers (positive or negative, no duplicates, all fitting in
`int`). The first argument represents the top of stack `a`. With no arguments
the program exits silently. On any error (non-integer, overflow, duplicate,
unknown flag) it prints `Error\n` on stderr and exits.

The strategy selectors are mutually exclusive in spirit; the last one on the
command line wins. If none is given, `--adaptive` is used.

| Flag         | Strategy                            | Complexity in ops          |
|--------------|-------------------------------------|----------------------------|
| `--simple`   | Selection sort by min-extraction    | O(n²)                      |
| `--medium`   | Chunk-based push to `b` with ranks  | O(n·√n)                    |
| `--complex`  | Radix sort on ranks                 | O(n·log n)                 |
| `--adaptive` | Dispatch by measured `disorder`     | matches the chosen regime  |

`--bench` is an optional flag that, after sorting, prints a structured report
on **stderr** so the operation stream on stdout can still be piped into a
checker. The report contains the disorder (in percent), the strategy actually
used, the total number of operations, and the count of every individual
operation.

### Examples

```sh
$ ./push_swap 2 1 3 6 5 8
ra
pb
rra
pb
...

$ ARG="4 67 3 87 23"; ./push_swap --adaptive $ARG | wc -l
13

$ ARG="4 67 3 87 23"; ./push_swap --complex $ARG | ./checker_linux $ARG
OK

$ shuf -i 0-9999 -n 500 > args.txt
$ ./push_swap --bench $(cat args.txt) 2> bench.txt | ./checker_linux $(cat args.txt)
OK
$ cat bench.txt
[bench] disorder: 49.93%
[bench] strategy: Adaptive / O(n*sqrt(n))
[bench] total_ops: 7997
[bench] sa: 0 sb: 0 ss: 0 pa: 500 pb: 500
[bench] ra: 4840 rb: 1098 rr: 0 rra: 0 rrb: 1059 rrr: 0

$ ./push_swap --adaptive 0 one 2 3
Error
$ ./push_swap --simple 3 2 3
Error
```

## Disorder metric

Before any move is emitted, the program walks every pair `(i, j)` with `i < j`
in stack `a` and counts how many of those pairs are inverted (i.e. the
top-most element is greater than the bottom-most one). The ratio of inversions
to total pairs gives the disorder, a number in `[0, 1]`:

```
disorder = inversions(a) / (n * (n - 1) / 2)
```

A sorted stack scores `0`, a reverse-sorted stack scores `1`. The adaptive
strategy uses this number to pick a sub-algorithm whose operation cost stays
within the budget for that regime.

## Algorithms and why we picked them

The subject demands four strategies covering three complexity classes plus an
adaptive dispatcher. We aimed for implementations that are both
norm-compliant and easy to defend during evaluation rather than hyper-optimized
black boxes.

### Simple — selection sort by min-extraction · O(n²)

`sort_simple.c` repeatedly walks stack `a` to locate the minimum, brings it to
the top with the cheaper of `ra` / `rra`, then `pb`'s it. Once `a` is empty,
everything is moved back with `pa`'s. Each of the `n` iterations costs at most
`n/2` rotations plus a push, so the total cost is bounded by `n²/2 + 2n`,
firmly inside the O(n²) class. We use it as the baseline because it is short,
obviously correct, and naturally well-suited to *almost-sorted* input where
the rotations rarely move anything.

### Medium — chunk-based push with rank windows · O(n·√n)

`sort_medium.c` first compresses values into ranks `0..n-1` (so the data
becomes a permutation), then partitions the rank space into about `√n`
contiguous chunks. Going through `a` once, each element is pushed to `b` and
shoved into place inside its chunk; once `a` is drained, `b` is unwound from
its largest element back onto `a` using the cheaper rotation each time. With
`√n` chunks of size `√n`, every chunk contributes `O(n)` operations while
unwinding contributes `O(n·√n)` in the worst case, which is the regime we
target.

### Complex — radix sort on ranks · O(n·log n)

`sort_complex.c` again compresses to ranks (so values fit in `⌈log₂ n⌉` bits),
then performs an LSD radix sort using `b` as a scratch stack. For each bit
level it `pb`'s elements whose current bit is `0` and rotates the rest, then
flushes everything back with `pa`'s. Each pass is O(n), there are `⌈log₂ n⌉`
passes, hence O(n·log n) operations overall. Radix sort fits the two-stack
model far better than merge or quick sort, both of which require recursion
patterns that are awkward to express with rotations only.

### Adaptive — disorder-driven dispatch

`sort_adaptive.c` measures the disorder once and dispatches:

| Disorder regime          | Strategy                | Why                                                                                  |
|--------------------------|-------------------------|--------------------------------------------------------------------------------------|
| `disorder < 0.2`         | Simple   (O(n²))        | The input is nearly sorted; selection sort barely rotates and beats anything fancy.  |
| `0.2 ≤ disorder < 0.5`   | Medium   (O(n·√n))      | Mid-range chaos; chunked partitioning keeps the operation count tame.                |
| `disorder ≥ 0.5`         | Complex  (O(n·log n))   | High-entropy input rewards the asymptotically best strategy.                         |

The thresholds (`0.2` and `0.5`) come straight from the subject. They split
the disorder spectrum into thirds where each algorithm is cheapest in
operation count for our implementations on randomly generated inputs.

### Complexity summary (Push_swap operation model)

| Strategy   | Time (ops)  | Auxiliary space |
|------------|-------------|-----------------|
| Simple     | O(n²)       | O(1)            |
| Medium     | O(n·√n)     | O(1)            |
| Complex    | O(n·log n)  | O(1)            |
| Adaptive   | regime-bound (above) | O(1)   |

Auxiliary space is O(1) on top of the two stacks themselves, which together
hold exactly the `n` input nodes throughout the run.

## Performance benchmarks

Measured with `shuf` on randomized inputs of the given size, default
strategy (`--adaptive`):

| n   | typical ops | subject pass | good   | excellent |
|-----|-------------|--------------|--------|-----------|
| 100 | ~700        | < 2000       | < 1500 | < 700     |
| 500 | ~6800       | < 12000      | < 8000 | < 5500    |

## Repository layout

```
1_push_swap/
├── Makefile
├── push_swap.h
├── main.c
├── parse.c           		# argv → stack, integer/duplicate/overflow checks
├── init.c            		# rank assignment, disorder computation
├── data_init.c       		# node/stack/state allocation
├── data_free.c       		# cleanup paths
├── ops_swap.c        		# sa / sb / ss
├── ops_push.c        		# pa / pb
├── ops_rotate.c      		# ra / rb / rr
├── ops_reverse_rotate.c	# rra / rrb / rrr
├── sort_simple.c     		# O(n^2)  selection sort
├── sort_medium.c     		# O(n*√n) chunk sort
├── sort_complex.c    		# O(n*log n) radix sort
├── sort_adaptive.c   		# disorder-driven dispatch
├── benchmark.c       		# --bench reporting
├── utils.c
├── libft/            		# vendored libft
└── ft_printf/        		# vendored ft_printf
```

## Contributors

| Login      | Focus                                                                |
|------------|----------------------------------------------------------------------|
| `bkabagoz` | Stack/state data structures, operation primitives, medium & complex sorts, adaptive dispatcher, benchmark mode. |
| `erearsla` | Argument parsing & error handling, rank assignment and disorder metric, simple sort, build system & test harness. |

Both members participated in design discussions, peer review, and debugging of
every component.

## Resources

- 42 norm reference: <https://github.com/42School/norminette>.
- Wikipedia: [Stack](http://en.wikipedia.org/wiki/Stack_(abstract_data_type)),
[Radix sort](https://en.wikipedia.org/wiki/Radix_sort),
  [Selection sort](https://en.wikipedia.org/wiki/Selection_sort),
  [Algorithmic Complexity](https://en.wikipedia.org/wiki/Analysis_of_algorithms)
- [The subject PDF](https://cdn.intra.42.fr/pdf/pdf/192929/en.subject.pdf)

### AI Usage

AI tools (ChatGPT and Claude) were used for the following bounded tasks:

- Brainstorming the chunk-size heuristic for the medium strategy and
  sanity-checking the operation-count math for the radix pass count.
- Drafting the first version of this README, which we then edited to match
  the actual code, our chosen thresholds, and our contribution split.
- Rubber-ducking edge cases in the parser (leading `+`, lone `-`, overflow at
  `INT_MIN`/`INT_MAX`).

Every algorithmic decision and every line of code committed to this repository
was reviewed, understood, and rewritten by us where needed. We are able to
explain and defend any part of the implementation during the peer-review
defense.
