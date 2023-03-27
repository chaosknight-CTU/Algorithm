# include <stdio.h>

# define MAX_N 100
# define oo (float)999999

// tao kieu "Cung"
typedef struct{
    float w; // w: trong so cung
    int u, v;
    int used;
}Edge;

typedef struct{
    Edge edges[MAX_N][MAX_N];
    int n, m; // n: so dinh, m: so cung
}Graph;

// khoi tao danh sach cung
void initGraph(Graph *pG, int n){
    pG->n = n;
    pG->m = 0;
}

// them cung
void addEdge(Graph *pG, int x, int y, float w){
    Edge temp;
    temp.u = x;
    temp.v = y;
    temp.w = w;
    temp.used = 0;
    pG->edges[x][y] = temp;
    temp.u = y;
    temp.v = x;
    pG->edges[y][x] = temp;
    pG->m++;
}

// kiem tra dinh x & dinh y co ke nhau khong
int adjacent(Graph *pG, int x, int y){
    return (pG->edges[x][y].w != 0 && pG->edges[y][x].w != 0);
}

// doc du lieu tu tap tin
void readGraph(Graph *pG){
    int n, u, v, i, j;
    float w;
    freopen("test.txt", "r", stdin);
    scanf("%d", &n);
    initGraph(pG, n);
    for (i=0; i < n; i++)
        for (j=0; j < n; j++){
            scanf("%f", &w);
            if (!adjacent(pG, i, j))
                addEdge(pG, i, j, w);
        }
}

// in do thi
void printGraph(Graph *pG){
    int i, j;
    for (i=0; i < pG->n; i++){
        for (j=0; j < pG->n; j++){
            printf("(%c, %c): %.02f ", pG->edges[i][j].u+97, pG->edges[i][j].v+97, pG->edges[i][j].w);
        }
        printf("\n");
    }
}

// tim cung co gia tri nho nhat
float minEdge(Graph *pG){
    float minEdge = oo;
    int i, j;
    for (i=0; i < pG->n; i++)
        for (j=0; j < pG->n; j++)
            if (i != j && !pG->edges[i][j].used && pG->edges[i][j].w < minEdge)
                minEdge = pG->edges[i][j].w;
    
    return minEdge;
}

/* tinh can duoi cua 1 node
    - totalValue: tong gia tri cua node cha
    - i: bac cua node trong cay
*/
float lowerBound(Graph *pG, float totaValue, int i){
    return totaValue + (pG->n-i) * minEdge(pG);
}

/* kiem tra chu trinh */
int isCycle(Edge x[], int k, int next){
    int i=0, flag = 0;
    while (i < k && !flag){
        if (next == x[i].u)
            flag = 1;
        else
            i++;
    }

    return flag;
}

/* cap nhat phuong an tam thoi */
void updateTempSolution(Graph *pG, float totalValue, float *tempMinValue, Edge x[], Edge result[]){
    int i;
    x[pG->n-1] = pG->edges[x[pG->n-2].v][x[0].u];
    totalValue = totalValue + x[pG->n-1].w;
    if (*tempMinValue > totalValue){
        *tempMinValue = totalValue;
        for (i=0; i < pG->n; i++)
            result[i] = x[i];
    }
}

/* giai bai toan bang thuat toan Nhanh Can */
void solution(Graph *pG, int i, int start, float *totalValue, float *lowerBoundd, float *tempMinValue, Edge x[], Edge result[]){
    int j;
    for (j=0; j < pG->n; j++){
        if (start != j && !pG->edges[start][j].used && !isCycle(x, i, j)){
            *totalValue = *totalValue + pG->edges[start][j].w;
            *lowerBoundd = lowerBound(pG, *totalValue, i+1);
            if (*lowerBoundd < *tempMinValue){
                x[i] = pG->edges[start][j];
                pG->edges[start][j].used = 1;
                pG->edges[j][start].used = 1;

                if (i == pG->n-2)
                    updateTempSolution(pG, *totalValue, tempMinValue, x, result);
                else
                    solution(pG, i+1, j, totalValue, lowerBoundd, tempMinValue, x, result);
            }

            *totalValue = *totalValue - pG->edges[start][j].w;
            pG->edges[start][j].used = 0;
            pG->edges[j][start].used = 0;
        }
    }
}

void printResult(Edge result[], int n){
    int i;
    float sum = 0.0;
    for (i=0; i < n; i++){
        sum += result[i].w;
        printf("%c %c: %.2f\n", result[i].u+97, result[i].v+97, result[i].w);
    }
    printf("%.2f\n", sum);
}

int main(){
    Graph G;
    readGraph(&G);
    Edge x[G.n];
    Edge result[G.n];
    float totalValue = 0.0, lowerBoundd = 0.0, tempMinValue = oo;
    solution(&G, 0, 3, &totalValue, &lowerBoundd, &tempMinValue, x, result);
    printResult(result, G.n);
    return 0;
}