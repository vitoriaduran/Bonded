#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"

typedef struct {
    Vector2 pos;
    float velocidade;
    int hp;
    Texture2D sprite;
    Texture2D arma;
    Rectangle armaHitbox; //saber se o golpe foi certo
    int ataque;
} Player;

Player *CriarPlayer();
void UpdatePlayer(Player *p);
void Desenho_player(Player *p);
void Ataque(Player *p);

#endif
