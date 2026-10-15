#include <stdlib.h>
#include "algoritmos.h"

/*  BubbleSort*/
void Ordena_bubbleSort(int *v, int n){
    int i, continua, aux, fim = n;
    do{
        continua = 0;
        for(i = 0; i < fim - 1; i++){
            if(v[i] > v[i+1]){
                aux = v[i];
                v[i] = v[i+1];
                v[i+1] = aux;
                continua = i;
            }
        }
        fim--;
    }while(continua != 0);
}

void bubbleSort(int *v, int n){
    Ordena_bubbleSort(v, n);
}

/*  SelectionSort */
void Ordena_selectionSort(int *v, int n){
    int i, j, menor, troca;
    for(i = 0; i < n - 1; i++){
        menor = i;
        for(j = i + 1; j < n; j++){
            if(v[j] < v[menor]){
                menor = j;
            }
        }
        if(i != menor){
            troca = v[i];
            v[i] = v[menor];
            v[menor] = troca;
        }
    }
}

void selectionSort(int *v, int n){
    Ordena_selectionSort(v, n);
}

/*  InsertionSort */
void Ordena_insertionSort(int *v, int n){
    int i, j, aux;
    for(i = 1; i < n; i++){
        aux = v[i];
        for(j = i; (j > 0) && (aux < v[j-1]); j--){
            v[j] = v[j-1];
        }
        v[j] = aux;
    }
}

void insertionSort(int *v, int n){
    Ordena_insertionSort(v, n);
}

/*  MergeSort */
void merge(int *v, int inicio, int meio, int fim){
    int *temp, p1, p2, tamanho, i, j, k;
    int fim1 = 0, fim2 = 0;
    tamanho = fim - inicio + 1;
    p1 = inicio;
    p2 = meio + 1;
    temp = (int*) malloc(tamanho * sizeof(int));
    if(temp != NULL){
        for(i = 0; i < tamanho; i++){
            if(!fim1 && !fim2){
                if(v[p1] < v[p2]){
                    temp[i] = v[p1];
                    p1++;
                }else{
                    temp[i] = v[p2];
                    p2++;
                }
                if(p1 > meio){
                    fim1 = 1;
                }
                if(p2 > fim){
                    fim2 = 1;
                }
            }else{
                if(!fim1){
                    temp[i] = v[p1++];
                }else{
                    temp[i] = v[p2++];
                }
            }
        }
        for(j = 0, k = inicio; j < tamanho; j++, k++){
            v[k] = temp[j];
        }
        free(temp);
    }
}

void Ordena_mergeSort(int *v, int inicio, int fim){
    int meio;
    if(inicio < fim){
        meio = (inicio + fim)/2;
        Ordena_mergeSort(v, inicio, meio);
        Ordena_mergeSort(v, meio + 1, fim);
        merge(v, inicio, meio, fim);
    }
}

void mergeSort(int *v, int n){
    Ordena_mergeSort(v, 0, n - 1);
}

/*  QuickSort Conforme o
   proprio material (slide 26), com vetor ja ordenado ou invertido o
   algoritmo cai no pior caso O(n^2) e a recursao atinge profundidade n.
   Por isso o projeto do CodeBlocks foi configurado com pilha ampliada
   (opcao do linker -Wl,--stack), evitando stack overflow nos testes de
   comportamento natural / pior caso com vetores grandes.
   A unica alteracao em relacao ao slide e a ordem das condicoes nos
   while (testar o limite ANTES de acessar v[]), que evita leitura fora
   do vetor sem mudar o comportamento do algoritmo. */
int particiona(int *v, int inicio, int fim){
    int esq, dir, pivo, aux;
    esq = inicio;
    dir = fim;
    pivo = v[inicio];
    while(esq < dir){
        while(esq <= fim && v[esq] <= pivo){
            esq++;
        }
        while(dir >= inicio && v[dir] > pivo){
            dir--;
        }
        if(esq < dir){
            aux = v[esq];
            v[esq] = v[dir];
            v[dir] = aux;
        }
    }
    v[inicio] = v[dir];
    v[dir] = pivo;
    return dir;
}

void Ordena_quickSort(int *v, int inicio, int fim){
    int pivo;
    if(fim > inicio){
        pivo = particiona(v, inicio, fim);
        Ordena_quickSort(v, inicio, pivo - 1);
        Ordena_quickSort(v, pivo + 1, fim);
    }
}

void quickSort(int *v, int n){
    Ordena_quickSort(v, 0, n - 1);
}

/* Algoritmos apresentados nos seminários*/


/*  ShellSort */
void shellSort(int *vetor, int tamanho){
    int i, j, valorAtual;
    int h = tamanho / 2;
    while(h > 0){
        for(i = h; i < tamanho; i++){
            valorAtual = vetor[i];
            j = i;
            while(j > h - 1 && valorAtual <= vetor[j - h]){
                vetor[j] = vetor[j - h];
                j = j - h;
            }
            vetor[j] = valorAtual;
        }
        h = h / 2;
    }
}

/*  HeapSort */
void criaHeap(int *vet, int i, int f){
    int aux = vet[i];
    int j = i * 2 + 1;
    while(j <= f){
        if(j < f){
            if(vet[j] < vet[j + 1]) j = j + 1;
        }
        if(aux < vet[j]){
            vet[i] = vet[j];
            i = j;
            j = 2 * i + 1;
        }else{
            j = f + 1;
        }
    }
    vet[i] = aux;
}

void heapSort(int *vet, int N){
    int i, aux;
    for(i = (N - 1) / 2; i >= 0; i--){
        criaHeap(vet, i, N - 1);
    }
    for(i = N - 1; i >= 1; i--){
        aux = vet[0];
        vet[0] = vet[i];
        vet[i] = aux;
        criaHeap(vet, 0, i - 1);
    }
}

/*  BucketSort
   ADAPTACAO: o codigo original usava baldes de tamanho fixo (valores[10]).
   Com centenas de milhares de elementos varios baldes recebem mais de 10
   valores e o vetor estourava. Adaptamos cada balde e
   alocadando dinamicamente com o tamanho exato que precisa. A largura de cada
   balde (TAM) e a ordenacao interna por InsertionSort foram mantidas. */
#define TAM 10

void ordena_InsertionSort(int *v, int n){
    int i, j, aux;
    for(i = 1; i < n; i++){
        aux = v[i];
        for(j = i; (j > 0) && (aux < v[j - 1]); j--){
            v[j] = v[j - 1];
        }
        v[j] = aux;
    }
}

void bucketSort(int *V, int N){
    int i, j, maior, menor, nroBaldes, pos, b;
    int *qtd, *preenchido, **baldes;

    maior = menor = V[0];
    for(i = 1; i < N; i++){
        if(V[i] > maior) maior = V[i];
        if(V[i] < menor) menor = V[i];
    }

    nroBaldes = (maior - menor) / TAM + 1;
    qtd        = (int *)  calloc(nroBaldes, sizeof(int));
    preenchido = (int *)  calloc(nroBaldes, sizeof(int));
    baldes     = (int **) malloc(nroBaldes * sizeof(int *));

    for(i = 0; i < N; i++){
        qtd[(V[i] - menor) / TAM]++;
    }
    for(i = 0; i < nroBaldes; i++){
        baldes[i] = (qtd[i] > 0) ? (int *) malloc(qtd[i] * sizeof(int)) : NULL;
    }
    for(i = 0; i < N; i++){
        b = (V[i] - menor) / TAM;
        baldes[b][preenchido[b]++] = V[i];
    }
    pos = 0;
    for(i = 0; i < nroBaldes; i++){
        if(qtd[i] > 0){
            ordena_InsertionSort(baldes[i], qtd[i]);
            for(j = 0; j < qtd[i]; j++){
                V[pos++] = baldes[i][j];
            }
            free(baldes[i]);
        }
    }
    free(baldes);
    free(qtd);
    free(preenchido);
}

/*  RadixSort
    ADAPTACAO: optamos por simplificar o código */
void radixSort(int *v, int n){
    int i, maior, exp;
    int *saida = (int *) malloc(n * sizeof(int));
    int cont[10];
    if(!saida) return;

    maior = v[0];
    for(i = 1; i < n; i++) if(v[i] > maior) maior = v[i];

    for(exp = 1; maior / exp > 0; exp *= 10){
        for(i = 0; i < 10; i++) cont[i] = 0;
        for(i = 0; i < n; i++) cont[(v[i] / exp) % 10]++;
        for(i = 1; i < 10; i++) cont[i] += cont[i - 1];
        for(i = n - 1; i >= 0; i--){
            saida[cont[(v[i] / exp) % 10] - 1] = v[i];
            cont[(v[i] / exp) % 10]--;
        }
        for(i = 0; i < n; i++) v[i] = saida[i];
    }
    free(saida);
}

/*  CountingSort  */
void countingSort(int *v, int tamanho){
    int i, maior;
    int *cont, *saida;

    maior = v[0];
    for(i = 1; i < tamanho; i++){
        if(v[i] > maior) maior = v[i];
    }
    cont  = (int *) calloc(maior + 1, sizeof(int));
    saida = (int *) malloc(tamanho * sizeof(int));

    for(i = 0; i < tamanho; i++) cont[v[i]]++;
    for(i = 1; i <= maior; i++) cont[i] = cont[i] + cont[i - 1];
    for(i = tamanho - 1; i >= 0; i--){
        saida[cont[v[i]] - 1] = v[i];
        cont[v[i]]--;
    }
    for(i = 0; i < tamanho; i++) v[i] = saida[i];

    free(cont);
    free(saida);
}

/* TimSort */
#define MIN_RUN 32

int minimo(int a, int b){ return (a < b) ? a : b; }

void inverte(int arr[], int start, int end){
    while(start < end){
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++; end--;
    }
}

void insertionSortTim(int arr[], int left, int right){
    for(int i = left + 1; i <= right; i++){
        int temp = arr[i];
        int j = i - 1;
        while(j >= left && arr[j] > temp){
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

void mergeTim(int arr[], int l, int m, int r){
    int len1 = m - l + 1;
    int len2 = r - m;
    int *left  = (int *) malloc(len1 * sizeof(int));
    int *right = (int *) malloc(len2 * sizeof(int));

    for(int i = 0; i < len1; i++) left[i]  = arr[l + i];
    for(int i = 0; i < len2; i++) right[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;
    while(i < len1 && j < len2){
        if(left[i] <= right[j]) arr[k++] = left[i++];
        else                    arr[k++] = right[j++];
    }
    while(i < len1) arr[k++] = left[i++];
    while(j < len2) arr[k++] = right[j++];

    free(left);
    free(right);
}

void timSort(int arr[], int n){
    int i = 0;
    while(i < n){
        int runStart = i;
        int runEnd = i;
        if(i + 1 < n){
            if(arr[i] <= arr[i + 1]){
                while(runEnd + 1 < n && arr[runEnd] <= arr[runEnd + 1]) runEnd++;
            }else{
                while(runEnd + 1 < n && arr[runEnd] > arr[runEnd + 1]) runEnd++;
                inverte(arr, runStart, runEnd);
            }
        }
        int currentRunLength = runEnd - runStart + 1;
        if(currentRunLength < MIN_RUN){
            int targetEnd = minimo(runStart + MIN_RUN - 1, n - 1);
            insertionSortTim(arr, runStart, targetEnd);
            i = targetEnd + 1;
        }else{
            i = runEnd + 1;
        }
    }
    for(int size = MIN_RUN; size < n; size = 2 * size){
        for(int left = 0; left < n; left += 2 * size){
            int mid = left + size - 1;
            int right = minimo((left + 2 * size - 1), (n - 1));
            if(mid < right) mergeTim(arr, left, mid, right);
        }
    }
}
