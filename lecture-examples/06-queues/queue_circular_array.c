/*
 * Lecture 6 - Queues
 * Queue implemented with a CIRCULAR array.
 * Succ() moves an index forward and wraps it back to 0 at the end.
 *
 * Fixed from the slides:
 *  - CreateQueue: declared "Queue q;" but used "Q", and a printf was missing
 *    its closing quote. It also continued after the errors; now it returns NULL.
 */
#include <stdio.h>
#include <stdlib.h>

#define MinQueueSize 5

struct QueueRecord {
    int Capacity;
    int Front;
    int Rear;
    int Size;
    int* Array;
};

typedef struct QueueRecord* Queue;

int IsEmpty(Queue Q) {
    return Q->Size == 0;
}

int IsFull(Queue Q) {
    return Q->Size == Q->Capacity;
}

void MakeEmpty(Queue Q) {
    Q->Size = 0;
    Q->Front = 1;
    Q->Rear = 0;
}

Queue CreateQueue(int MaxElements) {
    Queue Q;
    if (MaxElements < MinQueueSize) {
        printf("Queue size is too small\n");
        return NULL;
    }
    Q = (Queue)malloc(sizeof(struct QueueRecord));
    if (Q == NULL) {
        printf("Out of space\n");
        return NULL;
    }
    Q->Array = (int*)malloc(sizeof(int) * MaxElements);
    if (Q->Array == NULL) {
        printf("Out of space\n");
        free(Q);
        return NULL;
    }
    Q->Capacity = MaxElements;
    MakeEmpty(Q);
    return Q;
}

void DisposeQueue(Queue Q) {
    if (Q != NULL) {
        free(Q->Array);
        free(Q);
    }
}

/* next index, wrapping around to 0 */
int Succ(int Value, Queue Q) {
    if (++Value == Q->Capacity)
        Value = 0;
    return Value;
}

void Enqueue(int X, Queue Q) {
    if (IsFull(Q))
        printf("Full Queue\n");
    else {
        Q->Size++;
        Q->Rear = Succ(Q->Rear, Q);
        Q->Array[Q->Rear] = X;
    }
}

int Front(Queue Q) {
    if (!IsEmpty(Q))
        return Q->Array[Q->Front];
    printf("Empty Queue!\n");
    return 0;
}

void Dequeue(Queue Q) {
    if (IsEmpty(Q))
        printf("Empty Queue!\n");
    else {
        Q->Size--;
        Q->Front = Succ(Q->Front, Q);
    }
}

int FrontAndDequeue(Queue Q) {
    int X = 0;
    if (IsEmpty(Q))
        printf("Empty Queue!\n");
    else {
        Q->Size--;
        X = Q->Array[Q->Front];
        Q->Front = Succ(Q->Front, Q);
    }
    return X;
}

/* main() from the slides */
int main(void) {
    Queue q;
    int i;
    q = CreateQueue(12);
    for (i = 0; i < 10; i++)
        Enqueue(i, q);
    while (!IsEmpty(q)) {
        printf("%d\n", Front(q)); /* 0 1 2 ... 9 (FIFO) */
        Dequeue(q);
    }
    DisposeQueue(q);
    return 0;
}
