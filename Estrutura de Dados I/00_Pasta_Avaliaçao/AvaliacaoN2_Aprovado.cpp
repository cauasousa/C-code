#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// registrar o nome, cpf e nível para cada paciente,
typedef struct fala
{
    char nome[50];
    int cpf, nivel_de_atend;
    struct fala *prox;
} fila;

typedef struct
{
    fila *firts;
    fila *last;
    int relatorio;
} Fila;

Fila urgencia;
Fila emergencia;
Fila eletivo;

fila *ins()
{
    fila *nova = (fila *)malloc(sizeof(fila));
    printf("\nNome: ");
    scanf(" %50[^\n]s", nova->nome);
    printf("\nCPF: ");
    scanf("%d", &nova->cpf);
    printf("\n\t**************\n\t1 - Emergencia\n\t2 - Urgencia\n\t3 - Eletivo\n");
    scanf("%d", &nova->nivel_de_atend);
    nova->prox = NULL;
    return nova;
}

// Adicionar na fila escolhida, para não repetir o mesmo processo depois
void adicio_fila(Fila *fila_escol, fila *e)
{
    if (fila_escol->firts == NULL)
    {
        fila_escol->firts = e;
        fila_escol->last = e;
        return;
    }
    fila_escol->last->prox = e;
    fila_escol->last = fila_escol->last->prox;
}

// Adicionando na FIla, com auxilio da funcao de cima
void enfileirar(fila *e)
{
    if (e->nivel_de_atend == 1)
    {
        adicio_fila(&emergencia, e);
    }
    else if (e->nivel_de_atend == 2)
    {
        adicio_fila(&urgencia, e);
    }
    else if (e->nivel_de_atend == 3)
    {
        adicio_fila(&eletivo, e);
    }
    else
    {
        printf("Fila Incorreta!");
    }
}

// Usar a função para atender o paciente da vez, OBS: Irá auxiliar a proxima funcao
fila *desenfileirar(Fila *fila_escolhida)
{
    // Guardar o paciente que está na vez
    fila *vez = NULL;

    if (fila_escolhida->firts == NULL)
    {
        return NULL;
    }

    vez = fila_escolhida->firts;
    fila_escolhida->firts = fila_escolhida->firts->prox;

    if (fila_escolhida->firts == NULL)
    {
        fila_escolhida->last = NULL;
    }

    vez->prox = NULL;

    return vez;
}

// Função para ATENDER a pessoa da vez, levando em consideração a prioridade
fila *next(int *n)
{
    if (emergencia.firts != NULL)
    {
        // n recebe zero pois pode chegar um paciente e quebrar a regra de atender 3 urgente e 1 eletivo
        (*n) = 0;
        emergencia.relatorio += 1;
        return desenfileirar(&emergencia);
    }
    else if ((urgencia.firts != NULL && (*n) < 3) || (eletivo.firts == NULL && urgencia.firts != NULL))
    {
        (*n) += 1;
        urgencia.relatorio += 1;
        return desenfileirar(&urgencia);
    }
    else if ((eletivo.firts != NULL && (*n) >= 3) || (urgencia.firts == NULL && eletivo.firts != NULL))
    {
        (*n) = 0;
        eletivo.relatorio += 1;
        return desenfileirar(&eletivo);
    }
    else
    {
        printf("\n\tSem Fila!!");
    }

    return NULL;
}

fila *entran(fila *aux, int cpf, int *frente, int *verificador, int n)
{

    while ((aux != NULL) && ((n > 0) || (n == -1)))
    {
        if (aux->cpf == cpf)
        {
            (*verificador) = 1;
            return aux;
        }
        (*frente) += 1;
        aux = aux->prox;

        if (n == -1)
        {
            n = -1;
        }
        else
        {
            n -= 1;
        }
    }
    return aux;
}
void buscando(Fila *fila_da_Vezes, int cpf)
{

    int ver = 0, frente = 0;

    fila *aux = fila_da_Vezes->firts;
    aux = entran(aux, cpf, &frente, &ver, -1);
    if (ver == 1)
    {
        printf("\n\t%d Na frente do Paciente %d", frente, cpf);
        return;
    }

    fila *aux1 = urgencia.firts;
    fila *aux2 = eletivo.firts;
    int n = 0;

    for (;;)
    {
        if ((aux1 != NULL && n < 1) || (aux2 == NULL && aux1 != NULL))
        {
            aux1 = entran(aux1, cpf, &frente, &ver, 3);
            n++;
        }
        else
        {
            aux2 = entran(aux2, cpf, &frente, &ver, 1);
            n = 0;
        }
        //Encontro ou nao encontro ou vou ficar repetindo ate achar ou não
        if (ver == 1)
        {
            printf("\n\t%d Na frente do Paciente %d", frente, cpf);
            return;
        }
        else if (aux1 == NULL && aux2 == NULL)
        {
            printf("\n\tNao encontrado");
            return;
        }
        else
        {
            continue;
        }
    }
}

void relatorio()
{
    printf("\n\n**************************************");
    printf("\n***\tQuantidade de Atendimentos****");
    printf("\n***\tEmergencia -> %d  *************", emergencia.relatorio);
    printf("\n***\tUrgencia -> %d    *************", urgencia.relatorio);
    printf("\n***\tELetivo -> %d    **************", eletivo.relatorio);
    printf("\n*************************************");
}

void menu();
void impr(fila *Vez);
void barra();
void limpa();

void vendo()
{
    fila *aux = emergencia.firts;
    printf("\nEmergencia -> ");
    while (aux != NULL)
    {
        printf("\t%s |", aux->nome);
        aux = aux->prox;
    }
    aux = urgencia.firts;
    printf("\nUrgencia -> ");
    while (aux != NULL)
    {
        printf("\t%s |", aux->nome);
        aux = aux->prox;
    }
    aux = eletivo.firts;
    printf("\nEletivo -> ");
    while (aux != NULL)
    {
        printf("\t%s |", aux->nome);
        aux = aux->prox;
    }
}

int main()
{
    urgencia.relatorio = 0;
    emergencia.relatorio = 0;
    eletivo.relatorio = 0;

    int op = 0;
    int verf = 0;
    while (true)
    {
        printf("\n");
        barra();
        barra();
        menu();
        scanf("%d", &op);
        barra();
        barra();

        switch (op)
        {
        case 1:
        {
            limpa();
            barra();
            fila *adc = ins();
            enfileirar(adc);
            barra();
            break;
        }
        case 2:
        {
            limpa();
            barra();
            barra();
            fila *Vez = next(&verf);
            impr(Vez);
            barra();
            barra();
            break;
        }
        case 3:
        {
            limpa();
            barra();
            barra();
            int cpf;
            printf("\n\tDigite o CPF Procurado: ");
            scanf(" %d", &cpf);
            buscando(&emergencia, cpf);
            barra();
            barra();
            break;
        }
        case 4:
        {
            limpa();
            relatorio();
            break;
        }
        case 5:{
            barra();
            barra();
            // codigo secreto para ver as filas
            vendo();
            barra();
            barra();
            break;
        }
        default:
            break;
        }
        if (op == 0)
        {
            system("cls");
            printf("\n\tFinalizando Programa!!");
            break;
        }
        else
        {
            continue;
        }
    }

    return 0;
}

void menu()
{

    printf("\n\t1 - Adicionar paciente\n\t2 - Atender Proximo\n\t3 - Verificar Na Fila\n\t4 - Relatorio\n\t0 - Sair\n\t");
}

void impr(fila *Vez)
{
    if (Vez != NULL)
    {
        printf("\n\n\t***********\n\tNome: %s\n\tCPF - %d\n\t", Vez->nome, Vez->cpf);
        if (Vez->nivel_de_atend == 1)
        {
            printf("Prioridade: Emergencia");
        }
        if (Vez->nivel_de_atend == 2)
        {
            printf("Prioridade: Urgencia");
        }
        if (Vez->nivel_de_atend == 3)
        {
            printf("Prioridade: Eletiva");
        }
    }
}
void limpa()
{
    system("cls");
}
void barra()
{
    printf("\n------------------------------------------");
}
