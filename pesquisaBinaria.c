#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int buscaBinaria(int lista[], int chave, int inicio, int fim){
    while(inicio <= fim){
        int meio = inicio + (fim - inicio)/2;

    if(chave == lista[meio]){
        return meio;}
    else if(chave < lista[meio]){
        fim = meio-1;}
    else if(chave > lista[meio]){
        inicio = meio+1;
    }
    }
    return -1;
}

int main(){
    int lista[] = {0,3,4,6,7,10,13,14,20,42};
    int chave;
    int tamanho = sizeof(lista)/sizeof(lista[0]);

    printf("Qual numero voce deseja buscar na lista? ");
    scanf("%d", &chave);

    int resultado = buscaBinaria(lista, chave, 0, tamanho-1);

    if (resultado != -1)
        printf("O numero %d esta na %da posicao da lista", chave, resultado);
    else
         printf("O numero %d nao se encontra na lista.", chave);

    return 0;
}
