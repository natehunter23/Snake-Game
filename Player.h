#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

enum Direction {
    STOP = 0,
    UP,
    DOWN,
    LEFT,
    RIGHT
};
class GameMechs;

class Player {
public:
    Player(GameMechs* gmRef);
    void updatePlayerDir();
    void movePlayer();
    void drawPlayer();
    objPos& getPlayerPos();
    void growPlayer();
    char getPlayerSymbolAtPosition(int x, int y); 
    bool checkSelfCollision();

private:
    Direction playerDir;
    GameMechs* gameMecRef;
    objPos playerPos;
    objPosArrayList bodyPositions;
};

#endif
