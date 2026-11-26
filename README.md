_This project has been created as part of the 42 curriculum by aaries, fmesci._

# push_swap

## Description

`push_swap` sorts a stack of integers using only two stacks (`a` and `b`) and a
fixed set of 11 operations (`sa sb ss pa pb ra rb rr rra rrb rrr`). The program
prints the operations it used, one per line. The goal is to print as few
operations as possible.

Four strategies are available, plus a benchmark mode:

| Flag                   | Strategy                                 | Complexity (in operations) |
| ---------------------- | ---------------------------------------- | -------------------------- |
| `--simple`             | selection sort                           | O(n²)                      |
| `--medium`             | chunks + extraction of the maximum       | O(n√n)                     |
| `--complex`            | 3-way quicksort on two stacks            | O(n log n)                 |
| `--adaptive` (default) | picks one of the above from the disorder | see below                  |
| `--bench`              | prints statistics on `stderr`            | -                          |

## Instructions

```
make
./push_swap [--simple | --medium | --complex | --adaptive] [--bench] n1 n2 n3 ...
```

- Flags must come **before** the numbers; one strategy flag at most.
- No arguments: prints nothing. Invalid input (non-integer, overflow, duplicate,
  unknown flag): `Error` on `stderr`, exit code 1.
- Verify a result with a checker: `./push_swap $ARG | ./checker $ARG` (see the
  [Bonus](#bonus-the-checker-program) section), or with the checker provided by
  42: `./push_swap $ARG | ./checker_linux $ARG`.
- `--bench` output (on `stderr`, so it never mixes with the operations):

```
[bench] disorder: 47.62%
[bench] strategy: medium / O(n√n)
[bench] total_ops: 21
[bench] sa: 0 sb: 0 ss: 0 pa: 7 pb: 7
[bench] ra: 1 rb: 4 rr: 0 rra: 0 rrb: 2 rrr: 0
```

## Bonus: the checker program

`checker` reads the stack `a` from its arguments, then reads a list of
instructions from the standard input (one per line, until EOF), executes them
and tells whether they sort the stack.

```
make bonus
ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker $ARG
```

- `OK` on `stdout`: `a` is sorted and `b` is empty after all the instructions.
- `KO` on `stdout`: any other case.
- `Error` on `stderr` (exit code 1): non-integer or overflowing argument,
  duplicate, unknown or badly formatted instruction (the line must be exactly
  an instruction followed by `\n`).
- No arguments: prints nothing.
- Run by hand, type the instructions and finish with `Ctrl+D` (EOF).
  To see the instructions while piping: `./push_swap $ARG | tee /dev/stderr | ./checker $ARG`.

The checker reuses the stack, parsing and operation code of `push_swap`
(everything except `srcs/main.c`). The operations do not print anything in the
checker: `t_ps` has a `silent` flag that `log_op` checks before writing.
Instructions are read with `get_next_line`, which keeps reading until EOF even
after an invalid instruction so its internal buffer is always freed.

## How it works

**Preparation.** The input is stored in a singly linked list (`t_stack`: `top`
and `size`). Every value is then replaced by its **rank** (`index`, from 0 to
n-1), so the algorithms never depend on the real values (negatives, large
numbers). The **disorder** is `inverted pairs / total pairs`: 0 means sorted,
1 means reversed, about 0.5 means random. It is computed once, before any move.

**Small inputs.** With 5 numbers or fewer, every strategy uses `sort_small`
(hard-coded 2, 3, 4, 5 cases). The input size is constant, so no complexity
class is broken. `--bench` still shows the strategy the user chose.

### Simple: O(n²)

Selection sort. Repeat n times: rotate the smallest number to the top of `a`
(`ra` or `rra`, whichever is shorter) and `pb` it. Then `pa` everything back.
Each selection costs at most n/2 rotations, so n selections cost O(n²).

### Medium: O(n√n)

1. Split the ranks into chunks of about 1.5·√n values.
2. Push to `b` every number of the current window (the smallest ranks first),
   with `rb` for the smaller half of the window so `b` stays roughly ordered.
   A number in the window is never more than O(√n) moves away.
3. Bring numbers back with `pa` from the largest to the smallest, rotating `b`
   the shortest way (`rb` or `rrb`) to reach the maximum.

Both phases cost O(√n) operations per number, hence O(n√n).

### Complex: O(n log n)

A 3-way quicksort adapted to two stacks. The work is done on **blocks**: a
block is a set of `n` consecutive ranks `[lo, lo + n)` stored together in one
of four places:

- `TA` top of `a`, `BA` bottom of `a`,
- `TB` top of `b`, `BB` bottom of `b`.

Using both ends of both stacks is what saves operations: a block parked at the
bottom of a stack is not touched until its turn comes, so numbers do not travel
back and forth between `a` and `b`.

`sort_block(loc, lo, n)` puts the block on top of `a`, sorted, above the larger
numbers that are already placed:

1. Split the block by rank into three thirds: **small** `[lo, lo + n/3)`,
   **medium** `[lo + n/3, lo + 2n/3)` and **large** `[lo + 2n/3, lo + n)`.
2. Take the `n` numbers one by one from the block (from the top, or from the
   bottom with `rra`/`rrb`) and send each one to the place that depends on
   where the block is:

   | block is in | large | medium | small |
   | ----------- | ----- | ------ | ----- |
   | `TA`        | `BA`  | `TB`   | `BB`  |
   | `BA`        | `TA`  | `TB`   | `BB`  |
   | `TB`        | `TA`  | `BA`   | `BB`  |
   | `BB`        | `TA`  | `BA`   | `TB`  |

3. Sort the three new blocks recursively in this order: **large, medium,
   small**. Each one ends on top of `a` and above the previous ones, so when
   the last (small) block is done, `a` is sorted.

Shortcuts and base cases:

- A block of 1 number is moved to the top of `a` (`move_elem`).
- A block that is already ordered is left alone (in `a`) or moved with `pa`
  (in `b`, when it is in descending order).
- A block of 2 numbers on top of a stack costs one `sa`, or `sb` + 2 `pa`.
- A block at the bottom of a stack that is the whole stack is treated as being
  on top (`to_top`), so no extra rotations are spent.

Moving one number costs at most 3 operations (for example `rrb`, `pa`, `ra`),
a constant. Every level of the recursion moves each number once, and the block
size is divided by 3 at each level, so there are about log₃ n levels:
O(n log n) operations.

Why not a binary partition (on the bits of the rank, or at the median)? We
tried both: with only two parts every level has to bring most numbers back
across `a` and `b`, which costs about 760-780 operations for 100 numbers, above
the 700 target. The three parts with four places cut that to about 680.

### Adaptive

| Disorder     | Strategy | Why                                                                                                                                                                                                                                                                                                           |
| ------------ | -------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| < 0.2        | simple   | On a nearly sorted stack the minimum is almost always close to the top, so each selection needs very few rotations: with only a few numbers out of place the total is a small multiple of n (500 numbers, disorder 0.83%: 1860 operations, about 3.7·n). The cost grows with the number of misplaced numbers. |
| 0.2 to < 0.5 | medium   | Too disordered for the cheap case, not random enough to need the full partition: O(n√n) with a small constant.                                                                                                                                                                                                |
| ≥ 0.5        | complex  | Random or reversed input, where the O(n log n) bound matters.                                                                                                                                                                                                                                                 |

**Why these thresholds.** The three regimes and their target complexities
(O(n), O(n√n), O(n log n)) come from the subject. 0.5 is the expected disorder
of a random permutation, so above it the input carries no useful order and the
general O(n log n) method is the right one. Below 0.2 most of the input is
already ordered, so a method that only has to fix a few misplaced numbers is
used.

**A note on O(n).** A strict O(n) bound for _every_ input with disorder < 0.2
is impossible. A disorder of 0.19 still allows about 0.19 · n²/2 inversions,
and there are so many permutations with that many inversions that any
algorithm needs Ω(n log n) operations in the worst case (each operation is one
of 11 choices, so it carries at most log₂ 11 bits of information). Linear cost
can only be reached on inputs where few numbers are out of place.

Measured on random inputs (operations): 100 numbers: simple about 1300-1500,
medium about 570, complex about 680 (200 runs: maximum 688). 500 numbers:
simple about 32000, medium about 5000, complex about 4630 (maximum about 4650).
In `--adaptive` a random input has about 50% disorder, so roughly half of the
random inputs go to medium and half to complex; with 500 numbers the worst case
seen was 5220, still below 5500.

## Complexity summary

|          | Time (operations)             | Extra space               |
| -------- | ----------------------------- | ------------------------- |
| simple   | O(n²)                         | O(n)                      |
| medium   | O(n√n)                        | O(n)                      |
| complex  | O(n log n)                    | O(n) + O(log n) recursion |
| adaptive | that of the strategy it picks | same                      |

Space: every number lives in exactly one list node (`a` and `b` together hold
n nodes), and the rank array used by `assign_index` is freed right after.
`complex` divides the block size by 3 at each level, so the recursion is about
log₃ n levels deep.
The cost of one operation on the linked list is O(1) except `ra` and `rra`
which are O(n) in CPU time; the complexity classes above count **operations
printed**, as the subject asks.

## Project layout

```
includes/push_swap.h  structures, block position constants and prototypes
includes/header_bonus.h  checker prototypes and get_next_line (bonus)
bonus/                checker and get_next_line (bonus, `make bonus`)
srcs/main.c           entry point
srcs/parsing/         flags and number parsing
srcs/stack/           linked-list stack and helpers
srcs/utils/           string and output helpers, ft_split
srcs/ops/             the 11 operations (print + count)
srcs/analysis/        ranks, disorder, --bench
srcs/sort/            dispatch, small, simple, medium, complex (+ move, utils),
                      adaptive
```

## Contributions

- **fmesci**: parsing and flags, stack and stack helpers, the 11 operations,
  `dispatch`, `sort_small`, `sort_simple`, project structure, Makefile and the
  bonus `checker`.
- **aaries**: `assign_index`, `compute_disorder`, `--bench`, `sort_medium`,
  `sort_complex`, `sort_adaptive`.

## Resources

- 42 subject for push_swap.
- [Big O notation](https://en.wikipedia.org/wiki/Big_O_notation): the
  complexity classes used to describe each strategy.
- [Inversion (discrete mathematics)](<https://en.wikipedia.org/wiki/Inversion_(discrete_mathematics)>):
  inversions and how they measure disorder.
- [Selection sort](https://en.wikipedia.org/wiki/Selection_sort): base of the
  simple strategy.
- [Quicksort](https://en.wikipedia.org/wiki/Quicksort): base of the 3-way
  partition used by the complex strategy.
- T. H. Cormen, C. E. Leiserson, R. L. Rivest, C. Stein, _Introduction to
  Algorithms_ (MIT Press): sorting algorithms and lower bounds for sorting.

**AI usage.** AI was used to reinforce our understanding of the concepts behind the project (algorithmic complexity, the sorting algorithms and their adaptation to two stacks), to review the code against the subject and to help draft this README.
