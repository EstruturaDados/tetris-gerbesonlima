/*
 * Projeto: Tetris Stack - Gerenciador de Fila de Peças
 * Desenvolvedor: [Seu Nome]
 * Descrição: Implementação de uma fila circular para gerenciar as próximas peças
 * do jogo Tetris Stack utilizando Structs e Arrays.
 * Data: 2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Necessário para gerar números aleatórios (srand, rand)

// --- Definições e Constantes ---
#define TAM_MAX 5 // Tamanho fixo da fila de peças futuras

// --- Estruturas de Dados ---

// Representa uma peça individual do Tetris
typedef struct {
    char nome; // Tipo da peça: 'I', 'O', 'T', 'L', 'J', 'S', 'Z'
    int id;    // Identificador único da peça
} Peca;

// Representa a Fila Circular
typedef struct {
    Peca itens[TAM_MAX]; // Array estático para armazenar as peças
    int inicio;          // Índice do elemento na frente da fila
    int fim;             // Índice onde o próximo elemento será inserido
    int total;           // Contador de elementos atuais na fila
} Fila;

// --- Protótipos das Funções ---
void inicializarFila(Fila *f);
Peca gerarPeca();
int filaCheia(Fila *f);
int filaVazia(Fila *f);
void inserirPeca(Fila *f); // Enqueue
void jogarPeca(Fila *f);   // Dequeue
void exibirFila(Fila *f);
void menu();

// --- Função Principal ---
int main() {
    Fila filaPecas;
    int opcao;

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Prepara a estrutura da fila
    inicializarFila(&filaPecas);

    // O jogo geralmente começa com a fila cheia de "próximas peças"
    printf("Inicializando sistema do Tetris Stack...\n");
    for(int i = 0; i < TAM_MAX; i++) {
        inserirPeca(&filaPecas);
    }

    // Loop principal do jogo (Game Loop simplificado)
    do {
        exibirFila(&filaPecas);
        menu();
        scanf("%d", &opcao);
        
        // Limpeza de buffer simples para evitar loops infinitos em caso de erro de digitação
        fflush(stdin); 

        switch (opcao) {
            case 1:
                jogarPeca(&filaPecas);
                break;
            case 2:
                inserirPeca(&filaPecas);
                break;
            case 0:
                printf("Encerrando Tetris Stack. Ate logo!\n");
                break;
            default:
                printf("\n[!] Opcao invalida! Tente novamente.\n");
        }
        printf("\n---------------------------------------------------\n");

    } while (opcao != 0);

    return 0;
}

// --- Implementação das Funções ---

// Inicializa os ponteiros lógicos da fila
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

// Gera uma peça aleatória com ID incremental
Peca gerarPeca() {
    static int contadorId = 0; // Variável estática mantém valor entre chamadas
    char tipos[] = {'I', 'O', 'T', 'L', 'J', 'S', 'Z'};
    Peca nova;

    // Escolhe um tipo aleatório baseado no índice do array 'tipos'
    nova.nome = tipos[rand() % 7];
    nova.id = contadorId++;
    
    return nova;
}

// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return (f->total == TAM_MAX);
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return (f->total == 0);
}

// Enqueue: Adiciona uma nova peça ao final da fila
void inserirPeca(Fila *f) {
    if (filaCheia(f)) {
        printf("\n[AVISO] A fila de pecas esta cheia! Nao e possivel adicionar mais.\n");
        return;
    }

    Peca novaPeca = gerarPeca();

    // Insere na posição 'fim'
    f->itens[f->fim] = novaPeca;

    // Lógica Circular: Se chegar no final do array, volta para o 0
    f->fim = (f->fim + 1) % TAM_MAX;
    
    f->total++;
    
    // Mensagem opcional (pode comentar se quiser limpar a tela)
    // printf("Peca [%c %d] adicionada a fila.\n", novaPeca.nome, novaPeca.id);
}

// Dequeue: Remove a peça da frente (Joga a peça no tabuleiro)
void jogarPeca(Fila *f) {
    if (filaVazia(f)) {
        printf("\n[ERRO] Nao ha pecas na fila para jogar!\n");
        return;
    }

    Peca pecaJogada = f->itens[f->inicio];

    // Lógica Circular: Avança o início e volta para 0 se necessário
    f->inicio = (f->inicio + 1) % TAM_MAX;
    
    f->total--;

    printf("\n>>> Voce jogou a peca: [%c %d] <<<\n", pecaJogada.nome, pecaJogada.id);
}

// Exibe o estado atual da fila
void exibirFila(Fila *f) {
    if (filaVazia(f)) {
        printf("\nFila de pecas: [ VAZIA ]\n");
        return;
    }

    printf("\nFila de pecas: ");
    
    // Percorre a fila do início até o total de elementos
    // Usa aritmética modular para imprimir na ordem correta mesmo sendo circular
    int indiceAux;
    for (int i = 0; i < f->total; i++) {
        // Calcula a posição real no vetor baseada no deslocamento i
        indiceAux = (f->inicio + i) % TAM_MAX;
        
        printf("[%c %d] ", f->itens[indiceAux].nome, f->itens[indiceAux].id);
    }
    printf("\n");
}

// Mostra as opções para o usuário
void menu() {
    printf("\nOpcoes de acao:\n");
    printf("1 - Jogar peca (dequeue)\n");
    printf("2 - Inserir nova peca (enqueue)\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
}