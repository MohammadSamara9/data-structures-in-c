/* Mohammed Samara */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#define INF INT_MAX

typedef struct Node {
    int dest;
    int weight;
    struct Node* next;
} Node;
typedef Node* NodePtr;

typedef struct City {
    char name[100];
    NodePtr adjList;
} City;
typedef City* CityPtr;

typedef struct Edge {
    int src;
    int dest;
    int weight;
} Edge;
typedef Edge* EdgePtr;

typedef struct HashEntry {
    char name[100];
    int index;
} HashEntry;

typedef struct HeapNode {
    int vertex;
    int key;
} HeapNode;
typedef HeapNode* HeapNodePtr;

typedef struct MinHeap {
    int size;
    int capacity;
    int* pos;
    HeapNodePtr* array;
} MinHeap;
typedef MinHeap* MinHeapPtr;

typedef struct MSTResult {
    int cost;
    double time;
} MSTResult;

CityPtr* cities = NULL;
int cityCount = 0;
int cityCap = 50;

EdgePtr edges = NULL;
int edgeCount = 0;
int edgeCap = 200;

HashEntry* hashTable = NULL;
int currentCount = 0;
int hashTableSize = 101;

int hash(char* key, int size);
int quadratic(int pos, int i, int size);
int findPos(char* name);
void initHash();
void resizeHashTable();
void addToHash(char* name, int index);
int findCity(char* name);
void addCity(char* name);
void addEdge(char* name1, char* name2, int weight);
void loadGraph();
void freeAll();
void showCities();
HeapNodePtr createHeapNode(int v, int k);
MinHeapPtr createHeap(int cap);
void swapNodes(HeapNodePtr* a, HeapNodePtr* b);
void heapify(MinHeapPtr h, int i);
HeapNodePtr extractMin(MinHeapPtr h);
void decreaseKey(MinHeapPtr h, int v, int key);
int inHeap(MinHeapPtr h, int v);
void primMST(int start, MSTResult* res);
void swapEdges(EdgePtr a, EdgePtr b);
int partition(EdgePtr edges, int low, int high);
void quickSortEdges(EdgePtr edges, int low, int high);
int findSet(int i, int* parent);
void unionSets(int x, int y, int* parent, int* rank);
void kruskalMST(MSTResult* res);
void compare(MSTResult prim, MSTResult kruskal);

int main(){
    printf("Palestinian Road Network System\n\n");
    printf("                              ***                \n");
    printf("                            ****                 \n");
    printf("                        *********                \n");
    printf("                      **********                 \n");
    printf("                      *********                  \n");
    printf("                    ************                 \n");
    printf("                    *************                \n");
    printf("                   *************                 \n");
    printf("                   ************                  \n");
    printf("                 **************                  \n");
    printf("                ***************                  \n");
    printf("              ****************                   \n");
    printf("             *****************                   \n");
    printf("            ******************                   \n");
    printf("            *****************                    \n");
    printf("             *****************                   \n");
    printf("              **************                     \n");
    printf("               *************                     \n");
    printf("                **********                       \n");
    printf("                 ********                        \n");
    printf("                  *******                        \n");
    printf("                   ******                        \n");
    printf("                    ****                         \n");
    printf("                     ***                         \n");
    printf("                      *                          \n");
    int choice;
    char name[100];
    MSTResult primRes, kruskalRes;
    int primDone=0,kruskalDone=0;
    int loaded=0;
    do {
        printf("\nMenu:\n");
        printf("1. Load cities\n");
        printf("2. Apply Prim's algorithm for a road network with a minimal cost.\n");
        printf("3. Apply Kruskal's algorithm for a road network with a minimal cost.\n");
        printf("4. Compare algorithms\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d",&choice);
        getchar();
        switch(choice){
            case 1:
                if(!loaded) {
                    loadGraph();
                    loaded = 1;
                }else{
                    printf("Graph already loaded.\n");
                }
                primDone=kruskalDone=0;
                break;
            case 2:
                if(!loaded) {
                    printf("Please load graph first.\n");
                    break;
                }
                showCities();
                printf("Enter start city name: ");
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = '\0';
                int idx=findCity(name);
                if(idx==-1) {
                    printf("City not found.\n");
                }else{
                    primMST(idx,&primRes);
                    primDone=1;
                }
                break;
            case 3:
                if (!loaded) {
                    printf("Please load graph first.\n");
                    break;
                }
                kruskalMST(&kruskalRes);
                kruskalDone=1;
                break;
            case 4:
                if(!loaded){
                    printf("Please load graph first.\n");
                }else if(!primDone||!kruskalDone){
                    printf("Please run both algorithms first.\n");
                }else{
                    compare(primRes,kruskalRes);
                }
                break;
            case 5:
                freeAll();
                printf("Thank you for using our system.\nGoodbye!\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while(choice!=5);
    return 0;
}

int hash(char* key,int size){
    int hashValue = 0;
    while (*key != '\0') {
        hashValue =( (hashValue << 5) + *key++)%size;
        }
    return hashValue;
}

int quadratic(int pos, int i, int size){
    return (pos + i*i) % size;
}

int findPos(char* name){
    int h = hash(name, hashTableSize);
    if (hashTable[h].index == -1 || strcmp(hashTable[h].name, name) == 0) {
        return h;
    }
    for (int i = 1; i < hashTableSize; i++){
        int pos=quadratic(h, i,hashTableSize);
        if (hashTable[pos].index==-1) {
            return pos;
        }
        else if (strcmp(hashTable[pos].name,name)== 0) {
            return pos;
        }
    }
    return -1;
}

void initHash(){
    hashTable = (HashEntry*)malloc(hashTableSize * sizeof(HashEntry));
    if (!hashTable) {
        printf("Memory is full\n");
        exit(1);
    }
    for (int i = 0; i < hashTableSize; i++) {
        hashTable[i].index = -1;
        hashTable[i].name[0] = '\0';
    }
    currentCount = 0;
}

void resizeHashTable(){
    int oldSize = hashTableSize;
    HashEntry* oldTable = hashTable;

    hashTableSize *= 2;
    currentCount = 0;
    hashTable = (HashEntry*)malloc(hashTableSize * sizeof(HashEntry));
    if (!hashTable) {
        printf("Failed to resize hash table\n");
        exit(1);
    }
    for (int i = 0; i < hashTableSize; i++) {
        hashTable[i].index = -1;
        hashTable[i].name[0] = '\0';
    }
    for (int i = 0; i < oldSize; i++) {
        if (oldTable[i].index != -1) {
            addToHash(oldTable[i].name, oldTable[i].index);
        }
    }
    free(oldTable);
}

void addToHash(char* name, int index){
    if ((float)currentCount / hashTableSize >= 0.7) {
        resizeHashTable();
    }
    int pos = findPos(name);
    if (pos == -1) {
        printf( "Hash table is full\n");
        exit(1);
    }

    if (hashTable[pos].index == -1){
        currentCount++;
    }
    strcpy(hashTable[pos].name, name);
    hashTable[pos].index = index;
}

int findCity(char* name){
    int pos = findPos(name);
    if (pos == -1 || hashTable[pos].index == -1) {
        return -1;
    } else {
        return hashTable[pos].index;
    }
}

void addCity(char* name){
    if (cityCount >= cityCap) {
        int newCap = cityCap * 2;
                CityPtr* newCities = (CityPtr*)malloc(newCap * sizeof(CityPtr));
        if(!newCities){
            printf("Memory out of space!\n");
            exit(1);
        }
        if(cities!=NULL){
            for (int i = 0; i < cityCount; i++) {
                newCities[i] = cities[i];
            }
            free(cities);
        }
        cities = newCities;
        for (int i = cityCap; i < newCap; i++) {
            cities[i] = NULL;
        }
        cityCap=newCap;
    }
    cities[cityCount]=(CityPtr)malloc(sizeof(City));
    if (!cities[cityCount]) {
        printf("Memory out of space\n");
        exit(1);
    }
    strcpy(cities[cityCount]->name, name);
    cities[cityCount]->adjList = NULL;
    addToHash(name,cityCount);
    cityCount++;
}

void addEdge(char* name1, char* name2, int weight){
    int u = findCity(name1);
    if (u == -1) {
        addCity(name1);
        u = cityCount - 1;
    }
    int v = findCity(name2);
    if (v == -1) {
        addCity(name2);
        v = cityCount - 1;
    }
    NodePtr curr = cities[u]->adjList;
    while (curr != NULL) {
        if (curr->dest == v) {
            return;
        }
        curr = curr->next;
    }
    NodePtr node1=(NodePtr)malloc(sizeof(Node));
    if (!node1) {
        printf("Memory out of space\n");
        exit(1);
    }
    node1->dest = v;
    node1->weight = weight;
    node1->next = cities[u]->adjList;
    cities[u]->adjList = node1;

    NodePtr node2=(NodePtr)malloc(sizeof(Node));
    if (!node2) {
        printf("Memory out of space\n");
        exit(1);
    }
    node2->dest = u;
    node2->weight = weight;
    node2->next = cities[v]->adjList;
    cities[v]->adjList = node2;

     if (edgeCount >= edgeCap) {
        int newCap = edgeCap * 2;
        EdgePtr newEdges = (EdgePtr)malloc(newCap * sizeof(Edge));
        if (!newEdges) {
            printf("Memory out of space!\n");
            exit(1);
        }
        if (edges != NULL) {
            for (int i = 0; i < edgeCount; i++) {
                newEdges[i] = edges[i];
            }
            free(edges);
        }
        edges = newEdges;
        edgeCap = newCap;
    }
    int tempu = u;
    int tempv = v;
    if (tempu > tempv){
        int temp = tempu;
        tempu = tempv;
        tempv = temp;
    }
    edges[edgeCount++] = (Edge){tempu, tempv, weight};
}

void loadGraph(){
    FILE* file = fopen("cities.txt", "r");
    if (!file) {
        printf("Failed to open the file");
        return;
    }
    freeAll();
    cities=(CityPtr*)malloc(cityCap * sizeof(CityPtr));
    if (!cities) {
        printf("Memory out of space!\n");
        exit(1);
    }
    for (int i=0;i< cityCap;i++) {
        cities[i]=NULL;
    }

    edges=(EdgePtr)malloc(edgeCap * sizeof(Edge));
    if (!edges) {
        printf("Memory out of space!!\n");
        exit(1);
    }
    initHash();
    char line[250];
    char name1[100], name2[100];
    int weight;
    char* token;
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';

        char* city1 = strtok(line, "#");
        char* city2 = strtok(NULL, "#");
        token = strtok(NULL, "#");
        if (city1 == NULL || city2 == NULL || token == NULL)
            continue; /* skip empty or broken lines */
        strncpy(name1, city1, sizeof(name1) - 1);
        name1[sizeof(name1) - 1] = '\0';
        strncpy(name2, city2, sizeof(name2) - 1);
        name2[sizeof(name2) - 1] = '\0';
        weight = atoi(token);
        addEdge(name1, name2, weight);
    }
    fclose(file);
    printf("Graph loaded. Cities: %d, Edges: %d\n", cityCount, edgeCount);
}

void freeAll(){
    for (int i = 0; i < cityCount; i++) {
        NodePtr node = cities[i]->adjList;
        while (node) {
            NodePtr temp = node;
            node = node->next;
            free(temp);
        }
        free(cities[i]);
    }
    free(cities);
    cities = NULL;
    cityCount = 0;
    cityCap = 50;

    free(edges);
    edges = NULL;
    edgeCount = 0;
    edgeCap = 200;

    free(hashTable);
    hashTable = NULL;
    hashTableSize = 101;
}

void showCities(){
    printf("\nAvailable cities:\n");
    for (int i = 0; i < cityCount; i++) {
        printf("%d. %s\n", i+1, cities[i]->name);
    }
}

HeapNodePtr createHeapNode(int v, int k){
    HeapNodePtr node = (HeapNodePtr)malloc(sizeof(HeapNode));
    if (!node) {
        printf("Memory out of space!\n");
        exit(1);
    }
    node->vertex = v;
    node->key = k;
    return node;
}

MinHeapPtr createHeap(int cap){
    MinHeapPtr h = (MinHeapPtr)malloc(sizeof(MinHeap));
    if (!h) {
        printf("Memory out of space!\n");
        exit(1);
    }
    h->size = 0;
    h->capacity = cap;
    h->pos = (int*)malloc(cap * sizeof(int));
    h->array = (HeapNodePtr*)malloc(cap * sizeof(HeapNodePtr));
    if (!h->pos || !h->array) {
        printf("Memory out of space!\n");
        exit(1);
    }
    return h;
}

void swapNodes(HeapNodePtr* a, HeapNodePtr* b){
    HeapNodePtr t =*a;
    *a =*b;
    *b =t;
}

void heapify(MinHeapPtr h, int i){
    int smallest=i;
    int left=2*i+1;
    int right=2*i+2;

    if (left < h->size && h->array[left]->key < h->array[smallest]->key)
        smallest = left;

    if (right < h->size && h->array[right]->key < h->array[smallest]->key)
        smallest = right;

    if (smallest != i) {
        h->pos[h->array[smallest]->vertex] = i;
        h->pos[h->array[i]->vertex] = smallest;
        swapNodes(&h->array[smallest], &h->array[i]);
        heapify(h, smallest);
    }
}

HeapNodePtr extractMin(MinHeapPtr h){
    if (h->size == 0) return NULL;
    HeapNodePtr root = h->array[0];
    HeapNodePtr last = h->array[h->size-1];
    h->array[0] = last;
    h->pos[root->vertex] = h->size-1;
    h->pos[last->vertex] = 0;
    h->size--;
    heapify(h, 0);
    return root;
}

void decreaseKey(MinHeapPtr h, int v,int key){
    int i = h->pos[v];
    h->array[i]->key = key;

    while (i && h->array[i]->key < h->array[(i-1)/2]->key) {
        h->pos[h->array[i]->vertex] = (i-1)/2;
        h->pos[h->array[(i-1)/2]->vertex] = i;
        swapNodes(&h->array[i], &h->array[(i-1)/2]);
        i = (i-1)/2;
    }
}

int inHeap(MinHeapPtr h, int v){
    return h->pos[v] < h->size;
}

void primMST(int start, MSTResult* res){
    if (!res) return;
    res->cost = 0;
    res->time = 0.0;

    if (cityCount == 0) {
        printf("No graph loaded.\n");
        return;
    }
    if (start < 0 || start >= cityCount) {
        printf("Invalid start city.\n");
        return;
    }

    int* parent = (int*)malloc(cityCount * sizeof(int));
    int* key = (int*)malloc(cityCount * sizeof(int));
    HeapNodePtr* nodes = (HeapNodePtr*)malloc(cityCount * sizeof(HeapNodePtr));
    if (!parent || !key || !nodes) {
        printf("Memory out of space!\n");
        exit(1);
    }

    MinHeapPtr h=createHeap(cityCount);
    for (int v = 0; v < cityCount; v++) {
        parent[v]= -1;
        key[v] =INF;
        nodes[v]=createHeapNode(v,key[v]);
        h->array[v]=nodes[v];
        h->pos[v] = v;
    }

    key[start] = 0;
    decreaseKey(h,start,key[start]);
    h->size=cityCount;
    int mstEdges = 0;
    clock_t startTime = clock();

    printf("\nPrim's MST:\n");
    while (h->size > 0 && mstEdges < cityCount-1) {
        HeapNodePtr min = extractMin(h);
        int u=min->vertex;
        if (key[u]==INF) break;

        if (parent[u]!=-1) {
            printf("%s <--> %s (%d)\n", cities[parent[u]]->name, cities[u]->name, key[u]);
            res->cost += key[u];
            mstEdges++;
        }

        NodePtr node = cities[u]->adjList;
        while (node) {
            int v = node->dest;
            if (inHeap(h, v) && node->weight < key[v]) {
                key[v] = node->weight;
                parent[v] = u;
                decreaseKey(h, v, key[v]);
            }
            node = node->next;
        }
    }

    res->time = (double)(clock() - startTime) / CLOCKS_PER_SEC;
    printf("Total cost: %d\n", res->cost);
    printf("Time: %.6f seconds\n", res->time);

    free(parent);
    free(key);
    free(h->pos);
    free(h->array);
    for (int i = 0; i < cityCount; i++) free(nodes[i]);
    free(nodes);
    free(h);
}

void swapEdges(EdgePtr a, EdgePtr b){
    Edge temp = *a;
    *a = *b;
    *b = temp;
}

int partition(EdgePtr edges, int low, int high){
    int pivot = edges[high].weight;
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (edges[j].weight <= pivot) {
            i++;
            swapEdges(&edges[i], &edges[j]);
        }
    }
    swapEdges(&edges[i + 1], &edges[high]);
    return (i + 1);
}

void quickSortEdges(EdgePtr edges, int low, int high){
    if (low < high) {
        int pi = partition(edges, low, high);
        quickSortEdges(edges, low, pi - 1);
        quickSortEdges(edges, pi + 1, high);
    }
}

int findSet(int i, int* parent){
    if (parent[i] != i)
        parent[i] = findSet(parent[i], parent);
    return parent[i];
}

void unionSets(int x, int y, int* parent, int* rank){
    int xroot = findSet(x, parent);
    int yroot = findSet(y, parent);
    if (xroot == yroot) return;

    if (rank[xroot] < rank[yroot]) {
        parent[xroot] = yroot;
    } else {
        parent[yroot] = xroot;
        if (rank[xroot] == rank[yroot])
            rank[yroot]++;
    }
}

void kruskalMST(MSTResult* res){
    if (!res) return;
    res->cost = 0;
    res->time = 0.0;

    if (cityCount == 0) {
        printf("No graph loaded.\n");
        return;
    }

    int* parent = (int*)malloc(cityCount * sizeof(int));
    int* rank = (int*)malloc(cityCount * sizeof(int));
    if (!parent || !rank) {
        printf("Memory out of space!\n");
        exit(1);
    }
    for (int i = 0; i < cityCount; i++) {
        rank[i] = 0;
    }
    for (int i = 0; i < cityCount; i++)
        parent[i] = i;
    quickSortEdges(edges, 0, edgeCount - 1);
    int mstEdges = 0;
    clock_t startTime = clock();
    printf("\nKruskal's MST:\n");
    for (int i = 0; i < edgeCount && mstEdges < cityCount - 1; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int w = edges[i].weight;
        if (findSet(u, parent) != findSet(v, parent)) {
            printf("%s <--> %s (%d)\n", cities[u]->name, cities[v]->name, w);
            res->cost += w;
            unionSets(u, v, parent, rank);
            mstEdges++;
        }
    }
    res->time = (double)(clock() - startTime) / CLOCKS_PER_SEC;
    printf("Total cost: %d\n", res->cost);
    printf("Time: %.6f seconds\n", res->time);
    free(parent);
    free(rank);
}

void compare(MSTResult prim, MSTResult kruskal){
    printf("\nComparison:\n");
    printf("--------------------------------\n");
    printf("| Method   | Cost | Time (s)    |\n");
    printf("--------------------------------\n");
    printf("| Prim     | %-4d | %.6f    |\n", prim.cost, prim.time);
    printf("| Kruskal  | %-4d | %.6f    |\n", kruskal.cost, kruskal.time);
    printf("--------------------------------\n");

    printf("\nTime Comparison:\n");
    if (prim.time < kruskal.time)
        printf("Prim's was faster by %.6f seconds\n", kruskal.time - prim.time);
    else if (kruskal.time < prim.time)
        printf("Kruskal's was faster by %.6f seconds\n", prim.time - kruskal.time);
    else
        printf("Both algorithms took same time\n");

    printf("\nCost Comparison:\n");
    if (prim.cost < kruskal.cost)
        printf("Prim's had a lower cost by %d\n", kruskal.cost - prim.cost);
    else if (kruskal.cost < prim.cost)
        printf("Kruskal's had a lower cost by %d\n", prim.cost - kruskal.cost);
    else
        printf("Both algorithms found the same MST cost\n");
    printf("--------------------------------\n");
}
