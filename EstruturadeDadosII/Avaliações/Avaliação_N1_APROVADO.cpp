#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int size = 0;

struct data{
    int day, month, year;
};

typedef struct node
{
    int cpf;
    char name[50];
    struct data date;
    node *prox;

}lista;

lista *data(){
    lista *aux = new lista;

    printf("CPF: ");
    scanf("%d", &aux->cpf);
    printf("Name: ");
    scanf(" %[^\n]s", aux->name);
    printf("\t-------DATE--------\n");
    printf("Day: ");
    scanf("%d", &aux->date.day);
    printf("Month: ");
    scanf("%d", &aux->date.month);
    printf("Year: ");
    scanf("%d", &aux->date.year);
    size = size + 1;

    aux->prox = NULL;
    return aux;
}

void Printf_data(lista *aux){
    if(aux == NULL){
        return;
    }
    //printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf(" %d |", aux->cpf);
    printf("\t%s |", aux->name);
    printf(" %d/", aux->date.day);
    printf("%d/", aux->date.month);
    printf("%d\n", aux->date.year);
    //printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
}

void print(lista *aux){
    printf("\n-=-=-=-=-=-=-=-=START-=-=-=-=-=-=-=-\n");
    while(aux != NULL){
        
        Printf_data(aux);
        aux = aux->prox;

    }
    printf("\n-=-=-=-=-=-=-=-END=-=-=-=-=-=-=-=-\n");
    
}

void insertion_end(lista **head, lista *novo){
    //insere um elemento
    if(*head == NULL){
        *head = novo;
        novo->prox = NULL;
        return;
    }
    lista *aux = *head;
    while(aux->prox != NULL){
        aux = aux->prox;
    }
    
    novo->prox = NULL;
    aux->prox = novo;
    

}

bool research_sequential(lista *head, lista *new_ele, int option = 0){
    // se option for zero, irá buscar a pessoa q tem todos os dados iguais ao new_ele.
    // caso não for zero, irá buscar todos os ingressos que tem o mesmo cpf igual ao do new_ele e então imprimir.
    while(head != NULL){
        if(head->cpf == new_ele->cpf){
            if(option == 0){
                if(head->date.day == new_ele->date.day){
                    if(head->date.month == new_ele->date.month){
                        if(head->date.year == new_ele->date.year){
                            printf("There is ticket !!");
                            return true;
                        }
                    }
                }
            }
            else{
                Printf_data(head);
            }
        }
        head = head->prox;
    }
    return false;
}

void insertion_sort(lista **head){
    lista *ins = (*head)->prox, *anterior_ins = *head;
    
    while(ins != NULL){

        lista *aux_1 = *head, *anterior_aux_1 = *head;

        while(aux_1 != ins){

            if(ins->cpf < aux_1->cpf){
                
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
        }

        anterior_ins = ins;
        ins = ins->prox;
    }

}

void method_insertion_sort(lista **head, lista *new_elem){
    //lista *new_elem = data();
    
    bool verif = research_sequential(*head, new_elem);

    if(verif == false){
        insertion_end(head, new_elem);
        if(size > 1){
            insertion_sort(head);
        }
    }
    else{
        delete new_elem;
        size--;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////QUICK_SORT///////////////////////////////////////////////////////////////////
bool cond(lista *aux_1, lista *aux_2, bool *equal = NULL){
    //return false aux_1 < aux_2 
    //return true aux_1 > aux_2 
    if(aux_1->date.year < aux_2->date.year){
        return false;
    }
    else if(aux_1->date.year > aux_2->date.year){
        return true;
    }

    if(aux_1->date.month < aux_2->date.month){
        return false;
    }
    else if(aux_1->date.month > aux_2->date.month){
        return true;
    }

    if(aux_1->date.day < aux_2->date.day){
        return false;
    }
    else if(aux_1->date.day > aux_2->date.day){
        return true;
    }

    if(equal != NULL){
        *equal = true;
    }
    return true;
}

int larger_pivo(lista *aux, lista *my_pivo)
{
    int larger = 0;

    while (aux != NULL)
    {
        if(cond(aux, my_pivo) == true)
        {
            larger++;
        }
        aux = aux->prox;
    }
    return larger;
}

lista *remover_pivo(lista **cabeca, int pivo)
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

lista *remover_start(lista **cabeca)
{
    lista *aux = *cabeca;

    if (aux == NULL)
    {
        return NULL;
    }
        
    *cabeca = (*cabeca)->prox;
    aux->prox = NULL;

    return aux;
}

lista *ord(lista **ceil_head, lista *pivo)
{
    lista *aux = NULL, *aux_floor_head = NULL;
    lista *aux_ceil_head = NULL, *temporario_ceil = NULL, *temporario_floor = NULL;
    
    aux = remover_start(ceil_head);

    while (aux != NULL)
    {
        if(cond(aux, pivo) == true)
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

        aux = remover_start(ceil_head);
    }

    *ceil_head = aux_ceil_head;
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

lista *quick_sort(lista **head, int tam = size)
{
    
    if (*head == NULL)
    {
        return NULL;
    }
    if (tam <= 1)
    {   
        return *head;
    }
    
    int local_pivo = tam/2;

    lista *new_pivo = remover_pivo(head, local_pivo);

    int maior = larger_pivo(*head, new_pivo);
    
    lista *menores = ord(head, new_pivo);
    
    new_pivo->prox = quick_sort(head, maior);
    *head = new_pivo;
    
    menores = quick_sort(&menores, tam - maior - 1);
    if (menores != NULL)
    {
        attach_end(menores, new_pivo);
        *head = menores;
    }
    return *head;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void information_ticket(lista *head){
    lista *aux = NULL;
    
    while (head != NULL){
        int cont = 0;
        aux = head->prox;

        while(aux != NULL){
            bool equal = false;
            cond(head, aux, &equal);
            if(equal == true){
                cont+=1;
            }else{
                break;
            }
            aux = aux->prox;
        }
        printf("In data %d/%d/%d has %d ticket sales\n", head->date.day, head->date.month, head->date.year, cont+1);
        head = aux;
    }
}


bool menu(lista **head){

    printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n0 - Close");
    printf("\n1. Add a new element");
    printf("\n2. Research by CPF");
    printf("\n3. FINALIZE SALES");
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
            lista *new_elem = data();
            method_insertion_sort(head, new_elem);
            return true;
        }
        case 2:{
            //RESEARCH BY CPF
            lista CPF;
            printf("which CPF: ");
            scanf("%d", &CPF.cpf);
            research_sequential(*head, &CPF, 1);
            return true;
        }
        case 3:{
            //FINZALIZE
            quick_sort(head);
            printf("\n");
            information_ticket(*head);
            return true;
        }
        case 4:{
            //Imprimir a lista
            print(*head);
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

    bool cond = true;
    while (cond != false){
        cond = menu(&cabeca);
    }
       
    return 0;
}