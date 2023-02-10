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

void remover_ocorrencia( chama **cabeca){
    chama *hed = *cabeca, *he_pr = NULL;
    int t = tamanho(*cabeca), vetor[t];
    int ele = 0;
    while(hed != NULL){
            int conte = 0;
            he_pr = hed->proxi;
            
            int jj = 0, teste = 0;
            for(jj = 0; jj<ele; jj++){
                if(vetor[jj] == hed->conteudo){
                    teste++;
                }
            }
            if(teste == 0){
                while(he_pr != NULL){
                    
                    if(hed->conteudo == he_pr->conteudo){
                        vetor[ele] = he_pr->conteudo;
                        ele++;
                        
                    }
                    he_pr = he_pr->proxi;
                } 
                               
            }


        hed = hed->proxi;
    }
    int i = 0;
    while(i < ele){

        remover(cabeca, vetor[i]);
        i++;
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
void removedor_str_todos(chama **cabeca, char eliminar[30])
{

    chama *aux = *cabeca;
    int contador = 0, j = 0;

    while (aux != NULL)
    {
        if (strcmp(eliminar, aux->nome) == 0)
        {
            contador++;
        }
        aux = aux->proxi;
    }

    if (contador != 0)
    { 
        while (j <= contador - 1)///<----//
        {
            aux = *cabeca;
            while (aux != NULL)
            {

                if (strcmp((*cabeca)->nome, eliminar) == 0)
                {

                    *cabeca = aux->proxi;
                    if (*cabeca != NULL)
                    {
                        (*cabeca)->anterior = NULL;
                    }
                    aux = *cabeca;
                    break;
                }
                else if (strcmp(aux->nome, eliminar) == 0)
                {

                    if (aux->proxi != NULL)
                    {
                        aux->proxi->anterior = aux->anterior;
                    }
                    aux->anterior->proxi = aux->proxi;
                    aux = aux->proxi;
                    break;
                }
                else
                {
                    aux = aux->proxi;
                    
                }
                
            }
            j++;  // aqui deixa uma ocorrencia
            
        }
    }
    else
    {
        printf("\n\tNão achado!");
    }
}

void rem_strin(chama **cabeca, char eliminar[30])
{

    chama *aux = *cabeca;
    int contador = 0, j = 0;

    while (aux != NULL)
    {
        if (strcmp(eliminar, aux->nome) == 0)
        {
            contador++;
        }
        aux = aux->proxi;
    }

    if (contador != 0)
    { 
    //Se coloca igual, tira todos as ocorrencias
// Se tirar o igual, deixa pelo menos um, porem para remover é preciso colocar igual, pois ele sempre deixa um quando tira o igual..
        while (j < contador - 1)///<----//
        {
            aux = *cabeca;
            while (aux != NULL)
            {

                if (strcmp((*cabeca)->nome, eliminar) == 0)
                {

                    *cabeca = aux->proxi;
                    if (*cabeca != NULL)
                    {
                        (*cabeca)->anterior = NULL;
                    }
                    aux = *cabeca;
                    break;
                }
                else if (strcmp(aux->nome, eliminar) == 0)
                {

                    if (aux->proxi != NULL)
                    {
                        aux->proxi->anterior = aux->anterior;
                    }
                    aux->anterior->proxi = aux->proxi;
                    aux = aux->proxi;
                    break;
                }
                else
                {
                    aux = aux->proxi;
                    
                }
                
                //IMPORTANTE!!!!!!
                //j++; //Aqui ele tira todos as ocorrencias
            }
            j++;  // aqui deixa uma ocorrencia
            
        }
    }
    else
    {
        printf("\n\tNão achado!");
    }
}

void rem_ocorrenc_strin(chama **cabeca)
{
    chama *hed = *cabeca, *he_pr = NULL;
    int t = tamanho(*cabeca);
    char vetor[t][30];
    int ele = 0;
    while (hed != NULL)
    {
        int conte = 0;
        he_pr = hed->proxi;

        int jj = 0, teste = 0;
        for (jj = 0; jj < ele; jj++)
        {
            if (strcmp(vetor[jj], hed->nome) == 0)
            {
                teste++;
                printf(" Achou %d", teste);
            }
        }

        if (teste == 0)
        {
            while (he_pr != NULL)
            {

                if (strcmp(hed->nome, he_pr->nome) == 0)
                {
                    printf(" Um igual ");
                    strcpy(vetor[ele], he_pr->nome);
                    // vetor[ele][] = he_pr->conteudo;
                    ele++;
                }
                he_pr = he_pr->proxi;
            }
        }

        hed = hed->proxi;
    }
    int i = 0;
    while (i < ele)
    {
        printf("%s", vetor[0]);
        rem_strin(cabeca, vetor[i]);
        i++;
    }
}