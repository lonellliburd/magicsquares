# include <stdio.h>

# define MAX 300

void fillSquare(int M[][MAX], int N){
    int i, j;
    for (i=0; i<N; i++)
        for (j=0; j<N; j++)
            M[i][j]=0;
}

void printSquare(int M[][MAX], int N, FILE*out){
    int i, j;
    for (i=0; i<N; i++){
        for (j=0; j<N; j++)
            fprintf(out, "%d \t", M[i][j]);
        fprintf(out, "\n");
    }
}

/*
Fills squares concentricly until it reaches a square of size
3. This square is then filled in an odd fashion
*/
void concentricSquare(int M[][MAX], int size){
    void magicSquareOdd(int[][], int,int);
    
    int m=size/2, sqSize=size, border=size;
    int row=0, col=0, i=0, j=1;
    int num=1;

    while(sqSize!=3){
        while(i==row && j<=m+1){
            if(j>m){
                M[border-1][border-1]=num;
                M[row][col]=((size*size)+1)-num;
                i++; j=border-1;
            }
            else {
                M[i][j]=num;
                M[border-1][j]=((size*size)+1)-num;
                j++;
            }
            num++;
        }
        while(i>row && i<=m+1 && j==border-1){
            if(i==m){
                M[m][col]=num;
                M[m][border-1]=((size*size)+1)-num;
                i=border-1;
                j=m+1;
            }
            else if(i<m){
                M[i][j]=num;
                M[i][col]=((size*size)+1)-num;
                i++;
            }
            num++;
        }
        while(i==border-1 && j>m && j<border-1){
            if(j<border-1) {
                M[i][j]=num;
                M[row][j]=((size*size)+1)-num;
                j++;
            }
            if(j>border-2){
                num++;
                M[i][col]=num;
                M[row][border-1]=((size*size)+1)-num;
                i--;
                while(i>m){
                    num++;
                    M[i][col]=num;
                    M[i][border-1]=((size*size)+1)-num;
                    i--;
                }
            }
            num++;
        }
        row++; col++;
        i=row; j=col+1;
        border--;
        sqSize-=2;
    }
    magicSquareOdd(M, num, m);
}

void magicSquareOdd(int M[][MAX], int num, int m){
    int row = m-1, col = m, i, j;
    int lastRow = row, lastColumn = col;
    
    M[row][col]=num; 
    for (i=num+1; i<num+9; i++){
        if (row-1<m-1)
            row = m+1;
        else row--;
        
        if (col+1 == m+2)
            col = m-1;
        else col++;
        
        if (M[row][col]==0)
            M[row][col] = i;
        else{
            row = lastRow;
            col = lastColumn;
            
            if (row+1 == m+2)
                row = m-1;
            else row++;
            M[row][col]=i;
        }
        lastRow = row;
        lastColumn = col;
    }
}

int main(){
    FILE * in = fopen("input.txt", "r");
    FILE * out = fopen("output.txt", "w");
    void fillSquare(int[][], int);
    void concentricSquare(int[][], int);
    
    int matrix[MAX][MAX], size;
    
    fscanf(in, "%d", &size);
    
    if (size%2==0 || in==NULL){
        printf("No solution possible");
        exit(0);
    }
    else{
        fillSquare(matrix, size);
        concentricSquare(matrix, size);
        printSquare(matrix, size, out);
    }
    
    return 0;
}