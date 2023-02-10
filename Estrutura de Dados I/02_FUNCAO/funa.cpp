#include <stdio.h>

int media(int num1, int num2){
    int media=0;
    media = (num1 + num2)/2;
    return media;
}

void Meddia(int a){
    printf("\n Media: %d ", a);
}

int main(){
    int num11, num2, Media;

    scanf("%d", &num11);
    scanf("%d", &num2);
   
    Meddia(media(num11, num2));

    return 0;

}
