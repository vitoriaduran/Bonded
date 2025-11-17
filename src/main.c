#include <raylib.h>
#include<game.h>

typedef struct protagonista{
    Vector2 position;
    Vector2 target_position;
    float speed;

    int vidas;
    int moedas;
    int forca;

    int frame_atual;
    int contador_frames;
    int loop_frames;
    int frames_por_loop;
    bool movimento;
} protagonista;





int main() {


    InitWindow(800, 600, "Bonded - MVP");

    const int screenWidth = 800;
    const int screenHeight = 600;
    
    InitWindow(screenWidth, screenHeight, "Bonded - MVP");

    InitAudioDevice();
    SetTargetFPS(60);

    Vector2  posicao_protagonista= { (float)screenWidth/2, (float)screenHeight/2 };
    
    Game *game = InitGame();

    while (!WindowShouldClose()) {
        UpdateGame(game);

        if (game->gameOver && IsKeyPressed(KEY_ENTER)) {
            Liberar_Game(game);
            game = InitGame();
        }

        if (IsKeyDown(KEY_RIGHT)) posicao_protagonista.x += 2.0f;
        if (IsKeyDown(KEY_LEFT)) posicao_protagonista.x -= 2.0f;
        if (IsKeyDown(KEY_UP)) posicao_protagonista.y -= 2.0f;
        if (IsKeyDown(KEY_DOWN)) posicao_protagonista.y += 2.0f;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        Desenho_Game(game);
        DrawCircleV(posicao_protagonista, 50, RED);
        EndDrawing();
    }

    Liberar_Game(game);
    CloseAudioDevice();
    CloseWindow();
    return 0;
} 

