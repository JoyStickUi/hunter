#include "enemy.h"

#include "game.h"
#include "textures.h"
#include "gamemap.h"
#include "player.h"
#include "gamescene.h"
#include "notifications.h"

Enemy::Enemy(int x, int y, int sprite_index, QString name, std::function<void()> onDead) : GameObject (Game::getInstance()->items_scale, Game::getInstance()->items_scale)
{
    this->moveItTo(x, y);
    this->setActivatable(true);
    this->setSpriteIndex(sprite_index);    
    this->isRestartable = true;
    this->isEnemy = true;
    this->setProperties();
    this->onDead = onDead;

    this->name = name;
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(Game::getInstance()->gameState == Game::Battle){
        painter->setFont(QFont("Rubik", 14));
        painter->setPen(QPen(QColor(Qt::black)));
        painter->setBrush(QBrush(QColor(Qt::white)));
        painter->drawRect(QRect(Game::getInstance()->items_scale * 8, Game::getInstance()->items_scale * 2.5, Game::getInstance()->items_scale, Game::getInstance()->items_scale * 0.1));
        painter->setBrush(QBrush(QColor(Qt::red)));
        painter->drawRect(QRect(Game::getInstance()->items_scale * 8, Game::getInstance()->items_scale * 2.5, Game::getInstance()->items_scale * (this->hp < 0.0f ? 0.0f : this->hp), Game::getInstance()->items_scale * 0.1));
        painter->drawText(QRect(Game::getInstance()->items_scale * 8, Game::getInstance()->items_scale * 2.5, Game::getInstance()->items_scale, Game::getInstance()->items_scale * 0.1), QString::number(100 * this->hp), QTextOption(Qt::AlignmentFlag::AlignCenter));
        painter->setBrush(QBrush(QColor(Qt::white)));
        painter->drawRect(QRect(Game::getInstance()->items_scale * 8, Game::getInstance()->items_scale * 2.7, Game::getInstance()->items_scale, Game::getInstance()->items_scale * 0.1));
        painter->setBrush(QBrush(QColor(Qt::yellow)));
        painter->drawRect(QRect(Game::getInstance()->items_scale * 8, Game::getInstance()->items_scale * 2.7, Game::getInstance()->items_scale * (this->will < 0.0f ? 0.0f : this->will), Game::getInstance()->items_scale * 0.1));
        painter->drawText(QRect(Game::getInstance()->items_scale * 8, Game::getInstance()->items_scale * 2.7, Game::getInstance()->items_scale, Game::getInstance()->items_scale * 0.1), QString::number(100 * this->will), QTextOption(Qt::AlignmentFlag::AlignCenter));
        painter->drawPixmap(
                    QPoint(Game::getInstance()->items_scale * 8, Game::getInstance()->items_scale * 3),
                    Textures::getInstance()->getTexture(this->getSpriteIndex())->scaled(Game::getInstance()->items_scale, Game::getInstance()->items_scale)
                    );
    }
}

void Enemy::change_health_by(float units)
{
    this->hp += units;
    if(this->hp > 1)
        this->hp = 1;
    if(this->hp < 0)
        this->hp = 0;
}

void Enemy::receiveDamage(int damage_type, float units)
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
    Notifications* notifications = Notifications::getInstance();
    switch (damage_type) {
        case FIRE:
        {
            if(rand() % 10 > 10 * this->fire_resist)
                if(units > this->fire_resist)
                {
                    this->hp -= (units - this->fire_resist);

                    this->current_effect = Fire;

                    QString str(this->name);
                    str.append(" получил ");
                    str.append(QString::number(this->hp * (units - this->fire_resist)));
                    str.append(" единиц урона огненной магией");
                    notifications->makeNotification(str);
                }
        }
        break;
        case ICE:
        {
            if(rand() % 10 > 10 * this->ice_resist)
                if(units > this->ice_resist)
                {
                    this->hp -= (units - this->ice_resist);
                    this->current_effect = Ice;

                    QString str(this->name);
                    str.append(" получил ");
                    str.append(QString::number(this->hp * (units - this->ice_resist)));
                    str.append(" единиц урона ледяной магией");
                    notifications->makeNotification(str);
                }
        }
        break;
        case LIGHTNING:
        {
            if(rand() % 10 > 10 * this->lightning_resist)
                if(units > this->lightning_resist)
                {
                    this->hp -= (units - this->lightning_resist);

                    QString str(this->name);
                    str.append(" получил ");
                    str.append(QString::number(this->hp * (units - this->lightning_resist)));
                    str.append(" единиц урона молнией");
                    notifications->makeNotification(str);
                }
        }
        break;
        case INTIMIDATION:
        {
            this->will -= (units / 3);
            QString str(this->name);
            str.append(" теряет интерес к битве");
            notifications->makeNotification(str);
        }
        break;
    }
    bool flag = false;
    if(this->will < 0.5f)
        flag = (rand() % 100) < (this->will * 100) ? true : false;
    if(!flag){
        Game::getInstance()->start_enemy_turn();
    }else{
        Game::getInstance()->start_player_turn();
    }
}

void Enemy::make_choose()
{
    Notifications* notifications = Notifications::getInstance();
    if(this->will <= 0.0f || this->hp <= 0.0f){
        this->surrender();
    }else{
        bool decision_flag = false;
        while(!decision_flag){
            switch (rand() % 4) {
                case FIRE:
                {
                    if(this->fire_skill <= 0.0f)
                        continue;
                    Player::getInstance()->receiveDamage(FIRE, this->fire_skill);
                    decision_flag = true;

                    QString str(this->name);
                    str.append(" атакует огненной магией");
                    notifications->makeNotification(str);
                }
                break;
                case ICE:
                {
                    if(this->ice_skill <= 0.0f)
                        continue;
                    Player::getInstance()->receiveDamage(ICE, this->ice_skill);
                    decision_flag = true;

                    QString str(this->name);
                    str.append(" атакует ледяной магией");
                    notifications->makeNotification(str);
                }
                break;
                case LIGHTNING:
                {
                    if(this->lightning_skill <= 0.0f)
                        continue;
                    Player::getInstance()->receiveDamage(LIGHTNING, this->lightning_skill);
                    decision_flag = true;

                    QString str(this->name);
                    str.append(" атакует молнией");
                    notifications->makeNotification(str);
                }
                break;
            }
        }
    }
}

void Enemy::surrender()
{
   this->onDead();
   GameMap::getInstance()->removeObject(this->x(), this->y());
   Player::getInstance()->kills += 1;
   Player::getInstance()->putMoney(5);
   Player::getInstance()->putMoney(
               (this->fire_skill + this->ice_skill + this->lightning_skill + this->fire_resist + this->ice_resist + this->lightning_resist) * 2
               );
   GameScene::getInstance()->removeItem(Player::getInstance()->current_enemy);
   Game::getInstance()->endBattle();   
}

void Enemy::setProperties(float fire_skill, float ice_skill, float lightning_skill, float fire_resist, float ice_resist, float lightning_resist, float will)
{
    this->fire_skill = fire_skill;
    this->ice_skill = ice_skill;
    this->lightning_skill = lightning_skill;
    this->fire_resist = fire_resist;
    this->ice_resist = ice_resist;
    this->lightning_resist = lightning_resist;
    this->startWill = will;
    this->will = will;
}

void Enemy::restoreHp()
{
    this->hp = 1.0f;
}

void Enemy::restoreWill()
{
    this->will = startWill;
}

void Enemy::activation_func()
{
    this->current_effect = None;
    Game::getInstance()->startBattle(this);    
}
