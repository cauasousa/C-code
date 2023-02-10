#include <stdio.h>
#include <stdlib.h>

int tam = 2;

typedef struct{
    float nota_1;
    float nota_2;
    float nota_3;
    float Media;
}Notas;

typedef struct{
    int matricula;
    char nome[30];
    Notas notas;
}Aluno;

Aluno ler_info(){

    Aluno aluno;

    printf("Nome: ");
    scanf(" %30[^\n]", aluno.nome);
    printf("Matricula: ");
    scanf("%d", &aluno.matricula);
    printf("Informe a 1 Nota: ");
    scanf("%f", &aluno.notas.nota_1);
    printf("Informe a 2 Nota: ");
    scanf("%f", &aluno.notas.nota_2);
    printf("Informe a 3 Nota: ");
    scanf("%f", &aluno.notas.nota_3);
    aluno.notas.Media = (aluno.notas.nota_1 + aluno.notas.nota_2 + aluno.notas.nota_3)/3;

    fflush(stdin);

    return aluno;
}

Aluno media (Aluno *ponto){
     
    Aluno cabeca = (ponto[0]);
    
    for(int j=1; j < tam; j++){
        
        if(ponto[j].notas.Media > cabeca.notas.Media){
            cabeca = ponto[j] ;
            
        }
    }
    printf("Maior Media : %s - %f\n", cabeca.nome, cabeca.notas.Media );

    return cabeca;
}

void imprimir(Aluno aluno){
    printf("\n\tNome: %s\n", aluno.nome);
    printf("\tMatricula: %d\n", aluno.matricula);
    printf("\tNota 1: %.2f\n", aluno.notas.nota_1);
    printf("\tNota 2: %.2f\n", aluno.notas.nota_2);
    printf("\tNota 3: %.2f\n", aluno.notas.nota_3);
}

void imprimirAlunos(Aluno *aluno){

    printf("\n\t--------------------\n");

    for(int i = 0; i < tam; i++){
        imprimir(aluno[i]);
    }

    printf("\n\t--------------------\n");
}

Aluno maior_nota_1(Aluno *aluno){

    Aluno m_Nota_1 = aluno[0];

    for(int i = 1; i < tam; i++){
        if(aluno[i].notas.nota_1 > m_Nota_1.notas.nota_1){
            m_Nota_1 = aluno[i];
        }
    }

    return m_Nota_1;
}

int main(){

    Aluno *aluno;

    aluno = (Aluno*)malloc(tam * sizeof(aluno));

    for(int i = 0; i < tam; i++){
        printf("\nALUNO: %d\n", i + 1);
        aluno[i] = ler_info();
    }

    imprimirAlunos(aluno);

    printf("\n\tALUNO COM A MAIOR NOTA:\n");
    Aluno maior_nota = maior_nota_1(aluno);
    imprimir(maior_nota);

    printf("----------------Media----------------------\n");

    Aluno receber = media(aluno);

    imprimir(receber);
    return 0;
}