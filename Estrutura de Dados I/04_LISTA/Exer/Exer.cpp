#include <stdio.h>
#include <stdlib.h>

typedef struct Dados
{
    char nome[20] = "";
    int conteudo = 0;
    Dados *prox;
} chama;
void imprimir(chama **cabeca)
{
    chama *aux;
    aux = *cabeca;
    printf("\n");
    if (aux == NULL)
    {
        printf("Sem lista");
    }
    else
    {
        while (aux != NULL)
        {
            printf("\tLista->");
            printf("\n\t\tNome: %s", aux->nome);
            printf("\t\tConteudo: %d\n", aux->conteudo);

            aux = aux->prox;
        }
        printf("FIM(NULL)!");
    }
}
chama *receber()
{
    chama *novo;
    novo = (chama *)malloc(sizeof(chama));

    printf("\n\t\tDigite o nome: ");
    scanf(" %20[^\n]", novo->nome);

    printf("\n\t\tDigite o valor: ");
    scanf("%d", &novo->conteudo);
    return novo;
}
chama *inserir_comeco(chama **cabeca)
{
    chama *ptr = (chama *)malloc(sizeof(chama));

    printf("\n\t\tDigite o nome: ");
    scanf(" %20[^\n]", ptr->nome);

    printf("\n\t\tDigite o valor: ");
    scanf("%d", &ptr->conteudo);
    ptr->prox = *cabeca;
    return ptr;
};
chama *inserir_final(chama **cabeca)
{
    chama *ptr;
    ptr = (chama *)malloc(sizeof(chama));

    printf("\n\t\tDigite o nome: ");
    scanf(" %20[^\n]", ptr->nome);

    printf("\n\t\tDigite o valor: ");
    scanf("%d", &ptr->conteudo);
    ptr->prox = NULL;

    if (*cabeca == NULL)
    {
        *cabeca = ptr;
        
    }
    else
    {
        chama *aux;
        aux = *cabeca;

        while ((aux->prox != NULL))
        {
            aux = aux->prox;
        }
        aux->prox = ptr;
    }
}
/*
chama *inserir_meio(chama **cabeca)
{
    chama *aux, *novo = NULL;

    int ant = 0;
    aux = *cabeca;

    novo = receber();
    printf("Digite o valor do número anterior onde você deseja adicionar: ");
    scanf("%d", &ant);
    imprimir(&novo);
    if (*cabeca == NULL)
    { //*cabeca = novo;
        novo->prox = NULL;
        *cabeca = novo;
    }
    else if(aux->prox != NULL){
        while ((aux->conteudo != ant))
        {
            aux = aux->prox;
        }
        novo->prox = aux->prox;
        aux->prox = novo;
    }

    else {
        aux->prox = novo;
        novo->prox = NULL;
    }


    return *cabeca;
};
*/
int quant(chama **cabeca)
{
    chama *aux;
    aux = *cabeca;

    int i = 0;
    while (aux != NULL)
    {
        i++;
        aux = aux->prox;
    }

    return i;
}
void inserir_no_meio(chama **lista){
    chama *aux, *novo = (chama*)malloc(sizeof(chama));
    int ant;

    printf("\n\t\tDigite o nome: ");
    scanf(" %20[^\n]", novo->nome);
    printf("\n\t\tDigite o valor: ");
    scanf("%d", &novo->conteudo);
    printf("Digite o valor do número anterior onde você deseja adicionar: ");
    scanf("%d", &ant);

  if (*lista == NULL) {
    novo->prox = NULL;
    *lista = novo;
  }
  else {
    aux = *lista;
    while (aux->conteudo != ant && aux->prox != NULL) {
      aux = aux->prox;
      if(aux->prox == NULL){
        printf("Não achei!!");
      }
    }
    if(aux->conteudo == ant){
    novo->prox = aux->prox;
    aux->prox = novo;     
     
    }
    else {
        printf("Não achei");
        
    }

  }

}
void remover (chama **cabeca, int valor){
        chama *aux0;
        chama *aux;
        chama *aux2;
        if(*cabeca != NULL){
            if((*cabeca)->conteudo == valor){
                aux0 = *cabeca;
                *cabeca = aux0->prox;
            }
            else{
                aux = *cabeca;
                aux2 = aux->prox;
                while((aux2->conteudo != valor)&&(aux2->prox != NULL)){
                    aux = aux->prox;
                    aux2 = aux2->prox;
                }
                if(aux2->conteudo == valor){
                    aux->prox = aux2->prox;
                }
                


            }
        
    }
}

int main()
{
    chama *head = NULL;
    // imprimir(&head);
    int op = 0;
    do
    {
        printf("\n\t\t-1 Sair\n\t\t0 - Imprimir\n\t\t1 - Inserir no começo\n\t\t2 - Inserir no Meio\n\t\t3 - Inserir no Final\n\t\t4 - Remover um número");
        printf("\n\t\t5 - QUantos elementos tem\n\t\t");
        scanf("%d", &op);
        switch (op)
        {
            case 0:{
                system("cls");
                imprimir(&head);
                break;
            }
            case 1:{
                system("cls");
                head = inserir_comeco(&head);
                break;
            }
            case 2:{
                system("cls");
                inserir_no_meio(&head);
                break;
            }
            case 3:{
                system("cls");
                inserir_final(&head);
                break;
            }
            case 4:{
                int num = 0;
                system("cls");
                printf("\n\t\tDigite o Valor para remover: ");
                scanf("%d", &num);
                remover(&head, num);
                break;
            }
            case 5:{
                int q;
                q = quant(&head);
                printf("\n Quantidade: %d", q);
                break;
            }
            default:{
                printf("FIM");
                break;
            }  
        }

    } while (op != -1);

    // head = inserir_comeco(&head);
    // system("cls");
    //  imprimir(&head);
    //   system("cls");
    //  printf("----------Inserir no Final------------");
    //  imprimir(&head);

    // inserir_final(&head);
    // imprimir(&head);
    //  printf("\n---------Inserir no Meio----------\n");
    //  head = inserir_meio(head);
    //  imprimir(&head);
    //  printf("\n----------Quantidade-----------");

    // int q = 0;
    // q = quant(head);
    // printf("\n Quantida: %d", q);

    // printf("\n----------Inverter-----------");
    // chama *L2;
    // L2 = inveter(head);
    // printf("\n----------L2-----------");

    //  imprimir(&L2);
    return 0;
}