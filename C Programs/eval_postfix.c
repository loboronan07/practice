#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int* arr;
    int tos;
} stack;

int pop(stack*);
void push(stack*, int);
int eval_postfix(char *);

int main() {
    char postfix[100];

    printf("Enter the postfix expression: ");
    scanf("%s", postfix);

    int ans = eval_postfix(postfix);

    printf("Evaluation of %s is %d.\n", postfix, ans);

    return 0;
}

int eval_postfix(char *postfix) {
    stack s;
    s.arr = (int *) calloc(strlen(postfix), sizeof(int));
    s.tos = -1;

    int op1, op2;

    for(int index = 0; postfix[index] != '\0'; index++) {
        if(postfix[index] >= '0' && postfix[index]) 
            push(&s, postfix[index] - '0');
        else {
            op2 = pop(&s);
            op1 = pop(&s);

            switch (postfix[index])
            {
            case '+': 
                push(&s, op1 + op2);
                break;
            case '-': 
                push(&s, op1 - op2);
                break;
            case '*': 
                push(&s, op1 * op2);
                break;
            case '%': 
                push(&s, op1 % op2);
                break;
            default:
                break;
            }
        }
    }

    return pop(&s);
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