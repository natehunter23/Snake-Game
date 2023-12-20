#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

const int SCREEN_WIDTH = 16;
const int SCREEN_HEIGHT = 30;

objPos gameBorder[SCREEN_WIDTH][SCREEN_HEIGHT];
GameMechs *gameMechs;  // Declare gameMechs globally
Player *player;

bool exitFlag;


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void) {
    gameMechs = new GameMechs();  // Initialize gameMechs
    player = new Player(gameMechs);  // Initialize player
    Initialize();

    while (!gameMechs->getExitFlagStatus() && !gameMechs->getLoseFlagStatus()) {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
}

void Initialize(void) {
    MacUILib_init();
    MacUILib_clearScreen();
    exitFlag = false;

    for (int i = 0; i < SCREEN_WIDTH; ++i) {
        for (int j = 0; j < SCREEN_HEIGHT; ++j) {
            if (i == 0 || i == SCREEN_WIDTH - 1 || j == 0 || j == SCREEN_HEIGHT - 1) {
                gameBorder[i][j].setObjPos(i, j, '#');
            } else {
                gameBorder[i][j].setObjPos(i, j, ' ');
            }
        }
    }
}

void GetInput(void) {
    // Collect input and set it in the gameMechs object
    char input;
    if (MacUILib_hasChar()) {
        input = MacUILib_getChar();
        gameMechs->setInput(input);
    }
}

void RunLogic(void) {

    // Check if there's a new input
    if (gameMechs->getInput() != 0) {
        player->updatePlayerDir();
        // Clear the input after processing
        gameMechs->clearInput();
    }

    // Move the player in the current direction
    player->movePlayer();

    if (player->checkSelfCollision()) {
        gameMechs->setLoseFlag();
        return;
    }

    if (player->getPlayerPos().isPosEqual(&gameMechs->getFoodPosition())) {
        player->growPlayer();
        gameMechs->incrementScore();
        gameMechs->generateRandomFoodPosition();
    }

}


void DrawScreen(void) {
    MacUILib_clearScreen();

    // Draw game border with player and food
    for (int i = 0; i < SCREEN_WIDTH; ++i) {
        for (int j = 0; j < SCREEN_HEIGHT; ++j) {
            objPos& foodPos = gameMechs->getFoodPosition();  // Get the food position by reference
            objPos currentPosition(i, j, ' ');

            if (currentPosition.isPosEqual(&foodPos)) {
                MacUILib_printf("%c", 'o');
            } else {
                char playerSymbol = player->getPlayerSymbolAtPosition(i, j);
                if (playerSymbol != 0) {
                    MacUILib_printf("%c", playerSymbol);
                } else if (i == 0 || i == SCREEN_WIDTH - 1 || j == 0 || j == SCREEN_HEIGHT - 1) {
                    MacUILib_printf("%c", '#');
                } else {
                    MacUILib_printf("%c", ' ');  // Empty space within the border
                }
            }
        }
        MacUILib_printf("\n");
    }
    MacUILib_printf("Score: %d", gameMechs->getScore());
}



void LoopDelay(void) {
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void) {
    MacUILib_clearScreen();

    MacUILib_printf("Game over.\nYou Scored: %d", gameMechs->getScore());
    MacUILib_uninit();
    delete player;
    delete gameMechs;
}
