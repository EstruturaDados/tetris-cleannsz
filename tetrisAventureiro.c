#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5     // tamanho fixo da fila circular
#define TAM_PILHA 3    // tamanho fixo da pilha de reserva

// ===============================================================
// STRUCT — representa uma peça do Tetris Stack
// ===============================================================
typedef struct {
    char nome;   // tipos possíveis: 'I', 'O', 'T', 'L'
    int id;      // identificador único
} Peca;

// ===============================================================
// VARIÁVEIS DA FILA CIRCULAR
// ===============================================================
Peca fila[TAM_FILA];
int inicio = 0;       // índice do primeiro elemento
int fim = 0;          // próximo índice livre
int quantidade = 0;   // número atual de peças na fila

// ===============================================================
// VARIÁVEIS DA PILHA
// ===============================================================
Peca pilha[TAM_PILHA];
int topo = -1;        // índice do topo (inicial: vazio)

int geradorID = 0;    // usado para gerar IDs únicos

// ===============================================================
// FUNÇÃO PARA GERAR UMA PEÇA AUTOMÁTICA
// ===============================================================
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;

    p.nome = tipos[rand() % 4];
    p.id = geradorID++;

    return p;
}

// ===============================================================
// ENQUEUE — Insere peça no final da fila circular
// ===============================================================
void enqueue() {
    if (quantidade == TAM_FILA) {
        // isso não deve acontecer, pois após toda ação a fila é reabastecida
        printf("ERRO: Fila cheia!\n");
        return;
    }

    fila[fim] = gerarPeca();
    fim = (fim + 1) % TAM_FILA;
    quantidade++;
}

// ===============================================================
// DEQUEUE — Remove peça da frente da fila
// ===============================================================
Peca dequeue() {
    Peca removida;

    if (quantidade == 0) {
        printf("ERRO: Fila vazia!\n");
        removida.nome = '?';
        removida.id = -1;
        return removida;
    }

    removida = fila[inicio];
    inicio = (inicio + 1) % TAM_FILA;
    quantidade--;

    return removida;
}

// ===============================================================
// PUSH — Insere peça na pilha
// ===============================================================
void push(Peca p) {
    if (topo == TAM_PILHA - 1) {
        printf("Pilha cheia! Nao eh possivel reservar mais pecas.\n");
        return;
    }

    pilha[++topo] = p;
    printf("Peca reservada: [%c %d]\n", p.nome, p.id);
}

// ===============================================================
// POP — Remove peça do topo da pilha
// ===============================================================
Peca pop() {
    Peca removida;

    if (topo == -1) {
        printf("Pilha vazia! Nao ha pecas reservadas para usar.\n");
        removida.nome = '?';
        removida.id = -1;
        return removida;
    }

    removida = pilha[topo--];
    printf("Peca usada da reserva: [%c %d]\n", removida.nome, removida.id);
    return removida;
}

// ===============================================================
// MOSTRAR FILA
// ===============================================================
void mostrarFila() {
    printf("\nFila de pecas: ");

    if (quantidade == 0) {
        printf("[Vazia]\n");
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
// MOSTRAR PILHA (Topo → Base)
// ===============================================================
void mostrarPilha() {
    printf("Pilha de reserva (Topo -> Base): ");

    if (topo == -1) {
        printf("[Vazia]\n");
        return;
    }

    for (int i = topo; i >= 0; i--) {
        printf("[%c %d] ", pilha[i].nome, pilha[i].id);
    }
    printf("\n");
}

// ===============================================================
// MOSTRAR ESTADO COMPLETO
// ===============================================================
void mostrarEstado() {
    printf("\n=== ESTADO ATUAL ===\n");
    mostrarFila();
    mostrarPilha();
}

// ===============================================================
// PROGRAMA PRINCIPAL
// ===============================================================
int main() {
    srand(time(NULL));

    // Inicializa fila com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue();
    }

    int opcao;

    do {
        mostrarEstado();

        printf("\n=== MENU ===\n");
        printf("1 - Jogar peca\n");
        printf("2 - Reservar peca\n");
        printf("3 - Usar peca reservada\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            // jogar a peça da frente da fila
            Peca jogada = dequeue();
            if (jogada.id != -1)
                printf("Peca jogada: [%c %d]\n", jogada.nome, jogada.id);

            enqueue(); // mantém fila sempre cheia

        } else if (opcao == 2) {
            // reservar a peça da fila
            Peca reservada = dequeue();
            if (reservada.id != -1)
                push(reservada);

            enqueue(); // mantém fila sempre cheia

        } else if (opcao == 3) {
            // usar peça da reserva
            pop();
            enqueue(); // sempre repõe peça na fila

        } else if (opcao != 0) {
            printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    printf("Encerrando sistema...\n");
    return 0;
}
