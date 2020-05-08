#include "gameobject.h"

#include "textures.h"

GameObject::GameObject()
{
    this->obj_width = 0;
    this->obj_height = 0;
}

GameObject::GameObject(int width, int height) : QGraphicsPixmapItem()
{
    this->obj_width = width;
    this->obj_height = height;
}

void GameObject::init(int x, int y, int width, int height)
{
    this->obj_x = x;
    this->obj_y = y;
    this->obj_width = width;
    this->obj_height = height;
}

void GameObject::moveItTo(int x, int y)
{
    this->deltaX = x - this->obj_x;
    this->deltaY = y - this->obj_y;
    this->obj_x = x;
    this->obj_y = y;
}

void GameObject::moveItBy(int xu, int yu)
{    
    this->moveItTo(this->obj_x + xu, this->obj_y + yu);
}

int GameObject::x()
{
    return this->obj_x;
}

int GameObject::y()
{
    return this->obj_y;
}

int GameObject::width()
{
    return this->obj_width;
}

int GameObject::height()
{
    return this->obj_height;
}

int GameObject::delta_x()
{
    return this->deltaX;
}

int GameObject::delta_y()
{
    return this->deltaY;
}

bool GameObject::isCollidable()
{
    return this->obj_collidable;
}

bool GameObject::isActivatable()
{
    return this->obj_activatable;
}

void GameObject::setCollidable(bool flag)
{
    this->obj_collidable = flag;
}

void GameObject::setActivatable(bool flag)
{
    this->obj_activatable = flag;
}

void GameObject::activate()
{
    if(this->obj_activatable)
        this->activation_func();
}

int GameObject::getSpriteIndex()
{
    return this->sprite_index;
}

void GameObject::setSpriteIndex(int index)
{
    this->sprite_index = index;
}

QPixmap *GameObject::getSprite()
{
    return this->sprite;
}

void GameObject::setSprite(QPixmap *sprite)
{
    this->sprite = sprite;
}

float GameObject::getEffectPower()
{
    return this->effect_power;
}

void GameObject::activation_func()
{

}
