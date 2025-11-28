#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5   // tamanho fixo da fila

// ===============================================================
// STRUCT PRINCIPAL — representa uma peça do Tetris
// ===============================================================
typedef struct {
    char nome;   // tipo da peça ('I', 'O', 'T', 'L')
    int id;      // identificador único
} Peca;

// ===============================================================
// VARIÁVEIS DA FILA CIRCULAR
// ===============================================================
Peca fila[TAM_FILA];
int inicio = 0;       // posição do primeiro elemento
int fim = 0;          // posição do próximo espaço livre
int quantidade = 0;   // elementos na fila
int geradorID = 0;    // incrementado automaticamente

// ===============================================================
// FUNÇÃO PARA GERAR PEÇA AUTOMATICAMENTE
// ===============================================================
Peca gerarPeca() {
    Peca nova;

    char tipos[] = {'I', 'O', 'T', 'L'};
    nova.nome = tipos[rand() % 4]; // escolhe um tipo aleatório

    nova.id = geradorID++;         // gera ID único crescente

    return nova;
}

// ===============================================================
// INSERIR NA FILA (ENQUEUE)
// ===============================================================
void enqueue() {
    if (quantidade == TAM_FILA) {
        printf("Fila cheia! Nao eh possivel inserir mais pecas.\n");
        return;
    }

    fila[fim] = gerarPeca();    // gera e insere peça
    fim = (fim + 1) % TAM_FILA; // avança circularmente
    quantidade++;

    printf("Peca inserida com sucesso!\n");
}

// ===============================================================
// REMOVER DA FILA (DEQUEUE)
// ===============================================================
void dequeue() {
    if (quantidade == 0) {
        printf("Fila vazia! Nao ha pecas para jogar.\n");
        return;
    }

    Peca jogada = fila[inicio];
    inicio = (inicio + 1) % TAM_FILA;
    quantidade--;

    printf("Peca jogada: [%c %d]\n", jogada.nome, jogada.id);
}

// ===============================================================
// MOSTRAR FILA
// ===============================================================
void mostrarFila() {
    printf("\n=== FILA DE PECAS ===\n");

    if (quantidade == 0) {
        printf("[Fila vazia]\n");
        return;
    }

    int i = inicio;
    for (int c = 0; c < quantidade; c++) {
        printf("[%c %d] ", fila[i].nome, fila[i].id);
        i = (i + 1) % TAM_FILA;
    }

    printf("\n");
}

// ===============================================================
// PROGRAMA PRINCIPAL
// ===============================================================
int main() {
    srand(time(NULL)); // para gerar peças aleatórias

    // inicializa fila com 5 peças
    printf("Inicializando fila com %d pecas...\n", TAM_FILA);
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue();
    }

    int opcao;

    do {
        mostrarFila();

        printf("\n=== MENU ===\n");
        printf("1 - Jogar peca (dequeue)\n");
        printf("2 - Inserir nova peca (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dequeue();
                break;
            case 2:
                enqueue();
                break;
            case 0:
                printf("Encerrando sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}
