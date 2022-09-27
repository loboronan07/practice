#include <stdio.h>
#include <stdlib.h>
#define MAX_LANE_SIZE 10

typedef struct {
    int no;
    int count;
} CAR;

typedef struct {
    CAR arr[MAX_LANE_SIZE];
    int last;
} LANE;

void push(LANE* lane, CAR* car);
CAR pop(LANE* lane);
void remove(LANE* lane, int carno);

int main(void) {
    LANE lane;
    lane.last = 0;

    char choice;
    int carno;
    int ip_lines;

    scanf("%d", &ip_lines);
    for(int i=0; i<ip_lines; i++) {
        scanf("%c %d", &choice, &carno);
        
        if(choice == 'D') {
            remove(&lane, carno);
        }
        else if(choice == 'A') {
            if(check_full(&lane)) {
                printf("Sorry the lane is currently full.\n");
                continue;
            }
            CAR new;
            new.count = 0;
            new.no = carno;    
            push(&lane, &new);
        }
    }

    return 0;
}