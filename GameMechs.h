#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include "objPos.h"
#include "Player.h"
class Player;
class GameMechs {
private:
    char input;
    bool exitFlag;
    bool loseFlag;
    int score;
    int boardSizeX;
    int boardSizeY;
    Player* player;
    objPos FoodPosition;

public:
    GameMechs();
    GameMechs(int boardX, int boardY);
    ~GameMechs();

    bool getExitFlagStatus();
    void setExitTrue();

    bool getLoseFlagStatus();
    void setLoseFlag();

    char getInput();
    void setInput(char thisInput);
    void clearInput();

    int getBoardSizeX();
    int getBoardSizeY();

    int getScore();
    void incrementScore();

    void generateRandomFoodPosition();
    objPos& getFoodPosition();
};

#endif
