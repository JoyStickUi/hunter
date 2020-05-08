#include "gameend.h"
#include "game.h"

GameEnd::GameEnd() : GameObject ()
{
    this->setActivatable(true);
}

void GameEnd::activation_func()
{
    Game::getInstance()->gameState = Game::END;
}


