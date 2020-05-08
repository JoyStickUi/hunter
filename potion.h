#ifndef POTION_H
#define POTION_H

#include "item.h"

class Potion : public Item
{
public:
    enum EFFECT_TYPES{
        NONE,
        HEAL,
        MANA_REGEN
    };
    Potion(int x, int y, int sprite_index, QString name, int effect_type, float effect_power);
    void use() override;
    int effect_type = NONE;    
};

#endif // POTION_H
