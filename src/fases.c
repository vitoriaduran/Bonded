#include "fases.h"
#include <stdlib.h>
#include "raylib.h"

Fase *CarregarFase(int id) {
    Fase *fase = malloc(sizeof(Fase));
    fase->id = id;
    fase->concluida = false;

    // Carrega o fundo da fase
    if (id == 1) {
        fase->background = LoadTexture("assets/backgrounds/floresta.png");
        fase->playerStart = (Vector2){100, 300};

        // Cria alguns inimigos na floresta
        Inimigo *novo1 = Criar_inimigo(400, 300);
        Inimigo *novo2 = Criar_inimigo(600, 200);
        novo1->next = novo2;
        fase->inimigos = novo1;
    }
    else if (id == 2) {
        fase->background = LoadTexture("assets/backgrounds/caverna.png"); //falta sprint
        fase->playerStart = (Vector2){80, 350};

        Inimigo *novo1 = Criar_inimigo(500, 250);
        fase->inimigos = novo1;
    }
    else {
        fase->background = LoadTexture("assets/backgrounds/default.png"); //falta sprint
        fase->playerStart = (Vector2){50, 50};
        fase->inimigos = NULL;
    }

    return fase;
}

void AtualizarFase(Fase *fase, Vector2 playerPos) {
    if (fase == NULL){
        return;

    }
  

    mov_inimigos(fase->inimigos, playerPos);

    // Exemplo de condição para "terminar" a fase
    if (playerPos.x > 750) {
        fase->concluida = true;
    }
}

void DesenharFase(Fase *fase) {
    if (fase == NULL){
        return;

    } 

    // Desenha o fundo
    DrawTexture(fase->background, 0, 0, WHITE);

    // Desenha inimigos
    Desenho_inimigos(fase->inimigos);
}

void LiberarFase(Fase *fase) {
    if (fase == NULL) return;

    UnloadTexture(fase->background);
    Liberar_memoria(fase->inimigos);
    free(fase);
}
