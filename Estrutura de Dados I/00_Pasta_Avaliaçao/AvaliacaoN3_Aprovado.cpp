#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// registrar o localizador, data, preço e destino de cada passagem.
typedef struct
{
    char destiny[100];
    float price;
    int day, month, year;
    int locator;

} Dice;

typedef struct Tree
{
    Dice dice;
    struct Tree *lift;
    struct Tree *right;
} no;

typedef struct
{
    no *root;
    int quantity_of_sale;
    float collection;
} tree;

void random_(int *value)
{
    *value = rand() % 100;
}

no *ins_dice()
{
    no *NEW = (no *)malloc(sizeof(no));

    printf("\nDestiny: ");
    scanf(" %s", NEW->dice.destiny);
    printf("\nDay: ");
    scanf("%d", &NEW->dice.day);
    printf("\nMonth: ");
    scanf("%d", &NEW->dice.month);
    printf("\nYear: ");
    scanf("%d", &NEW->dice.year);
    printf("\nPrice: ");
    scanf("%f", &NEW->dice.price);
    random_(&NEW->dice.locator);
    printf("\nLocator: %d\n", NEW->dice.locator);
    NEW->lift = NULL;
    NEW->right = NULL;

    return NEW;
}

// coloca o elemento dentro da árvore retornando false
bool insert_tree(no **root, no *NEW)
{
    if (*root == NULL)
    {
        *root = NEW;
        return false;
    }
//                6
//          5
//                4
//  1
//                0
//          -1
//               -2
//
    else if (NEW->dice.locator < (*root)->dice.locator)
    {
        insert_tree(&(*root)->lift, NEW);
    }
    else
    {
        insert_tree(&(*root)->right, NEW);
    }
    return false;
}

// retorna falso se não achar ninguem igual
bool _test(no *aux, int l)
{
    if (aux == NULL)
    {
        return false;
    }

    if (l == (aux)->dice.locator)
    {
        return true;
    }

    if (aux->dice.locator > l)
    {
        return (_test(aux->lift, l));
    }
    else
    {
        return (_test(aux->right, l));
    }
    return false;
}
// metodo de fato inserindo
void tree_ins_test(tree *root_N, no *novo)
{
    bool ver = false;
    // vai retornar falso se nao houver repetido
    ver = _test(root_N->root, novo->dice.locator);

    // verificando se existe algum número aleatorio, se caso existir ele é alterado
    while (ver != false)
    {
        random_(&novo->dice.locator);
        ver = _test(root_N->root, novo->dice.locator);
    }
    // vai retornar false se for colocado na arvore
    ver = insert_tree(&(root_N)->root, novo);

    if (ver == true)
    {
        printf("\nErro");
         return;
    }

    root_N->collection = root_N->collection + novo->dice.price;
    root_N->quantity_of_sale = root_N->quantity_of_sale + 1;
}

void search_tick(no *aux, char *desti)
{
    if (aux == NULL)
    {
        return;
    }

    search_tick(aux->lift, desti);
    if (strcmp(aux->dice.destiny, desti) == 0)
    {
        printf("**(%s | Date: %d/%d/%d | COD: %d)\n", aux->dice.destiny, aux->dice.day, aux->dice.month, aux->dice.year, aux->dice.locator);
    }
    search_tick(aux->right, desti);
};

void Search_Test(no *root_B, no *root_A)
{
    if (root_B != NULL || root_A != NULL)
    {
        char Dest[50];
        printf("Qual o Destino: ");
        scanf(" %[^\n]s", Dest);

        printf("\n************Brasil - %s************\n", Dest);
        if (root_B != NULL)
        {
            search_tick(root_B, Dest);
        }
        printf("\n************Argentina - %s************\n", Dest);
        if (root_A != NULL)
        {
            search_tick(root_A, Dest);
        }
    }
    else
    {
        printf("\n\tNo Ticket Sales ");
    }
}

void collecion_and_ticket_sales(tree *root_N)
{
    printf("\n\tQuantity of Sale - %d ", root_N->quantity_of_sale);
    printf("\n\tCollection - %0.2f", root_N->collection);
}
// relatorio
void report(tree *Brasil, tree *Argn)
{
    printf("\n\t*****REPORT BRAZIL*****");
    collecion_and_ticket_sales(Brasil);
    printf("\n\t*****REPORT ARGN******");
    collecion_and_ticket_sales(Argn);
    printf("\n\t*********************** ");
}

// vai entrar na arvore e se for 1, vai da direita pra mais esquerda q tiver. caso seja 2 vai pra esquerda e ir pra mais direita
no *right_or_lift(no *aux, int n)
{

    if (aux != NULL)
    {
        if (n == 1)
        {
            while (aux->lift != NULL)
            {
                aux = aux->lift;
            }
        }
        else if (n == 2)
        {
            while (aux->right != NULL)
            {
                aux = aux->right;
            }
        }
    }
    return aux;
}

no *removen(no **root, int l)
{

    no *aux = NULL;
    
    if (*root == NULL)
    {
        return NULL;
    }

    if ((*root)->dice.locator == l)
    {

        if ((*root)->lift == NULL && (*root)->right == NULL)
        {
            aux = *root;
            *root = NULL;
        }
        else if ((*root)->lift != NULL && (*root)->right == NULL)
        {
            aux = *root;
            *root = aux->lift;
            aux->lift = NULL;
        }
        else if ((*root)->lift == NULL && (*root)->right != NULL)
        {
            aux = *root;
            *root = aux->right;
            aux->right = NULL;
        }
        else if ((*root)->lift != NULL && (*root)->right != NULL)
        {
            // busca na sub arvore direita o mais esquerda q tiver
            no *half = right_or_lift((*root)->right, 1);
            removen(&(*root)->right, half->dice.locator);

            aux = *root;

            half->lift = aux->lift;
            half->right = aux->right;

            *root = half;

            aux->lift = NULL;
            aux->right = NULL;
        }
        return aux;
    }

    if ((*root)->dice.locator > l)
    {

        aux = removen(&(*root)->lift, l);
    }
    else
    {

        aux = removen(&(*root)->right, l);
    }
    return aux;
}

void initializer_tree(tree *Brasil, tree *Argn, tree *B_dados)
{
    while (Brasil->root != NULL)
    {
        tree_ins_test(B_dados, removen(&Brasil->root, Brasil->root->dice.locator));
    }
    while (Argn->root != NULL)
    {
        tree_ins_test(B_dados, removen(&Argn->root, Argn->root->dice.locator));
    }
}

void initialize(tree *aux){
    aux->root = NULL;
    aux->quantity_of_sale = 0;
    aux->collection = 0.0f;
}

void print(no *aux, int tab);
void menu();
void imprimir(no *node, int tab = 0);

int main()
{
    srand(time(NULL));

    tree root_Brazil;
    initialize(&root_Brazil);

    tree root_Argentina;
    initialize(&root_Argentina);

    tree root_Anos_Anterior;
    initialize(&root_Anos_Anterior);

    no *AUX = NULL;

    int op = 0;
    while (true)
    {
        printf("\n");
        system("pause");
        system("cls");
        menu();
        scanf("%d", &op);

        switch (op)
        {
        case 1:
        {
            AUX = ins_dice();

            while (true)
            {
                bool B = _test(root_Brazil.root, AUX->dice.locator);
                bool A = _test(root_Argentina.root, AUX->dice.locator);
                bool C = _test(root_Anos_Anterior.root, AUX->dice.locator);
                if (B == true || A == true || C == true)
                {
                    printf(" '_' ");
                    random_(&AUX->dice.locator);
                    continue;
                }
                else
                {
                    break;
                }
            }
            tree_ins_test(&root_Brazil, AUX);
            printf("\n\tStored in the System ");
            break;
        }
        case 2:
        {
            AUX = ins_dice();

            while (true)
            {
                bool B_ = _test(root_Brazil.root, AUX->dice.locator);
                bool A_ = _test(root_Argentina.root, AUX->dice.locator);
                bool C_ = _test(root_Anos_Anterior.root, AUX->dice.locator);
                if (B_ == true || A_ == true || C_ == true )
                {
                    printf(" *** ");
                    random_(&AUX->dice.locator);
                    continue;
                }
                else
                {
                    break;
                }
            }

            tree_ins_test(&root_Argentina, AUX);
            printf("\n\tStored in the System ");
            break;
        }
        case 3:
        {
            Search_Test(root_Brazil.root, root_Argentina.root);
            break;
        }
        case 4:
        {
            report(&root_Brazil, &root_Argentina);
            break;
        }
        case 5:
        {
            initializer_tree(&root_Brazil, &root_Argentina, &root_Anos_Anterior);
            initialize(&root_Brazil);
            initialize(&root_Argentina);
            break;
        }
        case 6:
        {
            // printf as tree
            printf("\nBrasil-> ");
            print(root_Brazil.root, 0);
            printf("\n");
            imprimir(root_Brazil.root);
            printf("\nArgentina-> ");
            print(root_Argentina.root, 0);
            printf("\n");
            imprimir(root_Argentina.root);
            printf("\nAcum-> ");
            print(root_Anos_Anterior.root, 0);
            printf("\n");
            imprimir(root_Anos_Anterior.root);
            printf("\n-----------");
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

void menu()
{
    printf("\n*****************************************");
    printf("\n*****************************************");
    printf("\n\t0 - Shutdown System\n\t1 - Sell Ticket in Brazil\n\t2 - Sell Ticket in Argentina");
    printf("\n\t3 - Search by Destination\n\t4 - Report\n\t5 - Initialize Cycle\n\t");
    printf("\n*****************************************");
    printf("\n*****************************************\n");
}
void print(no *aux, int tab)
{
    if (aux == NULL)
    {
        return;
    }

    print(aux->lift, tab + 1);

    if (tab == 0)
    {
        printf("| ");
    }
    printf("%d ", aux->dice.locator);
    if (tab == 0)
    {
        printf("| ");
    }
    print(aux->right, tab + 1);
};

void imprimir(no *node, int tab = 0)
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
    printf(" %d \n ", node->dice.locator);
    imprimir(node->lift, tab + 1);
}