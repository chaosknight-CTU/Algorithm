# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define MAX_N 100 // so p.tu toi da

// khai bao kieu "Money"
typedef struct{
	int numValue; // menh gia bang so
	char strValue[50]; // menh gia bang chu
}Money;

// khai bao danh sach chua cac menh gia
typedef struct{
	Money A[MAX_N];
	int n; // so luong p.tu trong danh sach
}List;

// khoi tao danh sach
void makeNullList(List *L){
	L->n = 0;
}

// doc cac menh gia tu file
void readList(List *L){
	FILE *f = fopen("ATM.txt", "r");
	char test[50];
	int temp;
	while (!feof(f)){
		fscanf(f, "%d", &temp);
		fgets(test, 50, f);
		if (test[strlen(test)-1] == '\n')
			test[strlen(test)-1] = '\0';
		L->A[L->n].numValue = temp;
		strcpy(L->A[L->n].strValue, test);
		L->n++;
	}
	fclose(f);
}

// in cac menh gia
void printList(List *L){
	int i;
	for (i=0; i < L->n; i++)
		printf("%d %s\n", L->A[i].numValue, L->A[i].strValue);
}

/* chuyen doi 2 gia tri */
void swap(Money *x, Money *y){
	Money temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

int findPivot(List *L, int start, int end){
	int firstkey = L->A[start].numValue;
	int k = start+1;
	while (k <= end && (L->A[k].numValue == firstkey)){
		k++;
	}

	if (k > end)
		return -1;
	else if (L->A[k].numValue > firstkey)
		return k;
	else
		return start;
}

int partition(List *L, int start, int end, int pivot){
	int Left = start, Right = end;

	while (Left < Right){
		while (L->A[Left].numValue >= pivot){
			Left++;
		}
		while (L->A[Right].numValue < pivot){
			Right--;
		}

		if (Left < Right){
			swap(&L->A[Left], &L->A[Right]);
		}
	}

	return Left;
}

void quickSort(List *L, int start, int end){
	int pivotIndex, k, pivot;
	pivotIndex = findPivot(L, start, end);
	
	if (pivotIndex != -1){
		pivot = L->A[pivotIndex].numValue;
		k = partition(L, start, end, pivot);
		quickSort(L, start, k-1);
		quickSort(L, k, end);
	}
}

void ATM(List *L, int money){
	int result[L->n];
	int i = 0, j, temp, total = 0;
	for (j=0; j < L->n; j++)
		result[j] = 0;
	while (money != 0){
		temp = money/L->A[i].numValue;
		money -= temp*L->A[i].numValue;
		result[i] = temp;
		i++;
	}

	for (i=0; i < L->n; i++){
		printf("So luong to co menh gia%s phai tra: %d\n", L->A[i].strValue, result[i]);
		total += result[i];
	}
	printf("Tong so to tien phai tra: %d\n", total);
}

int main(){
	List L;
    makeNullList(&L);
	readList(&L);
	int money;
	scanf("%d", &money);
	quickSort(&L, 0, L.n-1);
	ATM(&L, money);
    return 0;
}