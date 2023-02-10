#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dados{
    char nome[50];
    int cont;
}pessoa;

typedef struct node{
    pessoa *Pessoa;
    struct node *filh1;
    struct node *filh2;
    struct node *filh3;
}no;

pessoa *Pessoa_dados(){
    pessoa *p = (pessoa*)malloc(sizeof(pessoa));
    printf("\n**************\n\tNome: ");
    scanf(" %50[^\n]s", p->nome);
    printf("\n\tIdade: ");
    scanf("%d", &p->cont);
    return p;
}

void dados(no **guardar){
    pessoa *p = Pessoa_dados();
    no *novo = (no*)malloc(sizeof(no));
    novo->Pessoa = p;
    novo->filh1 = NULL;
    novo->filh2 = NULL;
    novo->filh3 = NULL;
    *guardar = novo;
}

void imprimir(no *raiz, int tab = 0){
    if(raiz == NULL){
        return ;
    }
    for(int i = 0; i<tab; i++){
        printf("\t");
    }
    printf("%s/%d\n", raiz->Pessoa->nome, raiz->Pessoa->cont);
    imprimir(raiz->filh1, tab + 1);
    imprimir(raiz->filh2, tab + 1);
    imprimir(raiz->filh3, tab + 1);
}

void arvore(no *raiz){
    printf("\n************ARVORE************\n");
    imprimir(raiz);
    printf("\n******************************");
}


no *busca_profunda(no *raiz, char *nome){
    if(raiz == NULL) {return NULL;}

    if(strcmp(raiz->Pessoa->nome, nome) == 0) {return raiz;}

    no *achei = busca_profunda(raiz->filh1, nome);
    if(achei != NULL){
        return achei;
    }
    achei = busca_profunda(raiz->filh2, nome);
    if(achei != NULL){
        return achei;
    }
    achei = busca_profunda(raiz->filh3, nome);
    if(achei != NULL){
        return achei;
    }
    return NULL;

}

void put_tree_child(no **root, no *p, char *nome){

    no *test = busca_profunda(*root, nome);

    if(test != NULL){
        if(test->filh1 == NULL){
            test->filh1 = p;
            return ;
        }
        if(test->filh2 == NULL){
            test->filh2 = p;
            return ;
        }
        if(test->filh3 == NULL){
            test->filh3 = p;
            return;
        }
        else{
            printf("\n\tAlready have too many Children");
            return;
        }
    }
    else{
        printf("\n\tNot found");
    }
}

void insert_into_tree(no **root){
    if((*root) == NULL){
        dados(root);
    }else{
        char nome[50];
        no *p = NULL;
        dados(&p);
        printf("\n\tDigite o nome do Pai/Mae: ");
        scanf(" %50[^\n]s", nome);
        put_tree_child(root, p, nome);
    }
}


int main(){
    no *root = NULL;
    int op = 0;

    while(true){
        printf("\nMenu");
        printf("\n\t1 - ins\n\t2 - imprimir\n\t");
        scanf("%d", &op);
        switch (op)
        {
            case 1:{
                insert_into_tree(&root);
                break;            
            }
            case 2:{
                imprimir(root);
                break;
            }
            default:
                break;
        }

        if(op != 0){
            continue;
        }else{
            break;
        }
    }
    


    return 0;

}