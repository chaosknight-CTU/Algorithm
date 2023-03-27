# include <stdio.h>
# include <string.h>

# define MAX_N 50

/* khai bai cau truc "do vat":
    - weight: khoi luong cua do vat
    - value: gia tri cua do vat
    - unitPrice: don gia cua do vat do
    - name[]: ten cua do vat 
    - maxN: so luong do vat toi da co the chon
    - n: so luong ma do vat do duoc chon */
typedef struct{
    float weight, value, unitPrice;
    char name[MAX_N];
    int n;
}Item;

/* khai bao danh sach luu tru do vat:
    - items[]: mang luu tru cac do vat
    - n: so luong do vat co trong balo
    - w: trong luong con lai cua balo */
typedef struct{
    Item items[MAX_N];
    int n;
    float w;
}List;

void swap(Item *x, Item *y){
	Item temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

/* ham sap xep */
void bubbleSort(List *pL){
	int i, j;
	for (i = pL->n-1; i >=1; i--)
		for (j=0; j < i; j++){
            if (pL->items[j].unitPrice < pL->items[j+1].unitPrice)
                swap(&pL->items[j], &pL->items[j+1]);
        }
}

/* ham tim gia tri nho nhat */
int min(int a, int b){
    return (a<b)? a:b;
}

/* doc du lieu tu file */
void readList(List *pL){
    pL->n = 0;
    FILE *f = fopen("Balo3.txt", "r");
    fscanf(f, "%f", &pL->w);
    while (!feof(f)){
        fscanf(f, "%f %f", &pL->items[pL->n].weight, &pL->items[pL->n].value);
        fgets(pL->items[pL->n].name, MAX_N, f);
        if (pL->items[pL->n].name[strlen(pL->items[pL->n].name)-1] == '\n')
            pL->items[pL->n].name[strlen(pL->items[pL->n].name)-1] = '\0';
        pL->items[pL->n].unitPrice = pL->items[pL->n].value / pL->items[pL->n].weight;
        pL->items[pL->n].n = 0;
        pL->n++;
    }
    fclose(f);
}

/* in danh sach */
void printList(List *pL, int x[]){
    int i;
    for (i=0; i < pL->n; i++)
        printf("%.2f %.2f %.2f %s %d\n", pL->items[i].weight, pL->items[i].value, pL->items[i].unitPrice, pL->items[i].name, pL->items[i].n);
}

/* khoi tao nut Goc cua cay tim kiem phuong an */
void createRoot(float weight, float *remainingWeight, float *upperBound, float *tempMaxValue,
float *totalValue, float maxUnitPrice){
    *totalValue = 0.0;
    *remainingWeight = weight;
    *upperBound = weight * maxUnitPrice;
    *tempMaxValue = 0.0;
}

/* update phuong an tot nhat tam thoi */
void update(List *pL, float totalValue, float *tempMaxValue, int x[]){
    int i;
    if (*tempMaxValue < totalValue){
        *tempMaxValue = totalValue;
        for (i=0; i < pL->n; i++)
            pL->items[i].n = x[i];
    }
}

void solution(int i, float *totalValue, float *upperBound, float *remainingWeight,
float *tempMaxValue, int x[], List *pL){
    int j;
    /* so luong toi da co the chon 1 do vat */
    int maxQuantity = min(1, *remainingWeight / pL->items[i].weight);
    for (j = maxQuantity; j >= 0; j--){
        /* tinh tong gia tri, Tl con lai & can tren cua 1 nut */
        *totalValue = *totalValue + j * pL->items[i].value;
        *remainingWeight = *remainingWeight - j * pL->items[i].weight;
        *upperBound = *totalValue + *remainingWeight * pL->items[i+1].unitPrice;

        /* khai trien nhanh' */
        if (*upperBound > *tempMaxValue){
            x[i] = j;
            /* neu da xet den do vat cuoi cung hoac trong luong cua balo bang 0 thi cap nhat phuong an */
            if ((i == pL->n-1) || (*remainingWeight == 0.0))
                update(pL, *totalValue, tempMaxValue, x);
            /* nguoc lai thi goi de quy de xet do vat ke tiep */
            else
                solution(i+1, totalValue, upperBound, remainingWeight, tempMaxValue, x, pL);
        }

        /* quay lui */
        x[i] = 0;
        *totalValue = *totalValue - j * pL->items[i].value;
        *remainingWeight = *remainingWeight + j * pL->items[i].weight;
    }
}

int main(){
    List L;
    readList(&L);
    float upperBound, totalValue, remainingWeight, tempMaxValue;
    int x[L.n]; // luu tru phuong an tot nhat tam thoi
    bubbleSort(&L);
    createRoot(L.w, &remainingWeight, &upperBound, &tempMaxValue, &totalValue, L.items[0].unitPrice);
    solution(0, &totalValue, &upperBound, &remainingWeight, &tempMaxValue, x, &L);
    printList(&L, x);
    return 0;
}