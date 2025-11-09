#ifndef ENEMY_H
#define ENEMY_H
#include "raylib.h"
#include "player.h"

typedef struct Inimigo {
    Vector2 pos;
    float velocidade;
    int hp;
    Texture2D sprite;
    struct Inimigo *next;
} Inimigo;

Inimigo *Criar_imimigos(float x, float y);
void mov_inimigos(Inimigo *head, Vector2 playerPos);
void Desenho_inimigos(Inimigo *head);
void add_inimigo(Inimigo **head);
void Colisao(Player *player, Inimigo **Inimigos, int *moedas);
void Liberar_memoria(Inimigo *head);

#endif
