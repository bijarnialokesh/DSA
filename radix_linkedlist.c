#include <stdio.h>
#include <stdlib.h>

int checkDigit(int number, int max) {
    int count = 0;

    do {
        count++;
        number /= 10;
    } while (number != 0);

    if(max < count) {
        max = count;
    }
    return max;
}

struct radix {
    int ele;
    struct radix *next;
};

struct radixhead {
    int number;
    struct radix *list;
    struct radixhead *next;
};

void appendToBucket(struct radixhead **bucket, int digit, int number) {
    struct radixhead *travel = *bucket;
    struct radixhead *prev = NULL;

    while(travel != NULL && travel->number < digit) {
        prev = travel;
        travel = travel->next;
    }

    if(travel == NULL || travel->number != digit) {
        struct radixhead *newBucket = (struct radixhead*)malloc(sizeof(struct radixhead));
        newBucket->number = digit;
        newBucket->list = NULL;
        newBucket->next = travel;

        if(prev == NULL) {
            *bucket = newBucket;
        } else {
            prev->next = newBucket;
        }
        travel = newBucket;
    }

    struct radix *newElement = (struct radix*)malloc(sizeof(struct radix));
    newElement->ele = number;
    newElement->next = NULL;

    if(travel->list == NULL) {
        travel->list = newElement;
    } else {
        struct radix *listTravel = travel->list;
        while(listTravel->next != NULL) {
            listTravel = listTravel->next;
        }
        listTravel->next = newElement;
    }
}

void freeBuckets(struct radixhead *bucket) {
    struct radixhead *tempBucket;
    while(bucket != NULL) {
        struct radix *tempList;
        while(bucket->list != NULL) {
            tempList = bucket->list;
            bucket->list = bucket->list->next;
            free(tempList);
        }
        tempBucket = bucket;
        bucket = bucket->next;
        free(tempBucket);
    }
}

struct radix* collectAndSort(struct radixhead *bucket, int *isEmpty) {
    struct radix *head = NULL;
    struct radix *tail = NULL;

    while(bucket != NULL) {
        struct radix *listTravel = bucket->list;
        while(listTravel != NULL) {
            struct radix *newElement = (struct radix*)malloc(sizeof(struct radix));
            newElement->ele = listTravel->ele;
            newElement->next = NULL;

            if(head == NULL) {
                head = newElement;
                tail = newElement;
            } else {
                tail->next = newElement;
                tail = newElement;
            }

            listTravel = listTravel->next;
        }
        bucket = bucket->next;
    }

    *isEmpty = (head == NULL);
    return head;
}

void radixSort(struct radix **head, int maxdigit) {
    int exp = 1;
    for(int i = 0; i < maxdigit; i++) {
        struct radixhead *bucket = NULL;
        struct radix *sort = *head;
        while(sort != NULL) {
            int digit = (sort->ele / exp) % 10;
            appendToBucket(&bucket, digit, sort->ele);
            sort = sort->next;
        }

        int isEmpty = 0;
        *head = collectAndSort(bucket, &isEmpty);
        freeBuckets(bucket);

        exp *= 10;
        if(isEmpty) break;
    }
}

void printList(struct radix *head) {
    struct radix *temp = head;
    while(temp != NULL) {
        printf("%d ", temp->ele);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int maxdigit = 0;
    struct radix *head = NULL;
    struct radix *temp = NULL;

    printf("Enter elements to sort\n-1 to end\n");
    int c = 0;
    while(c >= 0) {
        scanf("%d", &c);
        if(c < 0) break;

        struct radix *block = (struct radix*)malloc(sizeof(struct radix));
        block->ele = c;
        block->next = NULL;

        if(head == NULL) {
            head = block;
            temp = head;
        } else {
            temp->next = block;
            temp = block;
        }

        maxdigit = checkDigit(c, maxdigit);
    }

    printf("Before sorting: ");
    printList(head);

    radixSort(&head, maxdigit);

    printf("After sorting: ");
    printList(head);

    return 0;
}
