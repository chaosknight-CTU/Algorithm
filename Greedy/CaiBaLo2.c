# include <stdio.h>
# include <string.h>

# define MAX_N 100

/* khai bao cau truc "Do vat" */
typedef struct{
    char Name[MAX_N];
    int weight, value, maxSolution, solution;
}Item;

/* khai bao cau truc danh sach */
typedef struct{
    Item items[MAX_N]; // mang luu tru cac do vat
    int n; // so luong do vat
}List;

/* khoi tao danh sach */
void makeNullList(List *L){
	L->n = 0;
}

void readList(List *L, int *weightOfBag){
    FILE *f = fopen("CaiBalo2.txt", "r");
	char name[MAX_N];
	int weight, value;
    Item temp;
    makeNullList(L);
    /* doc vao trong luong cua balo */
    fscanf(f, "%d", weightOfBag);
    /* doc vao cac gia tri cua tung do vat */
	while (!feof(f)){
        fscanf(f, "%d %d %d", &temp.weight, &temp.value, &temp.maxSolution);
        fgets(temp.Name, 50, f);
        if (temp.Name[strlen(temp.Name)-1] == '\n')
            temp.Name[strlen(temp.Name)-1] = '\0';
        L->items[L->n++] = temp;
	}
	fclose(f);
}

void printList(List *L){
    int i;
    for (i=0; i < L->n; i++)
        printf("%d %d %d %s\n", L->items[i].weight, L->items[i].value,
        L->items[i].maxSolution, L->items[i].Name);
}

void swap(Item *x, Item *y){
	Item temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void bubbleSort(List *L){
	int i, j;
    float price1, price2;
	for (i = L->n-1; i >=1; i--){
		for (j=0; j < i; j++){
            price1 = L->items[j].value / (float)L->items[j].weight;
            price2 = L->items[j+1].value / (float)L->items[j+1].weight;
			if (price1 < price2)
                swap(&L->items[j], &L->items[j+1]);
		}
	}
}

void bag(List *L, int weightOfBag){
    /* sap xep danh sach giam dan */
    bubbleSort(L);
    int i, totalWeight = 0, totalValue = 0;
    for (i=0; i < L->n; i++){
        /* tinh so luong do vat co the lay */
        L->items[i].solution = weightOfBag/L->items[i].weight;
        /* neu so luong do vat co the lay lon hon
        so luong do vat toi da */ 
        if (L->items[i].solution > L->items[i].maxSolution)
            L->items[i].solution = L->items[i].maxSolution;
        totalWeight += L->items[i].weight * L->items[i].solution;
        totalValue += L->items[i].value;
        weightOfBag -= L->items[i].weight * L->items[i].solution;
    }

    /* in ket qua */
    for (i=0; i < L->n; i++)
        printf("So luong do vat%s trong balo: %d\n", L->items[i].Name, L->items[i].solution);
    printf("Tong trong luong: %d\n", totalWeight);
    printf("Tong gia tri: %d\n", totalValue);
}

int main(){
    List L;
    int weightOfBag;
    readList(&L, &weightOfBag);
    bag(&L, weightOfBag);
    return 0;
}