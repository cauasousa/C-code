#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct lista{
    int conteudo;
    char nome[30];
    struct lista *proximo;
}chama;

typedef struct cabeca{

    chama *inicio;
    chama *fim;
    int n;

}cab;

chama *inserir(){
    chama *novo = (chama*)malloc(sizeof(chama));
    printf("\n\tDigite o nome:   ");
    scanf(" %30[^\n]s", novo->nome);
    printf("\n\tDigite o Conteudo: ");
    scanf("%d", &novo->conteudo);
    novo->proximo = NULL;
    return novo;
}

void imprimir( cab *cabeca){
    chama *aux = cabeca->inicio;
    int j = 0;
    printf("Inicio: ");
    while(j<cabeca->n){
        printf("\n\t\t --> Nome: %s N %d", aux->nome, aux->conteudo);
        aux = aux->proximo;
        j++;
    }
    printf("\n\t\t\tFim\n");
}

void ins_com(cab **guarda){
    chama *novo = inserir();
    // Atualizando inicio
    novo->proximo = (*guarda)->inicio;
    (*guarda)->inicio = novo;

    if((*guarda)->fim == NULL){
        //Se for comeco da lista, guarda o primeiro valor
        (*guarda)->fim = novo;
    }
    (*guarda)->fim->proximo = novo;
    (*guarda)->n++;

}

void ins_meio( cab **guarda){
    int meio = ceil((*guarda)->n/2.0f), j = 0;
    chama *aux = (*guarda)->inicio;

    if ((*guarda)->n == 0){
        ins_com(guarda);
    }
    else{
        chama *novo = inserir();
        // 1
        // 1  2 
        // 1  2   3
        while(j<meio-1){
            aux = aux->proximo;
            j++;
        }

        if((*guarda)->inicio == aux->proximo){
            novo->proximo = aux->proximo;
            aux->proximo = novo;
            (*guarda)->fim = novo;
            
        }
        else{
            novo->proximo = aux->proximo;
            aux->proximo = novo;
        }
        (*guarda)->n++;
    }
}

void ins_fim( cab **guarda){
    if((*guarda)->inicio == NULL){
        ins_com(guarda);
    }
    else{
        // 1  - 2-> 3->     
        chama *nova = inserir();
        nova->proximo =  (*guarda)->fim->proximo;
        (*guarda)->fim->proximo = nova;
        (*guarda)->fim = nova;
        (*guarda)->n += 1;
    }

}
void inserir_referenciaNum( cab **guarda){
    int num = 0;
    printf("\n\tDigite a referencia ");
    scanf("%d", &num);
    scanf("");
    if((*guarda)->inicio == NULL){
        ins_com(guarda);
    }
    else{

        chama *aux = (*guarda)->inicio, *novo = inserir();

        while(aux->proximo != (*guarda)->inicio && aux->conteudo != num){
            aux = aux->proximo;
        }
        // 1 -> fim
        // 2   -> 1   ->> fim   
        novo->proximo = aux->proximo;

        if((*guarda)->inicio == aux->proximo){
            (*guarda)->fim = novo;
        }
        aux->proximo = novo;

        (*guarda)->n++;
    }

}

void remover(cab **guarda){
    int ioa = 0, remover = 0;
    chama *aux = (*guarda)->inicio;
    printf("Digite o numero procurado: ");
    scanf("%d", &remover);
    if(aux->conteudo == remover){
       // 1 - fim
       if(aux->proximo == (*guarda)->inicio){
        (*guarda)->inicio = NULL;
        (*guarda)->fim = NULL;
        (*guarda)->n -= 1;
       } 
       else{
        chama *rem = aux;
        (*guarda)->inicio = aux->proximo;
        (*guarda)->fim->proximo = (*guarda)->inicio;
        (*guarda)->n -= 1;
       }
    }
    else{
        // 1 -> 3 -> fim
        // 1 -> 2 - fim
        int j = 0;
        while(j < (*guarda)->n){
            if(aux->proximo->conteudo == remover){
                ioa += 1;
                printf("%d", ioa);
                break;
            }
            aux = aux->proximo;
            j++;
        }
        if(ioa > 0){
            chama *rem = aux->proximo;

            aux->proximo = rem->proximo;
            if(aux->proximo == (*guarda)->inicio){
                (*guarda)->fim = aux->proximo;
            }
            (*guarda)->n -= 1;

        }else{
            printf("\n\t\tNão encontrado!\n");
        }
    }


}
void ordenar_int(cab **guarda){

    if((*guarda)->inicio == NULL){
        ins_com(guarda);
    }
    else{
        chama *aux = (*guarda)->inicio, *ant = NULL, *novo = inserir();
        
        while(aux->proximo != (*guarda)->inicio){
            if(aux->conteudo > novo->conteudo){
                if(ant == NULL){
                    novo->proximo = (*guarda)->inicio;
                    (*guarda)->inicio = novo;
                    (*guarda)->fim->proximo = novo;
                }else{
                    novo->proximo = aux;
                    ant->proximo = novo;
                }
                (*guarda)->n++;
                return ;
            }
            ant = aux;
            aux = aux->proximo;
        }
        if(aux->proximo == (*guarda)->inicio){
            novo->proximo = aux->proximo;
            aux->proximo = novo;
            (*guarda)->fim = novo;
            (*guarda)->n++;
        }
    }
}
////////////////////////////////////////   STRINGS   ///////////////////////////////
void inserir_referenciaSTRI( cab **guarda){
    char nome[30];
    printf("\n\tDigite a referencia ");
    scanf(" %30[^\n]s", nome);
    scanf("");
    if((*guarda)->inicio == NULL){
        ins_com(guarda);
    }
    else{

        chama *aux = (*guarda)->inicio, *novo = inserir();

        while(aux->proximo != (*guarda)->inicio && strcmp(aux->nome, nome) != 0){
            aux = aux->proximo;
        }
        // 1 -> fim
        // 2   -> 1   ->> fim   
        novo->proximo = aux->proximo;

        if((*guarda)->inicio == aux->proximo){
            (*guarda)->fim = novo;
        }
        aux->proximo = novo;

        (*guarda)->n++;
    }

}

void ord_string( cab **guarda){

    chama *aux=(*guarda)->inicio, *ant = NULL, *novo = inserir();

    if(aux == NULL || strcmp(novo->nome, aux->nome) < 0){
        //printf("\n\tprim");
        novo->proximo = aux;
        (*guarda)->inicio = novo;
        if((*guarda)->fim == NULL){
            (*guarda)->fim = novo;
        }
        (*guarda)->fim->proximo = novo;
        (*guarda)->n++;
    }
    else{
        //printf("\n\tseg");

        while(aux->proximo != (*guarda)->inicio){
            if(strcmp( novo->nome, aux->proximo->nome) < 0){
                // 1   3
                novo->proximo = aux->proximo;
                aux->proximo = novo;
                (*guarda)->n++;
                return ;
            }
            ant = aux;
            aux = aux->proximo;
        }
        novo->proximo = aux->proximo;
        aux->proximo = novo;
        (*guarda)->fim = novo;
        (*guarda)->n++;
    }

}

void rem_stri( cab **guarda, char remover[30]){
    chama *aux = (*guarda)->inicio, *ant = NULL;
    int num = 0;

    if(strcmp(remover, aux->nome) == 0){
        if(aux->proximo == (*guarda)->inicio){
            (*guarda)->inicio = NULL;
            (*guarda)->fim = NULL;
            (*guarda)->n--;
        }
        else{
            (*guarda)->inicio = (*guarda)->inicio->proximo;
            (*guarda)->fim->proximo = (*guarda)->inicio;
            (*guarda)->n--;
        }
    }
    else{
        ant = aux;
        aux = aux->proximo;
        while(aux != (*guarda)->inicio ){
            // 1   2 
            if(strcmp(remover, aux->nome) == 0){
                // 1    2
                // 1    2     3
                ant->proximo = aux->proximo;
                if(aux->proximo == (*guarda)->inicio){
                    (*guarda)->fim = ant;
                }
                (*guarda)->n--;
                return ;
            }
            ant = aux;
            aux = aux->proximo;
        }
        printf("\n NÃO ENCONTRADO!");

    }

}
