/* CÓDIGO FEITO POR:

CAUAN TEIXEIRA MACHADO
MARIA EDUARDA MASCARARENHAS DA SILVA */



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
//#include <windows.h> // Para usar Sleep() no Windows

// Estrutura para representar um participante
typedef struct Participante {
    char nome[100];          // Nome do participante
    char cpf[15];            // CPF do participante
    struct Participante *proxNo; // Ponteiro para o próximo nó (lista circular)
} Participante;

// Função para criar um novo participante
Participante* criarParticipante(char nome[], char cpf[]) {
    Participante *novo = (Participante*)malloc(sizeof(Participante));
    if (!novo) {
        printf("Erro em alocar memoria, encerrando programa...");
        exit(1);
    }
    strcpy(novo->nome, nome); // Copia o nome
    strcpy(novo->cpf, cpf);   // Copia o CPF
    novo->proxNo = novo;      // Aponta para si mesmo (lista circular)
    return novo;
}

// Função para inserir um participante na lista circular
Participante* inserirParticipante(Participante *lista, char nome[], char cpf[]) {
    Participante *novo = criarParticipante(nome, cpf);
    if (lista == NULL) {
        return novo; // Se a lista estiver vazia, retorna o novo nó
    }

    // Encontra o último nó e insere o novo participante
    Participante *temp = lista;
    while (temp->proxNo != lista) {
        temp = temp->proxNo;
    }
    temp->proxNo = novo;
    novo->proxNo = lista;
    return lista;
}

// Função para imprimir a lista de participantes
void imprimirLista(Participante *lista) {
    if (lista == NULL) {
        printf("Lista vazia.");
        return;
    }

    Participante *temp = lista;
    printf("\nLista de Participantes:\n\n");
    do {
        printf("Nome: %s, CPF: %s\n", temp->nome, temp->cpf);
        temp = temp->proxNo;
    } while (temp != lista); // Percorre até voltar ao início (lista circular)
}

// Função para remover um participante da lista
Participante* removerParticipante(Participante *lista, int m) {
    if (lista == NULL || lista->proxNo == lista) {
        return NULL; // Lista vazia ou com apenas um nó
    }

    Participante *temp = lista, *antNo = NULL;

    // Encontra o nó a ser removido
    for (int i = 1; i < m; i++) {
        antNo = temp;
        temp = temp->proxNo;
    }

    printf("Participante eliminado: %s\nCPF: %s\n", temp->nome, temp->cpf);

    // Remove o nó da lista
    if (antNo == NULL) {
        // Caso especial: remover o primeiro nó
        Participante *ultimo = lista;
        while (ultimo->proxNo != lista) {
            ultimo = ultimo->proxNo;
        }
        ultimo->proxNo = temp->proxNo;
        lista = temp->proxNo;
    } else {
        antNo->proxNo = temp->proxNo;
    }

    free(temp); // Libera a memória do nó removido
    return lista;
}

// Função para sortear um número aleatório entre 1 e maximo
int sorteiaNumero(int maximo) {
    return rand() % maximo + 1;
}

// Função principal
int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    Participante *lista = NULL; // Inicializa a lista de participantes

    int max_participantes;
    char nome_aux[100];
    char cpf_aux[15];

    puts("Ola, seja bem-vindo(a) ao sorteador do cruzeiro!\n");

    // Solicita a quantidade de participantes
    printf("Qual vai ser a quantidade de participantes: ");
    fflush(stdin);
    scanf("%d", &max_participantes);

    // Insere os participantes na lista
    puts("Quem serao os participantes desse sorteio?\n");
    for (int i = 1; i <= max_participantes; i++) {
        printf("Digite o nome do participante %d: ", i);
        fflush(stdin);
        scanf("%s", nome_aux);

        printf("Digite o cpf do participante %d: ", i);
        fflush(stdin);
        scanf("%s", cpf_aux);

        lista = inserirParticipante(lista, nome_aux, cpf_aux); // Insere na lista
        puts("\nParticipante adicionado!!!");
        puts("-------------------------------------------------------------------------------------------------------------\n");
    }

    // Sorteia e remove participantes até sobrar apenas um
    printf("INICIANDO SORTEIO\n");
    int cont = 1;

    while (lista && lista->proxNo != lista) {
        printf("-------------------------------------------------------------------------------------------------------------\n");
        printf("\nRodada %d\n\n", cont);
        int m = sorteiaNumero(max_participantes); // Sorteia um número
        printf("Numero sorteado: %d\n", m);
        lista = removerParticipante(lista, m); // Remove o participante sorteado
        max_participantes--; // Decrementa o número de participantes
        imprimirLista(lista); // Imprime a lista atualizada
        printf("-------------------------------------------------------------------------------------------------------------\n\n");

        // Sleep(750); // Adiciona um delay (Windows)

        cont++;
    }

    // Exibe o vencedor
    printf("Vencedor: %s, CPF: %s\nParabens!!", lista->nome, lista->cpf);
    free(lista); // Libera a memória do último participante
    return 0;
}