// Construa uma estrutura aluno com nome, numero de matr  ́  ́ıcula e curso. Leia do usuario  ́
// a informac ̧ao de 5 alunos, armazene em vetor dessa estrutura e imprima os dados na  ̃
// tela.

#include <stdio.h>
#include <stdlib.h>


typedef struct {
    char nome[50], curso[100];
    int matricula;
}aluno;


int main(){

    aluno *Aluno = (aluno*) malloc(sizeof (aluno) * 5 );
   
    for(int i = 0; i < 5; i++){
        printf("%d\n", i);
        printf("\nDigite o nome: ");
        scanf("%s", Aluno[i].nome);

        printf("\nDigite a matricula: ");
        scanf("%d", &Aluno[i].matricula);

        printf("\nEscreva o Curso: ");
        scanf(" %[^\n]", Aluno[i].curso);
        
    }


    
    for ( int i = 0; i < 5; i++){
        printf("\tNome: %s\n", Aluno[i].nome);
        printf("\tMatricula: %d\n", Aluno[i].matricula);
        printf("\tCurso: %s\n\n", Aluno[i].curso);
    }
    



    return 0;

}