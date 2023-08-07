#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int tam = 0;

enum Cor
{
    VERMELHO = 1,
    PRETO = 0
};

typedef struct node
{
    int num = 0;
    Cor cor = VERMELHO;
    struct node *left = NULL;
    struct node *right = NULL;
    struct node *father = NULL;
} No;

No *crie(int num)
{
    No *NEW = new No;
    NEW->num = num;
    return NEW;
}

void inserir(No **raiz, No *NEW, No *anter = NULL)
{
    if (*raiz == NULL)
    {
        NEW->father = anter;
        *raiz = NEW;
        return;
    }

    if ((*raiz)->num > NEW->num)
    {
        inserir(&(*raiz)->left, NEW, *raiz);
    }
    else
    {
        inserir(&(*raiz)->right, NEW, *raiz);
    }
}

No *busca(No *no, int num)
{
    if (no == NULL){
        return NULL;
    }

    if (no->num == num){
        return no;
    }
    No *find = NULL;
    find = busca(no->left, num);
    if(find != NULL){
        return find;
    }
    find = busca(no->right, num);
    return find;
}

No *LARGER_LEFT(No *no)
{
    if (no == NULL)
        return NULL;

    if (no->right == NULL){
        return no;
    }

    no = LARGER_LEFT(no->right);
    return no;
}

No *LARGER_RIGHT(No *no)
{
    if (no == NULL)
        return NULL;

    if (no->left == NULL){
        return no;
    }

    no = LARGER_RIGHT(no->left);
    return no;
}

int sizeof_No(No *node)
{
    if (node == NULL)
    {
        return 1;
    }
    int cont = 0;
    if (node->cor == PRETO)
        cont++;

    cont += fmax(sizeof_No(node->left), sizeof_No(node->right));

    return cont;
}

void imprimir(No *node, int tab = 0)
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
    printf(" |%d ", node->num );
    if(node->cor == VERMELHO){
        printf("_V|\n");
    }else{
        printf("_P|\n");

    }

    imprimir(node->left, tab + 1);
}

void Rot_simples_Dir(No **raiz, No *no)
{
    if (no == NULL and *raiz == NULL)
    {
        return;
    }

    No *novo_head = no->left;
    if (novo_head == NULL){
        return;
    }


    novo_head->father = no->father;
    no->father = novo_head;

    no->left = novo_head->right;
    if (no->left != NULL){

        no->left->father = no;
    }

    novo_head->right = no;

    if (no == *raiz and novo_head->father == NULL)
    {
        *raiz = novo_head;
        novo_head->cor = PRETO;
        return;
    }
    else
    {

        if (novo_head->father->left == no)
        {
            novo_head->father->left = novo_head;
        }
        else if (novo_head->father->right == no)
        {
            novo_head->father->right = novo_head;
        }
    }
}

void Rot_simples_Esq(No **raiz, No *no)
{
    if (no == NULL and *raiz == NULL)
    {
        return;
    }

    No *novo_head = no->right;
    if (novo_head == NULL){
        return;
    }

    novo_head->father = no->father;

    no->father = novo_head;

    no->right = novo_head->left;

    if (no->right != NULL){

        no->right->father = no;
    }

    novo_head->left = no;

    if (no == *raiz and novo_head->father == NULL)
    {

        *raiz = novo_head;
        novo_head->cor = PRETO;
        return;
    }
    else
    {

        if (novo_head->father->left == no)
        {
            novo_head->father->left = novo_head;
        }
        else if (novo_head->father->right == no)
        {
            novo_head->father->right = novo_head;
        }
    } // 7 2 14 1 13 15  ->7
}

void Rot_Dupla_Dir(No **raiz, No *no, No *avo)
{
    if (no == NULL and avo == NULL and *raiz == NULL){
        return;
    }

    Rot_simples_Esq(raiz, no->father);
    Rot_simples_Dir(raiz, avo);
    avo->cor = VERMELHO;
    no->cor = PRETO;
}

void Rot_Dupla_Esq(No **raiz, No *no, No *avo)
{
    if (no == NULL and avo == NULL and *raiz == NULL){
        return;
    }

    Rot_simples_Dir(raiz, no->father);
    Rot_simples_Esq(raiz, avo);
    avo->cor = VERMELHO;
    no->cor = PRETO;
}

/////////////////////////
No *find_brother(No *ele){
    if(ele == NULL){
        return NULL;
    }

    if(ele->father != NULL){
        if(ele->father->left == ele){
            return ele->father->right;
        }
        else if(ele->father->right == ele){
            return ele->father->left;
        }
    }

    return NULL;
}

void colorir(No *avo)
{
    if (avo == NULL)
    {
        return;
    }
    if (avo->father != NULL){
        avo->cor = VERMELHO;
    }
    if (avo->left != NULL){
        avo->left->cor = PRETO;
    }
    if (avo->right != NULL){
        avo->right->cor = PRETO;
    }
}

bool pai_preto(No *no)
{
    if (no == NULL)
    {
        return true;
    }
    if(no->father != NULL){
        if (no->father->cor == PRETO)
        {
            return true;
        }
    }

    return false;
}

bool pai_and_tio_RED(No *no)
{
    if (no == NULL)
    {
        return false;
    }
    if (no->left == NULL or no->right == NULL){
        return false;
    }
    if (no->left->cor == VERMELHO and no->right->cor == VERMELHO){
        return true;
    }
    return false;
}

bool pai_RED_and_tio_PRETO(No *avo, No *no_add)
{
    if (avo == NULL)
    {
        return false;
    }
   //***********************
    if (avo->left == NULL and avo->right == NULL){
        return false;
    }

    if (no_add->father->cor != VERMELHO){
        return false;
    }
    No *tio = NULL;

    if (no_add->father == avo->left)
    {
        tio = avo->right;
    }
    else
    {
        tio = avo->left;
    }

    if (tio == NULL){
        return true;
    }
    else if (tio->cor == PRETO){
        return true;
    }

    return false;
}

void balancemento_sofredor(No **raiz, No *no)
{
    if (no == NULL)
    {
        return;
    }

    if (no->father == NULL)
    {
        no->cor = PRETO;
        return;
    }

    if (pai_preto(no))
    {
        return;
    }
    No *avo = no->father->father;
    if (pai_and_tio_RED(avo))
    {
        colorir(avo);
        return;
    }

    if (pai_RED_and_tio_PRETO(avo, no))
    {

        if (avo->left == no->father and no->father->left == no)
        {
            Rot_simples_Dir(raiz, avo);
            avo->father->cor = PRETO;
            avo->cor = VERMELHO;
            return;
        }
        if (avo->right == no->father and no->father->right == no)
        {
            Rot_simples_Esq(raiz, avo);
            avo->father->cor = PRETO;
            avo->cor = VERMELHO;
            return;
        }
        if (avo->left == no->father and no->father->right == no)
        {
            Rot_Dupla_Dir(raiz, no, avo);
            return;
        }
        if (avo->right == no->father and no->father->left == no)
        {

            Rot_Dupla_Esq(raiz, no, avo);
            return;
        }
        return;
    }
}

///////////////////////
void associacao(No **raiz, No *subst, No *ele_remover){
	if(subst == NULL and ele_remover == NULL){
		return;
	}else if (subst == ele_remover)
    {
        return;
    }


	subst->father = ele_remover->father;
	subst->right = ele_remover->right;
    if(subst->right != NULL){
        subst->right->father = subst;
    }
	subst->left = ele_remover->left;
    if(subst->left != NULL){
        subst->left->father = subst;
    }
	subst->cor = ele_remover->cor;

	if(ele_remover->father == NULL){

		*raiz = subst;
	}
	else{
		No *pai = ele_remover->father;

		if(pai->left == ele_remover){
			pai->left = subst;
		}
		else if(pai->right == ele_remover){
			pai->right  = subst;
		}
	}
}

void remover_ele(No **raiz, No *subst){
	if(subst == NULL){
		return ;
	}
	No *pai = subst->father;

	if(pai == NULL){
		*raiz = NULL;
	}
    //Se ele está na direita ou esquerda IMPORTA!!
	else if(pai->left == subst){

		if(subst->right != NULL){
			pai->left = subst->right;
		}else if(subst->left != NULL){
            pai->left = subst->left;
        }else{
            pai->left = NULL;
        }

		if(pai->left != NULL){
			pai->left->father = pai;
		}

	}else if(pai->right == subst){
		if(subst->left != NULL){
			pai->right = subst->left;
        }else if(subst->right != NULL){
            pai->right = subst->right;
        }
        else{
            pai->right = NULL;
        }

		if(pai->right != NULL){
			pai->right->father = pai;
		}
	}

	subst->father = NULL;
	subst->right = NULL;
	subst->left = NULL;
}

bool elemento_ROOT_sem_left_or_right(No **raiz, No *elem){
    if(elem == NULL){
        return false;
    }

    No *father_ele = elem->father;

    if(father_ele == NULL and *raiz == elem){
        *raiz = NULL;
        return true;
    }
    return false;
};

bool ele_remov_RED(No **raiz, No *subst){
    if(subst == NULL){
        return false;
    }
    if(subst->cor == VERMELHO){
        remover_ele(raiz, subst);
        return true;
    }

    return false;
}

bool brother_black_sem_filho(No **raiz, No *subst, bool left_or_right = false ){
    
    if(subst == NULL){
        return false;
    }
    No *brother = find_brother(subst);
    if(brother == NULL){

        if(subst->father != NULL){
            subst->father->cor = PRETO;
            remover_ele(raiz, subst);
            return true;
        }else{
            printf("\nExc3eptions");
        }
    }
    else{
        if(brother->left == NULL and brother->right == NULL ){

            if(subst->father != NULL){
                subst->father->cor = PRETO;
            }else{
                printf("\nE2xeption");
            }

            brother->cor = VERMELHO;
            remover_ele(raiz, subst);
            return true;

        }else if((brother->left == NULL and brother->right != NULL ) or (brother->left != NULL and brother->right == NULL)){
            
            if((left_or_right == false and brother->right->cor == VERMELHO ) or (left_or_right == true and brother->left->cor == VERMELHO)){
                
                
                if(subst->father != NULL){
                    subst->father->cor = PRETO;
                }else{
                    printf("\nE2xeption5");
                }

                brother->cor = VERMELHO;
                remover_ele(raiz, subst);
                return true;
            }
        }
    }

    return false;
}

bool brother_black_with_1_filho_RED(No **raiz, No *subst, bool left_or_right = false){

    /*Falso para verificar no lado esq do brother, o elemento(subst) é o maior à esquerda
    Verdadeiro para verificar lado direito, porém esse caso é para caso o elemento(subst) for o menor à direita
    */

    if(subst == NULL){
        return false;
    }
    No *brother = find_brother(subst);
    if(brother != NULL){
        if(left_or_right == false and brother->left != NULL){
            if(brother->left->cor == VERMELHO){
                remover_ele(raiz, subst);
                //////////////ISSO AQUI
                if(brother->father->cor == PRETO){
                    brother->left->cor = PRETO;
                }else{
                    brother->left->cor = VERMELHO;
                }

                Rot_simples_Dir(raiz, brother->father);
                return true;
            }
        }
        else if(left_or_right == true and brother->right != NULL){
            if(brother->right->cor == VERMELHO){
                remover_ele(raiz, subst);
                //////////////ISSO AQUI
                if(brother->father->cor == PRETO){
                    brother->right->cor = PRETO;
                }else{
                    brother->right->cor = VERMELHO;
                }
                
                Rot_simples_Esq(raiz, brother->father);
                return true;
            }
        }
    }
    return false;
}

bool brother_RED(No **raiz, No *subst, bool left_or_right = false){
    if(subst == NULL){
        return false;
    }
    No *brother = find_brother(subst);
    if(left_or_right == false and brother->cor == VERMELHO){
        No *filho_esq = brother->right;

        Rot_simples_Dir(raiz, brother->father);
        remover_ele(raiz, subst);

        if(filho_esq != NULL){
            if(filho_esq->father->cor == PRETO){
                filho_esq->cor = VERMELHO;

            }
        }
        return true;
    }
    else if(left_or_right == true and brother->cor == VERMELHO){

        No *filho_esq = brother->left;

        Rot_simples_Esq(raiz, brother->father);
        remover_ele(raiz, subst);

        if(filho_esq != NULL){
            if(filho_esq->father->cor == PRETO){
                filho_esq->cor = VERMELHO;
            }
        }
        return true;
    }
    return false;
}

// 25 10 28 30 ->25
void remocao(No **raiz, int num){
    if(*raiz == NULL){
        return;
    }
    No *remover = busca(*raiz, num);

    if(remover != NULL){
        bool left_or_right = false;
        No *substituto_esq = LARGER_LEFT(remover->left);

        if(substituto_esq == remover->left){
            left_or_right = true;
        }

        if(substituto_esq == NULL){
            substituto_esq = LARGER_RIGHT(remover->right);
            left_or_right = true;
        }

        // o maior da esquerda é o ele da esquerda do elemento a ser removido
        if(substituto_esq == remover->right){
                left_or_right = false;
        }

        if(substituto_esq == NULL){
            if(elemento_ROOT_sem_left_or_right(raiz, remover) == true){
                return;
            }else{
                // nao existe subst pra esse nó, logo vamos verificar ele proprio, por isso a existencia da variavel booleana
                substituto_esq = remover;
                if(remover->father->right == remover){
                    left_or_right = false;
                }else{
                    left_or_right = true;
                }

            }
        }


        if(substituto_esq != NULL){

            if(ele_remov_RED(raiz, substituto_esq) == true){
                printf("\n\tElemento a ser removido é VERMELHO");
                associacao(raiz, substituto_esq, remover);
                return;
            }
            else if(substituto_esq->cor == PRETO){
                printf("\n\tElemento a ser removido é PRETO\n");

                if(brother_black_sem_filho(raiz, substituto_esq, left_or_right) == true){
                    printf("\n\tIrmao preto sem filho");
                    associacao(raiz, substituto_esq, remover);
                    return;
                }


                if(brother_black_with_1_filho_RED(raiz, substituto_esq, left_or_right) == true){
                    printf("\n\tIrmao preto com 1 filho RED");
                    associacao(raiz, substituto_esq, remover);
                    return;
                }

                if(brother_RED(raiz, substituto_esq, left_or_right) == true){
                    printf("\n\tIrmao VermelhoO");
                    associacao(raiz, substituto_esq, remover);
                    return;
                }
                else{
                    printf("\n\tExceptions");
                }
            }
        }
    }else{
        printf("\n\tElement no find !!");
    }
}

//////////////////////////////////////
void verificacao(No **node, No *no){
    if(no == NULL){
        return;
    }
    if(no->cor == VERMELHO){
        balancemento_sofredor(node, no);
    }

    verificacao(node, no->left);
    verificacao(node, no->right);
}

bool menu(No **root);

int main()
{

    No *raiz = NULL;

    bool verif = true;
    while (verif == true){
        verif = menu(&raiz);
    }

    return 0;
}


bool menu(No **root){
    int op = 0;
    printf("\n\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
    printf("\n\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
    printf("\n\t*|| 1 - Add Element            ||*");
    printf("\n\t*|| 2 - Remover Element        ||*");
    printf("\n\t*|| 3 - Print Tree Red-Black   ||*");
    printf("\n\t*|| 0 - Close                  ||*");
    printf("\n\t>>>> ");
    scanf("%d", &op);

    No *NEW = NULL;

    switch(op){

        case 0:{
            printf("\n\n\t..........................BYE");
            return false;
        }
        case 1:{
            printf("\n\tWrite value of the Element");
            printf("\n\t>>>> ");
            scanf("%d", &op);
            NEW = crie(op);
            inserir(root, NEW);
            balancemento_sofredor(root, NEW);
            verificacao(root, *root);
            system("cls");
            return true;
        }
        case 2:{
            printf("\n\tWrite value of the Element");
            printf("\n\t>>>> ");
            scanf("%d", &op);
            remocao(root, op);
            verificacao(root, *root);
            printf("\n\tFinished");
            system("cls");
            return true;
        }
        case 3:{
            printf("\n\n\t|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-|");
            printf("\n\t|=-=-=-         PRINT      =-=-=-|");
            printf("\n\t|*=*=*-*=*-*=*-*=*-*=*-*=*-*=*-*=|\n");
            imprimir(*root);
            printf("\n\t|*=*=*-*=*-*=*-*=*-*=*-*=*-*=*-*=|");
            printf("\n\t|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-|\n");
            return true;
        }
        default:{
            system("cls");
            return true;
        }

    }

    return false;
}
