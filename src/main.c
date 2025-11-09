#include <raylib.h>

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
    InitWindow(800, 450, "Bonded");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Raylib funcionando!", 280, 200, 20, LIGHTGRAY);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

