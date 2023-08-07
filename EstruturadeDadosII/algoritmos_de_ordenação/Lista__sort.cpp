#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <random>
#include <time.h>

typedef struct node
{
    char nome[50];
    int num; //O número do localizador
    node *prox;

}lista;

int quant = 0;

lista *data(){

    lista *aux = (lista*)malloc(sizeof(lista));
    aux->prox = NULL;
    printf("Nome: ");
    scanf(" %[^\n]s", aux->nome);
    quant = quant + 1;
    aux->num = quant;
    return aux;
}

void inserir(lista **no, lista *novo){
    if(*no == NULL){
        *no = novo;
        novo->prox = NULL;
        return;
    }
    lista *aux = *no;
    while(aux->prox != NULL){
        aux = aux->prox;
    }
    
    novo->prox = aux->prox;
    aux->prox = novo;
    
}

void print(lista *aux){
    while(aux != NULL){

        printf(" %s ->", aux->nome);
        aux = aux->prox;

    }
    printf(" NULL");
}

void preencher_vetor(int *vetor, int quan){
    int quant_preenchida = 0;

    while(quant_preenchida < quan){
        int aleatorio = 1 + (rand() % quan);
        int achou = 0;

        for(int verificador = 0; verificador < quant_preenchida; verificador++){
            if( vetor[verificador] == aleatorio ){
                achou=1;
                break;
            }

        }
        if(achou == 0){
            vetor[quant_preenchida] = aleatorio;
            quant_preenchida+=1;
        }   
    }

}

lista *remov(lista **cabeca, int local){

    lista *aux = *cabeca;
    lista *ant = NULL;
    
    if(*cabeca != NULL){

        while(aux != NULL && aux->num != local){

            ant = aux;
            aux = aux->prox;

        }

        if(aux != NULL){
            if(aux->num == local){

                if(ant == NULL){
                    ant = aux->prox;
                    *cabeca = ant;
                } else{
                    ant->prox = aux->prox;
                }
                aux->prox = NULL;
            
            }
        }
    }
    
    return aux;
}

void shuffle(lista **cabeca){

    if(*cabeca != NULL){

        int *vetor = (int*)malloc( sizeof(int) * quant);
        preencher_vetor(vetor, quant);

        lista *ord = NULL;
        
        for(int i = 0; i<quant; i++){
            
            inserir(&ord, remov(cabeca, vetor[i]) );
            
        }

        *cabeca = ord;

    }

}

void bubble_sort(lista **cabeca){
    
    
    int i = 0;

    while(quant > i){
        
        lista *aux = *cabeca;
        lista *seg_comparacao = aux->prox;
        int otimi = 0;

        while(aux != NULL && seg_comparacao != NULL && (quant - i) > otimi){
            
            if(strcmp(aux->nome, seg_comparacao->nome) > 0){
                
                
                lista *rem = remov(cabeca, aux->num);
                rem->prox = seg_comparacao->prox;
                seg_comparacao->prox = rem;
                
            }else{
                aux = aux->prox;
            }
            seg_comparacao = aux->prox;  
            otimi = otimi + 1; 
        }

        i++;
    }
}

void selection_sort(lista **head){
    lista *aux = *head, *next = *head, *anterior_aux = NULL, *anterior_next = NULL;

    while(aux->prox != NULL){
        lista *proximo = aux->prox;

        next =  aux;
        lista *address = next, *temporary_2 = NULL;

        while(next != NULL){

            if(strcmp(address->nome, next->nome) > 0){
                
                anterior_next = temporary_2;
                address = next; 

            }
            temporary_2 = next;
            next = next->prox;

        }

        if(aux != address){

            if(*head == aux){

                *head = address;

            }else{
                //no head
                anterior_aux->prox = address;
            }
            //podem ta junto
            lista *aux_prox = aux;

            if(aux != anterior_next){
                //nao ta junto
                anterior_next->prox = aux;
                aux_prox = aux->prox;
            }
            
            aux->prox = address->prox;
            address->prox = aux_prox;

            anterior_aux = address;  

        }
        else{
            anterior_aux = aux;  
        }

        aux = proximo;
                
    }

};

void insertion_sort(lista **head){
    lista *ins = (*head)->prox, *anterior_ins = *head;
        
    for(int i = 1; i < quant; i++){

        if(ins!= NULL){
            
            int j = 0;
            lista *aux_1 = *head, *anterior_aux_1 = *head;

            while(aux_1 != NULL && j < i){

                if(strcmp(aux_1->nome, ins->nome) > 0){
                    //Obs: Outro método: utilizar a função remov, dependendo do caso médio pode aumentar a complexidade
                    if(aux_1->prox == ins){

                        //ta junto
                        aux_1->prox = ins->prox;
                        ins->prox = aux_1; 

                    }else{

                        //nao ta junto
                        anterior_ins->prox = ins->prox;
                
                    }

                    if(aux_1 == *head){
                        //Cabeca
                        *head = ins;
                        
                        if(aux_1->prox != ins){

                            //nao ta junto 
                            ins->prox = aux_1;

                        }
                        
                    }else{
                        //Não ta na cabeca

                        if(aux_1->prox != ins){
                            
                            //nao ta junto
                            ins->prox = anterior_aux_1->prox;
                            
                        }
                        anterior_aux_1->prox = ins;
                    }
                    ins = anterior_ins;
                    break;
                    
                }else{
                    anterior_aux_1 = aux_1;
                    aux_1 = aux_1->prox;
                }
                
                j++;
            }

            anterior_ins = ins;
            ins = ins->prox;
        }
    }

}

bool menu(lista **head){

    printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n0 - Close");
    printf("\n1. Adicionar um novo elemento");
    printf("\n2. Imprimir a lista");
    printf("\n3. shuffle a lista");
    printf("\n4. Ordenar utilizando Bubble Sort");
    printf("\n5. Ordenar utilizando Selection Sort");
    printf("\n6. Ordenar utilizando Insertion Sort");
    printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n-> ");
    int op = 999;

    scanf("%d", &op);

    switch (op)
    {
        case 0:{
            printf("Close");
            return false;
        }
        case 1:{
            //Adicionar um novo elemento
            lista *novo = data();
            inserir(head, novo);

            return true;
        }
        case 2:{
            //Imprimir a lista
            print(*head);
            return true;
        }
        case 3:{
            //shuffle a lista
            printf("The before - ");
            print(*head);

            shuffle(head);

            printf("\nThe after - ");
            print(*head);
            
            return true;
        }
        case 4:{
            //Ordenar utilizando Bubble Sort
            bubble_sort(head);
            printf("Buble Sort completed");
            return true;

        }
        case 5:{
            //Ordenar utilizando Selection Sort
            if(quant > 0){
                selection_sort(head);
            }
            
            printf("Selection Sort completed");
            return true;
        }   
        case 6:{
            //Ordenar utilizando Insertion Sort
            lista *novo = data();
            inserir(head, novo);
            if(quant > 1){

                insertion_sort(head);

            }
            
            printf("Insertion Sort completed");
            return true;
        }
        default:{
            return true;
        }
        
    }
    return true;

}


int main(){

    lista *cabeca = NULL;
    srand(time(NULL));

    bool cond = true;
    while (cond != false){
        cond = menu(&cabeca);
    }
       
    return 0;
}