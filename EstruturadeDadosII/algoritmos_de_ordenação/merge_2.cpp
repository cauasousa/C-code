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

void divide(lista *firt, lista **half, int size){
    int i = 0;
    lista *aux = firt;
    while(aux != NULL && i < size){ 
        aux = aux->prox;
        i++;
    }
    if(aux != NULL){
        *half = aux->prox;
        aux->prox = NULL;
    }

}

void fuse( lista **head, lista *head_2){
    lista *lst_1 = *head, *lst_2 = head_2, *inserido = NULL, *cabeca_nova = NULL;

    while(lst_1 != NULL && lst_2 != NULL){
        if(lst_1->num < lst_2->num){
            if(inserido == NULL){
                cabeca_nova = lst_1;
                inserido = lst_1;
                lst_1 = lst_1->prox;
                inserido->prox = NULL;
                continue;
            }
            inserido->prox = lst_1;
            lst_1 = lst_1->prox;
            inserido = inserido->prox;
            inserido->prox = NULL;
        }
        else{
            if(inserido == NULL){
                cabeca_nova = lst_2;
                inserido = lst_2;
                lst_2 = lst_2->prox;
                inserido->prox = NULL;
                continue;
            }
            inserido->prox = lst_2;
            lst_2 = lst_2->prox;
            inserido = inserido->prox;
            inserido->prox = NULL;
        }

    }
    
    if(lst_1 != NULL){
        inserido->prox = lst_1;
    }
    else if(lst_2 != NULL){
        inserido->prox = lst_2;
    }
    *head = cabeca_nova;
    
}

lista *merge_sort(lista *head, int star, int end)
{

    if(head == NULL){
        return NULL;
    }
    else if (end - star == 1){
        
        if((head)->num > head->prox->num){

            lista *aux_1 = head;
            head = aux_1->prox;
            aux_1->prox = NULL;
            (head)->prox = aux_1;

        }
        return head;
    }
    else if (end == star){
        
        return head;
    }

    lista *start = head;
    lista *half = NULL;
    int meio = ((end-star)/2.0f);
    divide(start, &half, meio);

    start = merge_sort(start, star, (end+star)/2);
    half = merge_sort(half, (end+star)/2 + 1 , end);

    fuse(&start, half);
    return start;
}

int main()
{
    lista *head = NULL;
    srand(time(NULL));
    
    inserir(&head, data(22));
    inserir(&head, data(4));
    inserir(&head, data(3));
    inserir(&head, data(20));
    inserir(&head, data(17));
    inserir(&head, data(1));
    inserir(&head, data(3));
    inserir(&head, data(3));
    inserir(&head, data(7));
    inserir(&head, data(1));
    inserir(&head, data(5));
    inserir(&head, data(2));
    inserir(&head, data(6));
    inserir(&head, data(8));
    print(head);

    
    head = merge_sort(head, 0, quant-1);
    printf("\n");
    print(head);
    
    return 0;
}