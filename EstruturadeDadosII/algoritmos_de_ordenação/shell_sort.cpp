#include <stdio.h>
#include <random>
#include <math.h>
#include <time.h>

#define tam 10

void print(int *vetor, int quant)
{
    printf("\n");
    for (int i = 0; i < quant; i++)
    {
        printf("|%d| ", vetor[i]);
    }
}

void preencher_vetor(int *vetor, int quan)
{
    int quant_preenchida = 0;

    while (quant_preenchida < quan)
    {
        int aleatorio = (rand() % quan) + 1;
        int achou = 0;

        for (int verificador = 0; verificador < quant_preenchida; verificador++)
        {
            if (vetor[verificador] == aleatorio)
            {
                achou = 1;
                break;
            }
        }
        if (achou == 0)
        {
            vetor[quant_preenchida] = aleatorio;
            quant_preenchida += 1;
        }
    }
}

void empurra(int *vetor, int j, int index_less, int gap)
{

    int less = vetor[index_less];

    for (int i = index_less; i > j; i = i - gap)
    {
        vetor[i] = vetor[i - gap];
    }
    vetor[j] = less;
}

void shell_sort(int *vetor)
{
    int gap = tam / 2;

    for (int i = gap; i > 0; i = i/2)
    {
        for(int index_start = 0; index_start <= (tam/i) ; index_start++){
            for (int j = index_start; j < tam; j = j + i)
            {
                int index_less = j;
                for (int interacao = j + i; interacao < tam; interacao = interacao + i)
                {
                    if (vetor[index_less] > vetor[interacao])
                    { 
                        index_less = interacao;
                    }
                }
                
                if (index_less != j)
                {
                    
                    empurra(vetor, j, index_less, i);
                }
                
            }
        }
    }
}

int main()
{

    // int vetor_1[tam]={1, 3, 7, 8, 0, 2, 4, 9, 5, 6};
    //int vetor_1[tam] = {8, 9, 3, 7, 2};
    //int vetor_1[tam] = {40, 50, 10, 30, 70, 20, 1, 60};
    int vetor_1[tam];
    srand((unsigned)time(NULL));
    preencher_vetor(vetor_1, tam);
    print(vetor_1, tam);

    shell_sort(vetor_1);
    printf("\n==============================\nOrdenado");
    print(vetor_1, tam);
}
