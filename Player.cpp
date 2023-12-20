#include "Player.h"
#include "GameMechs.h"
#include <stdio.h>


Player::Player(GameMechs* gmRef) : playerDir(STOP), gameMecRef(gmRef) {
    playerPos.setObjPos(10, 5, '*');
}

void Player::updatePlayerDir() {
    Direction newDir = static_cast<Direction>(gameMecRef->getInput());

    // Check if the new direction is not the opposite of the current direction
    if (!((playerDir == UP && newDir == DOWN) ||
          (playerDir == DOWN && newDir == UP) ||
          (playerDir == LEFT && newDir == RIGHT) ||
          (playerDir == RIGHT && newDir == LEFT))) {
        playerDir = newDir;
    }
}

void Player::movePlayer() {
    // Save current position for wrap-around logic
    int prevX = playerPos.x;  // Use x directly
    int prevY = playerPos.y;  // Use y directly

    switch (playerDir) {
        case UP:
            playerPos.moveUp();
            break;
        case DOWN:
            playerPos.moveDown();
            break;
        case LEFT:
            playerPos.moveLeft();
            break;
        case RIGHT:
            playerPos.moveRight();
            break;
        default:
            break;
    }

    // Wrap around if hitting the game board
    if (playerPos.x == 0) {
        playerPos.x = (gameMecRef->getBoardSizeY() - 2);
    } else if (playerPos.x == gameMecRef->getBoardSizeY()-1) {
        playerPos.x = 1;
    }

    if (playerPos.y == 0) {
        playerPos.y = (gameMecRef->getBoardSizeX() - 2);
    } else if (playerPos.y == gameMecRef->getBoardSizeX() - 1) {
        playerPos.y = 1;
    }

    bodyPositions.insertHead(playerPos);
    
    // Remove the tail if the body size exceeds the score
    while (bodyPositions.getSize() > gameMecRef->getScore()+1) {
        bodyPositions.removeTail();
    }

}


void Player::drawPlayer() {
    // Drawing logic for the player
    printf("%c", playerPos.getSymbol());
}

objPos& Player::getPlayerPos() {
    return playerPos;
}

void Player::growPlayer() {
    // Add a new position at the head when the player grows
    bodyPositions.insertHead(playerPos);
}

char Player::getPlayerSymbolAtPosition(int x, int y) {
    // Check if the given position is part of the player's body
    objPos checkPos(x, y, ' ');
    for (int i = 0; i < bodyPositions.getSize(); ++i) {
        objPos currentPos;
        bodyPositions.getElement(currentPos, i);
        if (checkPos.isPosEqual(&currentPos)) {
            return '*';
        }
    }
    return 0;
}

bool Player::checkSelfCollision() {
    objPos headPos = playerPos;
    
    // Check if the head position matches any position in the body
    for (int i = 1; i < bodyPositions.getSize(); ++i) {
        objPos currentPos;
        bodyPositions.getElement(currentPos, i);
        if (headPos.isPosEqual(&currentPos)) {
            return true;  // Collision detected
        }
    }
    
    return false;  // No collision
}