#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QGraphicsPixmapItem>

enum DAMAGE_TYPES{
    NONE,
    FIRE,
    ICE,
    LIGHTNING,
    INTIMIDATION
};

enum DAMAGE_EFFECTS{
    None,
    Fire,
    Ice
};

class GameObject : public QGraphicsPixmapItem
{
public:
    GameObject();    
    GameObject(int width, int height);
    void init(int x, int y, int width, int height);
    void moveItTo(int x, int y);
    void moveItBy(int xu, int yu);    
    int x();
    int y();
    int width();
    int height();
    int delta_x();
    int delta_y();
    bool isCollidable();
    bool isActivatable();
    void setCollidable(bool flag);
    void setActivatable(bool flag);
    void activate();
    void setSpriteIndex(int index);
    int getSpriteIndex();
    QPixmap *getSprite();
    void setSprite(QPixmap* sprite);
    GameObject& operator=(const GameObject& other);
    bool visiability = true;
    bool isRestartable = false;
    bool isEnemy = false;
    bool isSkillBook = false;
    float getEffectPower();
private:
    bool obj_collidable = false;
    bool obj_activatable = false;
    int obj_x = 0;
    int obj_y = 0;
    int obj_width = 0;
    int obj_height = 0;
    int deltaX = 0;
    int deltaY = 0;
protected:
    float effect_power = 0.0f;
    virtual void activation_func();
    int sprite_index = 0;
    QPixmap* sprite = nullptr;
};

#endif // GAMEOBJECT_H
