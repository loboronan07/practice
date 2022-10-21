#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int *arr;
	int tos[2];
	int bound[3];
} STACK2;

STACK2* initialize_stack(int);
void push(STACK2*, int, int);
int pop(STACK2*, int);
void display(STACK2*, int);
void free_stack(STACK2*);

int main(void) {
	int n;

	printf("Enter the size of the array: ");
	scanf("%d", &n);

	printf("Initializing Two Stacks in an Array of size %d....\n", n);
	STACK2* stack = initialize_stack(n);

	int s, choice, ele;

	while(1) {
		printf("Available Stacks:\n");
		printf("\t1. Stack 1\n");
		printf("\t2. Stack 2\n");
		printf("Enter Stack Choice(0 to exit): ");
		scanf("%d", &s);

		if(s == 0) 
			break;

		if(s == 1 || s == 2) {
			printf("Available Operations:\n");
			printf("\t1. Push an Element\n");
			printf("\t2. Pop an Element\n");
			printf("\t3. Display Stack Elements\n");
			printf("Enter Operation(0 to exit): ");
			scanf("%d", &choice);

			if(choice == 0) 
				break;

			if(choice == 1) {
				printf("Enter element to be pushed into stack: ");
				scanf("%d", &ele);
				push(stack, ele, s);
			}
			else if(choice == 2) {
				ele = pop(stack, s);
				if(ele == -5555) 
					printf("Stack Empty...\n");
				else 
					printf("%d was popped out of the stack...\n", ele);
			}
			else if(choice == 3) {
				printf("Elements in Stack %d:\n", s);
				display(stack, s);
			}
			else 
				printf("Invalid Operation...\n");
		}
		else {
			printf("Invalid Stack...\n");
		}
	}
	
	free_stack(stack);

	return 0;
}

STACK2* initialize_stack(int size) {
	STACK2* stack = (STACK2*) malloc(sizeof(STACK2));
	stack->arr = (int*) calloc(size, sizeof(int));
	stack->tos[0] = stack->bound[0] = -1;
	stack->tos[1] = stack->bound[1] = size/2 - 1;
	stack->bound[2] = size-1;
}

void push(STACK2* stack, int ele, int s) {
	if(stack->tos[s-1] == stack->bound[s]) {
		printf("Stack %d is full...\n", s);
		return;
	}
	stack->arr[++(stack->tos[s-1])] = ele;
}

int pop(STACK2* stack, int s) {
	if(stack->tos[s-1] == stack->bound[s-1]) 
		return -5555;
	return stack->arr[stack->tos[s-1]--];
}

void display(STACK2* stack, int s) {
	if(stack->tos[s-1] == stack->bound[s-1]) {
		printf("\tStack is Empty...\n");
		return;
	}
	for(int i=stack->bound[s-1]+1; i<=stack->tos[s-1]; i++) 
		printf("\t%d", stack->arr[i]);
	printf("\n");
}

void free_stack(STACK2* stack) {
	free(stack->arr);
	free(stack);
}