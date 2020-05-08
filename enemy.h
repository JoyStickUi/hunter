#ifndef ENEMY_H
#define ENEMY_H

#include "gameobject.h"
#include "spritecoords.h"
#include <functional>

#include <QPixmap>
#include <QPainter>

class Enemy : public GameObject
{
public:
    Enemy(int x, int y, int sprite_index, QString name, std::function<void()> onDead);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void change_health_by(float units);

    void receiveDamage(int damage_type, float units);
    void make_choose();
    void surrender();
    void setProperties(float fire_skill = 0.1f, float ice_skill = 0.1f, float lightning_skill = 0.1f, float fire_resist = 0.1f, float ice_resist = 0.1f, float lightning_resist = 0.1f, float will = 0.1f);
    void restoreHp();
    void restoreWill();
protected:
    void activation_func() override;
private:    
    float hp = 1.0f;

    QString name;

    float startWill = 1.0f;

    float fire_resist = 0.0f;
    float ice_resist = 0.0f;
    float lightning_resist = 0.0f;
    float fire_skill = 0.0f;
    float ice_skill = 0.0f;
    float lightning_skill = 0.0f;
    float will = 1.0f;

    std::function<void()> onDead;

    int current_effect = None;
};

#endif // ENEMY_H
