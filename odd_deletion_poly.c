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

    struct Node* temp = *head;
    while (temp->next != *head) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->next = *head;
}

void removeOddCoefficientTerms(struct Node** head) {
    if (*head == NULL) return;

    struct Node *curr = *head, *prev = NULL;
    int isFirstIteration = 1;

    do {
        if (curr->coeff % 2 != 0) {
            if (curr == *head) {
                struct Node* last = *head;
                while (last->next != *head) {
                    last = last->next;
                }
                if (curr->next == *head) {
                    free(curr);
                    *head = NULL;
                    return;
                } else {
                    *head = curr->next;
                    last->next = *head;
                    free(curr);
                    curr = *head;
                }
            } else {
                prev->next = curr->next;
                free(curr);
                curr = prev->next;
            }
        } else {
            prev = curr;
            curr = curr->next;
        }
        isFirstIteration = 0;
    } while (curr != *head || isFirstIteration);
}

void printPolynomial(struct Node* head) {
    if (head == NULL) {
        printf("Polynomial is empty.\n");
        return;
    }

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
    struct Node* poly = NULL;

    insertTerm(&poly, 5, 3);
    insertTerm(&poly, 4, 2);
    insertTerm(&poly, 3, 1);
    insertTerm(&poly, 2, 0);

    printf("Original Polynomial: ");
    printPolynomial(poly);

    removeOddCoefficientTerms(&poly);

    printf("Polynomial after removing terms with odd coefficients: ");
    printPolynomial(poly);

    return 0;
}
