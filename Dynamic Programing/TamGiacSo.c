# include <stdio.h>

# define MAX_N 50

/* khai bao kieu "square"
    - length: tong gia tri den o (i, j)
    - column: vi tri cua cot duoc chon truoc do */
typedef struct{
    int length, colunm;
}square;

/* doc du lieu */
void readFile(int A[][MAX_N], int *n){
    int i = 1, j, temp;
    char c;
    FILE *f = fopen("TamGiacSo.txt", "r");
    while (!feof(f)){
        for (j=1; j <= i; j++){
            fscanf(f, "%d", &temp);
            c = fgetc(f);
            A[i][j] = temp;
            if (c == '\n')
                break;
        }
        i++;
    }
    fclose(f);
    *n = i-1;
}

/* in tam giac so */
void printMatrix(int A[][MAX_N], int n){
    int i, j;
    printf("Tam giac so: \n");
    for (i=1; i <= n; i++){
        for (j=1; j <= i; j++)
            printf("%d ", A[i][j]);
        printf("\n");
    }
}

/* tim` o co F[][] lon nhat o dong` i-1*/
int CS_max(square F[][MAX_N], int i, int j){
    if (j == 1)
        return (F[i-1][1].length > F[i-1][2].length)? 1:2;
    if (j == i)
        return i-1;
    if (j == i-1)
        return (F[i-1][i-2].length > F[i-1][i-1].length)? i-2:i-1;
    if (F[i-1][j-1].length > F[i-1][j].length && F[i-1][j-1].length > F[i-1][j+1].length)
        return j-1;
    if (F[i-1][j].length > F[i-1][j-1].length && F[i-1][j].length > F[i-1][j+1].length)
        return j;
    if (F[i-1][j+1].length > F[i-1][j].length && F[i-1][j+1].length > F[i-1][j-1].length)
        return j+1;
}

/* khoi tao bang */
void initTable(int A[][MAX_N], int n, square F[][MAX_N]){
    int i, j;
    /* khoi tao bang cho 2 dong` dau` */
    F[1][1].length = A[1][1];
    F[1][1].colunm = 0;
    F[2][1].length = A[2][1] + F[1][1].length;
    F[2][1].colunm = 1;
    F[2][2].length = A[2][2] + F[1][1].length;
    F[2][2].colunm = 1;

    for (i=3; i <= n; i++)
        for (j=1; j <= i; j++){
            int k = CS_max(F, i, j);
            F[i][j].length = A[i][j] + F[i-1][k].length;
            F[i][j].colunm = k;
        }
}

/* in bang F */
void printTable(int n, square F[][MAX_N]){
    int i, j;
    printf("Bang so lieu F: \n");
    for (i=1; i <= n; i++){
        for (j=1; j <= i; j++)
            printf("%d-%d ", F[i][j].length, F[i][j].colunm);
        printf("\n");
    }
}

/* tim duong di trong tam giac so */
void findPath(int n, square F[][MAX_N]){
    int i, j, result[n+1], maxIndex = 1, total = 0;
    square max = F[5][1];
    /* tim F[][] lon nhat o dong` cuoi cung` */
    for (i=2; i <= n; i++)
        if (F[n][1].length > max.length){
            max = F[n][i];
            maxIndex = i;
        }
    result[n] = maxIndex;
    j = max.colunm;

    /* tim duong` di */
    for (i=n-1; i >= 1; i--){
        result[i] = j;
        j = F[i][j].colunm;
    }

    printf("Phuong an: \n");
    /* in duong` di */
    for (i=1; i <= n; i++){
        if (i == n)
            printf("(%d, %d)\n", i, result[i]);
        else
            printf("(%d, %d) -> ", i, result[i]);
        total += F[i][result[i]].length;
    }

    printf("Tong gia tri duong di: %d\n", total);
}

int main(){
    int A[MAX_N][MAX_N];
    square F[MAX_N][MAX_N];
    int n;
    readFile(A, &n);
    initTable(A, n, F);
    printMatrix(A, n);
    printTable(n, F);
    findPath(n, F);
    return 0;
}