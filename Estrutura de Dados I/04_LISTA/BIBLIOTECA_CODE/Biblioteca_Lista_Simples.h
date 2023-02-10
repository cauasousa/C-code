#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct No{
    int num;
    struct No *prox;
}chama;

void imprimir( chama *cabeca){
    printf("\n\tINÍCIO");
    while( cabeca != NULL){
        printf("--> %d", cabeca->num);
        cabeca = cabeca->prox;
    }
    printf("\t->>NULL");

}
chama *adc(){
    chama *nova = (chama*)malloc(sizeof(chama));
    printf("\n\tConteúdo: ");
    scanf("%d", &nova->num);
    printf("\n\tInserido!!");
    return nova;
}
void ins_inicio( chama **cabeca){

    chama *nova = adc();

    nova->prox = *cabeca;
    *cabeca = nova;

}

void ins_meio_ref( chama **cabeca, int conteudo){
    chama *nova = adc();

    if(*cabeca == NULL){
        nova->prox = NULL;
        *cabeca = nova;
        printf("Sem lista!");

    }
    else if((*cabeca)->num == conteudo){
        nova->prox = (*cabeca)->prox;
        (*cabeca)->prox = nova;
    }
    else{
        chama *aux = *cabeca;

        while(aux->prox != NULL && aux->num != conteudo){
            aux = aux->prox;
        }

        if(aux->prox != NULL){
            nova->prox = aux->prox;
            aux->prox = nova;
            printf("Inserindo no Meio");
        }
        else{
            nova->prox = NULL;
            aux->prox = nova;
            printf("Inserindo no Final");

        }
    }

}
int tamanho(chama *cabeca){
    int cont = 0;
    while(cabeca != NULL){
        cont++;
        cabeca = cabeca->prox;
    }
    return cont;
}

void ins_Meio( chama **cabeca){

    chama *nova = adc(), *aux = *cabeca;
    int tam = ceil(tamanho(*cabeca)/2.0f), j = 0;

    if(*cabeca == NULL){
        nova->prox = NULL;
        *cabeca = nova;
    }
    else{
        while(j<tam-1){
            aux = aux->prox;
            j++;
        }
        nova->prox = aux->prox;        
        aux->prox = nova;        
    }


}
void ins_final( chama **cabeca){
    chama *nova = adc(), *aux = *cabeca;

    if(*cabeca == NULL){
        nova->prox = NULL;
        *cabeca = nova;
    }
    else{
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        
        nova->prox = NULL;
        aux->prox = nova;

    }
}
///////////////////////
void remover(chama **cabeca, int valor){
    chama *aux = *cabeca;
    int cont = 0;

    while(aux != NULL){
        if(aux->num == valor){
            cont++;
        }
        aux=aux->prox;
    }

    int j = 0;
    for( j = 0; j<cont-1; j++){
         aux = *cabeca;
        if((*cabeca)->num == valor){
          chama *fre = *cabeca;  
          if((*cabeca)->prox != NULL){
            *cabeca = fre->prox;
          }
          else{
            *cabeca = NULL;
          }
            free(fre);
            }
        else{
            chama *ant = NULL, *anterior = NULL;
            while(aux->prox!= NULL){
                if(aux->prox->num == valor){
                    chama *Remm = aux->prox;
                    if(Remm->prox != NULL){
                        aux->prox = Remm->prox;
                    }
                    else{
                        aux->prox = NULL;
                    }
                    free(Remm);
                }
                aux = aux->prox;
            }

        }

    }
}


void ocor_remo( chama **cabeca){
    int tam = tamanho(*cabeca), opa = 0;
    int vetor[tam];
    chama *aux = *cabeca;

    while(aux != NULL){

        chama *aux_2 = aux->prox;

        while(aux_2 != NULL){

            if(aux->num == aux_2->num){
                vetor[opa] = aux->num;
                opa++;
            }

            aux_2 = aux_2->prox;

        }

        aux = aux->prox;
    }

    for(int j = 0; j<opa; j++){
        remover(cabeca, vetor[j]);
    }
}

///////////////////Strings///////////////////////



// void orde_strin(chama **cabeca){
    
//     chama *aux = *cabeca;
//     chama *ant = NULL;
//     chama *nova = (chama*)malloc(sizeof(chama));
//     nova = INS();

//     if(*cabeca == NULL){
//         *cabeca = nova; 
//         nova->prox = NULL;
//     }
//     else {
//         while(aux != NULL){
//             if(strcmp(nova->nome, aux->nome) < 0 ){
//                 //printf("oi");
//                 if(ant != NULL){
//                     ant->prox = nova;
//                 }
//                 else {
//                     *cabeca = nova;
//                 }
//                 nova->prox = aux;
//                 return ; 
//             }
//             ant = aux;
//             aux = aux->prox;
//         }
//         //printf("FIm");
//         ant->prox = nova;
//         nova->prox = NULL;
//         return; 
//     }
// }