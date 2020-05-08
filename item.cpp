#include "item.h"

#include "player.h"
#include "gamemap.h"
#include "notifications.h"
#include "textures.h"

Item::Item(int x, int y, int sprite_index, QString name) : GameObject()
{
    this->moveItTo(x, y);
    this->setActivatable(true);
    this->setSpriteIndex(Textures::CHEST);
    this->slot_image = sprite_index;
    this->name = name;
    this->isRestartable = true;
}

void Item::use()
{

}

int Item::getSlotImage()
{
    return this->slot_image;
}

QString Item::getName()
{
    return this->name;
}

void Item::activation_func()
{
    Player::getInstance()->pick_up(this);
    GameMap::getInstance()->removeObject(this->x(), this->y());
    QString str("Был найден предмет: ");
    str.append(this->name);
    Notifications::getInstance()->makeNotification(str);
}
