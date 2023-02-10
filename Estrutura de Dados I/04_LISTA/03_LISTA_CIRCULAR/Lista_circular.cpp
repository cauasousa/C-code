#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Biblioteca_Lista_Circular.h"

int main(){
    cab *head;
    head->fim = NULL;
    head->inicio = NULL;
    head->n = 0;

    int op = 0;

    while(true){
        printf("\n------ Menu------");
        printf("\n\t0 - Sair\n\t1 - Inserir inicio\n\t2 - Inserir Meio\n\t3 - Inserir Fim\n\t4 - Inserir com Referencia com numero\n\t5 - Imprimir");
        printf("\n\t6 - Remover\n\t 7 - Ordenar\n\t8 - Retirar Ocorrencia");
        printf("\n\t9 - Inserir com Referencia com Strings");
        printf("\n\t10 - Remover com String\n\t 11 - Ordenar Com String\n\t\n\t");
        scanf("%d", &op);

        switch (op)
        {
        case 0:{break;}
        case 1:{
            ins_com(&head);
            break;
        }
        case 2:{
            ins_meio(&head);
            break;
        }
        case 3:{
            ins_fim(&head);
            break;
        }
        case 4:{
            inserir_referenciaNum(&head);
            break;
        }
        case 5:{
            imprimir(head);
            break;
            }
        case 6:{
            remover(&head);
            break;
        }
        case 7:{
            ordenar_int(&head);
            break;
        }
        case 8:{break;}

        case 9:{
            inserir_referenciaSTRI(&head);
            break;
        }
        case 10:{
            char nome[30]; 
            printf("\n\tD ");
            scanf(" %30[^\n]s", nome);
            rem_stri(&head, nome);
            break;
            }
        case 11:{
            ord_string(&head);
            break;
            }
        case 12:{break;}
                
        default:
            break;
        }


        if(op != 0){
            continue;
        }
        else{
            break;
        }

    }
    

    return 0;
}