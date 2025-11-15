#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5
#define TAMANHO_PILHA 3

// Estrutura para representar uma peça do Tetris
typedef struct {
    char nome;
    int id;
} Peca;

// Estrutura para representar a fila circular
typedef struct {
    Peca elementos[TAMANHO_FILA];
    int frente;
    int tras;
    int tamanho;
} Fila;

// Estrutura para representar a pilha de reserva
typedef struct {
    Peca elementos[TAMANHO_PILHA];
    int topo;
    int tamanho;
} Pilha;

// Variável global para gerar IDs únicos
int contador_id = 0;

// Função para inicializar a fila
void inicializarFila(Fila *fila) {
    fila->frente = 0;
    fila->tras = -1;
    fila->tamanho = 0;
}

// Função para inicializar a pilha
void inicializarPilha(Pilha *pilha) {
    pilha->topo = -1;
    pilha->tamanho = 0;
}

// Função para verificar se a fila está vazia
int filaVazia(Fila *fila) {
    return fila->tamanho == 0;
}

// Função para verificar se a fila está cheia
int filaCheia(Fila *fila) {
    return fila->tamanho == TAMANHO_FILA;
}

// Função para verificar se a pilha está vazia
int pilhaVazia(Pilha *pilha) {
    return pilha->tamanho == 0;
}

// Função para verificar se a pilha está cheia
int pilhaCheia(Pilha *pilha) {
    return pilha->tamanho == TAMANHO_PILHA;
}

// Função para gerar uma nova peça
Peca gerarPeca() {
    Peca nova_peca;
    char tipos[] = {'I', 'O', 'T', 'L'};
    
    // Gera um tipo aleatório
    int indice = rand() % 4;
    nova_peca.nome = tipos[indice];
    nova_peca.id = contador_id++;
    
    return nova_peca;
}

// Função para inserir uma peça na fila (enqueue)
void inserirFila(Fila *fila, Peca peca) {
    if (!filaCheia(fila)) {
        fila->tras = (fila->tras + 1) % TAMANHO_FILA;
        fila->elementos[fila->tras] = peca;
        fila->tamanho++;
    }
}

// Função para remover uma peça da fila (dequeue)
Peca removerFila(Fila *fila) {
    Peca peca_removida;
    
    if (!filaVazia(fila)) {
        peca_removida = fila->elementos[fila->frente];
        fila->frente = (fila->frente + 1) % TAMANHO_FILA;
        fila->tamanho--;
    }
    
    return peca_removida;
}

// Função para inserir uma peça na pilha (push)
void empilhar(Pilha *pilha, Peca peca) {
    if (!pilhaCheia(pilha)) {
        pilha->topo++;
        pilha->elementos[pilha->topo] = peca;
        pilha->tamanho++;
    }
}

// Função para remover uma peça da pilha (pop)
Peca desempilhar(Pilha *pilha) {
    Peca peca_removida;
    
    if (!pilhaVazia(pilha)) {
        peca_removida = pilha->elementos[pilha->topo];
        pilha->topo--;
        pilha->tamanho--;
    }
    
    return peca_removida;
}

// Função para exibir o estado atual da fila e pilha
void exibirEstado(Fila *fila, Pilha *pilha) {
    printf("\n=== ESTADO ATUAL ===\n");
    
    // Exibir fila de peças
    printf("Fila de peças:\t");
    if (filaVazia(fila)) {
        printf("Fila vazia!");
    } else {
        int indice = fila->frente;
        for (int i = 0; i < fila->tamanho; i++) {
            printf("[%c %d] ", fila->elementos[indice].nome, fila->elementos[indice].id);
            indice = (indice + 1) % TAMANHO_FILA;
        }
    }
    printf("\n");
    
    // Exibir pilha de reserva
    printf("Pilha de reserva (Topo -> Base):\t");
    if (pilhaVazia(pilha)) {
        printf("Pilha vazia!");
    } else {
        for (int i = pilha->topo; i >= 0; i--) {
            printf("[%c %d] ", pilha->elementos[i].nome, pilha->elementos[i].id);
        }
    }
    printf("\n");
}

// Função para exibir o menu de opções
void exibirMenu() {
    printf("\n=== OPÇÕES DE AÇÃO ===\n");
    printf("Código\tAção\n");
    printf("1\tJogar peça\n");
    printf("2\tReservar peça\n");
    printf("3\tUsar peça reservada\n");
    printf("0\tSair\n");
    printf("\nEscolha uma opção: ");
}

// Função para preencher a fila até o tamanho máximo
void preencherFila(Fila *fila) {
    while (!filaCheia(fila)) {
        Peca nova_peca = gerarPeca();
        inserirFila(fila, nova_peca);
    }
}

int main() {
    Fila fila;
    Pilha pilha;
    int opcao;
    
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));
    
    // Inicializa as estruturas
    inicializarFila(&fila);
    inicializarPilha(&pilha);
    
    // Preenche a fila inicial com peças
    preencherFila(&fila);
    
    printf("=== Tetris Stack - Gerenciamento de Peças ===\n");
    
    do {
        exibirEstado(&fila, &pilha);
        exibirMenu();
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 0:
                printf("Saindo do jogo...\n");
                break;
                
            case 1:
                // Jogar peça (remover da frente da fila)
                if (filaVazia(&fila)) {
                    printf("Erro: Não há peças para jogar!\n");
                } else {
                    Peca peca_jogada = removerFila(&fila);
                    printf("Peça jogada: [%c %d]\n", peca_jogada.nome, peca_jogada.id);
                    
                    // Adiciona nova peça para manter fila cheia
                    preencherFila(&fila);
                }
                break;
                
            case 2:
                // Reservar peça (mover da fila para a pilha)
                if (filaVazia(&fila)) {
                    printf("Erro: Não há peças na fila para reservar!\n");
                } else if (pilhaCheia(&pilha)) {
                    printf("Erro: Pilha de reserva cheia! Não é possível adicionar mais peças.\n");
                } else {
                    Peca peca_reservada = removerFila(&fila);
                    empilhar(&pilha, peca_reservada);
                    printf("Peça reservada: [%c %d]\n", peca_reservada.nome, peca_reservada.id);
                    
                    // Adiciona nova peça para manter fila cheia
                    preencherFila(&fila);
                }
                break;
                
            case 3:
                // Usar peça reservada (remover do topo da pilha)
                if (pilhaVazia(&pilha)) {
                    printf("Erro: Não há peças reservadas para usar!\n");
                } else {
                    Peca peca_usada = desempilhar(&pilha);
                    printf("Peça reservada usada: [%c %d]\n", peca_usada.nome, peca_usada.id);
                }
                break;
                
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
        
    } while (opcao != 0);
    
    return 0;
}