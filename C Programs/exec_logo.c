#include<stdio.h>
#include<time.h>

void delay(int milli_seconds)
{
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}

int main()
{
    int k=0;
    for(int i=0; i<10; i++) {
        k = i % 8;
        switch (k)
        {
            case 0: 
                printf("- ");
                break;
            case 1: 
                printf("\\ ");
                break;
            case 2: 
                printf("| ");
                break;
            case 3: 
                printf("/ ");
                break;
            case 4: 
                printf("- ");
                break;
            case 5: 
                printf("\\ ");
                break;
            case 6: 
                printf("| ");
                break;
            case 7: 
                printf("/ ");
                break;
        
            default:
                break;
        }
        delay(250);
        printf("\r");
    }
    printf("\r  ");
    return 0;
}