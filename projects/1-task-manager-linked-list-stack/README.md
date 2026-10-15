# 📝 Project 1: Task Management System (Linked List + Stack)

A console task manager written in C for the Data Structures course (COMP2421) at Birzeit University.

## Data Structures Used

| Structure | Used for |
|---|---|
| **Singly linked list** (with header node) | Unperformed tasks |
| **Stack** (linked list) | Performed tasks, so the **last** one can be undone |
| **Singly linked list** | Undone tasks (history of undo operations) |

## Features

1. Load tasks from `tasks.txt`
2. Add a new task
3. Delete a task by ID
4. Search for a task by ID or name (in unperformed and performed tasks)
5. View unperformed tasks
6. Perform a task (moves it from the list to the stack)
7. Undo the last performed task (pops it from the stack)
8. View performed tasks in the order they were completed
9. Generate a summary report in `Report.txt`

## Input File Format

`tasks.txt`, one task per line:

```
ID#Name#Date#Duration
101#Study Data Structures#20/10/2026#3.5
```

## How to Run

```bash
gcc main.c -o tasks
./tasks
```

Keep `tasks.txt` in the same folder as the program.
