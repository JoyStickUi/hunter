#include "portal.h"

#include "player.h"
#include "textures.h"
#include "game.h"
#include <functional>

Portal::Portal(int x_tp_to, int y_tp_to, std::function<void()> onTp) : GameObject ()
{
    this->x_tp_to = x_tp_to;
    this->y_tp_to = y_tp_to;
    this->setSpriteIndex(Textures::DEVIL_STAR);
    this->setActivatable(true);
    this->onTp = onTp;
}

void Portal::activation_func()
{
    Player::getInstance()->moveItTo(Game::getInstance()->items_scale * this->x_tp_to, Game::getInstance()->items_scale * this->y_tp_to);
    this->onTp();
}
