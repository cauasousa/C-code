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

}Dice;

typedef struct Tree
{
    Dice dice;
    struct Tree *lift;
    struct Tree *right;
}no;

typedef struct
{
    no *root;
    int quantity_of_sale;
    float collection;
}tree;

void random_(int *value){
///////////////////////////////
    *value = rand() % 1000;
}

no *ins_dice()
{
    no *NEW = (no*)malloc(sizeof(no));

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

bool insert_tree(no **root, no *NEW)
{

    if (*root == NULL)
    {
        *root = NEW;
        return true;
    }

    else if (NEW->dice.locator < (*root)->dice.locator)
    {
        insert_tree(&(*root)->lift, NEW);
    }
    else
    {
        insert_tree(&(*root)->right, NEW);
    }
    return true;
}

// retorna falso se não achar ninguem igual
bool _test( no *aux, int l){
    if(aux == NULL){return false;}

    if (l == (aux)->dice.locator)
    {
        printf("\n*77Locator Error*");
        system("pause");
        return true;
    }    

    if(aux->dice.locator > l ){
        return _test(aux->lift, l);
    }else{
        return _test(aux->right, l);
    }
    return false;
}

void tree_ins_test(tree *root_N, no *novo)
{
        bool ver = false;
        while(ver != true){
            ver = insert_tree(&(root_N)->root, novo);
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

void report(tree *Brasil, tree *Argn)
{
    printf("\n\t*****REPORT BRAZIL*****");
    collecion_and_ticket_sales(Brasil);
    printf("\n\t*****REPORT ARGN******");
    collecion_and_ticket_sales(Argn);
    printf("\n\t*********************** ");
}

no *right_or_lift(no *aux, int n){

    if(aux != NULL){
        if(n == 1){
            while(aux->lift != NULL){
               aux = aux->lift;
            }
        }
        else if(n == 2){
            while(aux->right != NULL){
               aux = aux->right;
            }            
        }
        
    }
    return aux;
}

no *removen(tree *Dice_tree, no **root, int l){
    
    no *aux = NULL;
    if(*root == NULL){
        return NULL;
    }

    if((*root)->dice.locator == l){

        if((*root)->lift == NULL && (*root)->right == NULL){
            aux = *root;
            *root = NULL;
        }
        else if((*root)->lift != NULL && (*root)->right == NULL){
            aux = *root;
            *root = aux->lift;
            aux->lift = NULL;    
        }
        else if((*root)->lift == NULL && (*root)->right != NULL){
            aux = *root;
            *root = aux->right;
            aux->right = NULL; 
        }
        else if((*root)->lift != NULL && (*root)->right != NULL){
            no *half = right_or_lift((*root)->right, 1);

            if(half == NULL){
                half = right_or_lift((*root)->lift, 2);
            }
            if(half == NULL){
                aux = *root;
                *root = NULL;
            }else{
                half = removen(Dice_tree, &Dice_tree->root, half->dice.locator);
                aux = *root;
                half->lift = aux->lift;
                half->right = aux->right;
                *root = half;
                aux->lift = NULL;
                aux->right = NULL;
            }
        }
        return aux;         
    }

    if((*root)->dice.locator > l){
        aux = removen(Dice_tree, &(*root)->lift, l);
    }
    else{
        aux = removen(Dice_tree, &(*root)->right, l);
    }
    return aux;
}

void initializer_tree(tree *Brasil, tree *Argn, tree *B_dados)
{
    while (Brasil->root != NULL)
    {
        tree_ins_test(B_dados, removen(Brasil, &Brasil->root, Brasil->root->dice.locator));
    }
    while (Argn->root != NULL)
    {
        tree_ins_test(B_dados, removen(Argn, &Argn->root, Argn->root->dice.locator));
    }
}



void initialize(tree *aux){
    aux->root = NULL;
    aux->quantity_of_sale = 0;
    aux->collection= 0.0f;  
}
void print(no *aux, int tab);
void menu();
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

            while(true){
                bool B = _test(root_Brazil.root, AUX->dice.locator);
                bool A  = _test(root_Argentina.root, AUX->dice.locator);
                if(B == true || A == true){
                    printf("Opa");
                    random_(&AUX->dice.locator);
                    continue;
                }else{
                    break;
                }
            }
            tree_ins_test(&root_Brazil, AUX);
            printf("\n\t\tStored in the System ");
            break;
        }
        case 2:
        {
            AUX = ins_dice();


            while(true){
                bool B_ = _test(root_Brazil.root, AUX->dice.locator);
                bool A_  = _test(root_Argentina.root, AUX->dice.locator);
                if(B_ == true || A_ == true){
                    printf("Opa");
                    random_(&AUX->dice.locator);
                    continue;
                }else{
                    break;
                }
            }

            tree_ins_test(&root_Argentina, AUX);
            printf("\n\t\tStored in the System ");
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
            printf("\nArgentina-> ");
            print(root_Argentina.root, 0);
            printf("\nAcum-> ");
            print(root_Anos_Anterior.root, 0);
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

    print(aux->lift, tab+1);

    if(tab == 0){printf("| ");}
    printf("%d ", aux->dice.locator);
    if(tab == 0){printf("| ");}    
    print(aux->right, tab + 1);

};