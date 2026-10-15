# Data Structures in C

Solutions to Data Structures problems in C, written while studying the course at **Birzeit University**.

Each file is **self-contained**: it has the structure definition, the solution, and a small `main()` that shows the result, so you can compile and run any file on its own.

![C](https://img.shields.io/badge/language-C-00599C?logo=c&logoColor=white)
![Problems](https://img.shields.io/badge/problems-23-brightgreen)

---

## 📂 Structure

```
data-structures-in-c/
├── linked-lists/     6 problems
├── stacks-queues/    3 problems
├── trees/           13 problems
└── heaps/            1 problem
```

## 🔗 Linked Lists

| Problem | File | Idea |
|---|---|---|
| Find the middle node | [find_middle.c](linked-lists/find_middle.c) | Slow and fast pointers |
| Even intersection of two sorted lists | [intersection_even.c](linked-lists/intersection_even.c) | Walk both lists like in merge |
| Union of two sorted lists | [union_sorted_lists.c](linked-lists/union_sorted_lists.c) | Merge step of merge sort |
| Duplicate multiples of 5 or 7 | [duplicate_multiples_of_5_or_7.c](linked-lists/duplicate_multiples_of_5_or_7.c) | Recursion |
| Remove consecutive duplicates | [remove_consecutive_duplicates.c](linked-lists/remove_consecutive_duplicates.c) | Recursion |
| Reversed copy of a doubly linked list | [reverse_doubly_linked_list.c](linked-lists/reverse_doubly_linked_list.c) | Insert at the front |

## 📚 Stacks & Queues

| Problem | File | Idea |
|---|---|---|
| Valid parentheses `()[]{}` | [valid_parentheses.c](stacks-queues/valid_parentheses.c) | Stack |
| Palindrome check | [is_palindrome.c](stacks-queues/is_palindrome.c) | Stack (LIFO) vs Queue (FIFO) |
| Slice a stack from i to j | [slice_stack.c](stacks-queues/slice_stack.c) | Temporary stack |

## 🌳 Trees

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

## ⛰️ Heaps

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
