/*
 * Check if the brackets in a string are balanced: ( ) { } [ ]
 *
 * Push every opening bracket. For every closing bracket, the top of the
 * stack must be its matching opening bracket. At the end the stack
 * must be empty.
 *
 * Examples: "{[()]}" valid,  "([)]" not valid,  "((" not valid
 */
#include <stdio.h>
#include <stdlib.h>

struct node {
    int Data;
    struct node* Next;
};

typedef struct node* Stack;

/* ---------- stack ---------- */

Stack CreateStack(void) {
    Stack S = (Stack)malloc(sizeof(struct node));
    S->Next = NULL;
    return S;
}

int IsEmpty(Stack S) { return S->Next == NULL; }

void Push(int X, Stack S) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->Data = X;
    temp->Next = S->Next;
    S->Next = temp;
}

int Top(Stack S) { return S->Next->Data; }

void Pop(Stack S) {
    if (IsEmpty(S))
        return;
    struct node* first = S->Next;
    S->Next = first->Next;
    free(first);
}

void DisposeStack(Stack S) {
    while (!IsEmpty(S))
        Pop(S);
    free(S);
}

/* ---------- solution ---------- */

int isMatching(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

int isValid(char str[]) {
    Stack S = CreateStack();
    int i = 0;
    int result = 1;
    char x;

    while (str[i] != '\0') {
        if (str[i] == '(' || str[i] == '{' || str[i] == '[') {
            Push(str[i], S);
        } else if (str[i] == ')' || str[i] == '}' || str[i] == ']') {
            if (IsEmpty(S)) {
                result = 0;
                break;
            }

            x = (char)Top(S);
            Pop(S);

            if (!isMatching(x, str[i])) {
                result = 0;
                break;
            }
        }
        i++;
    }

    if (!IsEmpty(S))
        result = 0;

    DisposeStack(S);
    return result;
}

int main(void) {
    char* tests[] = {"{[()]}", "([)]", "((", "a(b)c[d]", ")"};

    for (int k = 0; k < 5; k++)
        printf("%-10s -> %s\n", tests[k], isValid(tests[k]) ? "valid" : "not valid");

    return 0;
}
