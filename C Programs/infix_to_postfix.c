#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char* arr;
    int tos;
} stack;

char* infix_to_postfix(char *);
char pop(stack*);
void push(stack*, char);
int check_precedence(stack*, char);
int check_operator(char);

int main() {
    char infix[100];
    
    printf("Enter the infix expression: ");
    scanf("%s", infix);

    char *postfix = infix_to_postfix(infix);

    printf("Postfix Expression Generated: %s", postfix);

    return 0;
}

char* infix_to_postfix(char *infix) {
    stack s;
    char* postfix = (char *) calloc(strlen(infix), sizeof(char));
    int postfix_index = -1;

    s.arr = (char *) calloc(strlen(infix), sizeof(char));
    s.tos = -1;

    for(int index = 0; infix[index] != '\0'; index++) {
        if(check_operator(infix[index])) {
            if(infix[index] == ')') {
                for(char op = pop(&s); op != '('; op = pop(&s))
                    postfix[++postfix_index]  = op;
                continue;
            }
            while(!check_precedence(&s, infix[index]))
                postfix[++postfix_index]  = pop(&s);
            push(&s, infix[index]);
        }
        else 
            postfix[++postfix_index] = infix[index];
    }

    for(char op = pop(&s); op != '\0'; op = pop(&s)) 
        postfix[++postfix_index]  = op;

    return postfix;
}

char pop(stack* s) {
    if(s->tos ==-1) {
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
    
    if(incoming == '(' || in_stack == '(') {
        return 1;
    }
    switch(incoming) {
        case '*':
        case '/':
        case '%':
            switch(in_stack) {
                case '*':
                case '/':
                case '%':
                    return 0;
                default:
                    return 1;
            }
        default:
            return 0;
    }
}