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
    newNode->next = NULL;
    return newNode;
}

void insertTerm(struct Node** head, int coeff, int exp) {
    if (coeff == 0)
        return;

    struct Node* newNode = createNode(coeff, exp);
    if (*head == NULL || (*head)->exp < exp) {
        newNode->next = *head;
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL && temp->next->exp > exp)
            temp = temp->next;

        if (temp->next != NULL && temp->next->exp == exp) {
            temp->next->coeff += coeff;
            if (temp->next->coeff == 0) {
                struct Node* toDelete = temp->next;
                temp->next = temp->next->next;
                free(toDelete);
            }
            free(newNode);
        } else {
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }
}

struct Node* addPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;
    while (poly1 != NULL) {
        insertTerm(&result, poly1->coeff, poly1->exp);
        poly1 = poly1->next;
    }
    while (poly2 != NULL) {
        insertTerm(&result, poly2->coeff, poly2->exp);
        poly2 = poly2->next;
    }
    return result;
}

struct Node* subtractPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;
    while (poly1 != NULL) {
        insertTerm(&result, poly1->coeff, poly1->exp);
        poly1 = poly1->next;
    }
    while (poly2 != NULL) {
        insertTerm(&result, -poly2->coeff, poly2->exp);
        poly2 = poly2->next;
    }
    return result;
}

struct Node* multiplyPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;
    struct Node* temp1 = poly1;
    while (temp1 != NULL) {
        struct Node* temp2 = poly2;
        while (temp2 != NULL) {
            int coeff = temp1->coeff * temp2->coeff;
            int exp = temp1->exp + temp2->exp;
            insertTerm(&result, coeff, exp);
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
    return result;
}

struct Node* differentiatePolynomial(struct Node* poly) {
    struct Node* result = NULL;
    struct Node* temp = poly;
    while (temp != NULL) {
        if (temp->exp != 0) {
            insertTerm(&result, temp->coeff * temp->exp, temp->exp - 1);
        }
        temp = temp->next;
    }
    return result;
}

void displayPolynomial(struct Node* poly) {
    struct Node* temp = poly;
    while (temp != NULL) {
        printf("%dx^%d", temp->coeff, temp->exp);
        temp = temp->next;
        if (temp != NULL && temp->coeff > 0)
            printf(" + ");
        else if (temp != NULL && temp->coeff < 0)
            printf(" ");
    }
    printf("\n");
}

void freePolynomial(struct Node* poly) {
    while (poly != NULL) {
        struct Node* temp = poly;
        poly = poly->next;
        free(temp);
    }
}

int main() {
    struct Node *poly1 = NULL, *poly2 = NULL, *result = NULL;
    int choice, coeff, exp, n, i;

    printf("Enter number of terms in the first polynomial: ");
    scanf("%d", &n);
    printf("Enter terms for first polynomial (coefficient and exponent):\n");
    for (i = 0; i < n; i++) {
        printf("Term %d: ", i + 1);
        scanf("%d %d", &coeff, &exp);
        insertTerm(&poly1, coeff, exp);
    }

    printf("Enter number of terms in the second polynomial: ");
    scanf("%d", &n);
    printf("Enter terms for second polynomial (coefficient and exponent):\n");
    for (i = 0; i < n; i++) {
        printf("Term %d: ", i + 1);
        scanf("%d %d", &coeff, &exp);
        insertTerm(&poly2, coeff, exp);
    }

    do {
        printf("\nChoose an operation:\n");
        printf("1. Add Polynomials\n");
        printf("2. Subtract Polynomials\n");
        printf("3. Multiply Polynomials\n");
        printf("4. Differentiate First Polynomial\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                result = addPolynomials(poly1, poly2);
                printf("Resultant Polynomial after Addition:\n");
                displayPolynomial(result);
                freePolynomial(result);
                result = NULL;
                break;
            case 2:
                result = subtractPolynomials(poly1, poly2);
                printf("Resultant Polynomial after Subtraction:\n");
                displayPolynomial(result);
                freePolynomial(result);
                result = NULL;
                break;
            case 3:
                result = multiplyPolynomials(poly1, poly2);
                printf("Resultant Polynomial after Multiplication:\n");
                displayPolynomial(result);
                freePolynomial(result);
                result = NULL;
                break;
            case 4:
                result = differentiatePolynomial(poly1);
                printf("Resultant Polynomial after Differentiation of First Polynomial:\n");
                displayPolynomial(result);
                freePolynomial(result);
                result = NULL;
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 5);

    freePolynomial(poly1);
    freePolynomial(poly2);

    return 0;
}
