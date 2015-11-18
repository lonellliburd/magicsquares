/*
    Name: Lonell Liburd
    ID: 809001220
    Assignment: 5
    Magic Squares: Odd, Singly Even, Doubly Even
*/

# include <stdio.h>

# define MAX 300

void magicNumber(int M[][MAX], int N){
    int i, j, sum1=0, sum2=0, sum3=0, sum4=0;
    for (i=0; i<N; i++){
        sum1+=M[0][i];
        sum2+=M[i][0];
        sum4+=M[i][(N-1)-i];
        for (j=0; j<N; j++)
            if (i==j)sum3+=M[i][j];
    }
    printf("Sum 0th Row %d\n", sum1);
    printf("Sum 0th Column %d\n", sum2);
    printf("Sum L-R diagonal %d\n", sum3);
    printf("Sum R-L diagonal %d\n", sum4);
}
    
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

void doL(int M[][MAX], int i, int j, int num){
    M[i][j]=num;
    M[i+1][j-1]=num+1;
    M[i+1][j]=num+2;
    M[i][j-1] = num+3;
}

void doU(int M[][MAX], int i, int j, int num){
    M[i][j-1]=num;
    M[i+1][j-1]=num+1;
    M[i+1][j]=num+2;
    M[i][j]=num+3;
}

void doX(int M[][MAX], int i, int j, int num){
    M[i][j-1]=num;
    M[i+1][j]=num+1;
    M[i+1][j-1]=num+2;
    M[i][j]=num+3;
}

void magicSquareOdd(int M[][MAX], int size){
    int row = 0, col = size/2, i, j;
    int lastRow = row, lastColumn = col;
    int n = size*size;
    
    M[row][col]=1; 
    for (i=2; i<n+1; i++){
        if (row-1<0) 
            row = size-1;
        else row--;
        
        if (col+1 == size)
            col = 0;
        else col++;
        
        if (M[row][col]==0)
            M[row][col] = i;
        else{
            row = lastRow;
            col = lastColumn;
            
            if (row+1 == size)
                row = 0;
            else row++;
            M[row][col]=i;
        }
        lastRow = row;
        lastColumn = col;
    }
}

void magicSquareEven(int M[][MAX], int size){
    int returnM(int);
    int m =  (size-2)/4; 
    int L = ((m+1)*2)-1;
    int U = ((m+1)*2)+1;
    int X = ((m-1)*2)-1;
    
    int row = 0, col = (size/2), i, j;
    int lastRow = row, lastColumn = col;
    int n = size*size;
    int num = 1;
    
    doL(M, row, col, num);
    num+=4;
     
    while(num<n+1){
        if (row-2<0) 
            row = size-2;
        else row-=2;
        
        if (col+2 > size)
            col = 1;
        else col+=2;
        
        if (M[row][col]==0){
            if (row<=L){ //do L
                if(row==m*2 && col==(m*2)+1)
                    doU(M, row, col, num);
                else 
                    doL(M,row, col, num);
            }   
            else if (row>L && row <=U){
                if(row==(m+1)*2 && col==((m+1)*2)-1)
                    doL(M, row, col, num);
                else 
                    doU(M, row, col, num); 
            }
            else if(row>U)
                doX(M, row, col, num);
            
            num+=4;
        }
        else{
            row=lastRow;
            col=lastColumn;
            
            if (row+4==size)
                row=0;
            else row+=4;
            col-=2;
            
        }
        lastRow = row;
        lastColumn = col;
    }
}

void magicSquareDoubly(int M[][MAX], int size){
    int s2=(size*size) + 1;
    int i,j,num=1;
     
    for(i=0; i<size; i++){
        for(j=0; j<size; j++){
            if(((i%4==0)||(i%4==3)) && ((j%4==0)||(j%4==3))){
                M[i][j]=s2-num;
                num++;
            }
            else if(((i%4==1)||(i%4==2)) && ((j%4==1)||(j%4==2))){
                M[i][j]=s2-num;
                num++;
            }
           
            else {
                M[i][j]=num;
                num++;
            }
        }
    }
}

int main(){
    FILE * in = fopen("input.txt", "r");
    FILE * out = fopen("output.txt", "w");

    void magicSquareOdd(int[][],int);
    void magicSquareEven(int[][], int);
    void magicSquareDoubly(int[][], int);
    void magicNumber(int[][], int);
    
    int matrix[MAX][MAX];
    int size, i;
    
    fscanf(in, "%d", &size);
    
    
    if (size<3 || in==NULL){
        printf("No solution Possible\n");
        exit(0);
    }
    
    fillSquare(matrix, size);
    
    if (size%2!=0)
        magicSquareOdd(matrix, size);
    
    else if (size%2==0 && size %4!=0)
        magicSquareEven(matrix, size);
        
    else if (size%4==0 && size%2==0)
        magicSquareDoubly(matrix, size);

    printSquare(matrix, size, out);    
    magicNumber(matrix, size);
    
    return 0;
}