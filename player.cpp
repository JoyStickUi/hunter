#include "player.h"

#include "game.h"
#include "gamescene.h"
#include "gamemap.h"
#include "notifications.h"

Player* Player::instance = nullptr;

Player *Player::getInstance()
{
    if(instance == nullptr)
        instance = new Player();
    return instance;
}

Player::Player() : GameObject (Game::getInstance()->items_scale, Game::getInstance()->items_scale)
{
    this->sprite = new QPixmap("://img/764uUrl3.png");

    this->animation_list = new std::vector<std::vector<SpriteCoords*>*>();    

    //forward
    this->crop(0, 651, 64, 49, 9);
    //back
    this->crop(0, 524, 64, 49, 9);
    //left
    this->crop(0, 588, 64, 49, 9);
    //right
    this->crop(0, 716, 64, 49, 9);

    this->inventory = new std::vector<Item*>();
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(this->current_sprite > 8) this->current_sprite = 0;
    switch (Game::getInstance()->gameState) {
        case Game::Adventure:
        {
            SpriteCoords* coords = this->animation_list->at(this->anim_state)->at(this->current_sprite);
            painter->drawPixmap(
                        QPoint(Game::getInstance()->items_scale * 4.5, Game::getInstance()->items_scale * 2.5),
                        this->sprite->copy(coords->x, coords->y, coords->width, coords->height).scaled(Game::getInstance()->items_scale, Game::getInstance()->items_scale)
                        );
            int items_scale = Game::getInstance()->items_scale;
            painter->setPen(QPen(QColor(Qt::black)));
            painter->setBrush(QBrush(QColor(Qt::white)));
            painter->drawRect(items_scale * 0.1, items_scale * 0.1, items_scale, items_scale * 0.2);
            painter->setBrush(QBrush(QColor(Qt::red)));
            painter->drawRect(items_scale * 0.1, items_scale * 0.1, items_scale * this->hp, items_scale * 0.2);
            painter->setBrush(QBrush(QColor(Qt::white)));
            painter->drawRect((items_scale * 0.1) + items_scale + (items_scale * 0.1), items_scale * 0.1, items_scale, items_scale * 0.2);
            painter->setBrush(QBrush(QColor(Qt::blue)));
            painter->drawRect((items_scale * 0.1) + items_scale + (items_scale * 0.1), items_scale * 0.1, items_scale * this->mana, items_scale * 0.2);
            painter->setPen(QPen(QColor(Qt::black)));
            painter->setFont(QFont("Rubik", 16));
            painter->drawText(QRect(items_scale * 0.1, items_scale * 0.1, items_scale, items_scale * 0.2), QString::number(100 * this->hp), QTextOption(Qt::AlignmentFlag::AlignCenter));
            painter->drawText(QRect((items_scale * 0.1) + items_scale + (items_scale * 0.1), items_scale * 0.1, items_scale, items_scale * 0.2), QString::number(100 * this->mana), QTextOption(Qt::AlignmentFlag::AlignCenter));
        }
        break;
        case Game::Battle:
        {
            painter->setPen(QPen(QColor(Qt::black)));
            painter->setBrush(QBrush(QColor(Qt::white)));
            painter->setFont(QFont("Rubik", 14));
            painter->drawRect(QRect(Game::getInstance()->items_scale, Game::getInstance()->items_scale * 2.5, Game::getInstance()->items_scale, Game::getInstance()->items_scale * 0.1));
            painter->setBrush(QBrush(QColor(Qt::red)));
            painter->drawRect(QRect(Game::getInstance()->items_scale, Game::getInstance()->items_scale * 2.5, Game::getInstance()->items_scale * (this->hp < 0.0f ? 0.0f : this->hp), Game::getInstance()->items_scale * 0.1));
            painter->drawText(QRect(Game::getInstance()->items_scale, Game::getInstance()->items_scale * 2.5, Game::getInstance()->items_scale, Game::getInstance()->items_scale * 0.1), QString::number(100 * this->hp), QTextOption(Qt::AlignmentFlag::AlignCenter));

            painter->setBrush(QBrush(QColor(Qt::white)));
            painter->drawRect(QRect(Game::getInstance()->items_scale, Game::getInstance()->items_scale * 2.7, Game::getInstance()->items_scale, Game::getInstance()->items_scale * 0.1));
            painter->setBrush(QBrush(QColor(Qt::blue)));
            painter->drawRect(QRect(Game::getInstance()->items_scale, Game::getInstance()->items_scale * 2.7, Game::getInstance()->items_scale * (this->mana < 0.0f ? 0.0f : this->mana), Game::getInstance()->items_scale * 0.1));
            painter->drawText(QRect(Game::getInstance()->items_scale, Game::getInstance()->items_scale * 2.7, Game::getInstance()->items_scale, Game::getInstance()->items_scale * 0.1), QString::number(100 * this->mana), QTextOption(Qt::AlignmentFlag::AlignCenter));

            switch(this->current_effect){
                case None:
                {
                    painter->drawPixmap(
                            QPoint(Game::getInstance()->items_scale, Game::getInstance()->items_scale * 3),
                            this->sprite->copy(0, 716, 64, 49).scaled(Game::getInstance()->items_scale, Game::getInstance()->items_scale)
                            );
                }
                break;
                case Fire:
                {
                    painter->drawPixmap(
                                QPoint(Game::getInstance()->items_scale, Game::getInstance()->items_scale * 3),
                                QPixmap("://img/FiredPlayer.png").scaled(Game::getInstance()->items_scale, Game::getInstance()->items_scale)
                                );
                }
                break;
                case Ice:
                {
                    painter->drawPixmap(
                                QPoint(Game::getInstance()->items_scale, Game::getInstance()->items_scale * 3),
                                QPixmap("://img/FrozenPlayer.png").scaled(Game::getInstance()->items_scale, Game::getInstance()->items_scale)
                                );
                }
                break;
            }
        }
        break;
        case Game::Paused:
        {

        }
        break;
    }
}

void Player::crop(int x, int y, int width, int height, int frames)
{
    std::vector<SpriteCoords*>* sprite_list = new std::vector<SpriteCoords*>();

    for(int frame = 0; frame < frames; ++frame){
        sprite_list->push_back(new SpriteCoords(x + (width * frame), y, width, height));
    }

    this->animation_list->push_back(sprite_list);
}

void Player::forceBy(int xu, int yu)
{
    ++this->current_sprite;
    this->moveItBy(xu, yu);
}

GameObject* Player::hitTest(int x_offset, int y_offset)
{
    Game* game = Game::getInstance();
    int x = (this->x() + (this->width() / 2)) / game->items_scale;
    int y = (this->y() + (this->height() * 0.5)) / game->items_scale;
    return GameMap::getInstance()->getObject(x + x_offset, y + y_offset);
}

void Player::change_mana_by(float units)
{
    this->mana += units;
    if(this->mana > 1)
        this->mana = 1;
    if(this->mana < 0)
        this->mana = 0;
}

void Player::change_health_by(float units)
{
    this->hp += units;
    if(this->hp > 1)
        this->hp = 1;
    if(this->hp < 0)
        this->hp = 0;
}

void Player::pick_up(Item *item)
{
    if(this->inv_slots > this->inventory->size())
    {
        this->inventory->push_back(item);
    }else{
        Notifications::getInstance()->makeNotification("Инвентарь полон");
    }
}

void Player::use(int slot_index)
{
    if(this->inventory->size() > slot_index)
    {
        this->inventory->at(slot_index)->use();
        this->inventory->erase(this->inventory->begin() + slot_index);
    }
}

void Player::cellItem(int slot_index)
{
    Notifications* notifications = Notifications::getInstance();
    if(this->inventory->size() > slot_index)
    {
        QString notify("\"");
        notify.append(this->inventory->at(slot_index)->getName());
        notify.append("\" был продан");
        notifications->makeNotification(notify);
        this->putMoney(this->inventory->at(slot_index)->price / 2);
        this->inventory->erase(this->inventory->begin() + slot_index);
    }
}

std::vector<Item *> *Player::getInventory()
{
    return this->inventory;
}

void Player::setHp(float hp)
{
    this->hp = hp;
}

void Player::setMana(float mana)
{
    this->mana = mana;
}

void Player::restore_mana()
{
    if(this->current_effect != Ice)
        this->change_mana_by(this->mana_restore_skill);
}

void Player::restore_hp()
{
    if(this->current_effect != Fire)
        this->change_health_by(this->hp_restore_skill);
}

float Player::getSkillValue(int type)
{
    switch (type) {
        case FIRE:
        {
            return this->fire_skill;
        }
        case ICE:
        {
            return this->ice_skill;
        }
        case LIGHTNING:
        {
            return this->lightning_skill;
        }
        case INTIMIDATION:
        {
            return this->intimidation_skill;
        }
    }
}

float Player::getResistValue(int type)
{
    switch (type) {
        case FIRE:
        {
            return this->fire_resist;
        }
        case ICE:
        {
            return this->ice_resist;
        }
        case LIGHTNING:
        {
            return this->lightning_resist;
        }
    }
}

void Player::receiveDamage(int damage_type, float units)
{
    switch(this->current_effect){
        case Fire:
        {
            this->hp -= (0.1f - (0.1f * this->fire_resist));
        }
        break;
        case Ice:
        {
            this->hp -= (0.05f - (0.05f * this->ice_resist));
        }
        break;
    }

    switch (damage_type) {
        case FIRE:
        {
            if(rand() % 10 > 10 * this->fire_resist)
                if(units > this->fire_resist){
                    this->hp -= (units - this->fire_resist);
                    this->current_effect = Fire;
                }
        }
        break;
        case ICE:
        {
            if(rand() % 10 > 10 * this->ice_resist)
                if(units > this->ice_resist){
                    this->hp -= (units - this->ice_resist);
                    this->current_effect = Ice;
                }
        }
        break;
        case LIGHTNING:
        {
            if(rand() % 10 > 10 * this->lightning_resist)
                if(units > this->lightning_resist)
                    this->hp -= (units - this->lightning_resist);
        }
        break;
    }
    if(this->hp <= 0.0f)
        Game::getInstance()->playerDeath();
    bool flag = false;
    if(this->hp < 0.5)
        flag = (rand() % 100) < (this->hp * 100) ? true : false;
    if(!flag){
        Game::getInstance()->start_player_turn();
    }else{
        Game::getInstance()->start_enemy_turn();
    }

}

void Player::update_skill_value_by(int type, float points)
{
    switch (type) {
        case FIRE:
        {
            if(this->fire_skill < 1.0f)
                this->fire_skill += points;
        }
        break;
        case ICE:
        {
            if(this->ice_skill < 1.0f)
                this->ice_skill += points;
        }
        break;
        case LIGHTNING:
        {
            if(this->lightning_skill < 1.0f)
                this->lightning_skill += points;
        }
        break;
        case INTIMIDATION:
        {
            if(this->intimidation_skill < 1.0f)
                this->intimidation_skill += points;
        }
        break;
    }
}

void Player::update_resist_value_by(int type, float points)
{
    switch (type) {
        case FIRE:
        {
            if(this->fire_resist < 0.5f)
                this->fire_resist += points;
        }
        break;
        case ICE:
        {
            if(this->ice_resist < 0.5f)
                this->ice_resist += points;
        }
        break;
        case LIGHTNING:
        {
            if(this->lightning_resist < 0.5f)
                this->lightning_resist += points;
        }
        break;
    }
}

float Player::getManaValue()
{
    return this->mana;
}

void Player::putMoney(int money)
{
    this->money += money;
    if(this->money < 0)
        this->money = 0;
    if(this->money > 1000)
        this->money = 1000;
}

void Player::stealMoney(int money)
{
    this->putMoney(-1 * money);
}

int Player::getMoney()
{
    return this->money;
}

void Player::restart()
{
    this->current_effect = None;
    this->moveItTo(Game::getInstance()->items_scale * 4.5, Game::getInstance()->items_scale * 2.5);
    this->fire_skill = 0.0f;
    this->ice_skill = 0.0f;
    this->lightning_skill = 0.0f;
    this->intimidation_skill = 0.0f;

    this->fire_resist = 0.0f;
    this->ice_resist = 0.0f;
    this->lightning_resist = 0.0f;

    this->kills = 0;
    this->money = 0;

    this->hp = 1.0f;
    this->mana = 1.0f;

    GameScene::getInstance()->removeItem(this->current_enemy);
    this->current_enemy = nullptr;

    this->inventory->clear();
}


