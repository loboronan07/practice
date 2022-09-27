#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int **array;
    int rows, columns;

    printf("Enter the number of rows: ");
    scanf("%d", &rows);

    array = (int **) calloc(rows + 1, sizeof(int *));

    if(array == NULL) {
        printf("Memory Allocation Unsuccessful...");
        exit(1);
    }
    
    printf("\n");

    for(int i=0; i<rows; i++) {
        printf("Enter the number of columns in row %d: ", i+1);
        scanf("%d", &columns);

        array[i] = (int *) calloc(columns + 1, sizeof(int));

        if(array[i] == NULL) {
            printf("Memory Allocation Unsuccessful...");

            for(int j=0; j<i; j++) {
                free(array[i]);
            }
            free(array);

            exit(1);
        }

        array[i][0] = columns;

        printf("Enter %d elements: ", columns);
        for(int j=1; j <= columns; j++) {
            scanf("%d", &array[i][j]);
        }
        printf("\n");
    }

    array[rows] = NULL;

    printf("The ragged array entered is: \n");
    for(int i=0; array[i] != NULL; i++) {
        columns = array[i][0];
        for(int j=1; j<=columns; j++) {
            printf("%3d\t", array[i][j]);
        }
        printf("\n");
    }

    for(int i=0; array[i] != NULL; i++) {
        free(array[i]);
    }
    free(array);

    return 0;
}