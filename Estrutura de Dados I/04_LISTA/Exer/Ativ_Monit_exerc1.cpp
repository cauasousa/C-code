#include <stdio.h>
#include <stdlib.h>

typedef struct noDaLista 
{
 char titulo[51]; 
 char autor[51]; 
 int ano; 
 int quantidade; 
 noDaLista *prox; 
}chama; 

noDaLista *novo(){
    noDaLista *nova = (noDaLista*)malloc(sizeof(noDaLista));
    printf("\n\t\tDigite o nome da Obra:  ");
    scanf(" %50[^\n]s", nova->titulo);
    printf("\n\t\tAutor:  ");
    scanf(" %50[^\n]s", nova->autor);
    printf("\n\t\tAno:  ");
    scanf("%d", &nova->ano);
    printf("\n\t\tQuant:  ");
    scanf("%d", &nova->quantidade);
    return nova;
}

void imprimir(noDaLista *novo){
    noDaLista *nova = NULL;
    nova = novo;
    while(nova != NULL){
        printf("\n");
        printf("\n\t\tnome da Obra:  ");
        printf(" %s", nova->titulo);
        printf("\tAutor:  ");
        printf(" %s", nova->autor);
        printf("\tAno:  ");
        printf("%d", nova->ano);
        printf("\tQuant:  ");
        printf("%d", nova->quantidade);  
        nova = nova->prox;      
    }

}

void inserir(noDaLista **cabeca){
    noDaLista *nova = novo();
    printf("%s", nova->autor);
    noDaLista *aux = *cabeca;
    noDaLista *aux_2 = NULL;


    if(*cabeca == NULL){
        printf("Entrou");
        nova->prox = NULL;
        *cabeca = nova;
        return; 
    }
    else {
        while(aux != NULL){
            if(nova->ano < aux->ano){
                
                if(aux_2 != NULL){
                    aux_2->prox = nova;}
                else{
                    *cabeca = nova;
                }
                nova->prox = aux;
                return ;
            }
        aux_2 = aux;
        aux = aux->prox;
        }
        aux_2->prox = nova;
        nova->prox = NULL;
        return; 

    }




}
int quant(noDaLista *cabeca){
    int soma = 0;
    noDaLista *aux = cabeca;

    while(aux != NULL){
        soma = soma + aux->quantidade;
        aux = aux->prox;
    }
    return soma;
}
void livros_ano(noDaLista *novo, int ano){
    noDaLista *nova = NULL;
    nova = novo;
    printf("\n\t-----iNÍCIO----->>");
    while(nova != NULL){
        if( ano == nova->ano){

        printf("");
        printf("\n\t\tnome da Obra:  ");
        printf(" %s", nova->titulo);
        printf("\tAutor:  ");
        printf(" %s", nova->autor);
        printf("\tAno:  ");
        printf("%d", nova->ano);
        printf("\tQuant:  ");
        printf("%d", nova->quantidade);              
        }

        nova = nova->prox;      
    }

}

int main(){
    noDaLista *head = NULL;
    int num = 1;
    do{

        printf("\n\t\t\t\t--Menu-- ");
        printf("\n\t\t1 - Inserir");
        printf("\n\t\t2 - Quantidade de Livros");
        printf("\n\t\t3 - Buscar Livro por ano");
        printf("\n\t\t4 - Imprimir");
        printf("-------------------------");

        scanf("%d", &num);
        switch (num)
        {
        case 1:{
            inserir(&head);    
            system("cls");
            break;            
        }

        case 2:{
            int quan = 0;
            quan = quant(head);
            printf("\nTem %d", quan);            
            break;
        }
        case 3: {
            int Ano = 0;
            printf("\n\t\tDigite o ano de busca");
            scanf("%d", &Ano);
            livros_ano(head , Ano);
            printf("\n-----FIM-----");
            break;
        }

        case 4:{
            system("cls");
            printf("----Início----");
            imprimir(head);
            printf("----FIm----");

            break;            
        }

        default:{
            printf("\n\t\tNúmero Inválido!");
            break;            
        }

        }

    }while( num != 0);

    return 0;
}