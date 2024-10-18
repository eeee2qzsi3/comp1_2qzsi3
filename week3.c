#include <stdio.h>
#define MAXSIZE 10

char cmd;

int rowsA = 1;
int columnsA = 1;
int rowsB = 1;
int columnsB = 1;
int rowsC = 1;
int columnsC = 1;




void print ( float matrix[MAXSIZE][MAXSIZE], int rows, int columns, char name){
    printf("Matrix %c (%d X %d):\n", name, rows, columns);
    for (int i = 0; i<rows; i++){//줄 바꿈꿈
        for(int j = 0; j<columns; j++){
            printf("%8.2f", matrix[i][j]);
            //문제에서 주어진대로 8자리너비(total), 소수점 2자리까지(accuracy)
        }
        printf("\n");
    }
}


void add(float matrixA[MAXSIZE][MAXSIZE], int rowsA, int columnsA, float matrixB[MAXSIZE][MAXSIZE], int rowsB, int columnsB, float matrixC[MAXSIZE][MAXSIZE], int rowsC, int columnsC){
        for(int i = 0; i < rowsA; i++){
            for(int j = 0; j < columnsA; j++){
                matrixC[i][j] = matrixA[i][j]+matrixB[i][j];
            }
        }
    }



void mult(float matrixA[MAXSIZE][MAXSIZE], int rowsA, int columnsA, float matrixB[MAXSIZE][MAXSIZE], int rowsB, int columnsB, float matrixC[MAXSIZE][MAXSIZE], int rowsC, int columnsC){
    for(int ic = 0; ic <rowsC; ic++){
        for(int jc = 0; jc < columnsC; jc++){
            matrixC[ic][jc] = 0; //다음 펑션진행할때 그 전값이반영돼서 나오는거 방지지
        }
    }
    
    
    
    for (int i = 0; i < rowsA; i++){
        for(int jb = 0; jb < columnsB; jb++){
            for(int jaib = 0; jaib < columnsA; jaib++){//columnsA = rowsB  같이 증가함함
                matrixC[i][jb] += matrixA[i][jaib] * matrixB[jaib][jb];
            }
        }
    }
}



void printRecursive(float matrixA[MAXSIZE][MAXSIZE], int rowsA, int columnsA, int currentRow, int currentColumn){
    float current = 0.0;
        if (rowsA==currentRow && columnsA == currentColumn){
            printf("exit printRecursive with current row=%d column=%d\n", currentRow, currentColumn);
        } else {
            for(int i = 0; i<rowsA; i++){
                for(int j = 0; j<columnsA; j++){
                    currentRow=i;
                    currentColumn=j;
                    printf("enter printRecursive with current row=%d column=%d\n", currentRow, currentColumn);
                    
                }
            } 
            currentRow = currentRow + 1;
            printf("enter printRecursive with current row=%d column=%d\n", currentRow, 0);
            printf("finished the recursion with current row=%d column=%d\n", currentRow, 0);
            for(int i = rowsA-1; i>=0; i--){
                for(int j = columnsA-1; j>=0; j--){
                    currentRow=i;
                    currentColumn=j;
                    current = matrixA[i][j];
                    printf("%8.2f\n", current);
                    printf("exit printRecursive with current row=%d column=%d\n", currentRow, currentColumn);
                }
            }
            
        }
}




void minorMatrix(float matrixA[MAXSIZE][MAXSIZE], int rowsA, int columnsA, int r, int c, float min[MAXSIZE][MAXSIZE]){
    int newrow = 0;
    
    for(int i = 0; i<rowsA;i++){
        if(r == i){
            continue;
        }
        int newcol=0;//예)첫번째 행이 실행되었을때 newcol은 2가 되었고
        //다음 행에서 처리할때도 그대로 2부터 시작하는 문제를 피하기 위해
        // newcol을 각 행 처리 전마다 0으로 다시 초기화해야됨됨
        for (int j = 0; j<columnsA; j++){
            if(c == j){
                continue;
            }
            min[newrow][newcol]=matrixA[i][j];
            newcol++;
        }
        newrow++;
    }
}



float determinant (float matrixA[MAXSIZE][MAXSIZE], int rowsA, int columnsA){
    float det = 0.0;
    //❇️❇️❇️condition ? value_if_true: value_if_false
    // The determinant of a 1x1 matrix is that number itself
    
    if(rowsA==1 && columnsA==1){
        det=matrixA[0][0];
    }else if(rowsA==2 && columnsA==2){
        det = matrixA[0][0]*matrixA[1][1]-matrixA[0][1]*matrixA[1][0];
    } else {
        float minor[MAXSIZE][MAXSIZE] = {0};
        for (int i =0; i<columnsA; i++){
            int sign = (i%2==0) ? 1:-1;
            minorMatrix(matrixA, rowsA, columnsA, 0, i, minor);
            det += sign* matrixA[0][i]*determinant(minor,rowsA-1,columnsA-1);//minorMAtrix에서 하나씩 주니까까
        }
    }
    printf("%d", rowsA);
    //재귀함수가 실행될때마다 행의 크기rowsA가 줄어들면서 이값이 출력됨됨
    return det;
    
}




int main(void)
{
    //define three two-dimensional matrices in your main function of 
    //MAXSIZE by MAXSIZE float elements
     float matrixA[MAXSIZE][MAXSIZE] = {0};
     //{}를 안쓰면 배열이 초기화 되지 않음음
     float matrixB[MAXSIZE][MAXSIZE] = {0};
     float matrixC[MAXSIZE][MAXSIZE] = {0};
     
     
    do{
        printf("Command? ");
        scanf(" %c", &cmd);
        
        switch (cmd){
            case 'q':
                printf("Bye!\n");
            break;
            
            case 'a':
                print(matrixA, rowsA, columnsA, 'A');
            break;
            
            case 'b':
                print(matrixB, rowsB, columnsB, 'B');
            break;
            
            case 'c':
                print(matrixC, rowsC, columnsC, 'C');
            break;
            
            
            
            
            case 'I':
            
                int trA = 0;
                int tcA = 0;
                
                printf("Size of matrix A (rows columns)? ");
                scanf(" %d %d", &trA, &tcA);
                if (trA != tcA || trA > MAXSIZE || tcA > MAXSIZE || trA > 10 || tcA > 10 || trA < 1 || tcA < 1){
                    printf("Rows & columns must be equal and between 1 and 10\n");
                }else{
                    for (int i = 0; i<trA; i++){
                        for (int j = 0; j < tcA; j++){
                            if (j == i){
                                matrixA[i][j] = 1;
                                
                                //rowsA = trA;
                                //columnsA = tcA;
                                //✅❇️setIdentityMatrix(matrixA,rowsA);
                            } else {
                                matrixA[i][j] = 0;
                            }
                        }// printf("\n"); 
                        // 여기서 프린트하는거 아니니까 쓰면 안됨됨
                    }
                    rowsA = trA;
                    columnsA = tcA;
                }
            break;
            
            
            
            
            case 'A':
                //int trA = 0;
                //int tcA = 0;
                
                printf("Size of matrix A (rows columns)? ");
                scanf(" %d %d", &trA, &tcA);
                if (trA > MAXSIZE || tcA > MAXSIZE || trA > 10 || tcA > 10 || trA < 1 || tcA < 1){
                    printf("Rows & columns must be between 1 and 10\n");
                } else {
                    for(int i = 0; i < trA; i++){
                        printf("Row %d? ", i);
                        for(int j = 0; j<tcA; j++){
                            scanf(" %f", &matrixA[i][j]);
                        }
                    }
                    rowsA = trA;
                    columnsA =tcA;
                }
            break;
            
            case 'B':
                for(int i = 0; i < rowsA; i++){
                    for (int j = 0; j< columnsA ; j++){
                        matrixB[i][j]=matrixA[i][j];
                    }
                }
                rowsB = rowsA;
                columnsB = columnsA;
            break;
            
            case '+':
                if(rowsA == rowsB && columnsA == columnsB){ //이게 맞을때만 실행될수있게 해야됨됨
                    rowsC = rowsA;
                    columnsC = columnsA;
                    add(matrixA, rowsA, columnsA, matrixB, rowsB, columnsB, matrixC, rowsC, columnsC);
                } else {
                    printf("Dimensions of A & B do not match\n");
                }
            break;
            
            
            case '*':
                if(columnsA != rowsB){
                    printf("Dimensions of A & B do not match\n");
                } else {
                    rowsC = rowsA;
                    columnsC = columnsB;
                    // void mult 에 위에있는 rowsC랑columnsC안넣는 이유
                    //void mult = 사진(복사본), case '*'=실물
                    //함수에 복사본을 주면, 함수안에서 아무리 matrixC의 크기를 바꿔도 실제로 바뀌지 않음음
                    mult(matrixA, rowsA, columnsA, matrixB, rowsB, columnsB, matrixC, rowsC, columnsC);
                }
            break;
            
            
            case 't':
                int trowsA = 0;
                int tcolumnsA = 0;
                float tmatrixA[MAXSIZE][MAXSIZE] = {0};
                
                for (int i = 0; i<columnsA; i++){
                    for (int j = 0; j<rowsA; j++){
                        tmatrixA[i][j]=matrixA[j][i];
                    }
                }
                
                for (int i = 0; i<columnsA; i++){
                    for (int j = 0; j<rowsA; j++){
                        matrixA[i][j]=tmatrixA[i][j];
                        //matirxA[i][j]와 matirxA[j][i]가 바로 교환되면안됨
                        // 서로 덮어쓰여져 버림
                    }
                }
                
                trowsA=columnsA;
                tcolumnsA=rowsA;
                rowsA = trowsA;
                columnsA = tcolumnsA;
            break;
            
            
            
            case 'm':
                int r =0;
                int c=0;
                printf("Remove which row & column of matrix A? ");
                scanf(" %d %d", &r, &c);
                if (rowsA<2 || columnsA<2){//에러를 먼저 체크해야됨 실행하기전에
                    printf("Matrix A must have at least two rows & columns\n");
                    }
                else if (r < rowsA && r>=0 && c< columnsA && c>=0){
                rowsC = rowsA -1;
                columnsC = columnsA -1;
                minorMatrix(matrixA, rowsA, columnsA, r, c, matrixC);
                } else {
                    printf("Rows & columns must be between 0 and %d & %d, respectively\n", rowsA, columnsA);
                }
            break;
            
            
            
            case 'd':
            if(rowsA != columnsA){
                printf("Matrix A must be square\n");
            } else{
            float det =0.0;
            det = determinant(matrixA,rowsA,columnsA);
            printf("\n");
            printf("The determinant is %f\n", det);
            }
            break;
            
            
            case 'p':
                printRecursive(matrixA,rowsA,columnsA,0,0);
            break;
            
            
            default:
                printf("Unknown command '%c'\n", cmd);
            break;
        }
    } while (cmd != 'q');
    
    return 0;
}
