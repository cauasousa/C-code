#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct No{
    int num;
    No *prox;
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
int tamanho( chama *cabeca ){
    int i = 0;
    while( cabeca != NULL ){
        i++;
        cabeca = cabeca->prox;
    }

    return i;
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
void remover( chama **cabeca, int remover){
  chama *aux = *cabeca;
  chama *nada = NULL;

  if(aux->num == remover){
    *cabeca = aux->prox;
    free(aux);
  }
  else{

    chama *aux_2 = NULL;
    while( aux != NULL){

        if(aux->num == remover){
            break;
        }

        aux_2 = aux;
        aux = aux->prox;
    }
    
    if(aux_2 != NULL){

      nada = aux;

      if(aux_2->prox != NULL){
        aux_2->prox = nada->prox;
      }
      else{
        aux_2->prox == NULL;
      }

    }
    else{
      printf("\n\tNão encontrado!");
    }
  }
}
/*void rem_ocorrencia( chama **cabeca){
    chama *aux = *cabeca;
    while(aux!=NULL){
        int contador = 0;
        chama *rem_ant = NULL;
        if(aux->prox != NULL){

                chama *aux_2 = aux->prox; 
                chama *opa = aux;

                while(aux_2 != NULL){
                    // aux=1/1  aux_2 = 1/2
                    //1 --> 4 --> 7 --> --> NULL
                    //rem = NULL 
                    opa = opa->prox;//

                    if(aux->num == aux_2->num){
                        printf("%d==%d ", aux->num, aux_2->num);

                        contador++;
                        rem_ant = opa;// 
                        //break;
                    }

                    aux_2 = aux_2->prox;


                }             
            }

        if(contador >= 1){
                printf("Entrou %d", rem_ant->num);
                //1 --> 4 --> 7 --> --> NULL
                //rem =     
                chama *pro = rem_ant->prox;//4

                if(pro != NULL){
                    //4
                rem_ant = pro;                     
                }
                else{
                    aux->prox = NULL;
                    //rem_ant->prox = NULL;
                }

                aux = *cabeca;
                printf("Opa");

            }
        else{
            printf("nada");
            aux = aux->prox;
        }



    }
}*/
void rem_ocorrencia( chama **cabeca){
    if(*cabeca != NULL){

        int cont = 0;
        chama *aux = *cabeca, *aux2 = NULL, *ant = NULL, *g_ant = NULL;

        while(aux!=NULL){

            ant = aux;
            aux2 = aux->prox;

            while(aux2 != NULL){
                if((*cabeca)->num == aux2->num){
                    *cabeca = (*cabeca)->prox;
                    printf(" ->Opppppppa %d\n", (*cabeca)->num);
                    //   -    -    -  1  -  NULL
                }
                else if(aux->num == aux2->num){
                    g_ant = ant;//4
                    cont++;
                }
                ant = ant->prox;
                aux2 = aux2->prox;
                printf("\ttTes\t");
            }
            printf("\n");
            if(cont >= 1){
                //4 
                chama *teste = g_ant->prox;
                if(teste->prox != NULL){
                    g_ant->prox = teste->prox;                    
                }
                else{
                    g_ant->prox = NULL;
                }

                printf(" %dMais %d ", g_ant->num, cont);
                aux = *cabeca;
                //continue;
            }
            else{

                aux = aux->prox;
                //printf("Rodando");
            }

        }
        //printf("FIM");
    }
    else{
        printf("Vazio");
    }
}
int main(){
    chama *head = NULL;
    int op = 0;

    while(true){
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

        case 2:{
            int cont = 0;
            printf("\n\tDigite o Numero anterior onde deseja colocar: ");
            scanf("%d", &cont);
            ins_meio_ref(&head, cont);
            break;            
        }

        case 3:{
            ins_Meio(&head);
            break;
        }
        case 4:{
            ins_final(&head);
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
        case 6:{
            if(head != NULL){
                int remo = 0;
                printf("\n\tDigite o numero que deseja remover: ");
                scanf("%d", &remo);
                remover(&head, remo);
            }
            else{
                printf("\n\tLista Vazia");
            }

            break;
        }
        case 7:{
            rem_ocorrencia(&head);
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
    printf("\n----MENU----\n\t0 - Sair\n---------Lista-Simples----------\n\t1 - Inserir Cabeca\n\t2 - Inserir Meio, Com Referencia\n\t3 - Inserir No Meio\n\t4 - Inserir No Final");
    printf("\n\t5 - Imprimir\n\t6 - Remover\n\t7 - Remover as Ocorrencias\n\t ");
}