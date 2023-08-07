// ▪Implemente funções as funções abaixo em uma
// árvore binária de busca contendo números inteiros
// ▪Imprimir o maior, o menor e a média dos elementos
// ▪Receber um determinado nó e retornar sua altura
// ▪Realizar a troca entre dois nós da árvore
#include <iostream>
#include <stdio.h>
#include <random>
#include <math.h>
#include <time.h>

int tam = 0;

typedef struct tree
{

    int num = 0;
    tree *left;
    tree *right;

};

tree *crie(int num)
{
    tree *NEW = new tree;
    NEW->num = num;
    NEW->left = NULL;
    NEW->right = NULL;
    return NEW;
}

void inserir(tree **raiz, tree *NEW)
{
    if (*raiz == NULL)
    {
        *raiz = NEW;
        return;
    }

    if ((*raiz)->num > NEW->num)
    {
        inserir(&(*raiz)->left, NEW);
    }
    else
    {
        inserir(&(*raiz)->right, NEW);
    }
}


tree *search(tree *raiz, int num)
{
    if (raiz == NULL)
    {
        return NULL;
    }
    if (raiz->num == num)
    {
        return raiz;
    }
    tree *verif = NULL;
    if (raiz->num > num)
    {
        verif = search(raiz->left, num);
    }
    else
    {
        verif = search(raiz->right, num);
    }
    return verif;
}

tree *busca_antecessor(tree *raiz, tree *no_1){
    if(no_1 == NULL or raiz == NULL){
        return NULL;
    }
    if(raiz == no_1){
        return raiz;
    }
    if(raiz->left == no_1 || raiz->right == no_1){
        return raiz;
    }

    tree *ant = NULL;
    ant = busca_antecessor(raiz->left, no_1);
    if(ant != NULL){
        //if(ant->left == no_1 or ant->right == no_1){
        return ant;
        //}
    }
    ant = busca_antecessor(raiz->right, no_1);
    return ant;
}

int sizeof_tree(tree *node) {
    if (node == NULL) {
        return 0;
    }

  return 1 + fmax(sizeof_tree(node->left), sizeof_tree(node->right));
}

tree *search_all(tree *raiz, int num)
{
    if (raiz == NULL)
    {
        return NULL;
    }
    if (raiz->num == num)
    {
        return raiz;
    }
    tree *verif = NULL;
    
    verif = search_all(raiz->left, num);
    if(verif != NULL){
        if(verif->num == num){
            return verif;
        }
    }
    verif = search_all(raiz->right, num);
    return verif;
}

void Rot_simples_Dir(tree **raiz, tree *no){
    if(no == NULL){
        return ;
    }
        
    tree *antecessor_no, *novo_head = no->left;
    if(novo_head == NULL){
        printf("a1I");
    }
    antecessor_no = busca_antecessor(*raiz, no);

    no->left = novo_head->right;
    novo_head->right = no;

    if(no == *raiz){
        *raiz = novo_head;
    }else{

        if(antecessor_no->left == no){
            antecessor_no->left = novo_head;
        }
        else if(antecessor_no->right == no){
            antecessor_no->right = novo_head;
        }
    }
}

void Rot_simples_Esq(tree **raiz, tree *no){
    if(no == NULL){
        return ;
    }

    tree *antecessor_no, *novo_head = no->right;
    antecessor_no = busca_antecessor(*raiz, no);
    if(novo_head == NULL or antecessor_no == NULL){
        printf("ads");
    }
    no->right = novo_head->left;
    novo_head->left = no;

    if(no == *raiz){
        *raiz = novo_head;
    }
    else{
        if(antecessor_no->left == no){
            antecessor_no->left = novo_head;
        }
        else if(antecessor_no->right == no){
            antecessor_no->right = novo_head;
        }
        // antecessor_no->right = novo_head;
    }
    
}

// esquerda + direita
//void Rot_dupla_Dir( tree **raiz, tree *no){
void Rot_dupla_or_simpl_DIR( tree **raiz, tree *no){
    if(no == NULL){
        return;
    }
    int FB = 0;
    if(no->left == NULL){
        FB = 0;
    }
    else{
        FB = sizeof_tree(no->left->left) - sizeof_tree(no->left->right);
    }
    //printf(" 1 ");    
    
    if(FB <= -1){
        Rot_simples_Esq(raiz, no->left);
    }
    //printf(" 1 ");    

    Rot_simples_Dir(raiz, no);
    //printf(" 1 ");    
}

// direita + esquerda
//void Rot_dupla_Esq(tree *raiz, tree *no){
void Rot_dupla_or_simpl_ESQ(tree **raiz, tree *no){
    if(no == NULL){
        return;
    }

    int FB = 0;
    if(no->right == NULL){
        FB = 0;
    }
    else{
        FB = sizeof_tree(no->right->left) - sizeof_tree(no->right->right);
    }
    //printf(" 2 ");    

    if(FB >= 1){
        Rot_simples_Dir(raiz, no->right);
    }
    //printf(" 2 ");    

    Rot_simples_Esq(raiz, no);
    //printf(" 2 ");    

}

void balanca(tree **raiz, tree *no){
    if(no == NULL) {
        return;
    }

    balanca(raiz, no->left);
    balanca(raiz, no->right);
    
    int FD = sizeof_tree((no)->left) - sizeof_tree((no)->right);
       
    //imprimir(no);
    //printf("\n\t '-' ");
    
    if(FD >= 2){  
        //printf("-=-=-D>%d=-FD - %d=-=-=-\n", no->num, FD);
        Rot_dupla_or_simpl_DIR(raiz, no);
    }
    if(FD <= -2){
        //printf("-=-=E->%d=-FD - %d=-=-=-\n", no->num, FD);
        Rot_dupla_or_simpl_ESQ(raiz, no);
    }
    return;
}

void preencher_tree(tree **raiz, int quan = tam)
{
    int quant_preenchida = 0;

    while (quant_preenchida < quan)
    {
        int aleatorio = (rand() % tam) + 1;

        tree *achou = NULL;

        achou = search_all(*raiz, aleatorio);

        if (achou == NULL)
        {
            tree *NEW = crie(aleatorio);
            inserir(raiz, NEW);
            balanca(raiz, *raiz);
            quant_preenchida += 1;
        }
        
    }
}

void print(tree *raiz)
{
    if (raiz == NULL)
    {
        return;
    }
    printf(" %d", raiz->num);
    print(raiz->left);

    print(raiz->right);
}

void imprimir(tree *node, int tab = 0)
{
    if (node == NULL)
    {
        return;
    }

    imprimir(node->right, tab + 1);
    for (int i = 0; i < tab; i++)
    {
        printf(" \t ");
    }
    printf(" %d \n ", node->num);
    imprimir(node->left, tab + 1);
}

int larger(tree *raiz)
{
    if (raiz == NULL)
    {
        return -1;
    }

    if (raiz->right == NULL)
    {
        return raiz->num;
    }

    return larger(raiz->right);
}

int less(tree *raiz)
{
    if (raiz == NULL)
    {
        return -1;
    }

    if (raiz->left == NULL)
    {
        return raiz->num;
    }

    return (less(raiz->left));
}

// float son(tree *raiz, float num = 0)
// {
//     if (raiz == NULL)
//     {
//         return 0;
//     }
    
//     int aux = 0;
//     int aux_2 = 0;
//     num = raiz->num;
//     aux = son(raiz->left, num);
//     aux_2 =  son(raiz->right, num);
    
//     return num + aux + aux_2;
// }

float son(tree *node) {
  if (node == NULL) return 0;

  return node->num + son(node->right) + son(node->left);
}



// int sizeof_tree(tree *raiz, int siz = 0)
// {
//     if (raiz == NULL)
//     {
//         return siz;
//     }

//     siz += 1;
//     int aux = sizeof_tree(raiz->left, siz);
//     int aux_2 = sizeof_tree(raiz->right, siz);

//     if (aux > aux_2)
//     {
//         return aux;
//     }
//     else
//     {
//         return aux_2;
//     }

//     // return 1 + fmax(altura(node->esq), altura(node->dir));
//     return siz;
// }

void imprimir_fb(tree *node, int tab = 0) {
  if (node == NULL) return;

  imprimir_fb(node->right, tab + 1);
  for (int i = 0; i < tab; i++) {
    printf("\t");
  }
  printf("%d\n", sizeof_tree(node->left) - sizeof_tree(node->right));
  imprimir_fb(node->left, tab + 1);
}


void troca(tree **raiz, tree *no_1, tree *no_2){

    if(no_1 == NULL and no_2 == NULL and no_1 == no_2 ){
        return ;
    }

    tree *antecessor_no_1;
    antecessor_no_1 = busca_antecessor(*raiz, no_1);
    
    tree *antecessor_no_2 ;
    antecessor_no_2 = busca_antecessor(*raiz, no_2);

    if(antecessor_no_1 == antecessor_no_2){
        

        tree *left_no1 = no_1->left;
        tree *right_no1 = no_1->right;
        

        no_1->left = no_2->left;
        no_1->right = no_2->right;
        

        no_2->left = left_no1;
        no_2->right = right_no1;
        
        tree *troc = antecessor_no_2->left;
        antecessor_no_1->left = antecessor_no_1->right;
        antecessor_no_1->right = troc;
        return;
    }
    else if(antecessor_no_1 == no_2){
        if(no_2->left == no_1){
            tree *left_no_1 = no_1->left;
            tree *right_no_1 = no_1->right;

            no_1->left = no_2;
            no_1->right = no_2->right;

            no_2->left = left_no_1;
            no_2->right = right_no_1;
            
        }
        else if(no_2->right == no_1){
            tree *left_no1 = no_1->left;
            tree *right_no1 = no_1->right;

            no_1->right = no_2;
            no_1->left = no_2->left;

            no_2->left = left_no1;
            no_2->right = left_no1;

        }
        if(*raiz == no_2){
            *raiz = no_1;
        }
        else{
            if(antecessor_no_2->left == no_2){
                    antecessor_no_2->left = no_1;
            }else{
                antecessor_no_2->right = no_1;
            }
        }
    }
    else if(antecessor_no_2 == no_1){

        if(no_1->left == no_2){
            tree *left_no2 = no_2->left;
            tree *right_no2 = no_2->right;
            
            no_2->left = no_1;
            no_2->right = no_1->right;


            no_1->left = left_no2;
            no_1->right = right_no2;

        }
        if(no_1->right == no_2){
            tree *left_no2 = no_2->left;
            tree *right_no2 = no_2->right;
            
            no_2->right = no_1;
            no_2->left = no_1->left;


            no_1->left = left_no2;
            no_1->right = right_no2;
        }

        if(*raiz == no_1){
            *raiz = no_2;
        }else{
            if(antecessor_no_1->left == no_1){
                antecessor_no_1->left = no_2;
            }else{
                antecessor_no_1->right = no_2;
            }
        }
    }
    else{
        tree *left_no1 = no_1->left;
        tree *right_no1 = no_1->right;

        no_1->left = no_2->left;
        no_1->right = no_2->right;

        no_2->left = left_no1;
        no_2->right = right_no1;

        if(*raiz == no_1){
            *raiz = no_2;
            if(antecessor_no_2->left == no_2){
                antecessor_no_2->left = no_1;
            }else{
                antecessor_no_2->right = no_1;
            }
            return;
        }else{
            if(antecessor_no_1->left == no_1){
                antecessor_no_1->left = no_2;
            }else{
                antecessor_no_1->right = no_2;
            }
        }
        
        if(*raiz == no_2){
            *raiz = no_1;
        }else{
            if(antecessor_no_2->left == no_2){
                antecessor_no_2->left = no_1;
            }else{
                antecessor_no_2->right = no_1;
            }
        }
    }

}


bool menu(tree **raiz){
    int op = 0;
    printf("\n\t\t0 - SAIR\n\t\t1 - GERAR Arvore binaria de busca contendo numeros inteiros\n\t\t2 - Imprimir o maior, o menor e a media dos elementos\n\t\t3 - Receber um determinado no e retornar sua altura\n\t\t4 - Realizar a troca entre dois nos da arvore\n\t\t5 - Imprimir Arv\n\t\t6 - Imprimir FB\n\t\t>>> ");
    scanf("%d", &op);
    
    switch (op)
    {
        case 0:{
            printf("\n\t\tFinalizando!!!");
            return false;
        }
        case 1:{
            int adic = 0;
            printf("\n\t\tDigite a quantidade de números que deseja gerar: ");
            scanf("%d", &adic);
            tam = tam + adic;
            preencher_tree(raiz, adic);
            imprimir(*raiz);
            return true;
        }
        case 2:{
            if(tam == 0){
                printf("\n\t\tAdicione elemento!");
                return true;
            }
            int large = larger(*raiz);
            printf("\n\t\tO maior é %d", large);
            
            int le = less(*raiz);
            printf("\n\t\tO menor é %d", le);

            float media = son(*raiz)/tam;

            printf("\n\t\tMedia %f", media);
            return true;
        }
        case 3:{
            if(tam == 0){
                printf("\n\t\tAdicione elemento!");
                return true;
            }
            int numero_raiz = 0;
            printf("\n\t\tDigite o numero do no\n\t\t>>> ");
            scanf("%d", &numero_raiz);
            tree *no = search_all(*raiz, numero_raiz);
            int tam = sizeof_tree(no);
            printf("\n\t\tTamanho do no é %d", tam);
            return true;
        }
        case 4:{
            if(tam < 2){
                printf("\n\t\tAdicione Mais elementoS!");
                return true;
            }
            tree *no_1 = NULL;
            tree *no_2 = NULL;
            int numero_raiz = 0;

            while(true){
                printf("\n\t\tDigite o numero do Primeiro No\n\t\t>>> ");
                scanf("%d", &numero_raiz);
                no_1 = search_all(*raiz, numero_raiz);
                if(no_1 != NULL){
                    break;
                }else{
                    printf("\n\t\tNo não Encontrado\n\t\tNumero do Primeiro No Incorreto");
                }
            }
            while(true){
                printf("\n\t\tDigite o numero do Segundo No\n\t\t>>> ");
                scanf("%d", &numero_raiz);
                no_2 = search_all(*raiz, numero_raiz);
                if(no_2 != NULL){
                    break;
                }else{
                    printf("\n\t\tNo não Encontrado\n\t\tNumero do Segundo No Incorreto");
                }
            }
            troca(raiz, no_1, no_2);
            printf("\n\t\tTroca Realizada!!!");

            return true;
        }
        case 5:{
            imprimir(*raiz);
            return true;
        }
        case 6:{
            imprimir_fb(*raiz);
            return true;
        }
        case 7:{
            printf("\n-=-=-=-=\n");
            imprimir(*raiz);
            balanca(raiz, *raiz);
            printf("\n-=-=-=-=\n");
            imprimir(*raiz);
            printf("\n-=-=-=-=\n");

            return true;
        }
        default:{
            printf("\n\t\tIncorreto");
            return true;
        }
    }
    
}



int main()
{
    
    srand((unsigned)time(NULL));
    tree *raiz = NULL;

    bool verif = true;
    while (verif == true){
        verif = menu(&raiz);
    }

}