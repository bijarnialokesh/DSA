#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coeff;
    int expX;
    int expY;
    struct Node* next;
};

struct Node* createNode(int coeff, int expX, int expY) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->expX = expX;
    newNode->expY = expY;
    newNode->next = NULL;
    return newNode;
}

void insertTerm(struct Node** head, int coeff, int expX, int expY) {
    struct Node* newNode = createNode(coeff, expX, expY);
    newNode->next = *head;
    *head = newNode;
}

struct Node* addPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;
    struct Node* temp1 = poly1;
    struct Node* temp2 = poly2;

    while (temp1 != NULL && temp2 != NULL) {
        if (temp1->expX == temp2->expX && temp1->expY == temp2->expY) {
            insertTerm(&result, temp1->coeff + temp2->coeff, temp1->expX, temp1->expY);
            temp1 = temp1->next;
            temp2 = temp2->next;
        } else if (temp1->expX > temp2->expX ||
                  (temp1->expX == temp2->expX && temp1->expY > temp2->expY)) {
            insertTerm(&result, temp1->coeff, temp1->expX, temp1->expY);
            temp1 = temp1->next;
        } else {
            insertTerm(&result, temp2->coeff, temp2->expX, temp2->expY);
            temp2 = temp2->next;
        }
    }

    while (temp1 != NULL) {
        insertTerm(&result, temp1->coeff, temp1->expX, temp1->expY);
        temp1 = temp1->next;
    }

    while (temp2 != NULL) {
        insertTerm(&result, temp2->coeff, temp2->expX, temp2->expY);
        temp2 = temp2->next;
    }

    return result;
}

void printPolynomial(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%dx^%dy^%d", temp->coeff, temp->expX, temp->expY);
        temp = temp->next;
        if (temp != NULL)
            printf(" + ");
    }
    printf("\n");
}

int main() {
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;

    insertTerm(&poly1, 3, 2, 2);
    insertTerm(&poly1, 2, 1, 1);
    insertTerm(&poly1, 5, 0, 0);

    insertTerm(&poly2, 4, 2, 2);
    insertTerm(&poly2, 1, 1, 1);
    insertTerm(&poly2, 2, 0, 0);

    printf("Polynomial 1: ");
    printPolynomial(poly1);

    printf("Polynomial 2: ");
    printPolynomial(poly2);

    struct Node* sum = addPolynomials(poly1, poly2);

    printf("Sum of polynomials: ");
    printPolynomial(sum);

    return 0;
}
