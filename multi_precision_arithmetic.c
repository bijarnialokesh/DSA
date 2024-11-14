#include <stdio.h>
#include <stdlib.h>

struct arithmetic {
    int digit;
    struct arithmetic *next;
};

int main() {
    char str1[1000];
    char str2[1000];

    printf("Specify the first number\n");
    scanf("%s", str1);
    printf("Specify the second number\n");
    scanf("%s", str2);
    printf("You entered %s and %s\n", str1, str2);

    struct arithmetic *number1 = NULL;
    struct arithmetic *number2 = NULL;
    struct arithmetic *number3 = NULL;

    struct arithmetic *point1 = NULL;
    struct arithmetic *point2 = NULL;
    struct arithmetic *point3 = NULL;

    int i = 0;


    while (str1[i] != '\0') {
        int convert = str1[i] - '0';
        struct arithmetic *newdigit = (struct arithmetic*)malloc(sizeof(struct arithmetic));
        newdigit->digit = convert;
        newdigit->next = point1;
        point1 = newdigit;
        i++;
    }

    i = 0;


    while (str2[i] != '\0') {
        int convert = str2[i] - '0'; 
        struct arithmetic *newdigit = (struct arithmetic*)malloc(sizeof(struct arithmetic));
        newdigit->digit = convert;
        newdigit->next = point2;
        point2 = newdigit;
        i++;
    }

    int carry = 0;


    while (point1 != NULL || point2 != NULL || carry) {
        int sum = carry;

        if (point1 != NULL) {
            sum += point1->digit;
            point1 = point1->next;
        }

        if (point2 != NULL) {
            sum += point2->digit;
            point2 = point2->next;
        }

        carry = sum / 10;
        sum = sum % 10;

        struct arithmetic *newdigit = (struct arithmetic*)malloc(sizeof(struct arithmetic));
        newdigit->digit = sum;
        newdigit->next = point3;
        point3 = newdigit;
    }

	printf("Resultant\n");

    while (point3 != NULL) {
        printf("%d", point3->digit);
        point3 = point3->next;
    }
    return 0;
}

