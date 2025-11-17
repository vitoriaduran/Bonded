#include <stdlib.h>
#include <math.h>
#include "raylib.h"
#include "raymath.h"
#include "player.h"

Player *CriarPlayer() {
    Player *p = malloc(sizeof(Player));

    p->frameWidth  = 64;   // Ajuste para o tamanho REAL da sua sprite
    p->frameHeight = 64;

    p->estadoAtual = IDLE;
    p->currentFrame = 0;
    p->contador_frames = 0;
    p->velocidade_frames = 6;
    p->MAX_frames = 4;

    p->pos = (Vector2){400, 300};
    p->velocidade = 240.0f;
    p->hp = 5;

    p->spritesheet = LoadTexture("assets/player.png");
    p->arma = LoadTexture("assets/sword.png");

    p->ataque = 0;
    p->armaHitbox = (Rectangle){p->pos.x + 20, p->pos.y, 40, 40};

    p->frameRec = (Rectangle){0, 0, p->frameWidth, p->frameHeight};
    return p;
}

void UpdatePlayer(Player *p) {
    Vector2 movimento = {0, 0};

    // WASD
    if (IsKeyDown(KEY_D)) movimento.x = 1;
    else if (IsKeyDown(KEY_A)) movimento.x = -1;

    if (IsKeyDown(KEY_S)) movimento.y = 1;
    else if (IsKeyDown(KEY_W)) movimento.y = -1;

    // Movimento
    if (movimento.x != 0 || movimento.y != 0) {
        movimento = Vector2Normalize(movimento);
        p->pos.x += movimento.x * p->velocidade * GetFrameTime();
        p->pos.y += movimento.y * p->velocidade * GetFrameTime();
    }

    // Atualizar hitbox da arma
    p->armaHitbox.x = p->pos.x + 20;
    p->armaHitbox.y = p->pos.y;

    // Direção da animação
    float stateY = 0.0f;

    if (movimento.x != 0 || movimento.y != 0) {
        p->estadoAtual = WALK_DOWN;
        p->MAX_frames = 4;

        if (fabs(movimento.y) > fabs(movimento.x)) {
            if (movimento.y < 0) stateY = 1.0f;   // UP
            else stateY = 0.0f;                  // DOWN
        } else {
            if (movimento.x < 0) stateY = 2.0f;  // LEFT
            else stateY = 3.0f;                  // RIGHT
        }

    } else {
        p->estadoAtual = IDLE;
        stateY = 0.0f;
        p->MAX_frames = 4;
    }

    // Controle de FPS da animação
    p->contador_frames++;
    if (p->contador_frames >= (60 / p->velocidade_frames)) {
        p->contador_frames = 0;
        p->currentFrame++;

        if (p->currentFrame >= p->MAX_frames)
            p->currentFrame = 0;
    }

    p->frameRec.x = (float)p->currentFrame * p->frameWidth;
    p->frameRec.y = stateY * p->frameHeight;

    // Ataque
    if (IsKeyPressed(KEY_SPACE))
        Ataque(p);

    if (p->ataque > 0)
        p->ataque--;
}

void Ataque(Player *p) {
    p->ataque = 10; // duração em frames
}

void Desenho_player(Player *p) {
    DrawTextureRec(
        p->spritesheet,
        p->frameRec,
        p->pos,
        WHITE
    );

    // Desenhar arma se estiver atacando
    if (p->ataque > 0) {
        DrawTextureV(
            p->arma,
            (Vector2){p->pos.x + 30, p->pos.y},
            WHITE
        );
        // hitbox acompanha o ataque
        p->armaHitbox.x = p->pos.x + 30;
        p->armaHitbox.y = p->pos.y;
    }
}

void Liberar_player(Player *p) {
    UnloadTexture(p->spritesheet);
    UnloadTexture(p->arma);
    free(p);
}

