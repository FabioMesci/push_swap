*This project has been created as part of the 42 curriculum by aaries, fmesci.*

# push_swap

## Description

`push_swap` sorts a stack of integers using only two stacks (`a` and `b`) and a
fixed set of 11 operations (`sa sb ss pa pb ra rb rr rra rrb rrr`). The program
prints the operations it used, one per line. The goal is to print as few
operations as possible.

Four strategies are available, plus a benchmark mode:

| Flag | Strategy | Complexity (in operations) |
|---|---|---|
| `--simple` | selection sort | O(n²) |
| `--medium` | chunks + extraction of the maximum | O(n√n) |
| `--complex` | binary partition on the rank bits | O(n log n) |
| `--adaptive` (default) | picks one of the above from the disorder | see below |
| `--bench` | prints statistics on `stderr` | - |

## Instructions

```
make
./push_swap [--simple | --medium | --complex | --adaptive] [--bench] n1 n2 n3 ...
```

- Flags must come **before** the numbers; one strategy flag at most.
- No arguments: prints nothing. Invalid input (non-integer, overflow, duplicate,
  unknown flag): `Error` on `stderr`, exit code 1.
- Verify a result with a checker: `./push_swap $ARG | ./checker_linux $ARG`.
- `--bench` output (on `stderr`, so it never mixes with the operations):

```
[bench] disorder: 47.62%
[bench] strategy: medium / O(n√n)
[bench] total_ops: 21
[bench] sa: 0 sb: 0 ss: 0 pa: 7 pb: 7
[bench] ra: 1 rb: 4 rr: 0 rra: 0 rrb: 2 rrr: 0
```

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

A binary partition that works from the top bit of the rank down (similar to a
radix exchange / quicksort on bits):

- `sort_a(len, bit)`: on the `len` top numbers of `a`, a number whose bit is 0
  goes to `b` (`pb`), a number whose bit is 1 stays in `a` (`ra`). The ones are
  put back on top with `rra`, then the group is sorted recursively with the
  next bit.
- `sort_b(len, bit)` is the mirror image: ones go to `a` (`pa`), zeros stay in
  `b` (`rb`, restored with `rrb`). The ones are sorted in `a`, then the zeros
  are sorted and moved to `a`.
- Shortcuts: a group that is already ordered is only moved, a group of two
  needs at most one `sa`, and when a group is the whole stack no restore
  rotation is needed.
- Groups of exactly 4 numbers (the usual size near the bottom of the
  recursion) are not partitioned any more: `sort_micro.c` holds, for each of
  the 24 possible orders, the shortest sequence of operations (computed once by
  an exhaustive breadth-first search over all legal moves, with the rest of the
  stacks left untouched). This saves about 6% of all operations and is what
  brings 500 numbers under 5500.

Every level of the recursion touches each number a constant number of times and
there are ⌈log₂ n⌉ levels, so O(n log n) operations.

### Adaptive

| Disorder | Strategy | Why |
|---|---|---|
| < 0.2 | simple | Selection is cheap on a nearly sorted stack: the minimum is always close to the top, so each selection costs about 1 + its displacement. The total is about 2n + (number of inversions), i.e. close to O(n) when the input is nearly sorted. |
| 0.2 to < 0.5 | medium | Too disordered for the cheap case, not random enough to need the full partition: O(n√n) with a small constant. |
| ≥ 0.5 | complex | Random or reversed input, where the O(n log n) bound matters. |

The thresholds follow the subject: 0.2 is where the cost of selection stops
being close to linear, and 0.5 is the disorder of a random permutation.

Measured on random inputs (operations): 100 numbers: simple about 1300-1500,
medium about 570, complex about 760. 500 numbers: simple about 32000,
medium about 5000, complex about 5300 (40 runs: maximum 5329).

## Complexity summary

| | Time (operations) | Extra space |
|---|---|---|
| simple | O(n²) | O(n) |
| medium | O(n√n) | O(n) |
| complex | O(n log n) | O(n) + O(log n) recursion |
| adaptive | that of the strategy it picks | same |

Space: every number lives in exactly one list node (`a` and `b` together hold
n nodes), and the rank array used by `assign_index` is freed right after.
`complex` recurses at most once per bit of the rank, so at most 31 levels deep.
The cost of one operation on the linked list is O(1) except `ra` and `rra`
which are O(n) in CPU time; the complexity classes above count **operations
printed**, as the subject asks.

## Project layout

```
srcs/main.c          entry point
srcs/parsing/        flags and number parsing
srcs/stack/          linked-list stack and helpers
srcs/ops/            the 11 operations (print + count)
srcs/analysis/       ranks, disorder, --bench
srcs/sort/           dispatch, small, simple, medium, complex (+ micro, utils), adaptive
```

## Contributions

- **fmesci**: parsing and flags, stack and stack helpers, the 11 operations,
  `dispatch`, `sort_small`, `sort_simple`, project structure and Makefile.
- **aaries**: `assign_index`, `compute_disorder`, `--bench`, `sort_medium`,
  `sort_complex`, `sort_adaptive`.

## Resources

- 42 subject for push_swap.
- Notes on radix sort and on partition-based sorting (quicksort/radix exchange).
- AI assistance (Claude) was used to help write `sort_complex`, to review the
  code, to run tests and to draft this README.
