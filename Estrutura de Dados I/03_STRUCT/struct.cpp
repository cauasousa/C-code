#include <stdio.h>

// Horario: composto de hora, minutos e segundos.
typedef struct {
    int horas, minutos, segundos;

}horario;

// Data composto de dia, mes e ano. ˆ
typedef struct {
    int dia, mes, ano;
}Data;

// Compromisso: composto de uma data, horario e texto que descreve o compromisso.
typedef struct {
    char Compromisso[200];
    Data op1;
    horario op2;
}compromisso;


int main(){

    compromisso usuario;
    printf("\tDigite o seu compromisso: ");
    scanf(" %[^\n]", usuario.Compromisso);
    printf("\tDigite o seu o dia: ");
    scanf("%d", &usuario.op1.dia);
    printf("\tDigite o seu mes: ");
    scanf("%d", &usuario.op1.mes);
    printf("\tDigite o seu ano: ");
    scanf("%d", &usuario.op1.ano);
    printf("\tDigite o Horário, a hora: ");
    scanf("%d", &usuario.op2.horas);
    printf("\tDigite o minunto: ");
    scanf("%d", &usuario.op2.minutos);
    printf("\tDigite o segundos: ");
    scanf("%d", &usuario.op2.segundos);

    printf("O Compromisso: %s ", usuario.Compromisso);
    printf("\nData %d/%d/%d\n", usuario.op1.dia, usuario.op1.mes, usuario.op1.ano );
    printf("Horario %dh:%dMin:%ds", usuario.op2.horas, usuario.op2.minutos, usuario.op2.segundos);

    return 0;
}