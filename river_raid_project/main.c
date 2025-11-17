#include <stdio.h>
#include "raylib.h"

int main(void)
{
    int menu = 0;
    const int screenWidth = 800;
    const int screenHeight = 450;
    int x = 380;

    const Color COR_FUNDO = { 40, 44, 175};

    //tamanho reto
    const int naveRetoWidth = 55;
    const int naveRetoHeight = 51;
    //tamanho esquerda
    const int naveEsquerdaWidth = 40;
    const int naveEsquerdaHeight = 56;
    //tamanho direita
    const int naveDireitaWidth = 40;
    const int naveDireitaHeight = 56;

    InitWindow(screenWidth, screenHeight, "Jogo do djabo");
    SetTargetFPS(60);


    Texture2D texture_spritesheet = LoadTexture("./assets/sprites.png");

    Rectangle naveRetoSource = { 104.0f, 71.0f, (float)naveRetoWidth, (float)naveRetoHeight };
    Rectangle naveEsquerdaSource = { 51.0f, 74.0f, (float)naveEsquerdaWidth, (float)naveEsquerdaHeight };
    Rectangle naveDireitaSource = { 171.0f, 74.0f, (float)naveDireitaWidth, (float)naveDireitaHeight };



    float scale = 1.0f;

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();

        switch(menu)
        {
        case 0:

            BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawRectangle(300, 175, 200, 50, BLACK);
            DrawText("Jogar", 375, 190, 20, GRAY);
            DrawText(TextFormat("X: %i Y: %i", (int)mouse.x, (int)mouse.y), 20, 420, 20, GRAY);

            EndDrawing();

            if (mouse.x >= 300 && mouse.x <= 500 &&
                    mouse.y >= 175 && mouse.y <= 225 &&
                    IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                menu = 1;
            }
            break;

        case 1:



            BeginDrawing();
            ClearBackground(COR_FUNDO);

            DrawRectangle(10, 10, 200, 50, BLACK);
            DrawText("Menu", 70, 25, 25, GRAY);

            // TROCAR SPRITES DE ACORDO COM DIREÇÃO
            if (IsKeyDown(KEY_A) && x > 0)
            {
                x -= 4;
                DrawTexturePro(
                    texture_spritesheet,
                    naveEsquerdaSource,
                    (Rectangle)
                {
                    (float)x, 350.0f, naveEsquerdaSource.width * scale, naveEsquerdaSource.height * scale
                },
                (Vector2)
                {
                    0.0f, 0.0f
                },
                0.0f,
                WHITE
                );
            }
            else if (IsKeyDown(KEY_D) && x < 745)
            {
                x += 4;
                DrawTexturePro(
                    texture_spritesheet,
                    naveDireitaSource,
                    (Rectangle)
                {
                    (float)x, 350.0f, naveDireitaSource.width * scale, naveDireitaSource.height * scale
                },
                (Vector2)
                {
                    0.0f, 0.0f
                },
                0.0f,
                WHITE
                );
            }
            else
            {
                DrawTexturePro(
                    texture_spritesheet,
                    naveRetoSource,
                    (Rectangle)
                {
                    (float)x, 350.0f, naveRetoSource.width * scale, naveRetoSource.height * scale
                },
                (Vector2)
                {
                    0.0f, 0.0f
                },
                0.0f,
                WHITE
                );
            }


            DrawText(TextFormat("X: %i Y: %i", (int)mouse.x, (int)mouse.y), 20, 420, 20, GRAY);

            EndDrawing();

            if (mouse.x >= 10 && mouse.x <= 210 &&
                    mouse.y >= 10 && mouse.y <= 60 &&
                    IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                menu = 0;
            }
            break;
        }
    }

    UnloadTexture(texture_spritesheet);

    CloseWindow();
    return 0;
}
