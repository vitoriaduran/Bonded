#include "player.h"
#include <stdlib.h>
#include <math.h>

Player *CriarPlayer() { // se quiser que o personagem aparece em outra pos, adcionar parametros
    Player *p = malloc(sizeof(Player));
    p -> pos = (Vector2){400, 300};
    p -> velocidade = 4.0f;
    p -> hp = 5;
    p -> sprite = LoadTexture("assets/player.png"); //falta colocar
    p -> arma = LoadTexture("assets/sword.png"); //falta colocar 
    p -> ataque = 0;
    p ->armaHitbox = (Rectangle){p->pos.x, p->pos.y, 40, 40};
    return p;
}

void UpdatePlayer(Player *p) {
    if (IsKeyDown(KEY_W)) p -> pos.y -= p-> velocidade;
    if (IsKeyDown(KEY_S)) p -> pos.y += p-> velocidade;
    if (IsKeyDown(KEY_A)) p -> pos.x -= p-> velocidade;
    if (IsKeyDown(KEY_D)) p -> pos.x += p-> velocidade;

    if (IsKeyPressed(KEY_SPACE)) Ataque(p);
}

void Ataque(Player *p) {
    p -> ataque= 1;
    p -> armaHitbox = (Rectangle){p->pos.x + 20, p->pos.y, 40, 40};
}

void Desenho_player(Player *p) {
    DrawTexture(p->sprite, p->pos.x, p->pos.y, WHITE);
    if (p -> ataque) {
        DrawTexture(p -> arma, p->pos.x + 30, p->pos.y, WHITE);
        p -> ataque = 0;
    }
}

void Liberar_player(Player *p) {
    UnloadTexture(p -> sprite);
    UnloadTexture(p -> arma);
    free(p);
}
