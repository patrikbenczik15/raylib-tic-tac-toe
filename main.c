#include "raylib.h"

char board[3][3] = {
    {'#', '#', '#'},
    {'#', '#', '#'},
    {'#', '#', '#'},
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

bool checkBoardFull() {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (board[row][col] == '#')
                return false;
        }
    }
    return true;
}

void checkWin() {
    // Check horizontally
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2] && board[row][0] != '#') {
            updateScore();
            game_on = false;
            return;
        }
    }
    // Check vertically
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col] && board[0][col] != '#') {
            updateScore();
            game_on = false;
            return;
        }
    }
    // Check diagonally
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '#') {
        updateScore();
        game_on = false;
        return;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '#') {
        updateScore();
        game_on = false;
        return;
    }
    if (checkBoardFull()) {
        game_on = false;
        draw = true;
    }
}
void clearBoard() {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            board[row][col] = '#';
        }
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
        if (option == 2 && game_on) {
            // Parcurgem matricea de joc 3x3
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    // Calculăm coordonatele pentru fiecare pătrat
                    float x_min = j * (width / 3);
                    float x_max = (j + 1) * (width / 3);
                    float y_min = i * (height / 3);
                    float y_max = (i + 1) * (height / 3);

                    // Verificăm dacă mouse-ul este apăsat în interiorul pătratului curent și că pătratul este liber ('#')
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
                        GetMouseX() > x_min && GetMouseX() < x_max &&
                        GetMouseY() > y_min && GetMouseY() < y_max &&
                        board[i][j] == '#') {

                        // Actualizăm tabla cu simbolul jucătorului curent
                        board[i][j] = (current_player == 'X') ? 'X' : 'O';

                        // Verificăm dacă cineva a câștigat și schimbăm jucătorul
                        checkWin();
                        switchPlayer();
                    }
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

            // Desenăm liniile grilei
            for (int i = 1; i < 3; i++) {
                // Linii verticale
                DrawLineEx((Vector2){i * width / 3, 10}, (Vector2){i * width / 3, height - 10}, gridLineThickness, BLACK);
                // Linii orizontale
                DrawLineEx((Vector2){10, i * height / 3}, (Vector2){width - 10, i * height / 3}, gridLineThickness, BLACK);
            }

            // Desenăm pătratele și texturile
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    // Calculăm coordonatele pătratului
                    float x_min = j * (width / 3);
                    float x_max = (j + 1) * (width / 3);
                    float y_min = i * (height / 3);
                    float y_max = (i + 1) * (height / 3);

                    // Verificăm dacă mouse-ul este deasupra pătratului curent
                    if (GetMouseX() > x_min && GetMouseX() < x_max && GetMouseY() > y_min && GetMouseY() < y_max) {
                        if (board[i][j] == '#') {
                            DrawRectangle(x_min + 10, y_min + 10, (width / 3) - 20, (height / 3) - 20, LIGHTGRAY); // Desenăm pătratul gri
                        }
                    }

                    // Desenăm X și O
                    if (board[i][j] == 'X') {
                        DrawTexture(xTexture, x_min + (width / 6) - (xTexture.width / 2), y_min + (height / 6) - (xTexture.height / 2), RED);
                    } else if (board[i][j] == 'O') {
                        DrawTexture(oTexture, x_min + (width / 6) - (oTexture.width / 2), y_min + (height / 6) - (oTexture.height / 2), RED);
                    }
                }
            }

            // ! Display green line if someone wins
            if (!game_on && showWinnerLine) {
                // Horizontal lines
                if (board[0][0] == board[0][1] && board[0][1] == board[0][2] && board[0][0] != '#') {
                    DrawLineEx((Vector2){17, height / 3 / 2}, (Vector2){780, height / 3 / 2}, winnerLineThickness, GREEN);
                } else if (board[1][0] == board[1][1] && board[1][1] == board[1][2] && board[1][0] != '#') {
                    DrawLineEx((Vector2){17, height / 2}, (Vector2){780, height / 2}, winnerLineThickness, GREEN);
                } else if (board[2][0] == board[2][1] && board[2][1] == board[2][2] && board[2][0] != '#') {
                    DrawLineEx((Vector2){17, height - 90}, (Vector2){780, height - 90}, winnerLineThickness, GREEN);
                }
                // Vertical lines
                else if (board[0][0] == board[1][0] && board[1][0] == board[2][0] && board[0][0] != '#') {
                    DrawLineEx((Vector2){width / 3 / 2, 10}, (Vector2){width / 3 / 2, height - 10}, winnerLineThickness, GREEN);
                } else if (board[0][1] == board[1][1] && board[1][1] == board[2][1] && board[0][1] != '#') {
                    DrawLineEx((Vector2){width / 2, 10}, (Vector2){width / 2, height - 10}, winnerLineThickness, GREEN);
                } else if (board[0][2] == board[1][2] && board[1][2] == board[2][2] && board[0][2] != '#') {
                    DrawLineEx((Vector2){width / 3 * 2 + 135, 10}, (Vector2){width / 3 * 2 + 135, height - 10}, winnerLineThickness, GREEN);
                }
                // Diagonal lines
                else if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '#') {
                    Vector2 start = (board[0][0] == 'O') ? (Vector2){20, 10} : (Vector2){73, 25};
                    Vector2 end = (board[0][0] == 'O') ? (Vector2){790, height - 10} : (Vector2){width - 45, height - 10};
                    DrawLineEx(start, end, winnerLineThickness, GREEN);
                } else if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '#') {
                    Vector2 start = (board[0][2] == 'O') ? (Vector2){width - 20, 10} : (Vector2){width - 65, 25};
                    Vector2 end = (board[0][2] == 'O') ? (Vector2){10, height - 10} : (Vector2){55, height - 15};
                    DrawLineEx(start, end, winnerLineThickness, GREEN);
                }
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

        EndDrawing();
    }
    UnloadFont(menuButtonFont), UnloadFont(menuFont), UnloadFont(menuCopyrightFont), UnloadFont(gameOverFont), UnloadFont(buttonFont);
    CloseWindow();
    return 0;
}