/* This program checks for errors in the html code
    Limited only to finding missing and unnecessary closing braces.
    Does not check whether the html tag is properly structured.
    More Functionality to be added...
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *tag;
    int line;
} TAG;

typedef struct {
    TAG tags[100];
    int tos;
} TAG_STACK;

void check_html(char*);
void push(TAG_STACK*, char*, int);
TAG pop(TAG_STACK*);
int is_empty(TAG_STACK*);
void string_copy(char*, char*, int, int);

int main() {
    char html[1000];
    printf("Enter the html code(Enter # to stop receiving input):\n");
    scanf("%[^#]s", html);

    printf("\n");
    check_html(html);

    return 0;
}

void check_html(char *html) {
    TAG_STACK stack;
    stack.tos = -1;

    int start = -1, end = -1;
    char curr, tag = '\0';
    int line = 1;
    for(int index = 0; html[index] != '\0'; index++) {
        curr = html[index];

        if(curr == '\n') {
            line++;
            continue;
        }

        if(curr == '<') {
            start = index;
            tag = 'o';
        }
        else if(curr == '/') {
            tag = 'c';
        }
        else if(curr == '>' && start >= 0) {
            end = index - 1;
            if(tag == 'o') {
                start += 1;
            }
            else if(tag == 'c') {
                start += 2;
            }
            char *tag_name = (char *) calloc(end - start + 1, sizeof(int));
            string_copy(html, tag_name, start, end);
            if(tag == 'o') 
                push(&stack, tag_name, line);
            else {
                TAG t = pop(&stack);
                if(strcmp(tag_name, t.tag) != 0) {
                    printf("Error in line %d. Closing Brace for %s not required...\n", line, tag_name);
                    return;
                }
            }

            end = -1;
            start = -1;
            tag = '\0';
        }        
    }

    if(is_empty(&stack)) {
        printf("No Errors Found...\n");
    }
    else {
        TAG t;
        do {
            t = pop(&stack);
            printf("No closing brace for %s found which was opened on line %d...\n", t.tag, t.line);
        } while(!is_empty(&stack));
    }
}   

void push(TAG_STACK *stack, char *tag_name, int line) {
    stack->tos++;
    stack->tags[stack->tos].tag = tag_name;
    stack->tags[stack->tos].line = line;
}

TAG pop(TAG_STACK *stack) {
    return stack->tags[stack->tos--];
}

int is_empty(TAG_STACK* stack) {
    return stack->tos == -1;
}

void string_copy(char* inp, char* out, int start, int end) {
    int i, j;
    for(i=start, j=0; i<=end; i++, j++) 
        out[j] = inp[i];
    out[j] = '\0';
}