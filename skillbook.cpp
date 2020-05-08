#include "skillbook.h"

#include "player.h"
#include "textures.h"
#include "gamemap.h"
#include "notifications.h"

SkillBook::SkillBook(int x, int y, int sprite_index, QString name, int skill, float skill_points, bool isResist) : Item(x, y, sprite_index, name)
{
    this->isSkillBook = true;
    this->skill = skill;
    this->effect_power = skill_points;
    this->isResist = isResist;
    this->price += (200 * this->effect_power);
}

void SkillBook::activation_func()
{
    GameMap::getInstance()->removeObject(this->x(), this->y());
    QString str("Был найден предмет: ");
    str.append(this->name);
    Notifications::getInstance()->makeNotification(str);
    this->use();
}

void SkillBook::use()
{    
    Player* player = Player::getInstance();
    if(this->isResist){
        player->update_resist_value_by(this->skill, this->effect_power);
    }else{
        player->update_skill_value_by(this->skill, this->effect_power);
    }

}
