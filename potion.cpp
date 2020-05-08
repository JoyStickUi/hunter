#include "potion.h"

#include "player.h"

Potion::Potion(int x, int y, int sprite_index, QString name, int effect_type, float effect_power) : Item(x, y, sprite_index, name)
{
    this->effect_type = effect_type;
    this->effect_power = effect_power;
    this->price += (25 * this->effect_power);
}

void Potion::use()
{
    switch(this->effect_type){
        case HEAL:
        {
            Player::getInstance()->change_health_by(this->effect_power);
        }
        break;
        case MANA_REGEN:
        {
            Player::getInstance()->change_mana_by(this->effect_power);
        }
        break;        
    }
}
