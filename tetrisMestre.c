#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// ===============================================================
// STRUCT — Representa uma peça
// ===============================================================
typedef struct {
    char nome; // 'I', 'O', 'T', 'L'
    int id;    // identificador único
} Peca;

// ===============================================================
// FILA CIRCULAR
// ===============================================================
Peca fila[TAM_FILA];
int inicio = 0, fim = 0, quantidade = 0;

// ===============================================================
// PILHA
// ===============================================================
Peca pilha[TAM_PILHA];
int topo = -1;

int geradorID = 0; // ID único das peças

// ===============================================================
// GERAR PEÇA AUTOMÁTICA
// ===============================================================
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = geradorID++;
    return p;
}

// ===============================================================
// ENQUEUE — insere peça na fila
// ===============================================================
void enqueue() {
    if (quantidade == TAM_FILA) return;
    fila[fim] = gerarPeca();
    fim = (fim + 1) % TAM_FILA;
    quantidade++;
}

// ===============================================================
// DEQUEUE — remove peça da frente da fila
// ===============================================================
Peca dequeue() {
    Peca removida;
    if (quantidade == 0) {
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
// PUSH — insere peça na pilha
// ===============================================================
void push(Peca p) {
    if (topo == TAM_PILHA - 1) {
        printf("Pilha cheia! Nao eh possivel reservar mais pecas.\n");
        return;
    }
    pilha[++topo] = p;
}

// ===============================================================
// POP — remove peça do topo da pilha
// ===============================================================
Peca pop() {
    Peca removida;
    if (topo == -1) {
        removida.nome = '?';
        removida.id = -1;
        return removida;
    }
    removida = pilha[topo--];
    return removida;
}

// ===============================================================
// TROCAR PEÇA DA FRENTE DA FILA COM TOPO DA PILHA
// ===============================================================
void trocaSimples() {
    if (quantidade == 0 || topo == -1) {
        printf("Nao ha pecas suficientes para realizar a troca.\n");
        return;
    }
    Peca temp = fila[inicio];
    fila[inicio] = pilha[topo];
    pilha[topo] = temp;
    printf("Troca simples realizada entre frente da fila e topo da pilha.\n");
}

// ===============================================================
// TROCA MÚLTIPLA (3 primeiras da fila com 3 da pilha)
// ===============================================================
void trocaMultipla() {
    if (quantidade < 3 || topo < 2) {
        printf("Nao ha pecas suficientes para troca multipla.\n");
        return;
    }
    for (int i = 0; i < 3; i++) {
        int idxFila = (inicio + i) % TAM_FILA;
        Peca temp = fila[idxFila];
        fila[idxFila] = pilha[topo - i];
        pilha[topo - i] = temp;
    }
    printf("Troca multipla realizada entre 3 primeiros da fila e 3 da pilha.\n");
}

// ===============================================================
// MOSTRAR FILA
// ===============================================================
void mostrarFila() {
    printf("Fila de pecas: ");
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
// MOSTRAR PILHA
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
        printf("1 - Jogar peca da frente da fila\n");
        printf("2 - Enviar peca da fila para pilha de reserva\n");
        printf("3 - Usar peca da pilha de reserva\n");
        printf("4 - Trocar peca da frente da fila com topo da pilha\n");
        printf("5 - Trocar os 3 primeiros da fila com 3 da pilha\n");
        printf("0 - Sair\n");
        printf("Opcao escolhida: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            Peca jogada = dequeue();
            if (jogada.id != -1)
                printf("Peca jogada: [%c %d]\n", jogada.nome, jogada.id);
            enqueue();
        } else if (opcao == 2) {
            Peca reservada = dequeue();
            if (reservada.id != -1) {
                push(reservada);
                enqueue();
            }
        } else if (opcao == 3) {
            Peca usada = pop();
            if (usada.id != -1)
                printf("Peca usada da pilha: [%c %d]\n", usada.nome, usada.id);
            enqueue();
        } else if (opcao == 4) {
            trocaSimples();
        } else if (opcao == 5) {
            trocaMultipla();
        } else if (opcao != 0) {
            printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    printf("Encerrando sistema...\n");
    return 0;
}
