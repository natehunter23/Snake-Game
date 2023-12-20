#include "GameMechs.h"
#include "Player.h"
#include <cstdlib>
#include <ctime>

objPos FoodPosition;

GameMechs::GameMechs() {
    boardSizeX = 30;
    boardSizeY = 16;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    generateRandomFoodPosition();
}

GameMechs::GameMechs(int boardX, int boardY) {
    boardSizeX = boardX;
    boardSizeY = boardY;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    generateRandomFoodPosition();
}

GameMechs::~GameMechs() {
    // Destructor (if needed)
}

bool GameMechs::getExitFlagStatus() {
    return exitFlag;
}

void GameMechs::setExitTrue() {
    exitFlag = true;
}

bool GameMechs::getLoseFlagStatus() {
    return loseFlag;
}

void GameMechs::setLoseFlag() {
    loseFlag = true;
}

char GameMechs::getInput() {
    if (input == 'W' || input == 'w') {
        return static_cast<char>(Direction::UP);
    } else if (input == 'S' || input == 's') {
        return static_cast<char>(Direction::DOWN);
    } else if (input == 'A' || input == 'a') {
        return static_cast<char>(Direction::LEFT);
    } else if (input == 'D' || input == 'd') {
        return static_cast<char>(Direction::RIGHT);
    } else if (input == 'q' || input == 'Q') {
        setExitTrue();  
    } else {
        return input;
    }
}


void GameMechs::setInput(char thisInput) {
    input = thisInput;
}

void GameMechs::clearInput() {
    input = 0;
}

int GameMechs::getBoardSizeX() {
    return boardSizeX;
}

int GameMechs::getBoardSizeY() {
    return boardSizeY;
}

int GameMechs::getScore() {
    return score;
}

void GameMechs::incrementScore() {
    score++;
}

void GameMechs::generateRandomFoodPosition() {
    srand(time(nullptr)); // Seed for random number generation
    objPos playerPosition;
    // Gets the player's position
    if (score == 0) {
    playerPosition.setObjPos(10, 5, '*'); //checks initial position
    } else{
    objPos playerPosition = player->getPlayerPos();
    }
    // this generates a new food position until it's different from the player's position if the player has moved
    do {
        // this generates random coordinates inside the board boundaries
        int foodX = 1 + rand() % (boardSizeY - 2);
        int foodY = 1 + rand() % (boardSizeX - 2);

        // this sets the food position
        FoodPosition.setObjPos(foodX, foodY, 'o');

        // this checks if the food position is the same as the player's position
    } while (FoodPosition.isPosEqual(&playerPosition));
}

objPos& GameMechs::getFoodPosition() {
    return FoodPosition;
}
