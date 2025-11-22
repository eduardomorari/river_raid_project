#include <stdio.h>
#include "raylib.h"
#include <string.h>


void AtualizarNave( int *x, Texture2D texture,
                    Rectangle reto, Rectangle esquerda, Rectangle direita,
                    float scale)
{
    // Movimento para a esquerda
    if (IsKeyDown(KEY_A) && *x > 0 && !(IsKeyDown(KEY_D)))
    {
        *x -= 4;
        DrawTexturePro(
            texture,
            esquerda,
            (Rectangle)
        {
            (float)*x, 300.0f, esquerda.width * scale, esquerda.height * scale
        },
        (Vector2)
        {
            0, 0
        },
        0.0f,
        WHITE
        );
    }
    // Movimento para a direita
    else if (IsKeyDown(KEY_D) && *x < 755 && !(IsKeyDown(KEY_A)))
    {
        *x += 4;
        DrawTexturePro(
            texture,
            direita,
            (Rectangle)
        {
            (float)*x, 300.0f, direita.width * scale, direita.height * scale
        },
        (Vector2)
        {
            0, 0
        },
        0.0f,
        WHITE
        );
    }
    // Parado
    else
    {
        DrawTexturePro(
            texture,
            reto,
            (Rectangle)
        {
            (float)*x, 300.0f, reto.width * scale, reto.height * scale
        },
        (Vector2)
        {
            0, 0
        },
        0.0f,
        WHITE
        );
    }
}

int main(void)
{
    int menu = 0;
    const int screenWidth = 800;
    const int screenHeight = 450;
    int x = 380;
    int tempo = 0;
    float maxcombustivel = 500.0;

    const Color COR_FUNDO = { 40, 44, 175, 255 };
    const Color INTERFACE_COR = {131, 131, 131, 255};


    //tamanho reto
    const int naveRetoWidth = 55;
    const int naveRetoHeight = 51;
    //tamanho esquerda
    const int naveEsquerdaWidth = 40;
    const int naveEsquerdaHeight = 56;
    //tamanho direita
    const int naveDireitaWidth = 40;
    const int naveDireitaHeight = 56;
    //interface combustivel
    const int medidorCombustivelWidth = 328;
    const int medidorCombustivelHeight = 78;
    //indicador quantidade combustivel
    const int ponteiroMedidorWidth = 16;
    const int ponteiroMedidorHeight = 40;

    InitWindow(screenWidth, screenHeight, "River INF");
    SetTargetFPS(60);

    Texture2D texture_spritesheet = LoadTexture("./assets/sprites.png");

    Rectangle naveRetoSource = { 104.0f, 71.0f, (float)naveRetoWidth, (float)naveRetoHeight };
    Rectangle naveEsquerdaSource = { 51.0f, 74.0f, (float)naveEsquerdaWidth, (float)naveEsquerdaHeight };
    Rectangle naveDireitaSource = { 171.0f, 74.0f, (float)naveDireitaWidth, (float)naveDireitaHeight };
    Rectangle interfacePlayer = {286.0f, 262.0f,(float)medidorCombustivelWidth, (float)medidorCombustivelHeight };
    Rectangle ponteiroMedidor = {615.0f, 282.0f, (float)ponteiroMedidorWidth, (float)ponteiroMedidorHeight };
    float scale = 0.8f;

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();

        switch(menu)
        {
        // MENU INICIAL
        case 0:
            maxcombustivel = 500.0;
            tempo = 0;
            x = 380;
            BeginDrawing();
            ClearBackground(COR_FUNDO);

            DrawText("RIVER INF", 270, 80, 50, YELLOW);
            DrawRectangle(300, 175, 200, 50, YELLOW);
            DrawText("Novo jogo", 350, 190, 20, BLACK);
            DrawText(TextFormat("X: %i Y: %i", (int)mouse.x, (int)mouse.y), 20, 420, 20, BLACK);

            EndDrawing();

            if (mouse.x >= 300 && mouse.x <= 500 &&
                    mouse.y >= 175 && mouse.y <= 225 &&
                    IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                menu = 1;
            }
            break;

        // JOGO
        case 1:
            tempo++;
            maxcombustivel=maxcombustivel-0.25;
            BeginDrawing();
            ClearBackground(COR_FUNDO);

            DrawRectangle(10, 10, 200, 50, YELLOW);
            DrawText("pause", 70, 25, 25, BLACK);


            // FUNCIONALIDADES NAVE
            AtualizarNave(
                &x,
                texture_spritesheet,
                naveRetoSource,
                naveEsquerdaSource,
                naveDireitaSource,
                scale
            );
            DrawRectangle(0, 380, 800, 70, INTERFACE_COR);

            // DESENHA MEDIDOR DE COMBUSTÍVEL
            DrawTexturePro(
                texture_spritesheet,
                interfacePlayer,
                (Rectangle)
            {
                200.0f, 380.0f, medidorCombustivelWidth, medidorCombustivelHeight
            },
            (Vector2)
            {
                0, 0
            },
            0.0f,
            WHITE
            );
            //
            // DESENHA PONTEIRO MEDIDOR COMBUSTÍVEL
            if(maxcombustivel>218)
            {
                DrawTexturePro(
                    texture_spritesheet,
                    ponteiroMedidor,
                    (Rectangle)
                {
                    maxcombustivel, 380.0f, ponteiroMedidorWidth, ponteiroMedidorHeight
                },
                (Vector2)
                {
                    0, 0
                },
                0.0f,
                WHITE
                );
            }
            else
            {
                menu = 3;
            }
            //

            DrawText(TextFormat("X: %i Y: %i", (int)mouse.x, (int)mouse.y), 20, 420, 20, BLACK);
            DrawText(TextFormat("Tempo: %i", (int)tempo/60), 650, 420, 20, BLACK);
            EndDrawing();

            if (mouse.x >= 10 && mouse.x <= 210 &&
                    mouse.y >= 10 && mouse.y <= 60 &&
                    IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                menu = 2;
            }
            break;

        // PAUSADO
        case 2:
            BeginDrawing();
            DrawText("JOGO PAUSADO", 220, 80, 50, RAYWHITE);

            DrawRectangle(300, 175, 200, 50, YELLOW);
            DrawText("Continuar", 350, 190, 20, BLACK);

            DrawRectangle(300, 250, 200, 50, YELLOW);
            DrawText("Sair do jogo", 340, 270, 20, BLACK);

            EndDrawing();

            if (mouse.x >= 300 && mouse.x <= 500 &&
                    mouse.y >= 250 && mouse.y <= 300 &&
                    IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                menu = 0;
            }
            if (mouse.x >= 300 && mouse.x <= 500 &&
                    mouse.y >= 175 && mouse.y <= 225 &&
                    IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                menu = 1;
            }
            break;
        case 3:
            BeginDrawing();
            DrawText("VOCE PERDEU", 220, 80, 50, RED);
            DrawRectangle(300, 175, 200, 50, YELLOW);
            DrawText("Voltar ao menu", 325, 190, 20, BLACK);
            EndDrawing();
            if (mouse.x >= 300 && mouse.x <= 500 &&
                    mouse.y >= 175 && mouse.y <= 225 &&
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
