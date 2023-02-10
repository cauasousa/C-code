//um nome, ano de fabricação, preço de compra e
//preço de venda.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <strings.h>
#include "bibliote_prova.h"

int main(){
    chama *venda = NULL;
    chama *vendido = NULL;
    int op = 0;


    while (true)
    {
        printf("\n--------------------------");
        printf("\tBem-Vindo ao Programa");
        printf("\t--------------------------\n");
        //system("pause");
        //system("cls");
        printf("\n\t*\t0 - Sair\t**");         //
        printf("\n\t*\t1 - Inserir Veiculo\t"); //
        printf("\n\t*\t2 - Vender Veiculo\t");   //
        printf("\n\t*\t3 - Busca de Veiculo Pelo Preco\t"); 
        printf("\n\t*\t4 - Busca de Veiculo Pelo Ano\t");
        printf("\n\t*\t5 - Mostrar Lucro\t");
        printf("\n\t*\t6 - Mostrar lista de venda\t");
        printf("\n\t*\t7 - Mostrar lista do vendidos\t"); 
        
            //
           //


        scanf("%d", &op);

        switch (op)
        {
        case 0:
        {
            break;
        }

        case 1:
        {
            ornd_string(&venda);
            break;
        }
        case 2:
        {
            char nome[50];
            printf("\n\tNome do veiculo: ");
            scanf(" %50[^\n]s", nome);
            vender(&venda, nome, &vendido);
            break;
        }
        case 3:
        {
            float pre = 0.0f;
            if(venda != NULL){
                printf("\n\tPreco procurado: ");
                scanf("%f", &pre);
                imprimir_preco(venda, pre);
            }else{ 
                printf("Lista vazia!");
            }
            
            break;
        }
        case 4:
        {
            int pre = 0;
            if(venda != NULL){
                printf("\n\tAno procurado: ");
                scanf("%d", &pre);
                imprimir_ano(venda, pre);
            }else{ 
                printf("Lista vazia!");
            }
            
            break;
        }
        case 5:
        {
            if(vendido != NULL){
                lucro(vendido);
            }else{
                printf("\n\tSem Lucro!");
            }
            break;
        }
        case 6:
        {
            if (venda != NULL)
            {
                imprimirtodo(venda);
            }
            else
            {
                printf("\n\t\tLista Vazia!");
            }

            break;
        }
        case 7:
        {
            if (vendido != NULL)
            {
                imprimirtodo(vendido);
            }
            else
            {
                printf("\n\t\tLista Vazia!");
            }

            break;
        }
        default:
        {
            break;
        }
        }

        if (op != 0)
        {
            continue;
        }
        else
        {
            break;
        }
    }


    return 0;
}