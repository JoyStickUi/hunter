#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QPainter>

#include "spritecoords.h"
#include "item.h"
#include "enemy.h"

class Player : public GameObject
{
public:
    enum ANIM_STATES{
        FORWARD = 0,
        BACK,
        LEFT,
        RIGHT
    };
    int anim_state = ANIM_STATES::FORWARD;

    static Player *getInstance();

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;    
    void forceBy(int xu, int yu);
    GameObject* hitTest(int x_offset, int y_offset);

    void change_mana_by(float units);
    void change_health_by(float units);

    void pick_up(Item* item);
    void use(int slot_index);
    void cellItem(int slot_index);
    std::vector<Item*>* getInventory();

    void setHp(float hp);
    void setMana(float mana);

    void restore_mana();
    void restore_hp();

    float getSkillValue(int type);
    float getResistValue(int type);

    void receiveDamage(int damage_type, float units);

    Enemy* current_enemy = nullptr;

    void update_skill_value_by(int type, float points);
    void update_resist_value_by(int type, float points);

    float getManaValue();

    int kills = 0;

    void putMoney(int money);
    void stealMoney(int money);
    int getMoney();

    void restart();
private:
    Player();
    static Player* instance;
    std::vector<std::vector<SpriteCoords*>*>* animation_list;
    int current_sprite = 0;

    float mana = 1.0f;
    float hp = 1.0f;

    float fire_resist = 0.0f;
    float ice_resist = 0.0f;
    float lightning_resist = 0.0f;

    float mana_restore_skill = 0.1f;
    float hp_restore_skill = 0.05f;

    float fire_skill = 0.0f;
    float ice_skill = 0.0f;
    float lightning_skill = 0.0f;
    float intimidation_skill = 0.0f;

    int money = 0;

    int current_effect = None;

    int inv_slots = 6;
    std::vector<Item*>* inventory;

    void crop(int x, int y, int width, int height, int frames);
};

#endif // PLAYER_H
