#include "inimigo.h"
#include "player.h"
#include "raylib.h"
#include <stdlib.h>
#include <math.h>

// ============================
//  CRIAÇÃO DE INIMIGOS
// ============================

Inimigo *Criar_imimigos(float x, float y) {
    Inimigo *novo = malloc(sizeof(Inimigo));
    if (!novo){
        return NULL;
        
    } 

    novo ->pos = (Vector2){x, y};
    novo ->velocidade = 2.0f;
    novo ->hp = 3;  // Pontos de vida do inimigo
    novo ->sprite = LoadTexture("assets/enemy.png"); // Caminho da textura
    novo ->next = NULL;

    return novo;
}


//  MOVIMENTO DOS INIMIGOS


void mov_inimigos(Inimigo *head, Vector2 playerPos) {
    for (Inimigo *novo = head; novo != NULL; novo = novo->next) {
        Vector2 dir = {playerPos.x - novo->pos.x, playerPos.y - novo->pos.y};
        float len = sqrt(dir.x * dir.x + dir.y * dir.y);

        if (len != 0) {
            dir.x /= len;
            dir.y /= len;
        }

        novo ->pos.x += dir.x * novo ->velocidade;
        novo ->pos.y += dir.y * novo ->velocidade;
    }
}


//  DESENHO NA TELA

void Desenho_inimigos(Inimigo *head) {
    for (Inimigo *novo = head; novo != NULL; novo = novo->next) {
        DrawTexture(novo->sprite, novo->pos.x, novo->pos.y, WHITE);
    }
}

//  LIBERAÇÃO DE MEMÓRIA


void Liberar_memoria(Inimigo *head) {
    while (head) {
        Inimigo *temp = head;
        head = head->next;
        UnloadTexture(temp->sprite);
        free(temp);
    }
}


//  ADIÇÃO DE NOVOS INIMIGOS

void add_inimigo(Inimigo **head) {
    Inimigo *novo = Criar_imimigos(GetRandomValue(100, 700), GetRandomValue(100, 400));
    if (!novo){
        return;

    } 

    novo->next = *head;
    *head = novo;
}


//  COLISÃO JOGADOR E INIMIGOS

void Colisao(Player *player, Inimigo **Inimigos, int *moedas) {
    Inimigo *prev = NULL;
    Inimigo *curr = *Inimigos;

    while (curr != NULL) {
        Rectangle playerRect = {
            player->pos.x, player->pos.y,
            (float)player->sprite.width, (float)player->sprite.height
        };

        Rectangle enemyRect = {
            curr->pos.x, curr->pos.y,
            (float)curr->sprite.width, (float)curr->sprite.height
        };

        // Detecta colisão
        if (CheckCollisionRecs(playerRect, enemyRect)) {
            player->hp -= 1;  // jogador perde HP
            (*moedas)++;      // ganha uma moeda

            // Remove inimigo da lista
            if (prev == NULL) {
                *Inimigos = curr->next;
                UnloadTexture(curr->sprite);
                free(curr);
                curr = *Inimigos;
            } else {
                prev->next = curr->next;
                UnloadTexture(curr->sprite);
                free(curr);
                curr = prev->next;
            }
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
}


