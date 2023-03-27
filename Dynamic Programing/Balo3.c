# include <stdio.h>
# include <string.h>

# define MAX_N 50

/* khai bao cau truc "do vat" 
    - weight: trong luong cua do vat
    - value: gia tri cua do vat
    - number: so luong do vat duoc chon
*/
typedef struct{
    int weight, value, number;
    char name[MAX_N];
}Item;

/* khai bao cau truc danh sach
    - items[]: mang chua cac do vat
    - n: so luong do vat
    - w: tong trong luong cua balo
*/
typedef struct{
    Item items[MAX_N];
    int n, w;
}List;

/* doc du lieu tu tap tin */
void readList(List *pL){
    int i;
    FILE *f = fopen("Balo3.txt", "r");
    fscanf(f, "%d", &pL->w);
    pL->n = 0;
    while (!feof(f)){
        fscanf(f, "%d %d", &pL->items[pL->n].weight, &pL->items[pL->n].value);
        fgets(pL->items[pL->n].name, MAX_N, f);
        if (pL->items[pL->n].name[strlen(pL->items[pL->n].name)-1] == '\n')
            pL->items[pL->n].name[strlen(pL->items[pL->n].name)-1] = '\0';
        pL->items[pL->n].number = 0;
        pL->n += 1;
    }
    fclose(f);
}

/* in danh sach do vat */
void printList(List *pL){
    int i;
    for (i=0; i < pL->n; i++)
        printf("%d %d %s %d\n", pL->items[i].weight, pL->items[i].value, pL->items[i].name, pL->items[i].number);
}

int min(int a, int b){
    return (a < b)?a:b;
}

/* tao bang */
void initTable(List *pL, int X[][pL->w+1], int F[][pL->w+1]){
    int xk = 0, yk, k;
    int XMax, FMax, V;

    /* khoi tao dong` dau` tien cua 2 bang */
    for (V=0; V <= pL->w; V++){
        X[0][V] = min(1,V / pL->items[0].weight);
        F[0][V] = X[0][V] * pL->items[0].value;
    }

    /* khoi tao cac dong` con` lai */
    for (k=1; k < pL->n; k++)
        for (V=0; V <= pL->w; V++){
            FMax = F[k-1][V];
            XMax = 0;
            yk = min(1, V / pL->items[k].weight);

            for (xk=1; xk <= yk; xk++){
                if (F[k-1][V - xk*pL->items[k].weight] + (xk*pL->items[k].value) > FMax){
                    FMax = F[k-1][V - xk*pL->items[k].weight] + (xk*pL->items[k].value);
                    XMax = xk;
                }
            }
            F[k][V] = FMax;
            X[k][V] = XMax;
        }
}

void printTable(List *pL, int X[][pL->w+1], int F[][pL->w+1]){
    int V, k;
    for (k=0; k < pL->n; k++){
        for (V=0; V <= pL->w; V++)
            printf("%c%2d|%2d", 186, F[k][V], X[k][V]);
        printf("\n");
    }
}

void searchTable(List *pL, int X[][pL->w+1], int F[][pL->w+1]){
    int V = pL->w, k;
    for (k = pL->n-1; k >= 0; k--){
        pL->items[k].number = X[k][V];
        V -= X[k][V] * pL->items[k].weight;
    }
}

int main(){
    List L;
    readList(&L);
    int X[L.n][L.w+1], F[L.n][L.w+1];
    initTable(&L, X, F);
    printTable(&L, X, F);
    searchTable(&L, X, F);
    printList(&L);
    return 0;
}