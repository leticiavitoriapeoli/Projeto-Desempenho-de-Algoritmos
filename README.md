# Medição Experimental e Desempenho de Algoritmos de Ordenação 

Projeto desenvolvido para a disciplina de Estruturas de Dados II.

# Sobre o Projeto
O objetivo principal deste projeto foi desenvolver um programa  para realizar a medição experimental e análise de desempenho do tempo de execução de onze algoritmos de ordenação sobre vetores de inteiros. 

Os testes foram executados com seis tamanhos de vetores (10.000, 50.000, 100.000, 200.000, 500.000 e 1.000.000 de elementos), avaliando três cenários para cada tamanho:
1. Vetores aleatórios (média de 10 rodadas com sementes distintas via `srand`).
2. Vetores ordenados de forma crescente (comportamento natural).
3. Vetores ordenados de forma decrescente (pior caso).

## Algoritmos Implementados

Foram integrados 11 algoritmos de ordenação no mesmo programa:

Algoritmos Clássicos (Comparação de Complexidade Quadrática e Divisão e Conquista):
- BubbleSort
- InsertionSort
- SelectionSort
- MergeSort
- QuickSort

Algoritmos de Alto Rendimento e Não Comparativos:
- ShellSort
- HeapSort
- BucketSort
- RadixSort (LSD)
- CountingSort
- TimSort

## Estrutura e Decisões de Implementação

- Medição de Alta Precisão: Devido à limitação de resolução de 1 ms da função `gettimeofday()` em ambiente Windows/MinGW (que zerava medições de algoritmos muito rápidos), utilizou-se `QueryPerformanceCounter()` e `QueryPerformanceFrequency()` da biblioteca `windows.h`, permitindo medições com precisão inferior a 1 microssegundo. O código suporta compilação condicional via `#ifdef _WIN32`.
- Otimização do BucketSort: Para evitar estouro de memória em vetores grandes (1 milhão de elementos), os baldes foram ajustados para alocação dinâmica com cálculo exato do tamanho do balde, mantendo a ordenação interna por InsertionSort.
- Prevenção de Estouro de Pilha no QuickSort: Ajustadas as verificações de limites na partição para mitigar profundidade excessiva de recursão $O(n)$ em vetores já ordenados com pivô fixo no primeiro elemento.
- Automação do Ciclo de Testes: Para cada algoritmo e tamanho escolhido, a aplicação aloca dinamicamente o vetor (`malloc`), preenche os dados, realiza a medição temporal da ordenação, valida a integridade do resultado e desaloca a memória (`free`).


## Resultados e Principais Observações

- Algoritmo mais rápido: CountingSort obteve o menor tempo geral de execução em todas as cenários (abaixo de 0,01s para 1.000.000 de elementos), por não realizar comparações diretas.
- Sensibilidade à ordem inicial: TimSort, InsertionSort e BubbleSort apresentaram ganhos expressivos de desempenho ao lidar com vetores no seu comportamento natural (já ordenados).
- Algoritmos Insensíveis à disposição dos dados: SelectionSort, MergeSort, HeapSort e RadixSort mantiveram estabilidade de tempo independente do arranjo inicial dos dados.
- Degradação do QuickSort: Com a escolha do primeiro elemento como pivô fixo, o QuickSort degenerou para complexidade $O(n^2)$ nos vetores ordenados e inversamente ordenados.


## Ambiente de Testes

Todas as medições foram realizadas em hardware padronizado:
- Processador: Intel Core i5-12400F (12ª geração, 6 núcleos / 12 threads, até 4,4 GHz)
- Memória RAM: 16 GB
- Sistema Operacional: Microsoft Windows 10 Pro (64 bits)
- Ambientes de Compilação: Code::Blocks (GCC / MinGW)


## Como Compilar e Executar

1. Clone o repositório:
   git clone https://github.com/leticiavitoriapeoli/Projeto-Desempenho-de-Algoritmos.git
