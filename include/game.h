#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "inimigo.h"
#include "inventario.h"
#include "save.h"
#include "raylib.h"

// Estrutura para definir cada fase (nível do jogo)
typedef struct {
    Texture2D background;   // Imagem de fundo da fase
    int qtninimigos;         // Quantidade de inimigos na fase
    float tempolimite;        // Tempo máximo para completar a fase
} Fase;

// Estrutura principal do jogo
typedef struct {
    Player *player;         // Ponteiro para o jogador
    Inimigo *listainimigos;       // Lista encadeada de inimigos
    Inventario *inventario;   // Ponteiro para o inventário do jogador
    Fase fases[5];          // Array de 5 fases (para o MVP)
    int faseAtual;          // Índice da fase atual (0–4)
    float tempo;            // Contador do tempo atual
    int moedas;             // Moedas coletadas
    bool gameOver;          // Indica se o jogo acabou
} Game;

// Funções principais do ciclo do jogo
Game *InitGame();           // Inicializa o jogo (carrega fases, jogador etc.)
void UpdateGame(Game *game);// Atualiza lógica do jogo (movimento, combate, tempo)
void Desenho_Game(Game *game);  // Desenha tudo na tela
void Liberar_Game(Game *game);// Libera texturas e memória
void Liberar_player(Player *player);
void Liberar_Inventario(Inventario *inv);


#endif
