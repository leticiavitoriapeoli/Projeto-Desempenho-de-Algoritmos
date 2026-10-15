#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/time.h>
#endif
#include "algoritmos.h"

#define RODADAS 10

void gerarAleatorio(int *v, int n);
void gerarCrescente(int *v, int n);
void gerarDecrescente(int *v, int n);
int  verificaOrdenado(int *v, int n);
void ordenar(int opcao, int *v, int n);
double medirTempo(int opcao, int n, int tipoVetor);
void executarTestes(int opcao, char *nome, int n);

int contadorSemente = 0;

int main(){
    int opcao, opcaoTamanho, n;
    char *nome;

    do{
        printf("\n------------ MENU PRINCIPAL ------------\n");
        printf("  1 - BubbleSort\n");
        printf("  2 - InsertionSort\n");
        printf("  3 - SelectionSort\n");
        printf("  4 - MergeSort\n");
        printf("  5 - QuickSort\n");
        printf("  6 - ShellSort\n");
        printf("  7 - HeapSort\n");
        printf("  8 - BucketSort\n");
        printf("  9 - RadixSort (LSD)\n");
        printf(" 10 - CountingSort\n");
        printf(" 11 - TimSort\n");
        printf("  0 - Sair\n");
        printf("Escolha o algoritmo: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:  nome = "BubbleSort";      break;
            case 2:  nome = "InsertionSort";   break;
            case 3:  nome = "SelectionSort";   break;
            case 4:  nome = "MergeSort";       break;
            case 5:  nome = "QuickSort";       break;
            case 6:  nome = "ShellSort";       break;
            case 7:  nome = "HeapSort";        break;
            case 8:  nome = "BucketSort";      break;
            case 9:  nome = "RadixSort"; break;
            case 10: nome = "CountingSort";    break;
            case 11: nome = "TimSort";         break;
            case 0:  printf("\nPrograma encerrado.\n"); continue;
            default: printf("Opcao invalida!\n");      continue;
        }

        printf("\n---------- QUANTIDADE DE ELEMENTOS (%s) ----------\n", nome);
        printf(" 1 - 10.000\n");
        printf(" 2 - 50.000\n");
        printf(" 3 - 100.000\n");
        printf(" 4 - 200.000\n");
        printf(" 5 - 500.000\n");
        printf(" 6 - 1.000.000\n");
        printf(" 0 - Voltar\n");
        printf("Escolha a quantidade: ");
        scanf("%d", &opcaoTamanho);

        switch(opcaoTamanho){
            case 1:  n = 10000;   break;
            case 2:  n = 50000;   break;
            case 3:  n = 100000;  break;
            case 4:  n = 200000;  break;
            case 5:  n = 500000;  break;
            case 6:  n = 1000000; break;
            case 0:  continue;
            default: printf("Opcao invalida!\n"); continue;
        }

        executarTestes(opcao, nome, n);

    }while(opcao != 0);

    return 0;
}

void ordenar(int opcao, int *v, int n){
    switch(opcao){
        case 1:  bubbleSort(v, n);    break;
        case 2:  insertionSort(v, n); break;
        case 3:  selectionSort(v, n); break;
        case 4:  mergeSort(v, n);     break;
        case 5:  quickSort(v, n);     break;
        case 6:  shellSort(v, n);     break;
        case 7:  heapSort(v, n);      break;
        case 8:  bucketSort(v, n);    break;
        case 9:  radixSort(v, n);     break;
        case 10: countingSort(v, n);  break;
        case 11: timSort(v, n);       break;
    }
}

void gerarAleatorio(int *v, int n){
    int i;
    contadorSemente++;
    srand(time(NULL) + contadorSemente);
    for(i = 0; i < n; i++){
        v[i] = rand() % n;
    }
}

void gerarCrescente(int *v, int n){
    int i;
    for(i = 0; i < n; i++){
        v[i] = i;
    }
}

void gerarDecrescente(int *v, int n){
    int i, pos = 0;
    for(i = n - 1; i >= 0; i--){
        v[pos] = i;
        pos++;
    }
}

int verificaOrdenado(int *v, int n){
    int i;
    for(i = 1; i < n; i++){
        if(v[i - 1] > v[i]){
            return 0;
        }
    }
    return 1;
}


double medirTempo(int opcao, int n, int tipoVetor){
    double delta_T;
    int *v;
#ifdef _WIN32
    LARGE_INTEGER frequencia, Tempo_antes, Tempo_depois;
#else
    struct timeval Tempo_antes, Tempo_depois;
#endif

    v = (int*) malloc(n * sizeof(int));
    if(v == NULL){
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }

    switch(tipoVetor){
        case 0: gerarAleatorio(v, n);   break;
        case 1: gerarCrescente(v, n);   break;
        case 2: gerarDecrescente(v, n); break;
    }

#ifdef _WIN32
    QueryPerformanceFrequency(&frequencia);
    QueryPerformanceCounter(&Tempo_antes);
    ordenar(opcao, v, n);
    QueryPerformanceCounter(&Tempo_depois);
    delta_T = (double)(Tempo_depois.QuadPart - Tempo_antes.QuadPart) / (double) frequencia.QuadPart;
#else
    gettimeofday(&Tempo_antes, NULL);
    ordenar(opcao, v, n);
    gettimeofday(&Tempo_depois, NULL);
    delta_T = (Tempo_depois.tv_sec + Tempo_depois.tv_usec / 1000000.0) -
              (Tempo_antes.tv_sec  + Tempo_antes.tv_usec  / 1000000.0);
#endif

    if(verificaOrdenado(v, n) == 0){
        printf("  [AVISO] o vetor NAO ficou ordenado corretamente!\n");
    }

    free(v);
    return delta_T;
}

/* Ciclo completo: 10 rodadas aleatorias + media + crescente + decrescente */
void executarTestes(int opcao, char *nome, int n){
    double tempos[RODADAS];
    double soma = 0.0, media, tCresc, tDecresc;
    int i;

    printf("\n %s  |  N = %d elementos\n", nome, n);

    for(i = 0; i < RODADAS; i++){
        tempos[i] = medirTempo(opcao, n, 0);
        soma = soma + tempos[i];
        printf("  Rodada %2d: %f segundos\n", i + 1, tempos[i]);
        fflush(stdout);
    }
    media = soma / RODADAS;

    printf("--------------------------------------------------------\n");
    printf("  TEMPO MEDIO (%d rodadas): %f segundos\n", RODADAS, media);
    printf("--------------------------------------------------------\n");

    tCresc = medirTempo(opcao, n, 1);
    printf("  Vetor em seu Comportamento Natural (ordem crescente): %f segundos\n", tCresc);

    tDecresc = medirTempo(opcao, n, 2);
    printf("  Vetor em seu Pior Caso (ordem inversa): %f segundos\n", tDecresc);
}
