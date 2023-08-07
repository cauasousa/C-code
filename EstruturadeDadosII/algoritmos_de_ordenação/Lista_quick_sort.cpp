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
        adi_pos+=1;
    }

    novo->prox = aux->prox;
    aux->prox = novo;
}

void print(lista *aux)
{
    while (aux != NULL)
    {
        
        printf(" %d ->", aux->num);
        aux = aux->prox;
        
    }
    printf(" NULL");
}

// void preencher_head(lista *head, int *vetor)
// {
//     int quant_preenchida = quant;

//     while (head)
//     {
//         int aleatorio = rand() % quant;
//         int achou = 0;

//         for (int verificador = 0; verificador < quant_preenchida; verificador++)
//         {
//             if (h[verificador] == aleatorio)
//             {
//                 achou = 1;
//                 break;
//             }
//         }
//         if (achou == 0)
//         {
//             head[quant_preenchida] = aleatorio;
//             quant_preenchida += 1;
//         }
//     }
// }

void find_pivo(lista *aux, int start, int end, lista **my_pivo = NULL){
    int cont = 0;
    int posicao_pivo = ceil((start + end)/2.0f);
    
    
    while(aux != NULL){
        if ((cont >= start) && cont < end){
            if(posicao_pivo == cont ){
                *my_pivo = aux;
            }
            
        }
        cont++;
        aux = aux->prox;
    }
    
}

int larger_pivo(lista *aux, int start, int end, lista *my_pivo){
    int cont = 0, larger = 0;
    
    
    while(aux != NULL){

        if ((cont >= start) && cont <= end){
            if(aux->num > my_pivo->num ){
                larger++;
            }
            
        }
        cont++;
        aux = aux->prox;
    }
    return larger;
}

lista *remover(lista **cabeca, int pivo = quant){

    lista *aux = *cabeca, *ant = NULL;
    int rem_pivo = 0;
    

    while(aux->prox != NULL && pivo > rem_pivo){
        ant = aux;
        (aux) = (aux)->prox;
        rem_pivo+=1;
    }
    //printf(" \n||%d %d R=%d|| ", rem_pivo, pivo, aux->num);
    if(rem_pivo == pivo){
        if(aux != NULL){
            if(ant != NULL ){
                ant->prox = aux->prox;
            }else{
                *cabeca = (*cabeca)->prox;
            }

            aux->prox = NULL;
            return aux;
        }
        else{
            printf("opa");
        }
        
    }else{
            printf("opa");
    }

    return NULL;
}

void ord(lista **cabeca, lista *pivo){
    lista *aux = *cabeca, *new_cabeca = pivo;
    int cont = 1;
    
    while(quant > cont){
        //remov in head
        lista *rem = remover(cabeca, (quant - cont) - 1);
        
        if(rem->num < pivo->num){

            //insertion in firts
            rem->prox = new_cabeca;
            new_cabeca = rem;
            
        }else{
            //insertion in end
            rem->prox = pivo->prox;
            pivo->prox = rem;

        }
        
        cont+=1;
    } 
    
    *cabeca = new_cabeca;
    
}

void quick_sort(lista **head, int start, int end)
{
    
    if(*head == NULL){
        return;
    }
    else if (end - start == 1){
        return;
    }
    else if (end == start){
        return;
    }
    else{
        
        lista *new_pivo = NULL;
        int local_pivo = ceil((start + end)/2.0f);

        // this was for see the larger, but now is for find pivo
        find_pivo(*head, start, end, &new_pivo);
        int maior = larger_pivo(*head, start, end, new_pivo);
        
        lista *pivo = remover(head, local_pivo);
        ord(head, new_pivo);

        quick_sort(head, start, end - maior);
        quick_sort(head, end - maior + 1, end);
    }   
}

int main()
{
    lista *head = NULL;
    srand(time(NULL));
    
    inserir(&head, data(4));
    inserir(&head, data(3));
    inserir(&head, data(7));
    inserir(&head, data(1));
    inserir(&head, data(5));
    inserir(&head, data(2));
    inserir(&head, data(6));
    inserir(&head, data(8));
    print(head);

    
    quick_sort(&head, 0, quant-1);
    printf("\n");
    print(head);
    
    return 0;
}