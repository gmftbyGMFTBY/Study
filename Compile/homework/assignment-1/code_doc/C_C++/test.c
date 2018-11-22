// Author : GMFTBY
// Time   : 2018.2.27
#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#define M 200

// function to read
int read_file(int matrix[M][M], const char* path)
{
    int i, j;
    FILE *fp = NULL;
    fp = fopen(path, "r");
    for(i = 0; i < M; i++)
    {
        for(j = 0; j < M; j++)
        {
            fscanf(fp, "%d", &matrix[i][j]);
        }
    }
    fclose(fp);
    fp = NULL;
}

int main()
{
    // define for the matrix
    int i, j, k;
    int matrix1[M][M];
    int matrix2[M][M];
    int matrix[M][M];

    // read the file from path '../../data/matrix_a, b, c'
    // read matrix_a, matrix_b, matrix_c
    read_file(matrix1, "../../data/matrix_a");
    read_file(matrix2, "../../data/matrix_b");
    
    // init the matrix_c
    for(i = 0; i < M; i++)
    {
        for(j = 0; j < M; j++)
        {
            matrix[i][j] = 0;
        }
    }
    
    for(i = 0;i < M;i++)
    {
        for(j=0;j < M;j++)
        {
            for(k=0;k < M;k++) matrix[i][j] += matrix1[i][k] * matrix2[k][j]; 
        } 
    }

    /*
    // print result
    for(i = 0;i < M;i++)
    {
        for(j = 0;j < M;j++) printf("%d ",matrix[i][j]);
        printf("\n"); 
    } 
    */
    return 0;
}
