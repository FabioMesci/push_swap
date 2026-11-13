# push_swap — Team Plan

Shared plan for splitting the remaining work between the two of us.
Goal: each person works on **their own files**, so we never edit the same file at the same time.

> This is a working document. Tick boxes as we go, and update it when we change a decision.
> Delete it (or move what is useful into `README.md`) before the final submission.

---

## Contents

1. [Current status](#1-current-status)
2. [Program flow](#2-program-flow)
3. [Open decisions](#3-open-decisions)
4. [Files and functions](#4-files-and-functions)
5. [Work split by phase](#5-work-split-by-phase)
6. [Git workflow](#6-git-workflow)
7. [Subject requirements checklist](#7-subject-requirements-checklist)
8. [Testing](#8-testing)

---

## 1. Current status

### Done (on `main`)

- [x] Flag parsing: `--simple`, `--medium`, `--complex`, `--adaptive`, `--bench` (flags must come before the numbers)
- [x] Number parsing: non-integers, overflow and duplicates → `Error` on stderr, exit code 1
- [x] Stack `a` as a linked list (`t_node`, `t_stack`), `free_stack`
- [x] `enum e_op` (`OP_SA` … `OP_RRR`, `OP_COUNT`) and `int ops[OP_COUNT]` in `t_ps`
- [x] `op_name(t_op)` and `log_op(t_ps *, t_op)` in `ops_utils.c`: print the operation to stdout and count it
- [x] `main.c` refactored: `free_all`, `exit_with_error`, and `execute` (stub) as the single entry point for sorting
- [x] Header grouped by file; `strategy` values documented above `t_ps`
- [x] `srcs/` split into folders (`parsing/`, `stack/`, `utils/`, `ops/`, `analysis/`, `sort/`)
- [x] No leaks, no relink, compiles with `-Wall -Wextra -Werror`

### Design decisions already taken

| Topic | Decision | Why |
|---|---|---|
| Strategy storage | `const char *strategy` (the flag string itself), never `NULL` after `main` | Simple; strings are compared in very few places |
| Single quoted argument (`"3 2 1"`) | **Postponed to phase 3** (for now → `Error`) — see [open decisions](#3-open-decisions) | The change is isolated in `parsing.c`: sorting, ops and bench receive an already-built stack |
| Flags after numbers (`1 2 --bench`) | Not supported → `Error` | Flags are parsed first, then numbers |
| Repeated strategy flag | `Error` | Ambiguous input |
| Stack structure | Singly linked list, `t_stack` keeps only `top` and `size` (no `bottom`, no `prev`) | Fewer pointers to keep consistent in the 11 operations → fewer bugs. `ra`/`rra` cost O(n) CPU, irrelevant for n ≤ 500; the subject measures the **number of operations**, which does not change |

### Still needed before we split the work

- [x] Close the [open decisions](#3-open-decisions)
- [ ] Add the prototypes of the new modules to `push_swap.h`
- [ ] Create every new `.c` file as a **stub** that compiles, and add them all to the `Makefile`
- [ ] Fill in `execute` with the full flow (calling the stubs)

The 11 operations are **not** a blocker for B: `index.c`, `disorder.c` and `bench.c` do not need them, so both of us can start phase 1 at the same time.

---

## 2. Program flow

```
main
 ├─ parse_flags                       done
 ├─ build_stack                       done
 └─ execute(p)
     ├─ assign_index        index.c
     ├─ compute_disorder    disorder.c    must run before ANY move
     ├─ is_sorted           disorder.c    already sorted → skip dispatch (no operations)
     ├─ dispatch            dispatch.c    n <= 5 → small, otherwise the selected strategy
     └─ print_bench         bench.c       only with --bench (also when already sorted), on stderr
```

`main.c` is edited **once** (phase 0) and then nobody touches it again.

---

## 3. Open decisions

These had to be agreed **before** writing the stubs, because they change prototypes or the flow of `execute`.

- [x] **Disorder field in `t_ps`** → `double disorder`.
  It is a fraction between 0 and 1, computed before any move and printed by the bench at the end, so it must live in `t_ps`. `double` is the standard floating type in C. The bench prints it as a percentage with 2 decimals (e.g. `37.50%`), which we do by hand: multiply, split integer and decimal parts, print them as integers.
- [x] **2 to 5 numbers** → `dispatch` always uses `sort_small`, whatever the flag.
  The subject asks for the shortest list possible. For n ≤ 5 the input size is constant, so any method is within O(n²), O(n√n) and O(n log n): no strategy's complexity class is violated. The bench still shows the strategy the user selected.
- [x] **Already sorted + `--bench`** → print no operations, **but still print the bench** (disorder `0.00%`, 0 operations).
  Whoever passes `--bench` always gets information. In `execute`, the "already sorted" check skips only the sorting, not the bench.
- [x] **Shared `stack_utils.c`** → yes, written by **A** in phase 1, together with the operations.
  A knows the stack internals best after writing the operations. Starts with what the first algorithms need (e.g. position of the minimum, stack size checks); B asks A when a new helper is needed instead of writing a duplicate.
- [x] **Who is A and who is B** → **A** is the one writing the operations. **B** is the partner.
- [x] **Stack structure** → keep the singly linked list with only `top` (see the decisions table).
  `sa`, `pa`, `pb` are O(1); `ra` needs to reach the last node and `rra` the second-to-last, so both are O(n). A `bottom` pointer would make `ra` O(1) but **not** `rra` (you still need the second-to-last); only a doubly linked list fixes both, at the cost of maintaining `prev` everywhere.
- [x] **Quoted arguments (`"3 2 1"`, `"3 2" 1`)** → **postponed to phase 3.**
  The subject leaves argument handling to each group, but its own example `ARG="4 67 3"; ./push_swap $ARG` passes **one** argument in zsh (macOS default shell), so today it prints `Error` there. Idea: treat each `argv[i]` as a string that may contain several numbers separated by spaces. Two options: `ft_split` (must free the array on every path, including errors) or walking the string with a cursor (no `malloc`). Edge cases to decide: `"   "`, `"1  2"`, `" 1 2 "`, `"1 2" 1` (duplicate across arguments), `"--bench 1 2"`. The change must stay inside `parsing.c` so `main.c` and the header remain frozen.

---

## 4. Files and functions

### Folder layout

```
srcs/
├── main.c
├── parsing/    flags.c · parsing.c
├── stack/      stack.c · stack_utils.c
├── utils/      utils.c
├── ops/        ops_utils.c · ops_swap.c · ops_push.c · ops_rotate.c · ops_rrotate.c   (A)
├── analysis/   index.c · disorder.c · bench.c                                         (B)
└── sort/       dispatch.c · sort_small.c · sort_simple.c · sort_medium.c
                sort_complex.c · sort_adaptive.c                                       (shared)
includes/
└── push_swap.h
```

Every new file goes in its folder **and** in `SRCS` in the `Makefile` with its full path (e.g. `srcs/ops/ops_swap.c`). Move files with `git mv`, never plain `mv`, so git keeps their history.

Rules:
- **Max 5 functions per file** (Norm).
- Functions marked *(static)* are private to their file: no prototype in the header.
- Each sorting file has **one public function**; everything else in it is `static`.

### 4.1 Operations — the base of everything (owner: A, reviewed by B)

| File | Functions | Signatures | # |
|---|---|---|---|
| `ops_swap.c` | `swap` *(static)*, `sa`, `sb`, `ss` | `swap(t_stack *s)` · `sa/sb/ss(t_ps *p)` | 4 |
| `ops_push.c` | `push` *(static)*, `pa`, `pb` | `push(t_stack *dst, t_stack *src)` · `pa/pb(t_ps *p)` | 3 |
| `ops_rotate.c` | `rotate` *(static)*, `ra`, `rb`, `rr` | `rotate(t_stack *s)` · `ra/rb/rr(t_ps *p)` | 4 |
| `ops_rrotate.c` | `rrotate` *(static)*, `rra`, `rrb`, `rrr` | `rrotate(t_stack *s)` · `rra/rrb/rrr(t_ps *p)` | 4 |

Two levels:
- the **static** function only moves pointers on a stack and prints nothing;
- the **public** one calls it, then calls `log_op` **exactly once**.

So `ss` swaps both stacks, prints one line and only increments `ops[OP_SS]`.

Edge cases from the subject: swap/rotate do nothing with fewer than 2 elements; push does nothing if the source is empty. Remember to update `size` on both stacks when pushing.

Pitfalls with the singly linked list (only `top`):
- After `ra`, the node moved to the end **must** get `next = NULL`; after `rra`, the new last node (old second-to-last) too. Otherwise the list becomes a cycle → infinite loop or double free in `free_stack`.
- `size` must always be right: the algorithms rely on it (`ra` vs `rra`, chunk sizes…).
- If `sa` swaps values instead of nodes, swap `index` too.
- Reaching the last node will be needed in several places (e.g. `sort_small`): put that helper in `stack_utils.c` once.
- Defense: complexity classes are measured in **operations printed**; each rotation costs O(n) CPU time because of the list, which multiplies run time but not the operation count.

Order of work: `pb`, `pa`, `ra`, `rra` first and merged early (the algorithms use them most), then the rest. B reviews every line before the merge: both of us must be able to explain them in the defense.

### 4.2 Preparation

| File | Functions | What it does | Owner |
|---|---|---|---|
| `index.c` | `assign_index` + static helpers | Turns values into ranks 0 … n-1 | B |
| `disorder.c` | `compute_disorder`, `is_sorted` | Disorder = inverted pairs / total pairs (0 = sorted, 1 = reversed). Computed before any move, stored in `p->disorder` | B |
| `stack_utils.c` | shared helpers (position of the minimum…) | Used by several algorithms; one copy only | A |

### 4.3 Sorting

| File | Public function | Required class | Owner |
|---|---|---|---|
| `sort_small.c` | `sort_small(t_ps *p)` | 2, 3 and 5 elements | A |
| `sort_simple.c` | `sort_simple(t_ps *p)` | O(n²) | A |
| `sort_medium.c` | `sort_medium(t_ps *p)` | O(n√n) | B |
| `sort_complex.c` | `sort_complex(t_ps *p)` | O(n log n) | B |
| `sort_adaptive.c` | `sort_adaptive(t_ps *p)` | disorder < 0.2 → O(n) · 0.2–0.5 → O(n√n) · ≥ 0.5 → O(n log n) | Both |
| `dispatch.c` | `dispatch(t_ps *p)` | Reads `p->strategy` and calls the right sort | A |

Subject examples per class:
- **O(n²):** insertion, selection, bubble, min/max extraction
- **O(n√n):** chunk-based, block partition, bucket, range-based
- **O(n log n):** radix (LSD/MSD), merge sort with two stacks, quicksort with stack partition, heap sort

### 4.4 Output

| File | Functions | Prints (all on fd 2) | Owner |
|---|---|---|---|
| `bench.c` | `print_bench` + static helpers | Disorder as % with 2 decimals · strategy name and complexity class · total ops · count of each op (`sa sb ss pa pb ra rb rr rra rrb rrr`) | B |

Printing numbers without `printf` needs something like `ft_putnbr_fd`: either in `utils.c` (room for 2 more functions) or `static` in `bench.c`. `op_name` already gives the operation names in the right order.

### 4.5 Already existing files (do not reorganize)

| File | Functions |
|---|---|
| `srcs/main.c` | `free_all` *(static)*, `exit_with_error` *(static)*, `execute` *(static)*, `main` |
| `srcs/parsing/flags.c` | `is_strategy` *(static)*, `parse_flags` |
| `srcs/parsing/parsing.c` | `ft_atoi_safe`, `build_stack` |
| `srcs/stack/stack.c` | `new_node`, `stack_add_back`, `has_duplicate`, `free_stack` |
| `srcs/utils/utils.c` | `ft_bzero`, `ft_strcmp`, `ft_strlen` |
| `srcs/ops/ops_utils.c` | `op_name`, `log_op` |

---

## 5. Work split by phase

| Phase | Person A | Person B |
|---|---|---|
| **0 — together** (one session) | Close open decisions · header prototypes · stubs + `Makefile` · fill `execute` | ← same |
| **1** | The 4 `ops_*.c` files (all 11 operations) | `index.c`, `disorder.c`, `bench.c` |
| **2** | `sort_small.c`, `sort_simple.c`, `dispatch.c`, test script | `sort_medium.c`, `sort_complex.c` |
| **3 — together** | `sort_adaptive.c` · tuning with 100 / 500 numbers · `README.md` | ← same |

**Reviews:** B reviews the operations, A reviews index / disorder / bench, and each reviews the other's algorithms. Both of us must be able to explain **any** part during the defense.

**Balance note:** B gets the two hardest algorithms (medium and complex), A gets the operations plus small and simple. If we prefer that A also owns a big one, swap `sort_simple.c` and `sort_medium.c`.

### Phase checklists

**Phase 0**
- [x] Open decisions closed
- [x] `double disorder;` added to `t_ps`
- [ ] All prototypes in `push_swap.h`
- [ ] All stub files created and in `Makefile`, `make` compiles
- [ ] `execute` calls the full flow
- [ ] Norminette passes · pushed to `main`

**Phase 1**
- [x] A: `pb` · `pa` · `ra` · `rra` (merged first)
- [x] A: `stack_utils.c` (first shared helpers)
- [x] A: `sa` · `sb` · `ss` · `rb` · `rr` · `rrb` · `rrr`
- [ ] B: review of all operations
- [ ] B: `index.c` · `disorder.c` · `bench.c`
- [ ] A: review of index / disorder / bench

**Phase 2**
- [ ] A: `sort_small.c` (2, 3, 5) · `sort_simple.c` · `dispatch.c` · test script
- [ ] B: `sort_medium.c` · `sort_complex.c`
- [ ] Cross-review of all algorithms

**Phase 3**
- [ ] `sort_adaptive.c` with justified thresholds
- [x] Decide quoted arguments (`"3 2 1"`) — see [open decisions](#3-open-decisions); if accepted, change only `parsing.c` and update the decisions table
- [ ] Op counts checked for 100 and 500 numbers
- [ ] `README.md` complete (see [section 7](#7-subject-requirements-checklist))

---

## 6. Git workflow

- **One branch per task:** `feat/ops`, `feat/disorder`, `feat/sort-small`…
- **Pull before you start:** `git pull --rebase` every day before coding.
- **Merge early and often.** Small merges are easy to review; a week of changes is not.
- **Own your files.** After phase 0, `push_swap.h`, `Makefile` and `main.c` are frozen. If one needs a change, tell the other first and do it in a small separate commit.
- **Review each other's merges.** If you can't explain your partner's code, don't merge it yet. It will be asked in the defense.
- **Strategy strings:** copy the exact values from the comment above `t_ps`. A typo still compiles but silently never matches. Test each flag with `--bench`.
- **Before every push:** `make`, Norminette, and at least a quick run with the checker.

---

## 7. Subject requirements checklist

### Program
- [ ] Prints the shortest operation list it can, smallest number on top of `a` at the end
- [ ] Operations separated by `\n` only
- [ ] No arguments → prints nothing
- [ ] Errors → `Error\n` on stderr (non-integers, overflow, duplicates…)
- [ ] All four strategies work for any valid input, any size, any disorder
- [ ] `--adaptive` is the default
- [ ] No global variables
- [ ] Makefile: `NAME`, `all`, `clean`, `fclean`, `re`, `cc`, `-Wall -Wextra -Werror`, no relink
- [ ] Norminette passes on every file
- [ ] No leaks, no crashes (segfault, bus error, double free)

### `--bench` (stderr only, only when the flag is present)
- [ ] Disorder as % with two decimals
- [ ] Strategy name and its theoretical complexity class
- [ ] Total number of operations
- [ ] Count of each operation: `sa sb ss pa pb ra rb rr rra rrb rrr`

### `README.md` (mandatory)
- [ ] Logins of both students
- [ ] Clear description of each person's contributions
- [ ] Adaptive strategy: justification of the thresholds (0.2 / 0.5)
- [ ] Description of the internal technique used in each disorder range
- [ ] Complexity analysis (time and space upper bounds) in the push_swap operation model

---

## 8. Testing

Ideas for the test script (phase 2, A):

- **Run tests in bash, not zsh** (`#!/bin/bash` in the script). In zsh `$ARG` is not split into words, so `ARG="3 2 1"; ./push_swap $ARG` passes a single argument and prints `Error` while quoted arguments are not supported.
- Generate random inputs: `shuf -i 0-9999 -n 500`
- Verify correctness: `./push_swap $ARG | ./docs/checker_Mac $ARG` → must print `OK`
- Count operations: `./push_swap $ARG | wc -l`
- Run every strategy flag with every size (2, 3, 5, 100, 500)
- Test already sorted, reverse sorted and nearly sorted inputs (to exercise each adaptive range)
- Error cases: `1 1`, `1 a`, `2147483648`, `-2147483649`, `""`, `--foo 1`, `--simple --complex 1 2`
- Leaks: `leaks --atExit -- ./push_swap ...` (macOS) or `valgrind` (Linux)
