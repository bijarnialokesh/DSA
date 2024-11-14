#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct poly{
    int coeff;
    int deg;
    struct poly * next;
};

int main(){
    int n;
    printf("Number of terms\n");
    scanf("%d", &n);
    struct poly * polynomial1 = (struct poly*)malloc(sizeof(struct poly));
    polynomial1->coeff = 0;
    polynomial1->deg=0;
    polynomial1->next =NULL;
    struct poly * temp = polynomial1;
    int c,d;
    printf("Polynomial 1\n");
    while(n!=0){
        struct poly * newterm = (struct poly*)malloc(sizeof(struct poly));
        printf("Coefficient:\n");
        scanf("%d", &c);
        printf("Degree:\n");
        scanf("%d", &d);
        temp->next=newterm;
        newterm->coeff=c;
        newterm->deg=d;
        newterm->next=NULL;
        temp=newterm;
    }
    temp=polynomial1->next;
    printf("Polynomial 2\n");
    struct poly * polynomial2 = (struct poly*)malloc(sizeof(struct poly));
    polynomial2->coeff=0;
    polynomial2->deg=0;
    polynomial2->next=NULL;
    struct poly * temp2 = polynomial2;
    while(n!=0){
        struct poly * newterm = (struct poly*)malloc(sizeof(struct poly));
        printf("Coefficient:\n");
        scanf("%d", &c);
        printf("Degree:\n");
        scanf("%d", &d);
        temp2->next=newterm;
        newterm->coeff=c;
        newterm->deg=d;
        newterm->next=NULL;
        temp2=newterm;
    }
    temp2=polynomial2->next;
    struct poly * resultant = (struct poly*)malloc(sizeof(struct poly));
    resultant->coeff=-1;
    resultant->deg=-1;
    resultant->next=NULL;
    struct poly * temp3 = resultant;

    while(temp->next!=NULL){
        while(temp2->next!=NULL){
                while(temp3!=NULL){
                    if(temp3->deg == (temp->deg)*(temp2->deg)){
                        temp3->coeff= (temp2->coeff)*(temp->coeff);
                    }
                    temp3=temp3->next;
                }
                temp3=resultant;
                if(temp3->next == NULL){
                    struct poly * newterm = (struct poly*)malloc(sizeof(struct poly));
                    temp3->next = newterm;
                    newterm->coeff = (temp->coeff)*(temp2->coeff);
                    newterm->deg = (temp->deg)*(temp2->deg);
                    newterm->next = NULL;
                    temp3=resultant;
                }
                else{
                    while(((temp->deg)*(temp2->deg))< temp3->next->deg && temp3!=NULL){
                        temp3=temp3->next;
                    }
                    if(temp3->next==NULL){
                        struct poly * newterm = (struct poly*)malloc(sizeof(struct poly));
                        temp3->next=newterm;
                        newterm->next=NULL;
                         newterm->deg= (temp->deg)*(temp2->deg);
                        newterm->coeff=(temp->coeff)*(temp2->coeff);
                        temp3=resultant;
                    }
                    else{
                        struct poly * newterm = (struct poly*)malloc(sizeof(struct poly));
                    newterm->next=temp3->next;
                    temp3->next=newterm;
                    newterm->deg= (temp->deg)*(temp2->deg);
                    newterm->coeff=(temp->coeff)*(temp2->coeff);
                    temp3=resultant;
                    }
                }
        }
    }
    temp3=resultant;
    printf("Result polynomial\n");
    while(temp3!=NULL){
        printf("C:%d\tD:%d\n", temp3->coeff, temp->deg);
        temp3=temp3->next;
    }

    return 0;
}
