
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coeff;
    int exp;
    struct Node* next;
};

struct Node* createNode(int coeff, int exp) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = newNode;
    return newNode;
}

void insertTerm(struct Node** head, int coeff, int exp) {
    struct Node* newNode = createNode(coeff, exp);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    struct Node* curr = *head;
    struct Node* prev = NULL;
    do {
        if (curr->exp < exp) break;
        prev = curr;
        curr = curr->next;
    } while (curr != *head);

    if (prev == NULL) {
        newNode->next = *head;
        struct Node* temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
        }
        temp->next = newNode;
        *head = newNode;
    } else if (curr->exp == exp) {
        curr->coeff += coeff;
        free(newNode);
    } else {
        prev->next = newNode;
        newNode->next = curr;
    }
}

struct Node* subtractPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;

    struct Node* temp1 = poly1;
    do {
        insertTerm(&result, temp1->coeff, temp1->exp);
        temp1 = temp1->next;
    } while (temp1 != poly1);

    struct Node* temp2 = poly2;
    do {
        insertTerm(&result, -temp2->coeff, temp2->exp);
        temp2 = temp2->next;
    } while (temp2 != poly2);

    return result;
}

void printPolynomial(struct Node* head) {
    if (!head) return;
    struct Node* temp = head;
    do {
        printf("%dx^%d", temp->coeff, temp->exp);
        temp = temp->next;
        if (temp != head)
            printf(" + ");
    } while (temp != head);
    printf("\n");
}

int main() {
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;

    insertTerm(&poly1, 4, 3);
    insertTerm(&poly1, 3, 2);
    insertTerm(&poly1, 2, 1);

    insertTerm(&poly2, 3, 3);
    insertTerm(&poly2, 2, 2);
    insertTerm(&poly2, 5, 0);

    printf("Polynomial 1: ");
    printPolynomial(poly1);

    printf("Polynomial 2: ");
    printPolynomial(poly2);

    struct Node* diff = subtractPolynomials(poly1, poly2);

    printf("Difference of polynomials: ");
    printPolynomial(diff);

    return 0;
}
