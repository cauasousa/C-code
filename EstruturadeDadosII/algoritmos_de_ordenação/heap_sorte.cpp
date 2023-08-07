#include <stdio.h>
#include <random>
#include <time.h>

#define tam 10

void print(int *vetor, int quant){
    printf("\n");
    for(int i = 0; i<quant; i++){
        printf("|%d| ", vetor[i]);
    }
}

void shift(int *vetor, int i, int j){
    printf("\n%d-%d", vetor[i], vetor[j]);
    int aux = vetor[i];
    vetor[i] = vetor[j];
    vetor[j] = aux;
}

void insertion_heap(int *vetor, int quant_preenchida){
    if(quant_preenchida == 0){
        return;
    }
    
    for(int i = quant_preenchida  ; i > 0; i = ((i-1)/2) ){
        
        int pai_no = (i-1)/2;
        if(pai_no >= 0){
            if(vetor[pai_no] < vetor[i]){
                int aux = vetor[i];
                vetor[i] = vetor[pai_no];
                vetor[pai_no] = aux;
            }
        }
    }
}

void heap_sort_down(int *vetor, int quant){
    if(quant == 0){
        return;
    }
    
    for(int i = 0  ; i <= quant; i = i ){
        print(vetor, tam);
        int no_1 = 2*i+1;
        int no_2 = 2*i+2;
        
        if(no_1 <= quant && no_2 <= quant){

            if(vetor[no_1] > vetor[i] && vetor[no_2] > vetor[i]){
                if(vetor[no_1] > vetor[no_2]){
                    shift(vetor, i, no_1);
                    i = no_1;
                }else if(vetor[no_1] < vetor[no_2]){
                    shift(vetor, i, no_2);
                    i = no_2;
                }else{
                    break;
                }
            }else if(vetor[no_1] > vetor[i]){
                shift(vetor, i, no_1);
                i = no_1;
                    
            }else if(vetor[no_2] > vetor[i]){
                shift(vetor, i, no_2);
                i = no_2;
                    
            }else{
                break;
            }

        }else if(no_1 <= quant){
            if(vetor[no_1] > vetor[i]){
                shift(vetor, i, no_1);
                i = no_1; 
            }else{
                break;
            }
        }else if(no_2 <= quant){
            if(vetor[no_2] > vetor[i]){
                shift(vetor, i, no_2);
                i = no_2; 
            }else{
                break;
            }
        }else{
            break;
        }
    }
}

void remove(int *vetor, int quant){
    if(quant > 0){
        int prim = vetor[0];
        int ultim = vetor[quant];
        printf("\n%d %d", prim, ultim);
        vetor[quant] = prim;
        vetor[0] = ultim;
    }else{
        printf("OPA");
    }
}
    

void preencher_vetor(int *vetor, int quan){
    int quant_preenchida = 0;

    while(quant_preenchida < quan){
        int aleatorio = (rand() % quan) + 1;
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


void heap_sort(int *vetor, int quant){
    for(int i = 0; i<quant; i++){
        insertion_heap(vetor, i);
    }

    print(vetor, quant);

    for(int i = quant - 1; i>0; i--){
        printf("\n---------------------------");
        remove(vetor, i);

        heap_sort_down(vetor, i - 1);

        printf("\nORD->");
        print(vetor, i);

        
    }
}



int main(){

    //int vetor_1[tam]={1, 3, 7, 8, 0, 2, 4, 9, 5, 6};
    int vetor_1[tam];
    srand(time(NULL));

    preencher_vetor(vetor_1, tam);
    print(vetor_1, tam);
    heap_sort(vetor_1, tam);
    print(vetor_1, tam);


    return 0;
}
