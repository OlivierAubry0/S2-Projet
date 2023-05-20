#include "gameController.h"

GameController::GameController(int x, int y)
{
    Hitbox h = Hitbox({ x,y }, "O");
    player = GameObject(h, 'O', Player);
    currentLevel = 0;
    dead = false;
    POWER = false;
    oldControlsValue.UP = false;
    oldControlsValue.DOWN = false;
    oldControlsValue.LEFT = false;
    oldControlsValue.RIGHT = false;
    score = 0;
   
    
   
}

std::string GameController::display()
{
    int totalLength = WIDTH * HEIGHT;
    flashCounter++;
    std::string playerChar = "O";
    if (flashCounter > 20) {
        playerHidden = !playerHidden;
        flashCounter = 0;
    }
    if (powerUPCount != 0 && playerHidden) playerChar = " ";
    int playerIndex = player.getPosition().y * WIDTH + player.getPosition().x;
    std::string content;
    for (int i = 0; i < totalLength; i++)
    {
        if (i != playerIndex) {
            content.append(" ");
            continue;
        }
        content.append(playerChar);
    }
    levels[currentLevel].display(content);

    return content;
}

bool GameController::isDead()
{
    
    return dead;
}

void GameController::addLevel(Level& level)
{
    levels.push_back(level);
}
void GameController::ActivatePowerup()
{
    if (nbPowerUp>0 && powerUPCount == 0)
    {
        powerUPCount += 5;
        nbPowerUp--;
    }
}
void GameController::movePlayer(Controls cv)
{
    int x = player.getPosition().x;
    int y = player.getPosition().y;

    if (cv.UP && !oldControlsValue.UP && !levels[currentLevel].collisionObstacle({ x , y-1})) {
        bool worked = player.move({ 0,-1 });
        if (powerUPCount > 0) powerUPCount--;
        if (worked) score=score+1*(currentLevel+1);
    }
    if (cv.DOWN && !oldControlsValue.DOWN && !levels[currentLevel].collisionObstacle({ x , y + 1 })) {
        bool worked = player.move({ 0,1 });
        if (powerUPCount > 0) powerUPCount--;
        if (worked) score-=(currentLevel+1);
    }
    if (cv.LEFT && !oldControlsValue.LEFT && !levels[currentLevel].collisionObstacle({ x-1 , y })) {
        player.move({ -1,0 });
        if (powerUPCount > 0) powerUPCount--;
    }
    if (cv.RIGHT && !oldControlsValue.RIGHT && !levels[currentLevel].collisionObstacle({ x +1 , y })) {
        player.move({ 1,0 });
        if (powerUPCount > 0) powerUPCount--;
    }
    if (cv.ACTIVATEPOWERUP) 
    {
        ActivatePowerup();
    }
    
    oldControlsValue.UP = cv.UP;
    oldControlsValue.DOWN = cv.DOWN;
    oldControlsValue.LEFT = cv.LEFT;
    oldControlsValue.RIGHT = cv.RIGHT;

}

void GameController::nextCycle()
{
    levels[currentLevel].nextCycle();
   
    if (levels[currentLevel].collisionPowerUp(player))
    {
        nbPowerUp++;
    }
    if (levels[currentLevel].collision(player) && powerUPCount == 0)
    {   
        dead = true;
    }
}
