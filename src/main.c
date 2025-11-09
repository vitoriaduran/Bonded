#include "raylib.h"
#include "game.h"

int main() {
    InitWindow(800, 600, "Bonded - MVP");
    InitAudioDevice();
    SetTargetFPS(60);

    Game *game = InitGame();

    while (!WindowShouldClose()) {
        UpdateGame(game);

        if (game -> gameOver && IsKeyPressed(KEY_ENTER)){
            Liberar_Game(game);
            game = InitGame();
        }
        BeginDrawing();
        Desenho_Game(game);
        EndDrawing();
    }

    Liberar_Game(game);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}


