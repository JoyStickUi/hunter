#ifndef ITEM_H
#define ITEM_H

#include "gameobject.h"

class Item : public GameObject
{
public:
    Item(int x, int y, int sprite_index, QString name);
    virtual void use();    
    int getSlotImage();
    QString getName();

    int price = 5;
protected:
    void activation_func() override;
    QString name;
    int slot_image;
};

#endif // ITEM_H
