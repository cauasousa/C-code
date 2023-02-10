#include <stdio.h>
#include <stdlib.h>

struct notas_aluno {
   float n1, n2, n3;
   float media = (n1+n2+n3)/3;
};

struct endereco_aluno {
    int cep;
    int numero_casa;
    char rua[50];
    char bairro[50];
};

typedef struct aluno{
    char nome[50];
    int matricula;
    struct notas_aluno notas;
    struct endereco_aluno endereco;
}dados;

void imprimir(aluno *Aluno){

    printf("\n-----------------------Dados--------------------------\n");
    printf("\n\t Nome:%s", Aluno->nome);
    printf("\n\t Matricula:%d", Aluno->matricula);

    printf("\n-----------------------Notas--------------------------\n");
    printf("\n\t nota 1:%f", Aluno->notas.n1);
    printf("\n\t nota 2:%f", Aluno->notas.n2);
    printf("\n\t nota 3:%f", Aluno->notas.n3);
    printf("\n\t media:%f", Aluno->notas.media);

    printf("\n-----------------------Endereco--------------------------\n");
    printf("\n\t Cep:%d", Aluno->endereco.cep);
    printf("\n\t Numero da residencia:%d", Aluno->endereco.numero_casa);
    printf("\n\t Rua:%s", Aluno->endereco.rua);
    printf("\n\t Bairro:%s", Aluno->endereco.bairro);
}


dados *inserir(){

    dados *Aluno = (dados*)malloc(sizeof(dados));

    printf("\n\t Digite seu nome: ");
    scanf(" %50[^\n]s", Aluno->nome );
    printf("\n\t Digite sua matricula: ");
    scanf("%d", &Aluno->matricula );

    printf("\n\t Digite sua nota1: ");
    scanf("%f", &Aluno->notas.n1 );
    printf("\n\t Digite sua nota2: ");
    scanf("%f", &Aluno->notas.n2 );
    printf("\n\t Digite sua nota3: ");
    scanf("%f", &Aluno->notas.n3 );

    printf("\n\t Digite seu cep: "); 
    scanf("%d", &Aluno->endereco.cep);
    printf("\n\t Digite o numero de sua casa "); 
    scanf("%d", &Aluno->endereco.numero_casa);
    printf("\n\t  Digite sua rua"); 
    scanf(" %50[^\n]s", Aluno->endereco.rua);
    printf("\n\t  Digite seu bairro: "); 
    scanf(" %50[^\n]s", Aluno->endereco.bairro);
    
    return Aluno;
};

int main (){
    dados *Aluno;
    Aluno = inserir();
    imprimir(Aluno);
    return 0;
}