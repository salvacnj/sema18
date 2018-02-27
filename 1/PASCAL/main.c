#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n_rows=3;
    int n_cols[3]={1,2,3};
    int i,j;

    int **p_matriz=(int **)malloc(n_rows*sizeof(int *));

    for (i=0;i<n_rows;i++){
        p_matriz[i] = (int *)malloc(n_cols[i]*sizeof(int));

    }

    p_matriz[0][0]=1;
    p_matriz[1][0]=1;
    p_matriz[1][1]=1;
    p_matriz[2][0]=1;
    p_matriz[2][1]=2;
    p_matriz[2][2]=1;

    for(i=0;i<n_rows;i++){
        for (j=0;j<n_cols[i];j++){
            printf("%d ", p_matriz[i][j]);
        }

        printf("\n");
    }
    return 0;
}
