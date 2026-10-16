# Data Structures in C

Everything I wrote while studying **Data Structures and Algorithms (COMP2421)** at **Birzeit University**: course projects, lecture examples, and solved problems, all in C.

Each file is **self-contained**: it has the structure definition, the code, and a small `main()` that shows the result, so you can compile and run any file on its own.

![C](https://img.shields.io/badge/language-C-00599C?logo=c&logoColor=white)
![Projects](https://img.shields.io/badge/projects-3-orange)
![Lecture examples](https://img.shields.io/badge/lecture_examples-18-blue)
![Problems](https://img.shields.io/badge/problems-23-brightgreen)

---

## 📂 Structure

```
data-structures-in-c/
├── certificates/       Coursera certificate
├── projects/           3 course projects
├── lecture-examples/   code from the lecture slides, by lecture
├── linked-lists/       6 problems
├── stacks-queues/      3 problems
├── trees/             13 problems
└── heaps/              1 problem
```

---

## 🎓 Certificate

**Data Structures in C**, University of Michigan on Coursera (Sep 2026):
[PDF](certificates/coursera-data-structures-in-c.pdf) · [Verify](https://coursera.org/verify/3QDQB877TGOU)

---

## 🚀 Projects

| # | Project | Data structures & algorithms |
|---|---|---|
| 1 | [Task Manager](projects/1-task-manager-linked-list-stack) | Linked list, Stack (perform / undo) |
| 2 | [Task Manager with BST](projects/2-task-manager-bst) | Binary Search Tree that can be rebuilt by ID, name, date or duration |
| 3 | [Palestinian Road Network](projects/3-road-network-mst) | Graph, Hash table, Min-heap, Prim's & Kruskal's MST, Disjoint set, Quick sort |

---

## 📖 Lecture Examples

Code examples from the course slides, organized by lecture. Each one has a `main()` so you can run it, and any mistakes on the slides are fixed and marked in a comment at the top of the file.

| Lecture | Files |
|---|---|
| 01 Recursion | [count to ten](lecture-examples/01-recursion/count_to_ten.c), [sum of n numbers](lecture-examples/01-recursion/sum_natural_numbers.c), [multiply, factorial, fibonacci](lecture-examples/01-recursion/multiply_factorial_fibonacci.c), [Towers of Hanoi](lecture-examples/01-recursion/towers_of_hanoi.c) |
| 02 Time Analysis | [ArrayMax & log2](lecture-examples/02-time-analysis/array_max_and_log.c), [loop complexity examples](lecture-examples/02-time-analysis/loop_complexity_examples.c), [isPrime, power, binary search](lecture-examples/02-time-analysis/is_prime_power_binary_search.c) |
| 03 Linked List | [linked list ADT](lecture-examples/03-linked-list/linked_list.c) |
| 04 Cursor Linked List | [cursor linked list](lecture-examples/04-cursor-linked-list/cursor_linked_list.c) |
| 05 Stacks | [stack with linked list](lecture-examples/05-stacks/stack_linked_list.c) |
| 06 Queues | [queue with circular array](lecture-examples/06-queues/queue_circular_array.c) |
| 08 Binary Search Trees | [BST ADT](lecture-examples/08-binary-search-trees/bst.c) |
| 13 Hashing Strings | [3 string hash functions](lecture-examples/13-hashing-strings/string_hash_functions.c) |
| 15 Sorting | [insertion, selection, merge, shell sort](lecture-examples/15-sorting/sorting_algorithms.c) |
| 16 Graphs | [Bellman-Ford](lecture-examples/16-graphs/bellman_ford.c) (written in C from the slide's pseudocode) |
| 18 Dynamic Programming | [Fibonacci 4 ways](lecture-examples/18-dynamic-programming/fibonacci_four_ways.c), [binomial coefficient](lecture-examples/18-dynamic-programming/binomial_coefficient.c), [longest increasing subsequence](lecture-examples/18-dynamic-programming/longest_increasing_subsequence.c) |

> The lectures on Trees, AVL, Splay Trees, B-Trees, Hashing, Heaps and MST have no C code on the slides, so they are not in this folder. Heaps, hashing and MST are used in the projects and problems.

---

## 🧩 Solved Problems

### 🔗 Linked Lists

| Problem | File | Idea |
|---|---|---|
| Find the middle node | [find_middle.c](linked-lists/find_middle.c) | Slow and fast pointers |
| Even intersection of two sorted lists | [intersection_even.c](linked-lists/intersection_even.c) | Walk both lists like in merge |
| Union of two sorted lists | [union_sorted_lists.c](linked-lists/union_sorted_lists.c) | Merge step of merge sort |
| Duplicate multiples of 5 or 7 | [duplicate_multiples_of_5_or_7.c](linked-lists/duplicate_multiples_of_5_or_7.c) | Recursion |
| Remove consecutive duplicates | [remove_consecutive_duplicates.c](linked-lists/remove_consecutive_duplicates.c) | Recursion |
| Reversed copy of a doubly linked list | [reverse_doubly_linked_list.c](linked-lists/reverse_doubly_linked_list.c) | Insert at the front |

### 📚 Stacks & Queues

| Problem | File | Idea |
|---|---|---|
| Valid parentheses `()[]{}` | [valid_parentheses.c](stacks-queues/valid_parentheses.c) | Stack |
| Palindrome check | [is_palindrome.c](stacks-queues/is_palindrome.c) | Stack (LIFO) vs Queue (FIFO) |
| Slice a stack from i to j | [slice_stack.c](stacks-queues/slice_stack.c) | Temporary stack |

### 🌳 Trees

| Problem | File | Idea |
|---|---|---|
| Height of a tree | [height_of_tree.c](trees/height_of_tree.c) | Recursion |
| Count leaves | [count_leaves.c](trees/count_leaves.c) | Recursion |
| Count odd leaves | [count_odd_leaves.c](trees/count_odd_leaves.c) | Recursion |
| Sum of leaves | [sum_of_leaves.c](trees/sum_of_leaves.c) | Recursion |
| Leaves sum = internal nodes sum? | [equal_sum_leaves_internal.c](trees/equal_sum_leaves_internal.c) | Two recursive sums |
| Is it a Sum Tree? | [is_sum_tree.c](trees/is_sum_tree.c) | Recursion |
| Mirror a tree | [mirror_tree.c](trees/mirror_tree.c) | Swap children |
| Print all root-to-leaf paths | [print_root_to_leaf_paths.c](trees/print_root_to_leaf_paths.c) | Path array + recursion |
| Print BST from largest to smallest | [print_bst_descending.c](trees/print_bst_descending.c) | Reverse in-order |
| Count BST nodes greater than X | [count_nodes_greater_than_x.c](trees/count_nodes_greater_than_x.c) | BST property |
| Sum of the K smallest in a BST | [sum_k_smallest_bst.c](trees/sum_k_smallest_bst.c) | In-order + early stop |
| Lowest common ancestor in a BST | [lowest_common_ancestor_bst.c](trees/lowest_common_ancestor_bst.c) | BST property |
| Count subtrees with all values in [n, m] | [count_subtrees_in_range.c](trees/count_subtrees_in_range.c) | Post-order |

### ⛰️ Heaps

| Problem | File | Idea |
|---|---|---|
| Convert a min-heap to a max-heap | [min_heap_to_max_heap.c](heaps/min_heap_to_max_heap.c) | Bottom-up heapify, O(n) |

---

## ▶️ How to run

You need a C compiler such as `gcc`:

```bash
gcc trees/height_of_tree.c -o height
./height
```

On Windows:

```bash
gcc trees\height_of_tree.c -o height.exe
height.exe
```

## 📝 Notes

- The linked lists, stacks and queues use a **header (dummy) node**, like in the course lectures.
- The arrays in the heap use **1-based indexing**: `A[1]` is the root.
