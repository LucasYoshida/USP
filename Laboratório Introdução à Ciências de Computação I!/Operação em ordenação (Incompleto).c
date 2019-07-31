/*
***************************************************

	USP - ICMC
	LAB ICC2 - 2017
	
	Aula 13- Operacoes em Ordenacao

	Dezembro - 2017

	Lucas Noriyuki Yoshida - 10262586

****************************************************
*/
#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b){

    int t = *a;
    *a = *b;
    *b = t;
}

void bubblesort(int* vet, int* c, int* m, int n){

	int i, j;
	int aux;

	for (i = 0; i < n-1; i++){ 
		for (j = 0; j < n-i-1; j++){ 
        	if (vet[j] > vet[j+1]){
            	swap(&vet[j], &vet[j+1]);
        		aux = *m;
        		*m = aux + 1;
        	}
        	aux = *c;
        	*c = aux + 1;
    	}
    }

}

//**************************************************

void insertionsort(int* vet, int* c, int* m, int n){

	int i, key, j;
	int aux;

	for (i = 1; i < n; i++){
    	key = vet[i];
    	j = i-1;
    	while (j >= 0 && vet[j] > key){
        	vet[j+1] = vet[j];
        	j = j-1;
        	aux = *m;
        	*m = aux + 1;
        	aux = *c;
        	*c = aux + 1;
        }
    	vet[j+1] = key;
    	aux = *m;
        *m = aux + 1;
	}

}

//**************************************************

void merge(int* vet, int l, int n, int r, int* c, int* m){

	int i, j, k;
    int n1 = n - l + 1;
    int n2 =  r - n;
 
    int L[n1], R[n2];
 
    for (i = 0; i < n1; i++)
        L[i] = vet[l + i];
    for (j = 0; j < n2; j++)
        R[j] = vet[n + 1+ j];
 
    i = 0; 
    j = 0; 
    k = l;

    int aux; 
    
    while (i < n1 && j < n2){
        if (L[i] <= R[j]){
            vet[k] = L[i];
            i++;
            aux = *c;
            *c = aux + 1;
            aux = *m;
            *m = aux + 1;
       	}
        else{
            vet[k] = R[j];
            j++;
            aux = *c;
            *c = aux + 1;
            aux = *m;
            *m = aux + 1;
        }
        k++;
    }
 
    while (i < n1){
        vet[k] = L[i];
        i++;
        k++;
        aux = *m;
        *m = aux + 1;
    }
 
    while (j < n2){
        vet[k] = R[j];
        j++;
        k++;
        aux = *m;
        *m = aux + 1;
    }

}

void mergesort(int* vet, int l, int r, int* c, int* m){

    if (l < r){
        
        int n = l+(r-l)/2;
 
        mergesort(vet, l, n, c, m);
        mergesort(vet, n+1, r, c, m);
 
        merge(vet, l, n, r, c, m);
    }

}

//**************************************************

void heapify(int* vet, int n, int i, int* c, int* m){

    int largest = i;  
    int l = 2*i + 1;  
    int r = 2*i + 2;

    int aux;

    if (l < n && vet[l] > vet[largest]){
        largest = l;
    	aux = *c;
 		*c = aux + 1;
    }
 
    if (r < n && vet[r] > vet[largest]){
        largest = r;
    	aux = *c;
 		*c = aux + 1;
    }
 
    if (largest != i){
        swap(&vet[i], &vet[largest]);
 		aux = *m;
 		*m = aux + 1;

        heapify(vet, n, largest, c, m);
    }

}
 
void heapsort(int* vet, int n, int* c, int* m){

	int aux;

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(vet, n, i, c, m);
 
    for (int i=n-1; i>=0; i--){
        swap(&vet[0], &vet[i]);
        aux = *m;
        *m = aux + 1;
 
        heapify(vet, i, 0, c, m);
    }
}

//**************************************************

int partition (int* vet, int low, int high, int* c, int* m){

    int pivot = vet[high];
    int i = (low - 1);
 
    int aux;

    for (int j = low; j <= high- 1; j++){
        if (vet[j] < pivot){
            
            i++;
            aux = *c;
            *c = aux + 1;

            swap(&vet[i], &vet[j]);

        }
    }

    swap(&vet[i + 1], &vet[high]);
    aux = *m;
    *m = aux + 1;

    return (i + 1);
}

void quicksort(int* vet, int low, int high, int* c, int* m){

	int aux;

    if (low < high){
        int pi = partition(vet, low, high, c, m);

        aux = *m;
    	*m = aux + 1;

        quicksort(vet, low, pi - 1, c, m);
        quicksort(vet, pi + 1, high, c, m);
    }
}

//**************************************************

void copiavet(int* vet1, int* vet2, int n){

	for(int cont = 0; cont < n; cont++){
		vet2[cont] = vet1[cont];
	}

}

//**************************************************

void achamaxmin(int* vet, int n, int* min, int* max){

	int minimo = vet[0];
	*min = 0;

	for(int cont = 0; cont < n; cont++){
		if(vet[cont] < minimo){
			minimo = vet[cont];
			*min = cont;
		}
	}

	int maximo = vet[0];
	*max = 0;

	for(int cont = 0; cont < n; cont++){
		if(vet[cont] > maximo){
			maximo = vet[cont];
			*max = cont;
		}
	}

}

//**************************************************

int main(){

	int o;		//nuemro de sorts a serem feitos
	int n;		//numero de numeros a serem ordenados

	int* vet;		//vetor de numeros a serem ordenados
	int* aux;		//vetor auxiliar para ordenar

	vet = (int*)calloc(30001, sizeof(int));
	aux = (int*)calloc(30001, sizeof(int));

	char sort[5][20];		//quais sorts vao ser utilizados

	scanf("%d %d", &o, &n);

	int c[5] = {0};		//numero de comparacoes
	int m[5] = {0};		//numero de movimentacoes

	for(int cont = 0; cont < o; cont++){
		scanf("%s", sort[cont]);
		getchar();		//pega espaco
	}

	for (int cont = 0; cont < n; cont ++){
		scanf("%d", &vet[cont]);
	}

	for(int cont = 0; cont < o; cont++){
		copiavet(vet, aux, n);
		//faz bubble sort
		if(sort[cont][0] == 'B')
			bubblesort(aux, &c[cont], &m[cont], n);
		//faz insertion sort
		else if(sort[cont][0] == 'I')
			insertionsort(aux, &c[cont], &m[cont], n);	
		//faz merge sort
		else if(sort[cont][0] == 'M')
			mergesort(aux, 0, n -1, &c[cont], &m[cont]);
		//faz heap sort
		else if(sort[cont][0] == 'H')
			heapsort(aux, n, &c[cont], &m[cont]);
		//faz quick sort
		else if(sort[cont][0] == 'Q')
			quicksort(aux, 0, n-1, &c[cont], &m[cont]);	
	}

	int minM, maxM;
	int minC, maxC;

	achamaxmin(c, o, &minC, &maxC);
	achamaxmin(m, o, &minM, &maxM);

	printf("Menor C: %s\n", sort[minC]);
	printf("Maior C: %s\n", sort[maxC]);
	printf("Menor M: %s\n", sort[minM]);
	printf("Maior M: %s\n", sort[maxM]);

	free(vet);
	free(aux);

	return 0;

}