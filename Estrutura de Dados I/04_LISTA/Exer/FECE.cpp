#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int incr = 0;

typedef struct Relacao
{
    char amigo[50];
    Relacao *proximo;
} relacao;

typedef struct Amigos
{
    char nome[50];
    int ident = 0;
    relacao *ptr_cabeca_relacao;
    Amigos *prox;

} chama;

void imprimir_relacao(relacao *cabeca)
{
    relacao *aux = cabeca;

    while (aux != NULL)
    {
        printf("--%s", aux->amigo);
        aux = aux->proximo;
    }
}

void imprimir(chama *cabeca)
{
    chama *aux = cabeca;

    while (aux != NULL)
    {
        printf("\n\n\tUsername: %s", aux->nome);
        printf("\tCpf: %d", aux->ident);
        printf("\n\tAmigos: ");

        // struct Relacao *aux_2 = aux->ptr_cabeca_relacao;
        if (aux->ptr_cabeca_relacao == NULL)
        {
            printf("Sem Lista de Amigos!");
        }
        else
        {
            imprimir_relacao(aux->ptr_cabeca_relacao);
        }
        aux = aux->prox;
    }

    // printf("\nNada");
}

relacao *aux_ins_lista(chama *ptr, chama *novo)
{

    // chama *aux = ptr;
    relacao *guarda = (relacao *)malloc(sizeof(relacao));

    strcpy(guarda->amigo, novo->nome);

    guarda->proximo = ptr->ptr_cabeca_relacao;
    ptr->ptr_cabeca_relacao = guarda;

    return guarda;
}

relacao *aux_ins_novo(chama *ptr, chama *novo)
{
    chama *aux = ptr;
    relacao *guarda_2 = (relacao *)malloc(sizeof(relacao));

    strcpy(guarda_2->amigo, aux->nome);

    guarda_2->proximo = novo->ptr_cabeca_relacao;
    novo->ptr_cabeca_relacao = guarda_2;

    return guarda_2;
}

void inserir(chama *ptr, chama *Novo)
{
    char NOME[50];
    printf("\n\t\t\tEscreva o nome do Amigo \n\t\t\tpara adcionar em sua lista de amigos: ");
    scanf(" %49[^\n]s", NOME);

    chama *aux = ptr;

    while (aux != NULL)
    {
        if (strcmp(aux->nome, NOME) == 0)
        {
            // printf("Achei!!");
            break;
        }
        aux = aux->prox;
    }
    if (aux == NULL)
    {
        printf("Usurname Not Found!");
        return;
    }
    aux->ptr_cabeca_relacao = aux_ins_lista(aux, Novo);
    Novo->ptr_cabeca_relacao = aux_ins_novo(aux, Novo);
    // aux_ins(aux, Novo);
};

chama *ins_usu(chama **ptr)
{
    // chama *lista_ptr = *ptr;
    chama *novo = (chama *)malloc(sizeof(chama));
    novo->ptr_cabeca_relacao = NULL;
    int nu = 1;

    printf("\n\t\tUsername: ");
    scanf(" %49[^\n]s", novo->nome);

    incr += 1;
    novo->ident = incr;

    printf("\n\t\tSeu identificador: %d", novo->ident);

    printf("\n\t\t\t1 - Para Adicionar 1 Amigo");
    printf("\n\t\t\t2 - Sair\n\t\t\t");
    scanf("%d", &nu);
    while (nu != 2)
    {
        inserir(*ptr, novo);

        printf("\n\t\t\t1 - Adicionar Mais Amigo");
        printf("\n\t\t\t2 - Sair\n\t\t");
        scanf("%d", &nu);
    }

    novo->prox = *ptr;
    *ptr = novo;

    // printf("\n\tSalvo 2!");

    return *ptr;
}

void menu()
{
    printf("\n\t\t\t1 - Adicionar Usuario");
    printf("\n\t\t\t2 - Imprimir");
    printf("\n\t\t\t3 - Relacionar amigos");

    // printf("\n\t\t\t3 - Imprindo diferente");
    printf("\n\t\t\t0 - Sair\n");
}

void relacionar(int ind_1, int ind_2, chama *cabeca)
{
    chama *aux = cabeca;
    chama *aux_2 = cabeca;

    while (aux != NULL)
    {
        if (aux->ident == ind_1)
        {
            printf("\n\t\tPessoa 1 Encontrado!\n\t\t");
            break;
        }
        aux = aux->prox;
    }
    if (aux == NULL)
    {
        printf("Pessoa 1 não encontrada!");
        return;
    }

    while (aux_2 != NULL)
    {
        if (aux_2->ident == ind_2)
        {
            break;
        }
        aux_2 = aux_2->prox;
    }
    if (aux_2 == NULL)
    {
        printf("Pessoa 2 não encontrada!");
        return;
    }

    aux_2->ptr_cabeca_relacao = aux_ins_lista(aux_2, aux);
    aux->ptr_cabeca_relacao = aux_ins_novo(aux_2, aux);
}

int main()
{
    //continue;
    //memset()


     printf("Opa");
    chama *head = NULL;
    // head->prox = NULL;
    // head->ptr_cabeca_relacao = NULL;
    printf("Opa");
    int num = 0;

    do
    {

        menu();
        scanf("%d", &num);
        switch (num)
        {
        case 1:
            head = ins_usu(&head);
            printf("%s", head->nome);
            // system("cls");
            break;
        case 2:
        {
            imprimir_relacao(head->ptr_cabeca_relacao);
            imprimir(head);
            printf("\nFIM");
            break;
        }
        case 3:
        {
            int nu_1 = 0, nu_2 = 0;
            printf("\n\t\tDigite o cpf da pessoa 1:");
            scanf("%d", &nu_1);

            printf("\n\t\tDigite o cpf da Pessoa 2: ");
            scanf("%d", &nu_2);

            relacionar(nu_1, nu_2, head);
            break;
        }
        case 0:
        {
            return 0;
        }
        default:
            break;
        }

    } while (num != 4);

    return 0;
}
