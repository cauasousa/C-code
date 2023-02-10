#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int COD = 0;
bool alternating_1_B = false;
bool alternating_2_Ar = false;

// registrar o localizador, data, preço e destino de cada passagem.
typedef struct nada
{   
    int dia, mes, ano;
} Data;

typedef struct 
{
   char destino[100];
    Data data;
    float preco;
    int localizador;
} Dados;

typedef struct tree
{
    Dados dados;
    struct tree *esq;
    struct tree *dir;
} no;

typedef struct
{
    no *root;
    int qnt_venda;
    float arre;
} node;

no *ins_dado(bool *alternating)
{
    no *novo = (no *)malloc(sizeof(no));
    printf("\nDestino: ");
    scanf(" %s", novo->dados.destino);
    printf("\nDia: ");
    scanf("%d", &novo->dados.data.dia);
    printf("\nMes: ");
    scanf("%d", &novo->dados.data.mes);
    printf("\nAno: ");
    scanf("%d", &novo->dados.data.ano);
    printf("\nPreco: ");
    scanf("%f", &novo->dados.preco);

    if ((*alternating) == 1)
    {
        // COD + 1
        // 5 + 1 = 6
        // 0 -> 1
        // 1 -> 2
        // 2 -> 3
        novo->dados.localizador = COD + 1;
        COD += 1;
        (*alternating) = false;
    }
    else
    {
        //(( 1 - COD) - COD) - COD
        //((  -4 ) - 5) - 5 = -6
        // 0 ->  -1
        // 1 -> -2
        // 2 -> -3
        novo->dados.localizador = (-(1 - COD) - COD) - COD;
        COD += 1;
        (*alternating) = true;
    }
    printf("\nLocalizador %d\n", novo->dados.localizador);
    // scanf(" ");
    novo->dir = NULL;
    novo->esq = NULL;
    return novo;
}

void insert_tree(no **root, no *novo)
{

    if (*root == NULL)
    {
        *root = novo;
        return;
    }

    if (novo->dados.localizador == (*root)->dados.localizador)
    {
        printf("\n*Locator Error*");
        return;
    }
    else if (novo->dados.localizador < (*root)->dados.localizador)
    {
        insert_tree(&(*root)->esq, novo);
    }
    else
    {
        insert_tree(&(*root)->dir, novo);
    }
}

void tree_ins_test(node *root_N1, node *root_N2)
{
    int pais = 0;
    printf("Qual Pais da Venda da Passagem");
    printf("\n\t\t1 - Brazil\n\t\t2 - Argentina\n\t\t");
    scanf("%d", &pais);
    if (pais == 1)
    {
        no *novo = ins_dado(&alternating_1_B);
        insert_tree(&(root_N1)->root, novo);
        root_N1->arre = root_N1->arre + novo->dados.preco;
        root_N1->qnt_venda = root_N1->qnt_venda + 1;
    }
    else if (pais == 2)
    {
        no *nova = ins_dado(&alternating_2_Ar);
        insert_tree(&(root_N2)->root, nova);
        root_N2->arre = root_N2->arre + nova->dados.preco;
        root_N2->qnt_venda = root_N2->qnt_venda + 1;
    }
    else
    {
        printf("Pais Invalido");
    }
}

void search_tick(no *aux, char *nome, int tab)
{
    if (aux == NULL)
    {
        return;
    }
    search_tick(aux->esq, nome, tab);
    if (strcmp(aux->dados.destino, nome) == 0)
    {
        for (int i = 0; i < tab; i++)
        {
            printf("\t");
        }
        printf("**(%s | Data: %d/%d/%d | COD: %d)\n", aux->dados.destino, aux->dados.data.dia, aux->dados.data.mes, aux->dados.data.ano, aux->dados.localizador);
        tab += 1;
    }
    search_tick(aux->dir, nome, tab);
};

void Search_Test(no *root_B, no *root_A)
{
    if (root_B != NULL || root_A != NULL)
    {
        char Dest[50];
        printf("Qual o Destino: ");
        scanf(" %[^\n]s", Dest);
        printf("\n************Brasil************\n");
        if (root_B != NULL)
        {
            search_tick(root_B, Dest, 0);
        }
        printf("\n************Argentina************\n");
        if (root_A != NULL)
        {
            search_tick(root_A, Dest, 0);
        }
    }
    else
    {
        printf("*");
    }
}

void arre_venda(node *root_N)
{
    printf("\nQuant de Voo - %d ", root_N->qnt_venda);
    printf("\nArrecadacao - %0.2f", root_N->arre);
}

void report(node *Brasil, node *Argn)
{
    printf("\n*****REPORT BRAZIL*****");
    arre_venda(Brasil);
    printf("\n*****REPORT ARGN******");
    arre_venda(Argn);
    printf("\n*******");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
no *right_left(no **tree)
{
    no *aux = NULL;
    while (tree != NULL)
    {
        aux = *tree;
        tree = &(*tree)->esq;
    }
    return aux;
}

no *busca_prof(no **root_)
{

    if (*root_ != NULL)
    {

        no *aux = NULL;

        while ((*root_)->esq != NULL)
        {
            root_ = &(*root_)->esq;
        }
        aux = *root_;

        if ((*root_)->dir != NULL)
        {
            *root_ = (*root_)->dir;
            aux->dir = NULL;
            printf("\nB ");
            return aux;
        }
        printf("\nC ");

        *root_ = NULL;
        return aux;
    }
    return NULL;
}
void imprimir(no *aux, int tab);

no *remocao(node *Grd_Raiz, no **root_N, int l)
{

    if (*root_N == NULL)
    {
        // printf("P");
        return NULL;
    }
    if ((*root_N)->dados.localizador == l)
    {

        no *aux_ = NULL;
        no *aux_2 = NULL;

        if ((*root_N)->dir == NULL && (*root_N)->esq == NULL)
        {

            aux_ = *root_N;
            *root_N = NULL;
            // printf(" Ultimo ");
            return aux_;
        }
        if ((*root_N)->esq != NULL && (*root_N)->dir == NULL)
        {

            aux_ = *root_N;

            *root_N = (*root_N)->esq;

            aux_->esq = NULL;
        }
        if ((*root_N)->dir != NULL && (*root_N)->esq == NULL)
        {

            aux_ = *root_N;

            *root_N = (*root_N)->dir;

            aux_->dir = NULL;
        }
        if ((*root_N)->dir != NULL && (*root_N)->esq != NULL)
        {

            aux_2 = busca_prof(&Grd_Raiz->root->dir);

            if (aux_2 != NULL)
            {
                aux_2->esq = (*root_N)->esq;
                aux_2->dir = (*root_N)->dir;
                (*root_N)->esq = NULL;
                (*root_N)->dir = NULL;
            }
            aux_ = *root_N;
            *root_N = aux_2;
        }

        // insert_tree(&TREE_3->root, aux_);
        // printf(" G ");

        return aux_;
    }

    if ((*root_N)->dados.localizador > l)
    {

        //(*root_N)->esq = remocao(intocaval_caso_especifico, &(*root_N)->esq, l, TREE_3);
        remocao(Grd_Raiz, &(*root_N)->esq, l);
    }
    else
    {
        //(*root_N)->dir = remocao(intocaval_caso_especifico, &(*root_N)->dir, l, TREE_3);
        remocao(Grd_Raiz, &(*root_N)->dir, l);
    }
    // printf("F");
    return NULL;
}

void initializer_tree(node *Brasil, node *Argn, node *B_dados)
{
    while (Brasil->root != NULL)
    {
        // printf(" '-' ");
        insert_tree(&B_dados->root, remocao(Brasil, &Brasil->root, Brasil->root->dados.localizador));
        // printf("\n-----------------\n");
        // imprimir(B_dados->root, 0);
        // printf("\n-----------------\n");
    }
    while (Argn->root != NULL)
    {
        // printf(" :( ");
        insert_tree(&B_dados->root, remocao(Argn, &Argn->root, Argn->root->dados.localizador));
    }
}

void menu();
int main()
{
    node root_Brazil;
    root_Brazil.root = NULL;
    root_Brazil.qnt_venda = 0;
    root_Brazil.arre = 0.0f;

    node root_Argentina;
    root_Argentina.root = NULL;
    root_Argentina.arre = 0.0f;
    root_Argentina.qnt_venda = 0;

    node root_Anos_Anterior;
    root_Anos_Anterior.root = NULL;
    root_Anos_Anterior.arre = 0.0f;
    root_Anos_Anterior.qnt_venda = 0;

    int op = 0;
    while (true)
    {
        system("pause");
        system("cls");
        menu();
        scanf("%d", &op);

        switch (op)
        {
        case 1:
        {
            tree_ins_test(&root_Brazil, &root_Argentina);
            break;
        }
        case 2:
        {
            Search_Test(root_Brazil.root, root_Argentina.root);
            break;
        }
        case 3:
        {
            report(&root_Brazil, &root_Argentina);
            break;
        }
        case 4:
        {
            initializer_tree(&root_Brazil, &root_Argentina, &root_Anos_Anterior);

            root_Brazil.qnt_venda = 0;
            root_Brazil.arre = 0.0f;
            root_Argentina.arre = 0.0f;
            root_Argentina.qnt_venda = 0;

            break;
        }
        case 5:
        {
            // printf as tree
            printf("\n************");
            printf("\nBrasil\n");
            imprimir(root_Brazil.root, 0);
            printf("\nArgentina\n");
            imprimir(root_Argentina.root, 0);
            printf("\nAnterior\n");
            imprimir(root_Anos_Anterior.root, 0);
            printf("\n************");
            break;
        }
        default:
        {
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

void menu()
{
    printf("\n*****************************************");
    printf("\n*****************************************");
    printf("\n\t0 - Shutdown System\n\t1 - Sell Ticket");
    printf("\n\t2 - Search by Destination\n\t3 - Report\n\t4 - Initialize Cycle\n\t");
    printf("\n*****************************************");
    printf("\n*****************************************\n");
}
void imprimir(no *aux, int tab)
{
    if (aux == NULL)
    {
        return;
    }
    imprimir(aux->esq, tab + 1);

    for (int i = 0; i < tab; i++)
    {
        printf("\t");
    }
    printf("%d\n", aux->dados.localizador);
    imprimir(aux->dir, tab + 1);
};
