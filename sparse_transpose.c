#include <stdio.h>
#include <stdlib.h>

struct Node {
    int row;
    int col;
    int value;
    struct Node* next;
};

struct Node* createNode(int row, int col, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->row = row;
    newNode->col = col;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void insertElement(struct Node** head, int row, int col, int value) {
    struct Node* newNode = createNode(row, col, value);
    newNode->next = *head;
    *head = newNode;
}

struct Node* transposeMatrix(struct Node* head) {
    struct Node* transposed = NULL;
    struct Node* current = head;

    while (current != NULL) {
        insertElement(&transposed, current->col, current->row, current->value);
        current = current->next;
    }

    return transposed;
}

void printSparseMatrix(struct Node* head) {
    struct Node* temp = head;
    printf("Row\tCol\tValue\n");
    while (temp != NULL) {
        printf("%d\t%d\t%d\n", temp->row, temp->col, temp->value);
        temp = temp->next;
    }
}

int main() {
    struct Node* sparseMatrix = NULL;

    insertElement(&sparseMatrix, 0, 0, 1);
    insertElement(&sparseMatrix, 1, 2, 2);
    insertElement(&sparseMatrix, 2, 1, 3);

    printf("Original Sparse Matrix:\n");
    printSparseMatrix(sparseMatrix);

    struct Node* transposedMatrix = transposeMatrix(sparseMatrix);

    printf("\nTransposed Sparse Matrix:\n");
    printSparseMatrix(transposedMatrix);

    return 0;
}
