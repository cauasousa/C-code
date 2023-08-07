#include <stdio.h>
#include <random>
#include <time.h>

void preencher_vetor(int *vetor, int quan){
    int quant_preenchida = 0;

    while(quant_preenchida < quan){
        int aleatorio = rand() % quan;
        int achou = 0;

        for(int verificador = 0; verificador < quant_preenchida; verificador++){
            if( vetor[verificador] == aleatorio ){
                achou=1;
                break;
            }

        }
        if(achou == 0){
            vetor[quant_preenchida] = aleatorio;
            quant_preenchida+=1;
        }   
    }

}


void preenche_and_media(int *vetores, int quant){

    preencher_vetor(vetores, quant);

    // for(int i = 0; i<quant; i++){
    //     printf("|%d| ", vetores[i]);
    // }

    printf("\n");
    int i =0;
    
    int comparacao = 0;
    float tam = 1000000;

    while (i <tam) {
        int aleatorio = rand() % 15;

        for(int x = 0; x<quant; x++){
            if(vetores[x] == aleatorio){
                break;
            }
            comparacao++;

        }
        i++;
    }
    float media = (comparacao)/tam;
    printf("\nMedia %.2f", media);
}

int main(){
    int vetor_1[15];
    int vetor_2[127];
    int vetor_3[32767];
    srand(time(NULL));

    //preenche_and_media(vetor_1, 15);
    preenche_and_media(vetor_2, 127);
    //preenche_and_media(vetor_3, 32767);

    return 0;
}
