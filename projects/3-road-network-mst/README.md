# 🛣️ Project 3: Palestinian Road Network (Minimum Spanning Tree)

Finds the cheapest road network that connects all the cities, using **Prim's** and **Kruskal's** algorithms, then compares them. Written in C for the Data Structures course (COMP2421) at Birzeit University.

## Data Structures & Algorithms Used

| Part | Implementation |
|---|---|
| Graph | Adjacency list (undirected, weighted) |
| City name → index | **Hash table** with quadratic probing, resized when load factor ≥ 0.7 |
| Prim's algorithm | **Min-heap** with `decreaseKey` and a position array |
| Kruskal's algorithm | Edges sorted with **Quick Sort** + **Disjoint Set** (union by rank, path compression) |
| Timing | `clock()` to compare the running time of both algorithms |

## Features

1. Load cities and roads from `cities.txt`
2. Run Prim's algorithm from a start city you choose
3. Run Kruskal's algorithm
4. Compare both: total cost and running time

## Input File Format

`cities.txt`, one road per line:

```
City1#City2#Cost
Ramallah#Jerusalem#16
```

The included `cities.txt` is sample data for testing.

## Example Output

```
Kruskal's MST:
Jerusalem <--> Bethlehem (10)
Ramallah <--> Jerusalem (16)
Tulkarm <--> Qalqilya (18)
...
Total cost: 220
```

## How to Run

```bash
gcc main.c -o roads
./roads
```

Keep `cities.txt` in the same folder as the program.
