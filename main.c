#include "raylib.h"
char board[10] = {
    '|',
    '#',
    '#',
    '#',
    '#',
    '#',
    '#',
    '#',
    '#',
    '#',
};
int option = 0;                                  // * option 1 -> user wishes to play vs ai, option 2 -> user wishes to play vs another player
bool easy = false, medium = false, hard = false; // * vs ai difficulty options
bool menu = true, difficultyMenu = false;
bool game_on = false;
bool draw = false;

char current_player = 'X';

void switchPlayer() {
    if (current_player == 'X')
        current_player = 'O';
    else
        current_player = 'X';
}

int xScore = 0, oScore = 0;
void updateScore() {
    if (current_player == 'X')
        xScore++;
    else
        oScore++;
}
void checkWin() {
    // ! Check horizontally

    if ((board[1] == board[2] && board[2] == board[3] && board[1] != '#') ||
        (board[4] == board[5] && board[5] == board[6] && board[4] != '#') ||
        (board[7] == board[8] && board[8] == board[9] && board[7] != '#') ||
        // ! Check vertically
        (board[1] == board[4] && board[4] == board[7] && board[1] != '#') ||
        (board[2] == board[5] && board[5] == board[8] && board[2] != '#') ||
        (board[3] == board[6] && board[6] == board[9] && board[3] != '#') ||
        // ! Check diagonally
        (board[1] == board[5] && board[5] == board[9] && board[1] != '#') ||
        (board[3] == board[5] && board[5] == board[7] && board[3] != '#')) {
        updateScore();
        game_on = false;
    } else if (board[1] != '#' &&
               board[2] != '#' &&
               board[3] != '#' &&
               board[4] != '#' &&
               board[5] != '#' &&
               board[6] != '#' &&
               board[7] != '#' &&
               board[8] != '#' &&
               board[9] != '#') {
        game_on = false;
        draw = true;
    }
}
void clearBoard() {
    for (int i = 1; i < 10; i++)
        board[i] = '#';
}

int bestMove, bestScore, score;

int minimax(int depth, bool isMaximizing);

void findBestMove() {
    bestScore = -99999999;
    for (int i = 1; i < 10; i++) {
        if (board[i] == '#') {
            board[i] = 'X';
            score = minimax(0, true);
            board[i] = '#';
            if (score > bestScore) {
                bestScore = score;
                bestMove = i;
            }
        }
    }
}

int minimax(int depth, bool isMaximizing) {
    if (!game_on) {

        if (draw) {
            return 0;
        } else if (current_player == 'O' && !draw) {
            return 1;
        } else if (current_player == 'X' && !draw) {
            return -1;
        }
    }

    if (isMaximizing) {
        int bestScore = -99999999;
        for (int i = 1; i < 10; i++) {
            if (board[i] == '#') {
                board[i] = 'X';
                int score = minimax(depth + 1, false);
                board[i] = '#';

                if (score > bestScore) {
                    bestScore = score;
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 9999999;
        for (int i = 1; i < 10; i++) {
            if (board[i] == '#') {
                board[i] = 'O';
                int score = minimax(depth + 1, true);
                board[i] = '#';

                if (score < bestScore) {
                    bestScore = score;
                }
            }
        }
        return bestScore;
    }
}

int main() {
    InitWindow(800, 600, "Tic Tac Toe");
    SetWindowState(FLAG_VSYNC_HINT);
    SetExitKey(KEY_Q);

    Texture xTexture = LoadTexture("./resources/X.png");
    Texture oTexture = LoadTexture("./resources/O.png");

    Font menuFont = LoadFontEx("./resources/AovelSansRounded-rdDL.ttf", 100, 0, 0);
    Font menuButtonFont = LoadFontEx("./resources/AovelSansRounded-rdDL.ttf", 50, 0, 0);
    Font menuCopyrightFont = LoadFontEx("./resources/AovelSansRounded-rdDL.ttf", 25, 0, 0);
    Font gameOverFont = LoadFontEx("./resources/AovelSansRounded-rdDL.ttf", 55, 0, 0);
    Font buttonFont = LoadFontEx("./resources/AovelSansRounded-rdDL.ttf", 30, 0, 0); // * button and score share the same font

    const float width = GetScreenWidth(), height = GetScreenHeight(), gridLineThickness = 30;
    const float winnerLineThickness = 11;
    const char *winner = "";
    bool showGameOver = false, showWinnerLine = false;

    float textTimer = 1.7f, winnerLineTimer = 0.3f;
    while (!WindowShouldClose()) {
        if (option == 2) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && GetMouseX() < width / 3 && GetMouseY() < height / 3 && board[1] == '#' && game_on) {
                if (current_player == 'X') {
                    board[1] = 'X';
                } else {
                    board[1] = 'O';
                }
                checkWin();
                switchPlayer();
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && GetMouseX() < width / 3 * 2 + 10 && GetMouseX() > width / 3 + 20 && GetMouseY() < height / 3 && board[2] == '#' && game_on) {
                if (current_player == 'X') {
                    board[2] = 'X';
                } else {
                    board[2] = 'O';
                }
                checkWin();
                switchPlayer();
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && GetMouseX() > width / 3 * 2 + 20 && GetMouseY() < height / 3 && board[3] == '#' && game_on) {
                if (current_player == 'X') {
                    board[3] = 'X';
                } else {
                    board[3] = 'O';
                }
                checkWin();
                switchPlayer();
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && GetMouseX() < width / 3 && GetMouseY() > height / 3 && GetMouseY() < height / 3 * 2 && board[4] == '#' && game_on) {
                if (current_player == 'X') {
                    board[4] = 'X';
                } else {
                    board[4] = 'O';
                }
                checkWin();
                switchPlayer();
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && GetMouseX() > width / 3 && GetMouseX() < width / 3 * 2 && GetMouseY() > height / 3 && GetMouseY() < height / 3 * 2 && board[5] == '#' && game_on) {
                if (current_player == 'X') {
                    board[5] = 'X';
                } else {
                    board[5] = 'O';
                }
                checkWin();
                switchPlayer();
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && GetMouseX() > width / 3 * 2 && GetMouseY() > height / 3 && GetMouseY() < height / 3 * 2 && board[6] == '#' && game_on) {
                if (current_player == 'X') {
                    board[6] = 'X';
                } else {
                    board[6] = 'O';
                }
                checkWin();
                switchPlayer();
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && GetMouseX() < width / 3 && GetMouseY() > height / 3 * 2 && board[7] == '#' && game_on) {
                if (current_player == 'X') {
                    board[7] = 'X';
                } else {
                    board[7] = 'O';
                }
                checkWin();
                switchPlayer();
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && GetMouseX() > width / 3 && GetMouseX() < width / 3 * 2 && GetMouseY() > height / 3 * 2 && board[8] == '#' && game_on) {
                if (current_player == 'X') {
                    board[8] = 'X';
                } else {
                    board[8] = 'O';
                }
                checkWin();
                switchPlayer();
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && GetMouseX() > width / 3 * 2 && GetMouseY() > height / 3 * 2 && board[9] == '#' && game_on) {
                if (current_player == 'X') {
                    board[9] = 'X';
                } else {
                    board[9] = 'O';
                }
                checkWin();
                switchPlayer();
            }
        } else {
            // * Preplace the computer's moves

            if (current_player == 'X') {
                findBestMove();
                board[bestMove] = 'X';
                checkWin();
                switchPlayer();
            } else {

                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && GetMouseX() < width / 3 && GetMouseY() < height / 3 && board[1] == '#' && game_on) {
                    if (current_player == 'X') {
                        board[1] = 'X';
                    } else {
                        board[1] = 'O';
                    }
                    checkWin();
                    switchPlayer();
                }
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && GetMouseX() < width / 3 * 2 + 10 && GetMouseX() > width / 3 + 20 && GetMouseY() < height / 3 && board[2] == '#' && game_on) {
                    if (current_player == 'X') {
                        board[2] = 'X';
                    } else {
                        board[2] = 'O';
                    }
                    checkWin();
                    switchPlayer();
                }
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && GetMouseX() > width / 3 * 2 + 20 && GetMouseY() < height / 3 && board[3] == '#' && game_on) {
                    if (current_player == 'X') {
                        board[3] = 'X';
                    } else {
                        board[3] = 'O';
                    }
                    checkWin();
                    switchPlayer();
                }
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && GetMouseX() < width / 3 && GetMouseY() > height / 3 && GetMouseY() < height / 3 * 2 && board[4] == '#' && game_on) {
                    if (current_player == 'X') {
                        board[4] = 'X';
                    } else {
                        board[4] = 'O';
                    }
                    checkWin();
                    switchPlayer();
                }
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && GetMouseX() > width / 3 && GetMouseX() < width / 3 * 2 && GetMouseY() > height / 3 && GetMouseY() < height / 3 * 2 && board[5] == '#' && game_on) {
                    if (current_player == 'X') {
                        board[5] = 'X';
                    } else {
                        board[5] = 'O';
                    }
                    checkWin();
                    switchPlayer();
                }
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && GetMouseX() > width / 3 * 2 && GetMouseY() > height / 3 && GetMouseY() < height / 3 * 2 && board[6] == '#' && game_on) {
                    if (current_player == 'X') {
                        board[6] = 'X';
                    } else {
                        board[6] = 'O';
                    }
                    checkWin();
                    switchPlayer();
                }
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && GetMouseX() < width / 3 && GetMouseY() > height / 3 * 2 && board[7] == '#' && game_on) {
                    if (current_player == 'X') {
                        board[7] = 'X';
                    } else {
                        board[7] = 'O';
                    }
                    checkWin();
                    switchPlayer();
                }
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && GetMouseX() > width / 3 && GetMouseX() < width / 3 * 2 && GetMouseY() > height / 3 * 2 && board[8] == '#' && game_on) {
                    if (current_player == 'X') {
                        board[8] = 'X';
                    } else {
                        board[8] = 'O';
                    }
                    checkWin();
                    switchPlayer();
                }
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && GetMouseX() > width / 3 * 2 && GetMouseY() > height / 3 * 2 && board[9] == '#' && game_on) {
                    if (current_player == 'X') {
                        board[9] = 'X';
                    } else {
                        board[9] = 'O';
                    }
                    checkWin();
                    switchPlayer();
                }
            }
        }

        if (!game_on && !menu) {
            if (!draw) {
                /* Since after each marker is placed the player is switched, if the last marker was placed by player 1(X) and player 1
                wins the game, the current_player will be switched to Player 2 automatically so we need to check the opposite way  */
                winner = (current_player == 'X' ? "Game Over. Player 2 Wins" : "Game Over. Player 1 Wins");

            } else
                winner = "Game Over. Draw";
            textTimer -= GetFrameTime(), winnerLineTimer -= GetFrameTime();
            if (textTimer <= 0)
                showGameOver = true;
            if (winnerLineTimer <= 0)
                showWinnerLine = true;
        }

        BeginDrawing();

        // ! Draw menu

        if (menu) {
            ClearBackground(RAYWHITE);
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            DrawTextEx(menuFont, "Welcome to", (Vector2){160, 20}, 100, 10, BLACK);
            DrawTextEx(gameOverFont, "TIC TAC TOE", (Vector2){250, 110}, 55, 6, BLACK);
            DrawRectangle(0, 180, width, 5, BLACK);

            DrawRectangle(20, 230, 360, 80, LIGHTGRAY);
            DrawTextEx(menuButtonFont, "Play vs Computer", (Vector2){30, 245}, 50, 2, BLACK);
            if (GetMouseX() >= 20 && GetMouseX() <= 380 && GetMouseY() >= 230 && GetMouseY() <= 310) {
                DrawRectangle(20, 230, 360, 80, GRAY);
                DrawTextEx(menuButtonFont, "Play vs Computer", (Vector2){30, 245}, 50, 2, WHITE);
                SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    menu = false, option = 1;
                }
            }

            DrawRectangle(20, 340, 360, 80, LIGHTGRAY);
            DrawTextEx(menuButtonFont, "Play vs Friend", (Vector2){65, 355}, 50, 2, BLACK);
            if (GetMouseX() >= 20 && GetMouseX() <= 380 && GetMouseY() >= 340 && GetMouseY() <= 420) {
                DrawRectangle(20, 340, 360, 80, GRAY);
                DrawTextEx(menuButtonFont, "Play vs Friend", (Vector2){65, 355}, 50, 2, WHITE);
                SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    menu = false, game_on = true, option = 2;
                }
            }

            DrawRectangle(20, 450, 360, 80, LIGHTGRAY);
            DrawTextEx(menuButtonFont, "Exit Game", (Vector2){115, 465}, 50, 2, BLACK);
            if (GetMouseX() >= 20 && GetMouseX() <= 380 && GetMouseY() >= 450 && GetMouseY() <= 530) {
                DrawRectangle(20, 450, 360, 80, GRAY);
                DrawTextEx(menuButtonFont, "Exit Game", (Vector2){115, 465}, 50, 2, WHITE);
                SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    CloseWindow();
                }
            }

            DrawTextEx(menuCopyrightFont, "Developed by Patrik Benczik", (Vector2){490, height - 40}, 25, 2, BLACK);
        }
        if (!menu && option == 2) {
            ClearBackground(WHITE);
            if (IsKeyPressed(KEY_ESCAPE)) {
                game_on = false, menu = true, showGameOver = false, showWinnerLine = false, textTimer = 1.7f, winnerLineTimer = 0.3f;
                xScore = 0, oScore = 0;
                clearBoard();
            }
            // ! Grid drawing

            // ! Vertical lines
            DrawLineEx((Vector2){width / 3, 10}, (Vector2){width / 3, 590}, gridLineThickness, BLACK);
            DrawLineEx((Vector2){width / 3 * 2, 10}, (Vector2){width / 3 * 2, 590}, gridLineThickness, BLACK);

            // ! Horizontal Lines

            DrawLineEx((Vector2){10, height / 3}, (Vector2){790, height / 3}, gridLineThickness, BLACK);
            DrawLineEx((Vector2){10, height / 3 * 2}, (Vector2){790, height / 3 * 2}, gridLineThickness, BLACK);

            // ! Hover on square and Draw X and O for each square
            // * Top left Square (sq1)
            if (GetMouseX() < width / 3 && GetMouseY() < height / 3 && board[1] == '#' && game_on == true) {
                DrawRectangle(10, 10, width / 3 - 24, height / 3 - 25, LIGHTGRAY); // Draw a color-filled rectangle
            }

            if (board[1] == 'X') {
                DrawTexture(xTexture, 50, 10, RED);
            } else if (board[1] == 'O') {
                DrawTexture(oTexture, 50, 10, RED);
            }

            // * Top middle Square(sq2)
            if (GetMouseX() < width / 3 * 2 + 10 && GetMouseX() > width / 3 + 20 && GetMouseY() < height / 3 && board[2] == '#' && game_on == true) {
                DrawRectangle(width / 3 + 16, 10, 236, 175, LIGHTGRAY);
            }
            if (board[2] == 'X') {
                DrawTexture(xTexture, width / 2 - 85, 10, RED);
            } else if (board[2] == 'O') {
                DrawTexture(oTexture, width / 2 - 85, 10, RED);
            }

            // * Top right Square (sq3)
            if (GetMouseX() > width / 3 * 2 + 20 && GetMouseY() < height / 3 && board[3] == '#' && game_on == true) {
                DrawRectangle(width / 3 * 2 + 15, 10, 242, 175, LIGHTGRAY);
            }

            if (board[3] == 'X') {
                DrawTexture(xTexture, width - 220, 10, RED);
            } else if (board[3] == 'O') {
                DrawTexture(oTexture, width - 220, 10, RED);
            }

            // * Middle left Square(sq4)
            if (GetMouseX() < width / 3 && GetMouseY() > height / 3 && GetMouseY() < height / 3 * 2 && board[4] == '#' && game_on == true) {
                DrawRectangle(10, height / 3 + 15, width / 3 - 24, height / 3 - 30, LIGHTGRAY); // Draw a color-filled rectangle
            }
            if (board[4] == 'X') {
                DrawTexture(xTexture, 50, height / 2 - 85, RED);
            } else if (board[4] == 'O') {
                DrawTexture(oTexture, 50, height / 2 - 85, RED);
            }

            // * Middle center Square(sq5)
            if (GetMouseX() > width / 3 && GetMouseX() < width / 3 * 2 && GetMouseY() > height / 3 && GetMouseY() < height / 3 * 2 && board[5] == '#' && game_on == true) {
                DrawRectangle(width / 3 + 16, height / 2 - 85, 236, 170, LIGHTGRAY); // Draw a color-filled rectangle
            }
            if (board[5] == 'X') {
                DrawTexture(xTexture, width / 2 - 85, height / 2 - 85, RED);
            } else if (board[5] == 'O') {
                DrawTexture(oTexture, width / 2 - 85, height / 2 - 85, RED);
            }
            // * Right middle Square(sq6)
            if (GetMouseX() > width / 3 * 2 && GetMouseY() > height / 3 && GetMouseY() < height / 3 * 2 && board[6] == '#' && game_on == true) {
                DrawRectangle(width / 3 * 2 + 15, height / 2 - 85, 240, 170, LIGHTGRAY); // Draw a color-filled rectangle
            }
            if (board[6] == 'X') {
                DrawTexture(xTexture, width - 220, height / 2 - 85, RED);
            } else if (board[6] == 'O') {
                DrawTexture(oTexture, width - 220, height / 2 - 85, RED);
            }
            // * Left bottom Square(sq7)
            if (GetMouseX() < width / 3 && GetMouseY() > height / 3 * 2 && board[7] == '#' && game_on == true) {
                DrawRectangle(10, height - 185, 242, 175, LIGHTGRAY); // Draw a color-filled rectangle
            }
            if (board[7] == 'X') {
                DrawTexture(xTexture, 50, height - 175, RED);
            } else if (board[7] == 'O') {
                DrawTexture(oTexture, 50, height - 175, RED);
            }
            // * Middle bottom Square(sq8)
            if (GetMouseX() > width / 3 && GetMouseX() < width / 3 * 2 && GetMouseY() > height / 3 * 2 && board[8] == '#' && game_on == true) {
                DrawRectangle(width / 3 + 16, height - 185, 236, 175, LIGHTGRAY); // Draw a color-filled rectangle
            }
            if (board[8] == 'X') {
                DrawTexture(xTexture, width / 2 - 85, height - 175, RED);
            } else if (board[8] == 'O') {
                DrawTexture(oTexture, width / 2 - 85, height - 175, RED);
            }
            // * Right bottom Square(sq9)
            if (GetMouseX() > width / 3 * 2 && GetMouseY() > height / 3 * 2 && board[9] == '#' && game_on == true) {
                DrawRectangle(width / 3 * 2 + 15, height - 185, 242, 175, LIGHTGRAY); // Draw a color-filled rectangle
            }
            if (board[9] == 'X') {
                DrawTexture(xTexture, width - 220, height - 175, RED);
            } else if (board[9] == 'O') {
                DrawTexture(oTexture, width - 220, height - 175, RED);
            }

            // ! Display green line if someone wins
            if (!game_on && showWinnerLine) {
                if (board[1] == board[2] && board[2] == board[3] && board[1] != '#')
                    DrawLineEx((Vector2){17, height / 3 / 2}, (Vector2){780, height / 3 / 2}, winnerLineThickness, GREEN);
                else if (board[4] == board[5] && board[5] == board[6] && board[4] != '#')
                    DrawLineEx((Vector2){17, height / 2}, (Vector2){780, height / 2}, winnerLineThickness, GREEN);
                else if (board[7] == board[8] && board[8] == board[9] && board[7] != '#')
                    DrawLineEx((Vector2){17, height - 90}, (Vector2){780, height - 90}, winnerLineThickness, GREEN);
                else if (board[1] == board[4] && board[4] == board[7] && board[1] != '#')
                    DrawLineEx((Vector2){width / 3 / 2, 10}, (Vector2){width / 3 / 2, height - 10}, winnerLineThickness, GREEN);
                else if (board[2] == board[5] && board[5] == board[8] && board[2] != '#')
                    DrawLineEx((Vector2){width / 2, 10}, (Vector2){width / 2, 780}, winnerLineThickness, GREEN);
                else if (board[3] == board[6] && board[6] == board[9] && board[3] != '#')
                    DrawLineEx((Vector2){width / 3 * 2 + 135, 10}, (Vector2){width / 3 * 2 + 135, height - 10}, winnerLineThickness, GREEN);

                // * Special displays if player wins on the diagonals, depending on the winner's marker

                else if (board[1] == board[5] && board[5] == board[9] && board[1] == 'O')
                    DrawLineEx((Vector2){20, 10}, (Vector2){790, height - 10}, winnerLineThickness, GREEN);
                else if (board[3] == board[5] && board[5] == board[7] && board[3] == 'O')
                    DrawLineEx((Vector2){width - 20, 10}, (Vector2){10, height - 10}, winnerLineThickness, GREEN);
                else if (board[1] == board[5] && board[5] == board[9] && board[1] == 'X')
                    DrawLineEx((Vector2){73, 25}, (Vector2){width - 45, height - 10}, winnerLineThickness, GREEN);
                else if (board[3] == board[5] && board[5] == board[7] && board[3] == 'X')
                    DrawLineEx((Vector2){width - 65, 25}, (Vector2){55, height - 15}, winnerLineThickness, GREEN);
            }

            // ! Display game_over text and button
            if (showGameOver) {
                DrawRectangle(0, height / 3 - 10, width, 220, LIGHTGRAY);
                if (!draw)
                    DrawTextEx(gameOverFont, winner, (Vector2){150, height / 2 - 20}, 55, 1, BLACK);
                else
                    DrawTextEx(gameOverFont, winner, (Vector2){220, height / 2 - 20}, 55, 1, BLACK);

                // * Draw New Game Button
                DrawRectangle(width / 2 - 75, height / 2 + 50, 150, 30, GRAY);
                DrawTextEx(buttonFont, "New Game", (Vector2){width / 2 - 62.5, height / 2 + 50}, 30, 1, BLACK);

                if (GetMouseX() >= width / 2 - 75 && GetMouseX() <= width / 2 - 75 + 150 && GetMouseY() >= height / 2 + 50 && GetMouseY() <= height / 2 + 80) {
                    SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
                    DrawTextEx(buttonFont, "New Game", (Vector2){width / 2 - 62.5, height / 2 + 50}, 30, 1, RAYWHITE);
                } else
                    SetMouseCursor(MOUSE_CURSOR_DEFAULT);

                // * Draw Score
                DrawTextEx(buttonFont, TextFormat("Player 1 %i - ", xScore), (Vector2){width / 2 - 125, height / 2 - 70}, 30, 1, RED);
                DrawTextEx(buttonFont, TextFormat("%i Player 2", oScore), (Vector2){width / 2 + 10, height / 2 - 70}, 30, 1, RED);

                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && GetMouseX() >= width / 2 - 75 && GetMouseX() <= width / 2 - 75 + 150 && GetMouseY() >= height / 2 + 50 && GetMouseY() <= height / 2 + 80 && !game_on) {
                    game_on = true, draw = false;
                    showGameOver = false, showWinnerLine = false;
                    textTimer = 1.7f, winnerLineTimer = 0.3f;
                    SetMouseCursor(MOUSE_CURSOR_DEFAULT);
                    clearBoard();
                }
            }
        } else if (!menu && option == 1) {
            difficultyMenu = true;
            if (difficultyMenu) {
                ClearBackground(RAYWHITE);
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);

                DrawTextEx(menuFont, "Welcome to", (Vector2){160, 20}, 100, 10, BLACK);
                DrawTextEx(gameOverFont, "TIC TAC TOE", (Vector2){250, 110}, 55, 6, BLACK);
                DrawRectangle(0, 180, width, 5, BLACK);

                DrawTextEx(gameOverFont, "Choose difficulty", (Vector2){30, 200}, 55, 2, BLACK);

                DrawRectangle(20, 300, 320, 60, LIGHTGRAY);
                DrawTextEx(menuButtonFont, "Easy", (Vector2){140, 305}, 50, 2, BLACK);
                if (GetMouseX() >= 20 && GetMouseX() <= 340 && GetMouseY() >= 300 && GetMouseY() <= 360) {
                    DrawRectangle(20, 300, 320, 60, GRAY);
                    DrawTextEx(menuButtonFont, "Easy", (Vector2){140, 305}, 50, 2, WHITE);
                    SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        game_on = true;
                    }
                }

                DrawRectangle(20, 400, 320, 60, LIGHTGRAY);
                DrawTextEx(menuButtonFont, "Medium", (Vector2){110, 405}, 50, 2, BLACK);
                if (GetMouseX() >= 20 && GetMouseX() <= 340 && GetMouseY() >= 400 && GetMouseY() <= 460) {
                    DrawRectangle(20, 400, 320, 60, GRAY);
                    DrawTextEx(menuButtonFont, "Medium", (Vector2){110, 405}, 50, 2, WHITE);
                    SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        game_on = true;
                    }
                }

                DrawRectangle(20, 500, 320, 60, LIGHTGRAY);
                DrawTextEx(menuButtonFont, "Hard", (Vector2){140, 505}, 50, 2, BLACK);
                if (GetMouseX() >= 20 && GetMouseX() <= 340 && GetMouseY() >= 500 && GetMouseY() <= 560) {
                    DrawRectangle(20, 500, 320, 60, GRAY);
                    DrawTextEx(menuButtonFont, "Hard", (Vector2){140, 505}, 50, 2, WHITE);
                    SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        game_on = true, hard = true, difficultyMenu = false, option = 0, draw = false;
                        showGameOver = false, showWinnerLine = false;
                        textTimer = 1.7f, winnerLineTimer = 0.3f;
                        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
                        clearBoard();
                    }
                }
            }
            if (IsKeyPressed(KEY_ESCAPE)) {
                game_on = false, menu = true, showGameOver = false, showWinnerLine = false, textTimer = 1.7f, winnerLineTimer = 0.3f;
                xScore = 0, oScore = 0;
                clearBoard();
            }
        }
        // TODO AI pt hard mode -> minimax alg
        if (hard) {
            ClearBackground(RAYWHITE);
            // ! Grid drawing

            // ! Vertical lines
            DrawLineEx((Vector2){width / 3, 10}, (Vector2){width / 3, 590}, gridLineThickness, BLACK);
            DrawLineEx((Vector2){width / 3 * 2, 10}, (Vector2){width / 3 * 2, 590}, gridLineThickness, BLACK);

            // ! Horizontal Lines

            DrawLineEx((Vector2){10, height / 3}, (Vector2){790, height / 3}, gridLineThickness, BLACK);
            DrawLineEx((Vector2){10, height / 3 * 2}, (Vector2){790, height / 3 * 2}, gridLineThickness, BLACK);

            // ! Hover on square and Draw X and O for each square
            // * Top left Square (sq1)
            if (GetMouseX() < width / 3 && GetMouseY() < height / 3 && board[1] == '#' && game_on == true) {
                DrawRectangle(10, 10, width / 3 - 24, height / 3 - 25, LIGHTGRAY); // Draw a color-filled rectangle
            }

            if (board[1] == 'X') {
                DrawTexture(xTexture, 50, 10, RED);
            } else if (board[1] == 'O') {
                DrawTexture(oTexture, 50, 10, RED);
            }

            // * Top middle Square(sq2)
            if (GetMouseX() < width / 3 * 2 + 10 && GetMouseX() > width / 3 + 20 && GetMouseY() < height / 3 && board[2] == '#' && game_on == true) {
                DrawRectangle(width / 3 + 16, 10, 236, 175, LIGHTGRAY);
            }
            if (board[2] == 'X') {
                DrawTexture(xTexture, width / 2 - 85, 10, RED);
            } else if (board[2] == 'O') {
                DrawTexture(oTexture, width / 2 - 85, 10, RED);
            }

            // * Top right Square (sq3)
            if (GetMouseX() > width / 3 * 2 + 20 && GetMouseY() < height / 3 && board[3] == '#' && game_on == true) {
                DrawRectangle(width / 3 * 2 + 15, 10, 242, 175, LIGHTGRAY);
            }

            if (board[3] == 'X') {
                DrawTexture(xTexture, width - 220, 10, RED);
            } else if (board[3] == 'O') {
                DrawTexture(oTexture, width - 220, 10, RED);
            }

            // * Middle left Square(sq4)
            if (GetMouseX() < width / 3 && GetMouseY() > height / 3 && GetMouseY() < height / 3 * 2 && board[4] == '#' && game_on == true) {
                DrawRectangle(10, height / 3 + 15, width / 3 - 24, height / 3 - 30, LIGHTGRAY); // Draw a color-filled rectangle
            }
            if (board[4] == 'X') {
                DrawTexture(xTexture, 50, height / 2 - 85, RED);
            } else if (board[4] == 'O') {
                DrawTexture(oTexture, 50, height / 2 - 85, RED);
            }

            // * Middle center Square(sq5)
            if (GetMouseX() > width / 3 && GetMouseX() < width / 3 * 2 && GetMouseY() > height / 3 && GetMouseY() < height / 3 * 2 && board[5] == '#' && game_on == true) {
                DrawRectangle(width / 3 + 16, height / 2 - 85, 236, 170, LIGHTGRAY); // Draw a color-filled rectangle
            }
            if (board[5] == 'X') {
                DrawTexture(xTexture, width / 2 - 85, height / 2 - 85, RED);
            } else if (board[5] == 'O') {
                DrawTexture(oTexture, width / 2 - 85, height / 2 - 85, RED);
            }
            // * Right middle Square(sq6)
            if (GetMouseX() > width / 3 * 2 && GetMouseY() > height / 3 && GetMouseY() < height / 3 * 2 && board[6] == '#' && game_on == true) {
                DrawRectangle(width / 3 * 2 + 15, height / 2 - 85, 240, 170, LIGHTGRAY); // Draw a color-filled rectangle
            }
            if (board[6] == 'X') {
                DrawTexture(xTexture, width - 220, height / 2 - 85, RED);
            } else if (board[6] == 'O') {
                DrawTexture(oTexture, width - 220, height / 2 - 85, RED);
            }
            // * Left bottom Square(sq7)
            if (GetMouseX() < width / 3 && GetMouseY() > height / 3 * 2 && board[7] == '#' && game_on == true) {
                DrawRectangle(10, height - 185, 242, 175, LIGHTGRAY); // Draw a color-filled rectangle
            }
            if (board[7] == 'X') {
                DrawTexture(xTexture, 50, height - 175, RED);
            } else if (board[7] == 'O') {
                DrawTexture(oTexture, 50, height - 175, RED);
            }
            // * Middle bottom Square(sq8)
            if (GetMouseX() > width / 3 && GetMouseX() < width / 3 * 2 && GetMouseY() > height / 3 * 2 && board[8] == '#' && game_on == true) {
                DrawRectangle(width / 3 + 16, height - 185, 236, 175, LIGHTGRAY); // Draw a color-filled rectangle
            }
            if (board[8] == 'X') {
                DrawTexture(xTexture, width / 2 - 85, height - 175, RED);
            } else if (board[8] == 'O') {
                DrawTexture(oTexture, width / 2 - 85, height - 175, RED);
            }
            // * Right bottom Square(sq9)
            if (GetMouseX() > width / 3 * 2 && GetMouseY() > height / 3 * 2 && board[9] == '#' && game_on == true) {
                DrawRectangle(width / 3 * 2 + 15, height - 185, 242, 175, LIGHTGRAY); // Draw a color-filled rectangle
            }
            if (board[9] == 'X') {
                DrawTexture(xTexture, width - 220, height - 175, RED);
            } else if (board[9] == 'O') {
                DrawTexture(oTexture, width - 220, height - 175, RED);
            }

            // ! Display green line if someone wins
            if (!game_on && showWinnerLine) {
                if (board[1] == board[2] && board[2] == board[3] && board[1] != '#')
                    DrawLineEx((Vector2){17, height / 3 / 2}, (Vector2){780, height / 3 / 2}, winnerLineThickness, GREEN);
                else if (board[4] == board[5] && board[5] == board[6] && board[4] != '#')
                    DrawLineEx((Vector2){17, height / 2}, (Vector2){780, height / 2}, winnerLineThickness, GREEN);
                else if (board[7] == board[8] && board[8] == board[9] && board[7] != '#')
                    DrawLineEx((Vector2){17, height - 90}, (Vector2){780, height - 90}, winnerLineThickness, GREEN);
                else if (board[1] == board[4] && board[4] == board[7] && board[1] != '#')
                    DrawLineEx((Vector2){width / 3 / 2, 10}, (Vector2){width / 3 / 2, height - 10}, winnerLineThickness, GREEN);
                else if (board[2] == board[5] && board[5] == board[8] && board[2] != '#')
                    DrawLineEx((Vector2){width / 2, 10}, (Vector2){width / 2, 780}, winnerLineThickness, GREEN);
                else if (board[3] == board[6] && board[6] == board[9] && board[3] != '#')
                    DrawLineEx((Vector2){width / 3 * 2 + 135, 10}, (Vector2){width / 3 * 2 + 135, height - 10}, winnerLineThickness, GREEN);

                // * Special displays if player wins on the diagonals, depending on the winner's marker

                else if (board[1] == board[5] && board[5] == board[9] && board[1] == 'O')
                    DrawLineEx((Vector2){20, 10}, (Vector2){790, height - 10}, winnerLineThickness, GREEN);
                else if (board[3] == board[5] && board[5] == board[7] && board[3] == 'O')
                    DrawLineEx((Vector2){width - 20, 10}, (Vector2){10, height - 10}, winnerLineThickness, GREEN);
                else if (board[1] == board[5] && board[5] == board[9] && board[1] == 'X')
                    DrawLineEx((Vector2){73, 25}, (Vector2){width - 45, height - 10}, winnerLineThickness, GREEN);
                else if (board[3] == board[5] && board[5] == board[7] && board[3] == 'X')
                    DrawLineEx((Vector2){width - 65, 25}, (Vector2){55, height - 15}, winnerLineThickness, GREEN);
            }

            // ! Display game_over text and button
            if (showGameOver) {
                DrawRectangle(0, height / 3 - 10, width, 220, LIGHTGRAY);
                if (!draw)
                    DrawTextEx(gameOverFont, winner, (Vector2){150, height / 2 - 20}, 55, 1, BLACK);
                else
                    DrawTextEx(gameOverFont, winner, (Vector2){220, height / 2 - 20}, 55, 1, BLACK);

                // * Draw New Game Button
                DrawRectangle(width / 2 - 75, height / 2 + 50, 150, 30, GRAY);
                DrawTextEx(buttonFont, "New Game", (Vector2){width / 2 - 62.5, height / 2 + 50}, 30, 1, BLACK);

                if (GetMouseX() >= width / 2 - 75 && GetMouseX() <= width / 2 - 75 + 150 && GetMouseY() >= height / 2 + 50 && GetMouseY() <= height / 2 + 80) {
                    SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
                    DrawTextEx(buttonFont, "New Game", (Vector2){width / 2 - 62.5, height / 2 + 50}, 30, 1, RAYWHITE);
                } else
                    SetMouseCursor(MOUSE_CURSOR_DEFAULT);

                // * Draw Score
                DrawTextEx(buttonFont, TextFormat("Player 1 %i - ", xScore), (Vector2){width / 2 - 125, height / 2 - 70}, 30, 1, RED);
                DrawTextEx(buttonFont, TextFormat("%i Player 2", oScore), (Vector2){width / 2 + 10, height / 2 - 70}, 30, 1, RED);

                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && GetMouseX() >= width / 2 - 75 && GetMouseX() <= width / 2 - 75 + 150 && GetMouseY() >= height / 2 + 50 && GetMouseY() <= height / 2 + 80 && !game_on) {
                    game_on = true, draw = false;
                    showGameOver = false, showWinnerLine = false;
                    textTimer = 1.7f, winnerLineTimer = 0.3f;
                    SetMouseCursor(MOUSE_CURSOR_DEFAULT);
                    clearBoard();
                }
            }
        }
        EndDrawing();
    }
    UnloadFont(menuButtonFont), UnloadFont(menuFont), UnloadFont(menuCopyrightFont), UnloadFont(gameOverFont), UnloadFont(buttonFont);
    CloseWindow();
    return 0;
}