#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"

typedef enum
{
    IDLE = 0,
    WALK_UP,
    WALK_LEFTH,
    WALK_RIGHT,
    WALK_DOWN
}PlayerState;

typedef struct {
    Vector2 pos;
    float velocidade;
    int hp;
    Texture2D spritesheet; 
    Rectangle frameRec;      // Recorte da sprite atual
    int frameWidth;          // Largura de um único frame
    int frameHeight;         // Altura de um único frame
    PlayerState estadoAtual; // Estado atual do player (IDLE, WALK, etc.)
    int currentFrame;        // Frame atual da animação
    int contador_frames;     // Contador para controle de velocidade da animação
    int velocidade_frames;   // FPS da animação
    int MAX_frames;          // Máximo de frames para o estado atual

    Texture2D arma;
    Rectangle armaHitbox; //saber se o golpe foi certo
    int ataque;
} Player;

Player *CriarPlayer();
void UpdatePlayer(Player *p);
void Desenho_player(Player *p);
void Ataque(Player *p);

#endif

