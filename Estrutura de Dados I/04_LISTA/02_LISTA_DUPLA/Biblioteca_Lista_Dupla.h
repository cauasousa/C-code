#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <strings.h>

typedef struct lista{

    char nome[50];
    int conteudo;
    struct lista *proxi;
    struct lista *anterior;

}chama;

void imprimir( chama *cabeca){


    chama *cab_fim = NULL;

    printf("\n\t\tLista\n\t");
    while(cabeca != NULL){
        
        printf("- %d -", cabeca->conteudo);

        if(cabeca->proxi == NULL){
            cab_fim = cabeca;
        }
        cabeca = cabeca->proxi;
    }
    printf("\n\t\tVolta Lista\n\t");

    while(cab_fim != NULL){
        printf("- %d -", cab_fim->conteudo);
        cab_fim = cab_fim->anterior;
    }

}
int tamanho( chama *cabeca ){
    int tamm = 0;
    while(cabeca != NULL){
        tamm++;
        cabeca = cabeca->proxi;
    }
    return tamm;
}
chama *inserir(){
    chama *nova = (chama*)malloc(sizeof(chama));

    printf("Conteudo: ");
    scanf("%d", &nova->conteudo);
    nova->proxi = NULL;
    nova->anterior = NULL;
    return nova;
}

void ins_comeco( chama **cabeca ){
    chama *novo = inserir();
    if(*cabeca == NULL){
        *cabeca = novo;
    }
    else{

        (*cabeca)->anterior = novo;
        novo->proxi = *cabeca;
        *cabeca = novo;
    }
}

void ins_meio( chama **cabeca){
    int i = 0, tam = ceil(tamanho(*cabeca)/2.0f);
    chama *aux = *cabeca;

    while(i<tam-1){
        aux = aux->proxi;
        i++;
    }

    if( tam == 0){
        ins_comeco(cabeca);
    }
    else{
        chama *novo = inserir();
        if(aux->proxi != NULL){
            aux->proxi->anterior = novo;            
        }

        novo->proxi = aux->proxi;
        aux->proxi = novo;
        novo->anterior = aux;
    }
}

void ins_fim( chama **cabeca){

    if(*cabeca == NULL || (*cabeca)->proxi == NULL){
        ins_meio(cabeca);
    }
    else{
        chama *aux = *cabeca, *nova = inserir();
        while( aux->proxi != NULL){
            aux = aux->proxi;
        }        
        aux->proxi = nova;
        nova->anterior = aux;

    }

}

void remover( chama **cabeca, int procurado){
    chama *aux = *cabeca;
    if( (*cabeca)->conteudo == procurado ){

        if((*cabeca)->proxi != NULL){

            *cabeca = (*cabeca)->proxi;  
            (*cabeca)->anterior =NULL;  

        }else{

            *cabeca = NULL;

        }

    }
    else{
        while(aux != NULL && aux->proxi->conteudo != procurado){
            aux = aux->proxi;
        }
        if(aux != NULL){
            // 1 - 2 - NULL
            // 1 -- 2 - 3 - NULL
            if(aux->proxi->proxi != NULL){
                aux->proxi = aux->proxi->proxi;
                aux->proxi->anterior = aux;                
            }
            else{
                aux->proxi = NULL;
            }
        }
        else{
            printf("Não Encontrado!");
        }
    }
}

void ordenado( chama **cabeca ){

    if(*cabeca == NULL){
        ins_comeco(cabeca);
    }
    else{
        chama *aux = *cabeca, *ant = NULL;
        chama *nova = inserir();

        while(aux != NULL){
            if(aux->conteudo > nova->conteudo){
                 //5 > 4
                if(ant != NULL){
                    ant->proxi = nova;
                    nova->anterior = ant;                    
                }else{
                    *cabeca = nova;
                }
                nova->proxi = aux;
                aux->anterior = nova;
                return ; 
            }
            ant = aux;
            aux = aux->proxi;
        }
        if(aux == NULL){
            nova->anterior = ant;
            ant->proxi = nova;
            return ;
        }
    }
}

////////////////////////Strings//////////////////////
void ornd_string(chama **cabeca)
{
    if (*cabeca == NULL)
    {
        ins_comeco(cabeca);
        return;
    }
    else
    {

        chama *aux = *cabeca, *nova = inserir(), *ant = NULL;
        while (aux != NULL)
        {
            if (strcmp(aux->nome, nova->nome) >= 0)
            {
                if (ant != NULL)
                {
                    ant->proxi = nova;
                    nova->anterior = ant;
                }
                else
                {
                    *cabeca = nova;
                }
                nova->proxi = aux;
                aux->anterior = nova;
                return;
            }
            ant = aux;
            aux = aux->proxi;
        }
        if (aux == NULL)
        {
            ant->proxi = nova;
            nova->anterior = ant;
            return;
        }
    }
}