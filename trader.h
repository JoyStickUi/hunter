#ifndef TRADER_H
#define TRADER_H

#include "gameobject.h"
#include "item.h"
#include <QPainter>

class Trader : public GameObject
{
public:
    static Trader* getInstance();
    void activation_func() override;
    void update_inventory();
    void buyItem(int index);
    std::vector<Item*>* getInventory();
private:
    Trader();
    static Trader* instance;
    std::vector<Item*>* inventory;
    int max_slots = 6;
};

#endif // TRADER_H
