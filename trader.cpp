#include "trader.h"
#include "game.h"
#include "textures.h"
#include "gamescene.h"
#include "potion.h"
#include "skillbook.h"
#include "portal.h"
#include "notifications.h"
#include <QApplication>
#include <QDesktopWidget>

#include <iostream>

Trader::Trader() : GameObject()
{    
    this->setActivatable(true);
    this->setSpriteIndex(Textures::TRADER);
    this->inventory = new std::vector<Item*>();
    this->update_inventory();
}

Trader* Trader::instance = nullptr;

Trader *Trader::getInstance()
{
    if(instance == nullptr)
        instance = new Trader();
    return instance;
}

void Trader::activation_func()
{
    this->update_inventory();
    Game::getInstance()->startTrade();
}

void Trader::update_inventory()
{
    this->inventory->clear();
    for(int i = 0; i < this->max_slots; ++i){
        switch(rand() % 2){
            //potion
            case 0:
            {
                switch(rand() % 2){
                    //heal
                    case 0:
                    {
                        float effect_power = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                        QString item_title("Особое зелье лечения ");
                        this->inventory->push_back(new Potion(0, 0, Textures::HEAL_POTION, item_title, Potion::HEAL, effect_power));
                    }
                    break;
                    //mana regen
                    case 1:
                    {
                        float effect_power = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                        QString item_title("Особое зелье маны ");
                        this->inventory->push_back(new Potion(0, 0, Textures::MANA_POTION, item_title, Potion::MANA_REGEN, effect_power));
                    }
                    break;
                }
            }
            break;
            //skillbook
            case 1:
            {
                switch (rand() % 3) {
                    //fire
                    case 0:
                    {
                        bool skill_vector = rand() % 2 != 0;

                        float effect_power = static_cast <float> (rand()) / static_cast <float> (RAND_MAX * 2);

                        QString item_title("");
                        item_title.append(skill_vector ? "Особое заклинание защиты от огня " : "Особое заклинание огня ");

                        this->inventory->push_back(new SkillBook(0, 0, Textures::CHEST, item_title, DAMAGE_TYPES::FIRE, effect_power, skill_vector));
                    }
                    break;
                    //ice
                    case 1:
                    {
                        bool skill_vector = rand() % 2 != 0;

                        float effect_power = static_cast <float> (rand()) / static_cast <float> (RAND_MAX * 2);

                        QString item_title("");
                        item_title.append(skill_vector ? "Особое заклинание защиты от льда " : "Особое заклинание льда ");

                        this->inventory->push_back(new SkillBook(0, 0, Textures::CHEST, item_title, DAMAGE_TYPES::ICE, effect_power, skill_vector));
                    }
                    break;
                    //lightning
                    case 2:
                    {
                        bool skill_vector = rand() % 2 != 0;

                        float effect_power = static_cast <float> (rand()) / static_cast <float> (RAND_MAX * 2);

                        QString item_title("");
                        item_title.append(skill_vector ? "Особое заклинание защиты от молний " : "Особое заклинание молний ");

                        this->inventory->push_back(new SkillBook(0, 0, Textures::CHEST, item_title, DAMAGE_TYPES::LIGHTNING, effect_power, skill_vector));
                    }
                    break;
                    //intimidation
                    case 3:
                    {
                        this->inventory->push_back(new SkillBook(0, 0, Textures::CHEST, "Особое заклинание страха", DAMAGE_TYPES::INTIMIDATION, static_cast <float> (rand()) / static_cast <float> (RAND_MAX * 2), false));
                    }
                    break;
                }
            }
            break;
        }
    }
}

void Trader::buyItem(int index)
{
    Notifications* notifications = Notifications::getInstance();
    if(index < this->inventory->size()){
        if(Player::getInstance()->getMoney() >= this->inventory->at(index)->price){
            QString notify("\"");
            notify.append(Trader::getInstance()->getInventory()->at(index)->getName());
            notify.append("\" был куплен");
            notifications->makeNotification(notify);

            Player::getInstance()->stealMoney(this->inventory->at(index)->price);
            Player::getInstance()->pick_up(this->inventory->at(index));
            this->inventory->erase(this->inventory->begin() + index);
        }
    }
}

std::vector<Item *> *Trader::getInventory()
{
    return this->inventory;
}


