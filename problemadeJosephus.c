#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
//#include <windows.h>

typedef struct Participante{
    char nome[100];
    char cpf[15];
    struct Participante *proxNo;
} Participante;

Participante* criarParticipante(char nome[], char cpf[]){
    Participante *novo = (Participante*)malloc(sizeof(Participante));
    if(!novo){
        printf("Erro em alocar memoria, encerrando programa...");
        exit(1);
    }
    strcpy(novo->nome, nome);
    strcpy(novo->cpf, cpf);
    novo->proxNo = novo; // aponta p si msm (lista circular)
    return novo;
}

Participante* inserirParticipante(Participante *lista, char nome[], char cpf[]){
    Participante *novo = criarParticipante(nome, cpf);
    if(lista == NULL){
        return novo;
    }

    Participante *temp = lista;
    while(temp->proxNo != lista){
        temp = temp->proxNo;
    }
    temp->proxNo = novo;
    novo->proxNo = lista;
    return lista;
}

void imprimirLista(Participante *lista){
    if(lista == NULL){
        printf("Lista vazia.");
        return;
    }

    Participante *temp = lista;
    printf("\nLista de Participantes:\n\n");
    do{
        printf("Nome: %s, CPF: %s\n", temp->nome, temp->cpf);
        temp = temp->proxNo;
    }while(temp != lista);
}

Participante* removerParticipante(Participante *lista, int m){
    if (lista == NULL || lista->proxNo == lista){
        return NULL;
    }

    Participante *temp = lista, *antNo = NULL;

    for(int i = 1; i < m; i++){
        antNo = temp;
        temp = temp->proxNo;
    }

    printf("Participante eliminado: %s\nCPF: %s\n", temp->nome, temp->cpf);
    if (antNo == NULL) {
        // caso especial - remover primeiro nó
        Participante *ultimo = lista;
        while (ultimo->proxNo != lista) {
            ultimo = ultimo->proxNo;
        }
        ultimo->proxNo = temp->proxNo;
        lista = temp->proxNo;
    } else {
        antNo->proxNo = temp->proxNo;
    }

    free(temp);
    return lista;
}

int sorteiaNumero(int maximo){
    return rand() % maximo + 1;
}


int main()
{
    srand(time(NULL));
    Participante *lista = NULL;

    int max_participantes;

    char nome_aux[100];
    char cpf_aux[15];

    puts("Ola, seja bem-vindo(a) ao sorteador do cruzeiro!\n");
    
    printf("Qual vai ser a quantidade de participantes: ");
    fflush(stdin);
    scanf("%d",&max_participantes);



    // INSERINDO PARTICIPANTES

    puts("Quem serao os participantes desse sorteio?\n");

    for(int i = 1; i <= max_participantes; i++){
        
        printf("Digite o nome do participante %d: ",i);
        fflush(stdin);
        scanf("%s", nome_aux);
        
        printf("Digite o cpf do participante %d: ",i);
        fflush(stdin);
        scanf("%s", cpf_aux);

        lista = inserirParticipante(lista,nome_aux,cpf_aux);

        puts("\nParticipante adicionado!!!");
        puts("-------------------------------------------------------------------------------------------------------------\n");
    }


    // SORTEANDO PARTICIPANTES
    printf("INICIANDO SORTEIO\n");
    int cont = 1;
    
    while (lista && lista->proxNo != lista){
        printf("-------------------------------------------------------------------------------------------------------------\n");
        printf("\nRodada %d\n\n", cont);
        int m = sorteiaNumero(max_participantes);
        printf("Numero sorteado: %d\n", m);
        lista = removerParticipante(lista, m); // atualiza a lista removendo o participante do indice do numero sorteado (tenho uma duvida aqui // cauan)
        max_participantes--; //decrementa o numero de participantes
        imprimirLista(lista); //imprime a lista atualizada
        printf("-------------------------------------------------------------------------------------------------------------\n\n");

        // Sleep(750); (caso queira testae com delay, tire o comentário desse sleep e da biblioteca (#include <windows.h>))

        cont++;
    }
    
    printf("Vencedor: %s, CPF: %s\nParabens!!", lista->nome, lista->cpf);
    free(lista);
    return 0;
}
