#include <stdio.h>
#include <stdlib.h>
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
void menu();
///Removeu e deixou um
void remover_um_em_um(chama **cabeca, int valor){
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

            while(aux!= NULL){
                if(aux->prox->num == valor){
                    chama *Remm = aux->prox;
                    if(Remm->prox != NULL){
                        aux->prox = Remm->prox;
                        break;
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
int tamanho(chama *cabeca){
    int cont = 0;
    while(cabeca != NULL){
        cont++;
        cabeca = cabeca->prox;
    }
    return cont;
}
// Deu certo, deicou um
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
        remover_um_em_um(cabeca, vetor[j]);
    }
}
int main(){
    chama *head = NULL;
    int op = 0;

    while(1){
        menu();
        scanf("%d", &op);

        switch (op)
        {
        case 0:{
            printf("\n\tSaindo!!");
            break;
        }

        case 1:{
            ins_inicio(&head);
            break;
        }
        case 3:{
            ocor_remo(&head);
            break;
        }
        case 6:{
            remover_um_em_um(&head, 1);
            break;
        }
        case 5:{
            if( head == NULL){
                printf("\n\tLista Vazzia!\n");
            }
            else{
            imprimir(head);
            }

            break;
        }

        default:

            break;
        }


        if(op!=0){
            continue;
        }
        break;
    }

    return 0;
}

void menu(){
    printf("\n----MENU----\n\t0 - Sair\n---------Lista-Simples----------\n\t1 - Inserir Cabeca");
    printf("\n\t5 - Imprimir\n\t3 - Remover as Ocorrencias\n\t6 - Remover ");
}
