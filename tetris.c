#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5

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
    int contador_id; // Para gerar IDs únicos
} Fila;

// Função para inicializar a fila
void inicializarFila(Fila *fila) {
    fila->frente = 0;
    fila->tras = -1;
    fila->tamanho = 0;
    fila->contador_id = 0;
}

// Função para verificar se a fila está vazia
int filaVazia(Fila *fila) {
    return fila->tamanho == 0;
}

// Função para verificar se a fila está cheia
int filaCheia(Fila *fila) {
    return fila->tamanho == TAMANHO_FILA;
}

// Função para gerar uma nova peça
Peca gerarPeca(Fila *fila) {
    Peca nova_peca;
    char tipos[] = {'I', 'O', 'T', 'L'};
    
    // Gera um tipo aleatório
    int indice = rand() % 4;
    nova_peca.nome = tipos[indice];
    nova_peca.id = fila->contador_id++;
    
    return nova_peca;
}

// Função para inserir uma peça na fila (enqueue)
void inserirPeca(Fila *fila, Peca peca) {
    if (!filaCheia(fila)) {
        fila->tras = (fila->tras + 1) % TAMANHO_FILA;
        fila->elementos[fila->tras] = peca;
        fila->tamanho++;
    }
}

// Função para remover uma peça da fila (dequeue)
Peca removerPeca(Fila *fila) {
    Peca peca_removida;
    
    if (!filaVazia(fila)) {
        peca_removida = fila->elementos[fila->frente];
        fila->frente = (fila->frente + 1) % TAMANHO_FILA;
        fila->tamanho--;
    }
    
    return peca_removida;
}

// Função para exibir o estado atual da fila
void exibirFila(Fila *fila) {
    printf("\nFila de peças:\n");
    
    if (filaVazia(fila)) {
        printf("Fila vazia!\n");
        return;
    }
    
    int indice = fila->frente;
    for (int i = 0; i < fila->tamanho; i++) {
        printf("[%c %d] ", fila->elementos[indice].nome, fila->elementos[indice].id);
        indice = (indice + 1) % TAMANHO_FILA;
    }
    printf("\n");
}

// Função para exibir o menu de opções
void exibirMenu() {
    printf("\nOpções de ação:\n");
    printf("Código\tAção\n");
    printf("1\tJogar peça (dequeue)\n");
    printf("2\tInserir nova peça (enqueue)\n");
    printf("0\tSair\n");
    printf("\nEscolha uma opção: ");
}

int main() {
    Fila fila;
    int opcao;
    
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));
    
    // Inicializa a fila
    inicializarFila(&fila);
    
    // Preenche a fila inicial com 5 peças
    for (int i = 0; i < TAMANHO_FILA; i++) {
        Peca nova_peca = gerarPeca(&fila);
        inserirPeca(&fila, nova_peca);
    }
    
    printf("=== Tetris Stack - Controle de Peças ===\n");
    
    do {
        exibirFila(&fila);
        exibirMenu();
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 0:
                printf("Saindo do jogo...\n");
                break;
                
            case 1:
                // Jogar peça (remover da frente)
                if (filaVazia(&fila)) {
                    printf("Erro: Não há peças para jogar!\n");
                } else {
                    Peca peca_jogada = removerPeca(&fila);
                    printf("Peça jogada: [%c %d]\n", peca_jogada.nome, peca_jogada.id);
                }
                break;
                
            case 2:
                // Inserir nova peça
                if (filaCheia(&fila)) {
                    printf("Erro: Fila cheia! Não é possível adicionar mais peças.\n");
                } else {
                    Peca nova_peca = gerarPeca(&fila);
                    inserirPeca(&fila, nova_peca);
                    printf("Nova peça adicionada: [%c %d]\n", nova_peca.nome, nova_peca.id);
                }
                break;
                
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
        
    } while (opcao != 0);
    
    return 0;
}