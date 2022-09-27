#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int* arr;
    int tos;
} stack;

int pop(stack*);
void push(stack*, int);
int eval_prefix(char *);
char* string_reverse(char *);

int main() {
    char prefix[100];

    printf("Enter the prefix expression: ");
    scanf("%s", prefix);

    int ans = eval_prefix(prefix);

    printf("Evaluation of %s is %d.\n", prefix, ans);

    return 0;
}

int eval_prefix(char *prefix) {
    prefix = string_reverse(prefix);

    stack s;
    s.arr = (int *) calloc(strlen(prefix), sizeof(int));
    s.tos = -1;

    int op1, op2;

    for(int index = 0; prefix[index] != '\0'; index++) {
        if(prefix[index] >= '0' && prefix[index]) 
            push(&s, prefix[index] - '0');
        else {
            op1 = pop(&s);
            op2 = pop(&s);

            switch (prefix[index])
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

char* string_reverse(char *str) {
    int len = strlen(str);
    char *rev = (char *) calloc(strlen(str), sizeof(char));
    char temp;
    for(int i=0; i < len; i++) {
        rev[i] = str[len-1-i];
    }
    rev[len] = '\0';
    return rev;
}