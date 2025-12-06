#include <stdio.h>
#include "raylib.h"
#include <string.h>
#include <stdlib.h>

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 800
#define TAMANHO_GRADE 40

char mapa[20][24];
char arquivoMapa[20]= {"./maps/mapa1.txt"};

int chamafuncao = 0; //VARIAVEL DE CONTROLE PARA RANDOMIZAR SÓ A PARTIR DA SEGUNDA FASE.
int aleatorio = 0;

void CarregarMapa(const char *arquivoMapa, int *spawnx, int *spawny)
{
    chamafuncao++;

    FILE* fp = fopen(arquivoMapa, "r");

    if (fp == NULL)
    {
        printf("Erro\n");
    }

    char c;
    *spawnx = 0;
    *spawny = 0;

    for (int y = 0; y < 20; y++)
    {
        for (int x = 0; x < 24; x++)
        {
            c = fgetc(fp);

            aleatorio = rand()%100;

            if(c == 'T' && chamafuncao>1 && aleatorio>90 && x>4 && x<20)
            {
                c = ' ';
            }

            aleatorio = rand()%100;

            if(aleatorio>98 && c == 'T') //Gera as casinhas aleatoriamente pelo terreno.
            {
                c = 't';
            }

            aleatorio = rand()%100;

            //-----------------------------------------------------// Gera os inimigos aleatoriamente pela água, a partir da segunda chamada (segunda fase).
            if(c == ' ' && y<15 && aleatorio>95 && chamafuncao>1)  //
            {                                                      //
                c = 'X';                                           //
            }else if(chamafuncao>1 && c == 'X')                    //
            {                                                      //
                c = ' ';                                           //
            }                                                      //
            //-----------------------------------------------------//

            aleatorio = rand()%100;

            if(mapa[y+1][x] != 'T' && mapa[y+1][x] != 'X' && aleatorio>98 && c == ' ')
            {
                c = 'P';
            }

            if(c == 'A')
            {
                *spawnx = x*TAMANHO_GRADE;
                *spawny = y*TAMANHO_GRADE;
            }

            while (c == '\n')
                c = fgetc(fp);

            mapa[y][x] = c;
        }
    }
    fclose(fp);
}

void DesenharMapa(Texture2D texture, Rectangle inimigoSource, Rectangle gramaSource1, Rectangle gramaSource2, Rectangle postoSource)
{

    for (int y = 0; y < 20; y++)
    {
        for (int x = 0; x < 24; x++)
        {
            char c = mapa[y][x];
            int px = x * TAMANHO_GRADE;
            int py = y * TAMANHO_GRADE;

            if (c == 'T')
            {
                Rectangle destino = {(float)px, (float)py, (float)TAMANHO_GRADE, (float)TAMANHO_GRADE};
                DrawTexturePro(texture, gramaSource1, destino, (Vector2)
                {
                    0, 0
                }, 0.0f, WHITE);
            }
            if (c == 't')
            {
                Rectangle destino = {(float)px, (float)py, (float)TAMANHO_GRADE, (float)TAMANHO_GRADE};
                DrawTexturePro(texture, gramaSource2, destino, (Vector2)
                {
                    0, 0
                }, 0.0f, WHITE);
            }

            else if (c == 'P')
            {
                Rectangle destino = {(float)px, (float)py, (float)TAMANHO_GRADE, (float)70.0f};
                DrawTexturePro(texture, postoSource, destino, (Vector2)
                {
                    0, 0
                }, 0.0f, WHITE);
            }
            else if (c == 'A')
            {
                DrawRectangle(px, py, TAMANHO_GRADE, TAMANHO_GRADE, YELLOW);
            }
        }
    }
}

void DesenharInimigo(Texture2D texture, Rectangle srcInimigo)
{

    //            else if (c == 'X')
    //        {
    //            Rectangle destino = {(float)px, (float)py, (float)TAMANHO_GRADE, (float)TAMANHO_GRADE};
    //            DrawTexturePro(texture, inimigoSource, destino, (Vector2){0, 0}, 0.0f, WHITE);
    //        }

    Rectangle inimigo;
    inimigo.width  = srcInimigo.width * TAMANHO_GRADE;
    inimigo.height = srcInimigo.height * TAMANHO_GRADE;


    for (int y = 0; y < 20; y++)
    {
        for (int x = 0; x < 24; x++)
        {
            char c = mapa[y][x];
            int px = x * TAMANHO_GRADE;
            int py = y * TAMANHO_GRADE;

            if (c == 'X')
            {
                Rectangle destino = {(float)px, (float)py, (float)TAMANHO_GRADE, (float)TAMANHO_GRADE};
                DrawTexturePro(texture, srcInimigo, destino, (Vector2)
                {
                    0, 0
                }, 0.0f, WHITE);
            }

        }
    }

}

void AtualizarNave(int *velx, int *vely, Texture2D texture, Rectangle srcRet, Rectangle srcEsq, Rectangle srcDir, float escala)
{
    Rectangle movimento;
    movimento.width  = srcRet.width * escala;
    movimento.height = srcRet.height * escala;

    // esquerda
    if (IsKeyDown(KEY_A) && *velx > 0 && !IsKeyDown(KEY_D))
    {
        *velx -= 4;
        *vely -= 2;
        movimento.x = *velx;
        movimento.y = *vely;
        movimento.width  = srcEsq.width * escala;
        movimento.height = srcEsq.height * escala;
        DrawTexturePro(texture, srcEsq, movimento, (Vector2)
        {
            0, 0
        }, 0.0f, WHITE);

    }
    // direita
    else if (IsKeyDown(KEY_D) && *velx < (SCREEN_WIDTH - 30) && !IsKeyDown(KEY_A))
    {
        *velx += 4;
        *vely -= 2;
        movimento.x = *velx;
        movimento.y = *vely;
        movimento.width  = srcDir.width * escala;
        movimento.height = srcDir.height * escala;
        DrawTexturePro(texture, srcDir, movimento, (Vector2)
        {
            0, 0
        }, 0.0f, WHITE);

    }
    // reto
    else
    {
        *vely -= 2;
        movimento.x = *velx;
        movimento.y = *vely;
        DrawTexturePro(texture, srcRet, movimento, (Vector2)
        {
            0, 0
        }, 0.0f, WHITE);
    }
}

/*void tiro(int *x, int *y, Rectangle srcTiro, int escala, Texture2D texture)
{
    Rectangle trajeto;
    trajeto.width = srcTiro.width*escala;
    trajeto.height = srcTiro.height*escala;
    *y--;
    trajeto.x = *x;
    trajeto.y = *y;
    DrawTexturePro(texture, srcTiro, trajeto, (Vector2){0, 0}, 0.0f, WHITE);
}*/

int Botao(int x, int y, int w, int h, const char *texto)
{
    DrawRectangle(x, y, w, h, YELLOW);
    DrawText(texto, x + 20, y + 15, 20, BLACK);

    Vector2 m = GetMousePosition();
    return (m.x >= x && m.x <= x + w && m.y >= y && m.y <= y + h && IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
}



int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "River INF");
    SetTargetFPS(60);

    Texture2D texture = LoadTexture("./assets/sprites.png");

    // Srites cenario
    Rectangle grama1 = {335/*posX*/, 62/*posY*/, 128/*largura*/, 96/*altura*/};
    Rectangle grama2 = {467, 62, 128, 96};

    Rectangle posto = {611, 62, 56, 96};

    // Sprites nave
    Rectangle naveReto = {104, 71, 56, 52};
    Rectangle naveEsq = { 51, 74, 40, 56};
    Rectangle naveDir = {171, 74, 40, 56};
    Rectangle combIface = {286, 262, 328, 70};
    Rectangle combPonteiro = {615, 282, 16, 40};

    // Tiro
    Rectangle projetil = {23, 86, 8, 32};

    // Sprites inimigos
    Rectangle heli = {12, 186, 65, 40};
    Rectangle barco = {14, 234, 128, 32};

    const Color COR_FUNDO = {40, 44, 175, 255};
    const Color COR_IFACE = {131, 131, 131, 255};

    int x;
    int y;
    float escala = 0.5f;
    float nivel = 1.0f;
    int menu = 0;
    int tempo;
    int fase;
    int vidas;
    int pontuacao;
    float combustivel = 500.0f;

    int qtdcolisoes = 0; //VARIAVEL DE CONTROLE PARA EVIDAR DANO DUPLICADO QUE ACONTECIA DE BATESSE A INTERSECÇAO DAS HITBOXES

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(COR_FUNDO);
        Vector2 mouse = GetMousePosition();

        switch (menu)
        {


//#################################################################################################
//#################################################################################################


        case 0: // MENU
            combustivel = 625.0f;
            tempo = 0;
            fase = 1;
            vidas = 3;
            pontuacao = 0;
            DrawText("RIVER INF", 350, 150, 50, YELLOW);

            if (Botao(380, 225, 200, 50, "Novo jogo"))
            {
                chamafuncao = 0;
                CarregarMapa(arquivoMapa, &x, &y);
                menu = 1;
            }
            DrawText(TextFormat("X: %i  Y: %i", (int)mouse.x, (int)mouse.y), 20, 780, 20, BLACK);
            break;



//#################################################################################################
//#################################################################################################



        case 1: //JOGO
            tempo++;
            combustivel -= 0.25f;
            float hitbox_largura = naveReto.width * escala;
            float hitbox_altura = naveReto.height * escala;

            DesenharMapa(texture, heli, grama1, grama2, posto);
            DesenharInimigo(texture, heli);

            AtualizarNave(&x, &y, texture, naveReto, naveEsq, naveDir, escala);
            Rectangle nave_hitbox = {(float)x, (float)y, hitbox_largura, hitbox_altura};


            // botao pause
            if (IsKeyDown(KEY_ENTER))
            {
                menu = 2;
            }

            /*if(IsKeyDown(KEY_SPACE))
                {
                tiro(&x, &y, projetil, escala, texture);
                }*/

            // VERIFIQCA COLISOES
            for (int mapY = 0; mapY < 20; mapY++)
            {
                for (int mapX = 0; mapX < 24; mapX++)
                {
                    char c = mapa[mapY][mapX];
                    if (c == 'T')
                    {
                        Rectangle celula_hitbox = {(float)mapX * TAMANHO_GRADE, (float)mapY * TAMANHO_GRADE, TAMANHO_GRADE, TAMANHO_GRADE};
                        if (CheckCollisionRecs(nave_hitbox, celula_hitbox))
                        {
                            qtdcolisoes++; //VARIAVEL DE CONTROLE PARA EVIDAR DANO DUPLICADO QUE ACONTECIA DE BATESSE A INTERSECÇAO DAS HITBOXES.
                            if (qtdcolisoes>1)
                            {
                                qtdcolisoes = 0.5;//Gambiarra, mas funciona.
                            }
                            else
                            {
                                vidas -= qtdcolisoes;
                                CarregarMapa(arquivoMapa, &x, &y);
                                if(vidas == 0)
                                {
                                    menu = 3;
                                    break;
                                }
                            }
                        }
                    }

                    if (c == 'X')
                    {
                        Rectangle inimigo_hitbox = {(float)mapX * TAMANHO_GRADE, (float)mapY * TAMANHO_GRADE, TAMANHO_GRADE, TAMANHO_GRADE};
                        if (CheckCollisionRecs(nave_hitbox, inimigo_hitbox))
                        {
                            qtdcolisoes++;
                            if (qtdcolisoes>1)
                            {
                                qtdcolisoes = 0.5;
                            }
                            else
                            {
                                vidas -= qtdcolisoes;
                                CarregarMapa(arquivoMapa, &x, &y);
                                if(vidas == 0)
                                {
                                    menu = 3;
                                    break;
                                }
                            }
                        }

                    }

                    if (c == 'P')
                    {
                        Rectangle celula_hitbox = {(float)mapX * TAMANHO_GRADE, (float)mapY * TAMANHO_GRADE, TAMANHO_GRADE, TAMANHO_GRADE};
                        if(CheckCollisionRecs(nave_hitbox, celula_hitbox))
                        {
                            combustivel += 2.0f;
                            if(combustivel > 625.0f)
                            {
                                combustivel -= 2.0f;
                            }
                        }
                    }
                }
            }
            if (menu == 3) break;

            if(y<0)
            {
                fase += 1;
                CarregarMapa(arquivoMapa, &x, &y);
            }


            // INTERFACE COMBUSTIVEL
            DrawRectangle(0, 720, SCREEN_WIDTH, 80, COR_IFACE);
            DrawTexturePro(texture, combIface, (Rectangle)
            {
                320, 720, combIface.width, combIface.height
            }, (Vector2)
            {
                0,0
            }, 0.0f, WHITE);

            if (combustivel > 336)
            {
                DrawTexturePro(texture, combPonteiro,(Rectangle)
                {
                    combustivel, 720, combPonteiro.width, combPonteiro.height
                }, (Vector2)
                {
                    0,0
                }, 0.0f, WHITE);
            }
            else
            {
                menu = 3; // perdeu
            }

            DrawText(TextFormat("Nivel: %i", fase), 650, 770, 20, BLACK);
            DrawText(TextFormat("Vidas: %i", vidas), 650, 745, 20, GREEN);
            DrawText(TextFormat("Tempo: %i", tempo / 60), 650, 720, 20, BLACK);
            break;



//#################################################################################################
//#################################################################################################




        case 2: // JOGO PAUSADO
            DrawText("JOGO PAUSADO", 280, 150, 50, RAYWHITE);

            if (Botao(370, 225, 200, 50, "Continuar"))
                menu = 1;

            if (Botao(370, 300, 200, 50, "Sair do jogo"))
                menu = 0;
            break;



//#################################################################################################
//#################################################################################################



        case 3: // TELA DERROTA
            DrawText("VOCE PERDEU", 300, 220, 50, RED);
            DrawText(TextFormat("Tempo de sobrevivencia: %i segundos", tempo / 60), 300, 380, 20, RAYWHITE);
            DrawText(TextFormat("Nivel alcancado: %i", fase), 380, 430, 20, RAYWHITE);
            DrawText(TextFormat("Pontuacao: %i ptos", pontuacao), 380, 480, 20, RAYWHITE);
            if (Botao(380, 300, 200, 50, "Voltar ao menu"))
            {
                menu = 0;
            }
            break;
        }

        EndDrawing();
    }

    UnloadTexture(texture);
    CloseWindow();
    return 0;
}

