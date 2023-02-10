#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <strings.h>
//um nome, ano de fabricação, preço de compra e
//preço de venda.
typedef struct lista{

    char nome[50];
    int conteudo;
    float preco_compra;
    float preco_venda;
    struct lista *proxi;
    struct lista *anterior;

}chama;

void imprimir( chama *cabeca){

    printf("\n\t\tLista\n\t");
    while(cabeca != NULL){
        printf("- Nome: %s; Ano: %d; Preco de Compra: %.2f; Preco de venda: %.2f; -\n\t", cabeca->nome, cabeca->conteudo, cabeca->preco_compra, cabeca->preco_venda);
        printf("\t-------------------\n\t");
        cabeca = cabeca->proxi;
    }
    printf("\n\t\tFim\n\t");
}
void imprimir_vendido( chama *cabeca){

    printf("\n\t\tLista Dos Veiculos Vendidos\n\t");
    while(cabeca != NULL){
        printf("- Nome: %s; Ano: %d; Preco de Compra: %.2f; Preco de venda: %.2f; -\n\t", cabeca->nome, cabeca->conteudo, cabeca->preco_compra, cabeca->preco_venda);
        printf("\t-------------------\n\t");
        cabeca = cabeca->proxi;
    }
    printf("\n\t\tFim\n\t");
}

void imprimir_preco( chama *cabeca, float preco){

    printf("\n\t\tLista Dos Veiculos abaixo do Preco\n\t");
    while(cabeca != NULL){
        if( preco > cabeca->preco_venda){
            printf("- Nome: %s; \n\t", cabeca->nome);
            printf("\t-------------------\n\t");            
        }

        cabeca = cabeca->proxi;
    }
    printf("\n\t\tFim\n\t");
}

void imprimir_ano( chama *cabeca, int ano){

    printf("\n\t\tLista Dos Veiculos Pelo Ano\n\t");
    while(cabeca != NULL){
        if( ano == cabeca->conteudo){
            printf("- Nome: %s;\n\t", cabeca->nome);
            printf("\t-------------------\n\t");            
        }

        cabeca = cabeca->proxi;
    }
    printf("\n\t\tFim\n\t");
}
void lucro( chama *cabeca){
    float lucro = 0.0f;
    while(cabeca != NULL){
        lucro = lucro + (cabeca->preco_venda - cabeca->preco_compra);
        cabeca = cabeca->proxi;
    }
    printf("\n\t\tLucro: %.3f\n\t", lucro);
}
chama *inserir(){
    chama *nova = (chama*)malloc(sizeof(chama));
    printf("\n\tNome: ");
    scanf(" %50[^\n]s", nova->nome);
    printf("\n\tAno: ");
    scanf("%d", &nova->conteudo);
    printf("\n\tPreco de compra: ");
    scanf("%f", &nova->preco_compra);
    nova->preco_venda = (nova->preco_compra + (nova->preco_compra * 20.0)/100.0f);
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

void ornd_segunda(chama **cabeca, chama *opa, float vendido)
{
    opa->preco_venda = vendido;
    opa->anterior =NULL;
    opa->proxi = NULL;
    chama *nova = opa;
    
    if (*cabeca == NULL)
    {
        if(*cabeca == NULL){
            *cabeca = nova;
            printf("Opa");
        }

        return;
    }
    else
    {

        chama *aux = *cabeca, *ant = NULL;
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




void vender( chama **cabeca, char procurar[50], chama **cabeca_2){
    chama *aux = *cabeca, *guarde = NULL, *proximao = NULL;
    float preco_venda, preco_compra;

    while( aux!= NULL ){
        if(strcmp(procurar, aux->nome) == 0){
            guarde = aux;
            preco_compra = aux->preco_compra;
            break;
        }
        proximao = aux;
        aux = aux->proxi;
    }

    if(guarde != NULL){
        int nada = 0, cont = 0;

        while(true){
            
            printf("\n\tDigite o preco que deseja vender: ");
            scanf("%f", &preco_venda);

            if(preco_venda>preco_compra){
                cont++;
            }else{
                printf(" Não pode ser vendido ");
            }


            printf("\n\t0 - Finalizar\n\t1 - Alterar o valor\n\t->> ");
            scanf("%d", &nada);


            if(nada != 0){

                cont = 0;

                continue;
            }else{
                if(cont == 1){
                    if(proximao != NULL){
                        if(proximao->proxi->proxi != NULL){

                            proximao->proxi->proxi->anterior = proximao;
                            
                              
                            proximao->proxi = proximao->proxi->proxi;   


                        }else{
                            proximao->proxi = NULL;
                        }

                    }
                    else{
                        (*cabeca) = aux->proxi;
                        (*cabeca)->anterior = NULL;
                    }

                    ornd_segunda(cabeca_2, aux, preco_venda);
                    
                }

                break;
            }
        }



    }else{
        printf("\n\tVeiculo não encontrado\n");
        }


}
void imprimirtodo(chama *cabeca)
{

    chama *cab_fim = NULL;

    printf("\n\t\tLista\n\t");
    while (cabeca != NULL)
    {
        printf("-%s _ %d -", cabeca->nome, cabeca->conteudo);

        if (cabeca->proxi == NULL)
        {
            cab_fim = cabeca;
        }
        cabeca = cabeca->proxi;
    }
    printf("\n\t\tVolta Lista\n\t");

    while (cab_fim != NULL)
    {
        printf("-%s _ %d -", cab_fim->nome, cab_fim->conteudo);
        cab_fim = cab_fim->anterior;
    }
}