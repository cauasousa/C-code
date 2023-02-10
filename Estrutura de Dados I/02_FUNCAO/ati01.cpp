//Fazer um programa em C que pergunta um valor em metros e imprime o
//correspondente em decímetros, centímetros e milímetros.
#include <stdio.h>

void conv(float metro, float *dec, float *cen, float *mili){
    *dec = metro * 10;
    *cen = metro * 100;
    *mili = metro * 1000;
}

void pri( float metro ){
    printf("Dec: %.2f\t\t Cen: %.2f\t\tmili: %.2f", metro*10, metro*100, metro*1000);

}


int main(){
    float metro, dec, cent, mili;

    printf("Digite o Valor: ");
    scanf("%f", &metro); 

    conv(metro, &dec, &cent, &mili);
    printf("%.2f\n %.2f\n %.2f\n", dec, cent, mili);

    return 0; 
}