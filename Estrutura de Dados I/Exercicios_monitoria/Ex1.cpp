#include <stdio.h>

// Faça uma função que verifique se um valor é perfeito ou não. Um valor é
// dito perfeito quando ele é igual a soma dos seus divisores excetuando ele
// próprio. (Ex: 6 é perfeito, 6 = 1 + 2 + 3, que são seus divisores). A função
// deve retornar um valor booleano.
int valor(int num)
{
    int Soma = 0;
    int teste = num;

    for(int i = num-1; i>0; i--){
        if((num%i) == 0){

            Soma = Soma + i;
            //printf("%d", Soma);
        }

    }

    if(Soma == num){
        return true;
    }
    return false;

};

int main()
{
    int alor;
    printf("Digite o número: ");
    scanf("%d", &alor);

    bool oi;
    oi = valor(alor);
    
    if(oi == true){
        printf("Verdade");
    }
    else{
        printf("Falso");
    }

    //printf("%d", oi);

    return 0;
}