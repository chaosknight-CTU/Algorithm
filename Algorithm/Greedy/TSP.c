# include <stdio.h>

# define MAX_N 100

// tao kieu "Cung"
typedef struct{
    float w;
    int u, v;
}Edge;

typedef struct{
    Edge edges[MAX_N];
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
    pG->edges[pG->m++] = temp;
}

// tinh bac cua 1 dinh
int degree(Graph *pG, int x){
    int degree = 0, i;
    for (i=0; i < pG->m; i++){
        if (pG->edges[i].u == x)
            degree++;
        if (pG->edges[i].v == x)
            degree++;
    }

    return degree;
}

// kiem tra 2 dinh co ke nhau khong
int adjacent(Graph *pG, int x, int y){
    int i;
    for (i=0; i < pG->m; i++){
        if ((pG->edges[i].u == x && pG->edges[i].v == y) || 
			(pG->edges[i].u == y && pG->edges[i].v == x)){
            return 1;
        }
    }

    return 0;
}

// doc du lieu tu tap tin
void readGraph(Graph *pG){
    int n, u, v, i, j;
    float w;
    freopen("TSP.txt", "r", stdin);
    scanf("%d", &n);
    initGraph(pG, n);
    for (i=1; i <= n; i++)
        for (j=1; j <= n; j++){
            scanf("%f", &w);
            if (w != 0 && !adjacent(pG, i, j))
                addEdge(pG, i, j, w);
        }
}

// in do thi
void printGraph(Graph *pG){
    int i;
    for (i=0; i < pG->m; i++){
        printf("%c %c %.02f\n", pG->edges[i].u + 64, pG->edges[i].v + 64, pG->edges[i].w);
    }
}
 
/* hoan doi 2 cung */
void swap(Edge *x, Edge *y){
	Edge temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

/* sap xep du lieu giam dan */
void bubbleSort(Graph *pG){
	int i, j;
	for (i = pG->m-1; i >=1; i--)
		for (j=0; j < i; j++)
			if (pG->edges[j].w > pG->edges[j+1].w)
				swap(&pG->edges[j], &pG->edges[j+1]);
}

int parent[MAX_N]; // luu dinh cha cua cac dinh

int findRoot(int u){
    while (parent[u] != u)
        u = parent[u];
    return u;
}

void TSP(Graph *pG, Graph *pT){
    // sap xep cac cung giam dan
    bubbleSort(pG);
    // khoi tao do thi chua chu trinh
    initGraph(pT, pG->n);
    int i, u, v, w, root_u, root_v;
    float total = 0;
    /* khoi tao dinh cha cua cac dinh */
    for (i=1; i <= pG->n; i++)
        parent[i] = i;

    /* tim duong di di qua tat ca cac dinh */
    for (i=0; i < pG->m; i++){
        u = pG->edges[i].u;
        v = pG->edges[i].v;
        w = pG->edges[i].w;
        root_u = findRoot(u);
        root_v = findRoot(v);
        if ((root_u != root_v) && (degree(pT, u) < 2) && (degree(pT, v) < 2)){
            addEdge(pT, u, v, w);
            parent[root_v] = root_u;
            total += w;
        }
    }
    /* tim 2 dinh con lai co bac la 1, noi 2 dinh lai de tao
    thanh chu trinh */
    for (i=0; i < pG->m; i++){
        u = pG->edges[i].u;
        v = pG->edges[i].v;
        w = pG->edges[i].w;
        if ((degree(pT, u) < 2) && (degree(pT, v) < 2)){
            addEdge(pT, u, v, w);
            total += w;
        }
    }
    
    /* in ket qua */
    printGraph(pT); 
    printf("Tong do dai cua chu trinh: %.02f\n", total);
}

int main(){
    Graph G, T;
    readGraph(&G);
    TSP(&G, &T);
    return 0;
}