#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int removerPosicao(int lista[], int chave, int tamanho){
    if (chave < 0 || chave > tamanho){
        printf("Posicao inválida.");
        return 0;
    }

    for (int i = chave; i <= tamanho; i++){
        lista[i] = lista[i+1];
    }


    return 0;
}

int main(){
    int lista[] = {3,8,12,17,19,26,30,38};
    int chave;
    int tamanho = sizeof(lista)/sizeof(lista[0]);

    printf("Lista:\n");
    for (int i = 0; i < tamanho; i++)
        printf("%d ", lista[i]);

    printf("\nQual posicao da lista voce deseja remover (de 0 a %d)? ", tamanho-1);
    scanf("%d", &chave);
    removerPosicao(lista, chave, tamanho-1);

    printf("Lista atualizada: ");
    for (int i = 0; i < tamanho-1; i++)
        printf("%d ", lista[i]);
}