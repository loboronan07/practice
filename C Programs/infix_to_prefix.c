#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char* arr;
    int tos;
} stack;

char* infix_to_prefix(char *);
char pop(stack*);
void push(stack*, char);
int check_precedence(stack*, char);
int check_operator(char);
char* string_reverse(char *);

int main() {
    char infix[100];
    
    printf("Enter the infix expression: ");
    scanf("%s", infix);

    char *prefix = infix_to_prefix(infix);

    printf("Prefix Expression Generated: %s", prefix);

    free(prefix);
    return 0;
}

char* infix_to_prefix(char *infix) {
    stack s;
    char* prefix_r = (char *) calloc(strlen(infix) + 1, sizeof(char));
    int prefix_index = -1;

    char *infix_r = string_reverse(infix);

    s.arr = (char *) calloc(strlen(infix), sizeof(char));
    s.tos = -1;

    for(int index = 0; infix_r[index] != '\0'; index++) {
        if(check_operator(infix_r[index])) {
            if(infix_r[index] == '(') {
                for(char op = pop(&s); op != ')'; op = pop(&s))
                    prefix_r[++prefix_index]  = op;
                continue;
            }
            while(!check_precedence(&s, infix_r[index]))
                prefix_r[++prefix_index]  = pop(&s);
            push(&s, infix_r[index]);
        }
        else 
            prefix_r[++prefix_index] = infix_r[index];
    }

    for(char op = pop(&s); op != '\0'; op = pop(&s)) 
        prefix_r[++prefix_index]  = op;

    char *prefix = string_reverse(prefix_r);

    free(s.arr);
    free(infix_r);
    free(prefix_r);

    return prefix;
}

char pop(stack* s) {
    if(s->tos == -1) {
        return 0;
    }
    return s->arr[(s->tos)--];
}

void push(stack* s, char ele) {
    s->arr[++(s->tos)] = ele;
}

int check_operator(char inp) {
    switch(inp) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '(':
        case ')':
            return 1;
        default:
            return 0;
    }
}

int check_precedence(stack* s, char incoming) {
    if(s->tos == -1) 
        return 1;
    char in_stack = s->arr[s->tos];
    
    if(incoming == ')' || in_stack == ')') {
        return 1;
    }
    switch(incoming) {
        case '*':
        case '/':
        case '%':
            return 1;
        default:
            switch(in_stack) {
                case '+':
                case '-':
                    return 1;
                default:
                    return 0;
            }
    }
}

char* string_reverse(char *str) {
    int len = strlen(str);
    char *rev = (char *) calloc(strlen(str) + 1, sizeof(char));
    for(int i=0; i < len; i++) {
        rev[i] = str[len-1-i];
    }
    rev[len] = '\0';
    return rev;
}