#include <stdio.h>
#include <stdlib.h>

int top[2], boundary[3];
void push(int*, int, int);
void pop(int*, int);

int main() {
    int stack, choice, ele, k;
    int *array;

    printf("Enter number of elements of the array(stack): ");
    scanf("%d", &k);

    array = (int *) calloc(k, sizeof(int));

    if(array == NULL) {
        return 100;
    }

    top[0] = -1;
    top[1] = (k/2) - 1;
    boundary[0] = -1;
    boundary[1] = (k/2) - 1;
    boundary[2] = k - 1;

    while(1) {
        printf("\nAvailable Stacks:\n");
        printf("\t1. Stack 1\n");
        printf("\t2. Stack 2\n");
        printf("Enter Stack Choice(Hit any other key to exit): ");
        scanf("%d", &stack);

        if(stack != 1 && stack != 2) {
            break;
        }

        printf("Avaialbe Operations: \n");
        printf("\t1. Push an Element\n");
        printf("\t2. Pop an Element\n");
        printf("Enter Operation(Hit any other key to exit): ");
        scanf("%d", &choice);

        if(choice != 1 && choice != 2) {
            break;
        }

        if(choice == 1) {
            printf("Enter element to be pushed into stack: ");
            scanf("%d", &ele);

            push(array, stack-1, ele);
        }
        else {
            pop(array, stack-1);
        }
    }

    return 0;
}

void push(int *array, int stack, int ele) {
    if(top[stack] == boundary[stack + 1]) {
        printf("Stack %d is full....\n", stack + 1);
        return;
    }
    printf("Pushing %d onto Stack %d....\n", ele, stack+1);
    array[++top[stack]] = ele;
}

void pop(int *array, int stack) {
    if(top[stack] == boundary[stack]) {
        printf("Stack %d is empty....\n", stack + 1);
        return;
    }
    printf("Popping %d form Stack %d....\n", array[top[stack]], stack+1);
    top[stack]--;
}