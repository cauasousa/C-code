#include <stdio.h>
#include <stdlib.h>

typedef struct Dados
{
    int conteudo;
    Dados *prox;
} chama;

chama *inserir_comeco(chama **lista, int quant);
void imprimir(chama *cabeca);
int menu();
chama *ins_meio(chama **Lista, int ant, int valor);
chama *ins_Final(chama **Lista, int num);
void ordenado(chama **Lista, int quant);


int main()
{

    int op;
    Dados *head = NULL;
    int quant = 0;

    do
    {
        op = menu();

        switch (op)
        {

        case 1:
            system("cls");
            head = inserir_comeco(&head, 1);
            quant++;
            break;
        case 2:
            system("cls");
            int ant, adc;
            printf("\n\t\t\tDigite o numero que deseja colocar depois dele: ");
            scanf("%d", &ant);
            printf("\n\t\t\tDigite o valor a adicionar: ");
            scanf("%d", &adc);
            ins_meio(&head, ant, adc);
            quant++;
            break;

        case 3:
            system("cls");
            int ad;
            printf("Digite o número a adicionar: ");
            scanf("%d", &ad);
            ins_Final(&head, ad);
            quant++;
            break;

        case 4:
            system("cls");
            ordenado(&head, quant);
            break;

        case 6:
            printf("Certo");
            break;

        default:
        {
            system("cls");
            printf("Opção Inválida");
        }
        }
        imprimir(head);
    } while (op != 0);
    printf("\n------\n");
    imprimir(head);

    return 0;

}

int menu()
{
    int num;
    printf("\n------");
    printf("\n\t\t\t1- Inserir no Começo");
    printf("\n\t\t\t2- Inserir no Meio");
    printf("\n\t\t\t3- Inserir no Final");
    printf("\nOpção: ");
    scanf("%d", &num);
    return num;
}

chama *inserir_comeco(chama **lista, int quant)
{
    chama *novo;
    for (int i = 0; i < quant; i++)
    {
        novo = (chama *)malloc(sizeof(chama));
        printf("Inserir valor: ");
        scanf("%d", &novo->conteudo);
        // ender do prox do meu novo, recebe o ender da cabeca
        novo->prox = *lista;
        // o local que guarda o ender da cabeca será substituido por ender do meu novo
        *lista = novo;
    }
    return *lista;
}

void imprimir(chama *cabeca)
{
    while (cabeca->prox != NULL)
    {
        printf("%d->", cabeca->conteudo);
        cabeca = cabeca->prox;
    }
    printf("%d->", cabeca->conteudo);

    printf("NULL");
}

chama *ins_meio(chama **Lista, int ant, int valor)
{
    chama *novo;
    novo = (chama *)malloc(sizeof(chama));
    novo->conteudo = valor;
    chama *aux = *Lista;
    while ((aux->conteudo != ant) && (aux->prox != NULL))
    {
        aux = aux->prox;
    }
    novo->prox = aux->prox;
    aux->prox = novo;
}

chama *ins_Final(chama **Lista, int num)
{
    chama *novo, *aux;
    novo = (chama *)malloc(sizeof(chama));
    novo->conteudo = num;
    aux = *Lista;
    while (aux->prox != NULL)
    {
        aux = aux->prox;
    }
    novo->prox = NULL;
    aux->prox = novo;
}

// void ordenado(chama **Lista, int quant)
// {
//     chama *aux, *ord;
//     aux = *Lista;
//     ord = *Lista;
//     aux = aux->prox;
//     int teste = 0;
//     int menor_maior = 0;
//     do
//     {
        
        
//         if (aux->conteudo >= ord->conteudo)
//         {
//             teste++;
//             if (quant == teste)
//             {
//                 printf("Está ordenado do Menor ao Maior\n");
//                 break;
//             }
//         }
//         if (aux->conteudo <= ord->conteudo)
//         {
//             menor_maior++;
//             if (quant == menor_maior)
//             {
//                 printf("Está ordenado do Maior ao Menor\n");
//                 break;
//             }
//         }
//         ord = ord->prox;
//         aux = aux->prox;
//     } while (aux->prox != NULL);
// }