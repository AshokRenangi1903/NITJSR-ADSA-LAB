
#include <stdio.h>

int main()
{
    int rows,cols;
    printf("Enter number of rows: ");
    scanf("%d",&rows);
    
    printf("Enter number of columns: ");
    scanf("%d",&cols);
    
    int array[rows][cols];
    
    // initialize array elements with zeroes
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            
            array[i][j]=0;
            
        }
    }
    
    // printing Array here
    printf("Initial array with all zeroes:\n");
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            printf("%d ",array[i][j]);
            
        }
        printf("\n");
    }
    
    
    
    
    // Taking input from user
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            printf("Enter value of %d row and %d column :",i,j);
            scanf("%d",&array[i][j]);
        }
    }
    
    // printing Array here
    printf("Array :\n");
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            printf("%d ",array[i][j]);
            
        }
        printf("\n");
    }
  
  

    return 0;
}