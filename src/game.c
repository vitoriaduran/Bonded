#include "game.h"
#include "player.h"
#include "inventario.h"
#include <stdio.h>
#include <stdlib.h>

Game *InitGame() {
    Game *game = (Game *)malloc(sizeof(Game));
    if (!game){
        return NULL;

    }

    game->player = CriarPlayer();
    game->inventario = CreateInventory();


    // Nenhum inimigo ainda (será criado por fase)
    game->listainimigos = NULL;

    // Carrega os fundos das fases
    game->fases[0].background = LoadTexture("assets/background_fase1.png"); //falta a sprint
    game->fases[1].background = LoadTexture("assets/background_fase2.png"); //falta a sprint
    game->fases[2].background = LoadTexture("assets/background_fase3.png"); //falta a sprint
    game->fases[3].background = LoadTexture("assets/background_fase4.png"); //falta a sprint 
    game->fases[4].background = LoadTexture("assets/background_fase5.png"); //falta a sprint

    // Configuração de cada fase
    game->fases[0].qtninimigos = 3;  game->fases[0].tempolimite = 50.0f;
    game->fases[1].qtninimigos = 5;  game->fases[1].tempolimite = 45.0f;
    game->fases[2].qtninimigos = 7;  game->fases[2].tempolimite = 40.0f;
    game->fases[3].qtninimigos = 9;  game->fases[3].tempolimite = 35.0f;
    game->fases[4].qtninimigos = 12; game->fases[4].tempolimite = 30.0f;

    // Inicia a primeira fase
    game->faseAtual = 0;
    game->tempo = game->fases[0].tempolimite;
    game->moedas = 0;
    game->gameOver = false;

    // Cria os inimigos iniciais
    for (int i = 0; i < game->fases[0].qtninimigos; i++) {
        add_inimigo(&(game->listainimigos));
    }

    return game;
}

void UpdateGame(Game *game) {

    if (game->gameOver){

        return;
    }
    float dt = GetFrameTime();

    // Atualiza o tempo
    game->tempo -= dt;
    if (game->tempo <= 0) {
        game->gameOver = true;
        return;
    }

    // Movimentação do jogador
    UpdatePlayer(game->player);

    // Atualiza inimigos (seguem o jogador)
    mov_inimigos(game->listainimigos, game->player->pos);

    // Verifica colisões jogador e inimigos
    Colisao(game->player, &(game->listainimigos), &(game->moedas));

    // Verifica se todos os inimigos foram derrotados
    if (game->listainimigos == NULL) {
        game -> faseAtual +=1 ;
        if (game ->  faseAtual >= 5) {
            // Todas as fases vencidas
            game->gameOver = true;
        } else {
            // Passa para a próxima fase
            game -> tempo = game -> fases[game->faseAtual].tempolimite;

            // Cria novos inimigos
            for (int i = 0; i < game->fases[game->faseAtual].qtninimigos; i++) {
                add_inimigo(&( game -> listainimigos));
            }
        }
    }
}

void Desenho_Game(Game *game) {
    BeginDrawing();
    ClearBackground(BLACK);

    if (!game->gameOver) {
        // Fundo da fase atual
        DrawTexture(game->fases[game->faseAtual].background, 0, 0, WHITE);

        // Desenha o jogador e inimigos
        Desenho_player(game->player);
        Desenho_inimigos(game->listainimigos);

        // HUD (tempo e moedas)
        DrawText(TextFormat("Tempo: %.0f", game->tempo), 20, 20, 24, WHITE);
        DrawText(TextFormat("Moedas: %d", game->moedas), 20, 50, 24, YELLOW);
        DrawText(TextFormat("Fase: %d/5", game->faseAtual + 1), 20, 80, 24, GREEN);

    } else {
        if (game->faseAtual >= 5)
            DrawText("Você salvou sua amiga!", 200, 300, 30, GREEN);
        else
            DrawText("Você falhou... sua amiga morreu", 180, 300, 30, RED);

        DrawText("Pressione ENTER para reiniciar", 220, 400, 20, GRAY);
    }

    EndDrawing();
}

void Liberar_Game(Game *game) {
    if (!game){

        return;
    } 

    // Libera as texturas de fundo
    for (int i = 0; i < 5; i++) {
        UnloadTexture(game->fases[i].background);
    }

    // Libera jogador, inimigos e inventário
    Liberar_player(game->player);
    Liberar_memoria(game->listainimigos);
    Liberar_Inventario(game->inventario);

    free(game);
}
