#include <stdio.h>
#include <random>
#include <time.h>
#include <math.h>

typedef struct node
{
    int num;
    node *prox;

} lista;

int quant = 0;

lista *data(int qual)
{

    lista *aux = (lista *)malloc(sizeof(lista));
    aux->prox = NULL;
    // scanf(" %d", aux->num);
    aux->num = qual;
    quant = quant + 1;
    return aux;
}

void inserir(lista **no, lista *novo, int pos = quant)
{
    if (*no == NULL)
    {
        *no = novo;
        novo->prox = NULL;
        return;
    }
    lista *aux = *no;
    int adi_pos = 0;
    while (aux->prox != NULL && pos > adi_pos)
    {
        aux = aux->prox;
        adi_pos += 1;
    }

    novo->prox = aux->prox;
    aux->prox = novo;
}

void print(lista *aux)
{
    while (aux != NULL)
    {

        printf("%d-> ", aux->num);
        aux = aux->prox;
    }
    printf(" NULL");
}

void find_pivo(lista *aux, int posicao_pivo, lista **my_pivo = NULL)
{

    for (int i = 0; posicao_pivo < i; i++)
    {
        aux = aux->prox;
    }

    *my_pivo = aux;
}

int larger_pivo(lista *aux, lista *my_pivo)
{
    int cont = 0, larger = 0;

    while (aux != NULL)
    {

        if (aux->num > my_pivo->num)
        {
            larger++;
        }
        aux = aux->prox;
    }
    return larger;
}

lista *remover(lista **cabeca, int pivo)
{

    lista *aux = *cabeca, *ant = NULL;
    int rem_pivo = 0;

    if (aux == NULL)
    {
        return NULL;
    }

    while (aux->prox != NULL && pivo > rem_pivo)
    {
        ant = aux;
        (aux) = (aux)->prox;
        rem_pivo += 1;
    }

    if (aux != NULL)
    {

        if (ant != NULL)
        {
            ant->prox = aux->prox;
        }
        else
        {
            *cabeca = (*cabeca)->prox;
        }

        aux->prox = NULL;
    }

    return aux;
}

lista *ord(lista **ceil_head, lista *pivo, lista **last_less)
{
    lista *aux = NULL, *aux_floor_head = NULL, *aux_ceil_head = NULL, *temporario_ceil = NULL, *temporario_floor = NULL;
    
    // o zero é para indicar que não deve entrar no while q tem dentro dessa função, assim não aumenta a complexidade 
    aux = remover(ceil_head, 0);

    while (aux != NULL)
    {
        if (aux->num > pivo->num)
        {

            if (temporario_ceil == NULL)
            {
                aux_ceil_head = aux;
                temporario_ceil = aux;
            }
            else
            {
                temporario_ceil->prox = aux;
                temporario_ceil = temporario_ceil->prox;
            }
        }
        else
        {

            if (temporario_floor == NULL)
            {
                aux_floor_head = aux;
                temporario_floor = aux;
            }
            else
            {
                temporario_floor->prox = aux;
                temporario_floor = temporario_floor->prox;
            }
        }

        aux = remover(ceil_head, 0);
    }

    *ceil_head = aux_ceil_head;
    *last_less = temporario_floor;
    return aux_floor_head;
}

void attach_end(lista *head, lista *add){

    if(head == NULL){
        return;
    }
    
    while(head->prox != NULL){
        head = head->prox;
    }
    head->prox = add;

}


lista *quick_sort(lista **head, int tam = quant)
{
    
    if (*head == NULL)
    {
        return NULL;
    }
    if (tam <= 1)
    {   
        return *head;
    }
    
    int local_pivo = ((tam) / 2.0f);

    lista *new_pivo = remover(head, local_pivo);

    int maior = larger_pivo(*head, new_pivo);

    lista *last_less = NULL;
    lista *menores = ord(head, new_pivo, &last_less);

    int teste = tam - (tam - maior);
 
    new_pivo->prox = quick_sort(head, teste);
    *head = new_pivo;

    int tst = tam - maior - 1;

    menores = quick_sort(&menores, tst);
    if (menores != NULL)
    {
        attach_end(menores, new_pivo);
        *head = menores;
    }
    return *head;
}

int main()
{
    lista *head = NULL;
    srand(time(NULL));

    inserir(&head, data(5));
    inserir(&head, data(4));
    inserir(&head, data(4));
    inserir(&head, data(1));
    inserir(&head, data(1));
    inserir(&head, data(8));
    inserir(&head, data(8));
    inserir(&head, data(8));
    inserir(&head, data(3));
    inserir(&head, data(7));
    inserir(&head, data(1));
    inserir(&head, data(5));
    inserir(&head, data(2));
    inserir(&head, data(6));
    
    
    
    print(head);
    printf("\n");
    head = quick_sort(&head);
    printf("\n\nOrdenação\n");
    print(head);
    printf("\nFIM");

    return 0;
}