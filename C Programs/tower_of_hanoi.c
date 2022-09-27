#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char rod;
    int* arr;
    int tos;
} stack;

int pop(stack*);
void push(stack*, int);
void tower(int, stack*, stack*, stack*);
void display();

stack source, auxiliary, destination;
int n;
int main(void) {

    printf("Enter the source, auxiliary and destination rods: ");
    scanf("%c %c %c", &source.rod, &auxiliary.rod, &destination.rod);

    printf("Enter the number of disks on source %c: ", source.rod);
    scanf("%d", &n);

    source.arr = (int *) calloc(n, sizeof(int));
    if(source.arr == NULL) {
        exit(100);
    }

    auxiliary.arr = (int *) calloc(n, sizeof(int));
    if(auxiliary.arr == NULL) {
        free(source.arr);
        exit(100);
    }

    destination.arr = (int *) calloc(n, sizeof(int));
    if(auxiliary.arr == NULL) {
        free(source.arr);
        free(auxiliary.arr);
        exit(100);
    }

    for(int i=0; i<n; i++) {
        source.arr[i] = n-i;
    }
    source.tos = n-1;

    auxiliary.tos = -1;
    destination.tos = -1;

    display();
    tower(n, &source, &auxiliary, &destination);

    free(source.arr);
    free(auxiliary.arr);
    free(destination.arr);

    return 0;
}

void tower(int n, stack* source, stack* auxiliary, stack* destination) {
    if(n == 1) {
        printf("Move disk 1 from %c to %c.\n", source->rod, destination->rod);
        push(destination, pop(source));
        display();
        return;
    }

    tower(n-1, source, destination, auxiliary);

    printf("Move disk %d from %c to %c.\n", n, source->rod, destination->rod);
    push(destination, pop(source));
    display();

    tower(n-1, auxiliary, source, destination);
}

int pop(stack* s) {
    if(s->tos == -1) {
        return -1;
    }
    return s->arr[(s->tos)--];
}

void push(stack* s, int ele) {
    s->arr[++(s->tos)] = ele;
}

void display() {
    printf("\t%c\t%c\t%c\n", source.rod, auxiliary.rod, destination.rod);
    for(int i=n-1; i>=0; i--) {
        printf("\t");
        if(i <= source.tos) 
            printf("%d", source.arr[i]);
        printf("\t");
        if(i <= auxiliary.tos) 
            printf("%d", auxiliary.arr[i]);
        printf("\t");
        if(i <= destination.tos) 
            printf("%d", destination.arr[i]);
        printf("\n");
    }
}