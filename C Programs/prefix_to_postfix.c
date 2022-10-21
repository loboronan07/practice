#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char** arr;
    int tos;
} stack;

char* prefix_to_postfix(char* prefix);
int check_operator(char inp);
char* string_reverse(char *str);
char* pop(stack* s);
void push(stack* s, char *ele);
char* concat(char *a, char *b, char *c);
void free_stack(stack* s);

int main(void) {
    char prefix[100];
    
    printf("Enter the prefix expression: ");
    scanf("%s", prefix);

    char *postfix = prefix_to_postfix(prefix);

    printf("Postfix Expression Generated: %s\n", postfix);

    free(postfix);
    return 0;
}


char* prefix_to_postfix(char* prefix) {
    stack *s = (stack*) malloc(sizeof(stack)); 
    s->arr = (char**) calloc(strlen(prefix), sizeof(char*)); 
    s->tos = -1;
    char *prefix_r = string_reverse(prefix); 
    char curr, *op1, *op2, *con;
    char operator[2] = {}, operand[2] = {};
    for(int index = 0; prefix_r[index] !='\0'; index++) {
        curr = prefix_r[index];
        if(!check_operator(curr)) {
            operand[0] = curr;
            push(s, operand); 
        }
        else {
            op1 = pop(s);
            op2 = pop(s);
            operator[0] = curr;
            con = concat(op1, op2, operator);
            push(s, con);
            free(con);
            free(op1);
            free(op2);
        }
    }

    char *postfix = pop(s);

    free(prefix_r); 
    free_stack(s);

    return postfix;
}

int check_operator(char inp) {
    switch(inp) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
            return 1;
        default:
            return 0;
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

char* pop(stack* s) {
    if(s->tos == -1) {
        return NULL;
    }
    char *popped = (char *) calloc(strlen(s->arr[s->tos]) + 1, sizeof(char));
    strcpy(popped, s->arr[s->tos]);
    free(s->arr[s->tos]);
    s->arr[s->tos] = NULL;
    s->tos--;
    return popped;
}

void push(stack* s, char *ele) {
    char *new = (char *) calloc(strlen(ele) + 1, sizeof(char));
    strcpy(new, ele);
    s->arr[++(s->tos)] = new;
}

char* concat(char *a, char *b, char *c) {
    char *res = (char*) calloc(strlen(a) + strlen(b) + strlen(c) + 1, sizeof(char));
    int index = 0;
    for(int i=0; a[i] != '\0'; i++, index++) 
        res[index] = a[i];
    for(int i=0; b[i] != '\0'; i++, index++) 
        res[index] = b[i];
    for(int i=0; c[i] != '\0'; i++, index++) 
        res[index] = c[i];
    res[index] = '\0';
    return res;
}

void free_stack(stack* s) {
    free(s->arr); 
    free(s); 
}
