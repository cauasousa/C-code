#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

typedef struct cel
{
    char nome[30];
    int quan_esto;
    int quant_min;
    float preco;
    struct cel *prox;
} celula;

void imprimir(celula *aux)
{
    printf("Lista");
    
    while (aux != NULL)
    {
        printf("-->\n\t\tProduto: %s -> ", aux->nome);
        printf("\t\tEstoque: %d -> ", aux->quan_esto);
        printf("\t\tQuantiadade Minima: %d -> ", aux->quant_min);
        printf("\t\tPreço: %f -> ", aux->preco);

        aux = aux->prox;
    }
    printf("\nNULL\n");
}
void inserir(celula **ptr_cabeca)
{
    celula *nova = (celula *)malloc(sizeof(celula));

    printf("Digite o nome do produto: ");
    scanf(" %30[^\n]s", nova->nome);
    printf("\nEstoque: ");
    scanf("%d", &nova->quan_esto);
    printf("\nQuantidade Minima: ");
    scanf("%d", &nova->quant_min);
    printf("\nPreco: ");
    scanf("%f", &nova->preco);
    nova->prox = *ptr_cabeca;
    *ptr_cabeca = nova;
}
void imprimir_menu()
{
    printf("\n\n");
    printf("*******\t\tMENU\t********\n");
    printf("*\t\t1 - Inserir produto\t*\n");
    printf("*\t\t2 - Imprimir produtos\t*\n");
    printf("*\t\t3 - Valor Total e Valor Médio\t*\n");
    printf("*\t\t4 - Dividir a Lista em dua: Informe o nome da parte onde deseja começar a divisão\t*\n");
    printf("*\t\t5 - Acessar conteúdo da Lista 2\t\t*\n");
    printf("*\t\t6 - Inserir Com o código do prof\t\t*\n");

    printf("*\t0 - Sair\t\t*\n");
}
void V_estoque(celula **ptr_cabeca)
{
    celula *aux;
    float T_valor = 0.0;
    float prec1 = 0.0;
    float est2 = 0.0;
    float soma = 0.0;
    aux = *ptr_cabeca;
    float prec_medio = 0.0;

    if (*ptr_cabeca == NULL)
    {
        printf("\n\t\tSem Lista");
    }
    else
    {
        // Para contar/ usado no Preco médio
        float i = 0.0;
        while (aux != NULL)
        {
            
            prec1 = (*aux).preco;
            est2 = (*aux).quan_esto;
            T_valor = prec1 * est2;

            prec_medio = prec_medio + (aux->preco);

            soma = soma + T_valor;
            aux = aux->prox;
            i++;
        }
        prec_medio = (prec_medio / i);
        printf("\n\t\tValor Total: %.3f\n", soma);
        printf("\t\tPreço Médio: %.3f", prec_medio);
    }
}
celula *INS()
{
    celula *nova = (celula *)malloc(sizeof(celula));

    printf("Digite o nome do produto: ");
    scanf(" %30[^\n]s", nova->nome);
    printf("\nEstoque: ");
    scanf("%d", &nova->quan_esto);
    printf("\nQuantidade Minima: ");
    scanf("%d", &nova->quant_min);
    printf("\nPreco: ");
    scanf("%f", &nova->preco);
    return nova;
}
celula *dividir(celula **ptr_cabeca)
{
    celula *Lista_2 = NULL;
    celula *aux = *ptr_cabeca;
    celula *ant = *ptr_cabeca;

    if(*ptr_cabeca == NULL){
        printf("\n\t\tSem Lista 1 !!!");
        return NULL;
    }    

    char Nome[50];
    
    printf("Digite o nome de onde deseja dividir: ");
    scanf(" %50[^\n]s", Nome);
    printf("%s", Nome);


    if (strcmp(aux->nome, Nome) == 0)
    {
        Lista_2 = *ptr_cabeca;
        *ptr_cabeca = NULL;
        return Lista_2;
    }
    else
    {
        aux = aux->prox;
        while ((aux != NULL) && (strcmp(aux->nome, Nome) != 0))
        {
            aux = aux->prox;
            ant = ant->prox;
        }
        if ((aux == NULL) && (strcmp(aux->nome, Nome) != 0))
        {
            printf("Nome não encontrado!");
            return NULL;
        }
        else if (strcmp(aux->nome, Nome) == 0)
        {

            Lista_2 = aux;
            ant->prox = NULL;
            return Lista_2;
        }
    }
}

void orde_alfab(celula **cabeca){
    celula *aux, *aux_2;
    celula *nova = (celula *)malloc(sizeof(celula));
    char a[] = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
    nova = INS();
    int Cont = 0;
    int cont = 0;


    if(*cabeca == NULL){
        nova->prox = NULL;
        *cabeca = nova;
        return ;
    }

    else {

        for(int i = 0; i<52; i++){
            if(nova->nome[0] == a[i]){
                //printf("%c", a[i]);
                break;
            }
            cont++;
        }
        //printf("\n------%d-----\n", cont);
        //cont = 7

        for(int i = 0; i<cont; i++){
            aux = *cabeca;
            while(aux != NULL){
                if(a[i] == aux->nome[0]){
                    //printf("Segundo for == %s", aux->nome);
                    Cont++;
                }
                aux = aux->prox;
            }
        }
        //printf("\n---%d---\n", Cont);
        aux = *cabeca;

        if(Cont == 0){
            nova->prox = *cabeca;
            *cabeca = nova;
            //printf("Dentro do primeiro if0");
            return ; 
        }
        else if(Cont == 1){
            //printf("Segundo IF2");
            nova->prox = aux->prox;
            aux->prox = nova;
            return ;
        }
        else {
            aux_2 = *cabeca;
            //printf("Terceiro else");
            for(int i = 0; i<Cont-1; i++){
                aux_2 = aux_2->prox;
            }
            //printf("\nNome do ulimo %s \n", aux_2->nome);
            nova->prox = aux_2->prox;
            aux_2->prox = nova;

            return ;
        }

    }

}

void prof_orde(celula **cabeca){
    celula *aux = *cabeca;
    celula *ant = NULL;
    celula *nova = (celula*)malloc(sizeof(celula));
    nova = INS();

    if(*cabeca == NULL){
        *cabeca = nova; 
        nova->prox = NULL;
    }
    else {
        while(aux != NULL){
            if(strcmp(nova->nome, aux->nome) < 0 ){
                //printf("oi");
                if(ant != NULL){
                    ant->prox = nova;
                }
                else {
                    *cabeca = nova;
                }
                nova->prox = aux;
                return ; 
            }
            ant = aux;
            aux = aux->prox;
        }
        //printf("FIm");
        ant->prox = nova;
        nova->prox = NULL;
        return; 
    }
}


int main(int argc, char const *argv[])
{
    celula *head = NULL;
    celula *Lista_2 = NULL;

    int opc = 1;
    while (opc != 0)
    {
        imprimir_menu();
        scanf("%d", &opc);
        fflush(stdin);
        switch (opc)
        {
        case 1:{
            orde_alfab(&head);
            //ins_af(&head);
            break;            
        }
        case 2:{
            imprimir(head);
            break;            
        }
        case 3:{
            V_estoque(&head);
            break;            
        }
        case 4:{
            Lista_2 = dividir(&head);
            break;            
        }
        case 5:{
            imprimir(Lista_2);
            break;
        }    
        case 6:{
            prof_orde(&head);
            imprimir(head);
            break;
        }
        default:{
            printf("Opção inválida\n");
            break;            
        }

        }
    }

    return 0;
}
