/*
 * Lecture 4 - Cursor Linked List
 * A linked list built inside an ARRAY instead of using malloc/free.
 * "Pointers" are array indexes, and index 0 is the head of the FREE list.
 *
 *   CursorSpace[0].Next -> first free slot
 *   A list L is the index of its header slot. Next == 0 means "NULL".
 *
 * Fixed from the slides:
 *  - The slides mix CURSOR_SPACE/CursorSpace, element/Element, next/Next,
 *    and SpaceSize was never defined. One spelling is used here.
 *  - CursorAlloc: "return;" in a function that returns a Position, and the
 *    "out of space" check happened AFTER using slot P. Fixed both.
 *  - MakeEmpty: after DeleteList(L) the slide allocated a NEW header, so the
 *    old header slot was never freed. Now the old header is reused.
 */
#include <stdio.h>

#define SpaceSize 11

typedef int List;
typedef int Position;

struct node {
    int Element;
    int Next;
};

struct node CursorSpace[SpaceSize];

void InitializeCursorSpace(void) {
    int i;
    for (i = 0; i < SpaceSize - 1; i++)
        CursorSpace[i].Next = i + 1;
    CursorSpace[SpaceSize - 1].Next = 0;
}

/* Takes the first slot from the free list */
Position CursorAlloc(void) {
    Position P;
    /* get the position of the first position in the free list */
    P = CursorSpace[0].Next;
    if (P == 0) {
        printf("Out of space!\n");
        return 0;
    }
    CursorSpace[0].Next = CursorSpace[P].Next;
    return P;
}

/* Gives slot P back to the free list */
void CursorFree(Position P) {
    CursorSpace[P].Next = CursorSpace[0].Next;
    CursorSpace[0].Next = P;
}

List CursorList(void) {
    List L = CursorAlloc();
    CursorSpace[L].Next = 0;
    return L;
}

/* returns true if the list is empty */
int IsEmpty(List L) {
    return CursorSpace[L].Next == 0; /* header refers to zero */
}

/* Return true if P is the last position in list L */
/* Parameter L is unused in this implementation */
int IsLast(Position P, List L) {
    (void)L;
    return CursorSpace[P].Next == 0;
}

void DeleteList(List L) {
    Position P, Tmp;
    P = CursorSpace[L].Next; /* Header assumed */
    CursorSpace[L].Next = 0;
    while (P != 0) {
        Tmp = CursorSpace[P].Next;
        CursorFree(P);
        P = Tmp;
    }
}

/* empties the list that is sent here (the header of the list) */
List MakeEmpty(List L) {
    if (L)
        DeleteList(L);
    else
        L = CursorAlloc();
    if (L == 0)
        printf("Out of memory!\n");
    CursorSpace[L].Next = 0;
    return L;
}

/* Inserts X at the END of the list */
void Insert(int X, List L) {
    Position TmpCell, P = L;
    TmpCell = CursorAlloc(); /* takes a free slot from the array */
    if (TmpCell == 0)
        return;
    while (P && CursorSpace[P].Next != 0)
        P = CursorSpace[P].Next;
    CursorSpace[TmpCell].Element = X;
    CursorSpace[TmpCell].Next = CursorSpace[P].Next;
    CursorSpace[P].Next = TmpCell;
}

/* Return Position of X in L; 0 if not found */
Position Find(int X, List L) {
    Position P;
    P = CursorSpace[L].Next;
    while (P && CursorSpace[P].Element != X)
        P = CursorSpace[P].Next;
    return P;
}

/* If X is not found, then Next field of returned value is 0 */
Position FindPrevious(int X, List L) {
    Position P;
    P = L;
    while (CursorSpace[P].Next &&
           CursorSpace[CursorSpace[P].Next].Element != X)
        P = CursorSpace[P].Next;
    return P;
}

void Delete(int X, List L) {
    Position P, TmpCell;
    P = FindPrevious(X, L);
    if (!IsLast(P, L)) {
        TmpCell = CursorSpace[P].Next;
        CursorSpace[P].Next = CursorSpace[TmpCell].Next;
        CursorFree(TmpCell);
    }
}

/* Prints the slots of the list (the header has no element) */
void PrintList(List L) {
    Position P = CursorSpace[L].Next;
    printf("\nSlot \t Element \t Next\n");
    while (P != 0) {
        printf("%3d \t %3d \t\t %3d\n", P, CursorSpace[P].Element, CursorSpace[P].Next);
        P = CursorSpace[P].Next;
    }
}

int main(void) {
    InitializeCursorSpace();

    List L = CursorList();
    Insert(10, L);
    Insert(20, L);
    Insert(30, L);
    Insert(40, L);
    PrintList(L);

    Delete(20, L);
    printf("\nAfter Delete(20):");
    PrintList(L);

    printf("\nFind(30) is in slot %d\n", Find(30, L));
    printf("Next free slot: %d\n", CursorSpace[0].Next);
    return 0;
}
