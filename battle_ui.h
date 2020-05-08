#ifndef BATTLE_UI_H
#define BATTLE_UI_H

#include <QGraphicsPixmapItem>
#include <QPainter>

#include "gameobject.h"

class Battle_UI : public QGraphicsPixmapItem
{
public:
    static Battle_UI* getInstance();
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void setActiveSkill(int type);
private:
    Battle_UI();
    static Battle_UI* instance;
    int active_skill = NONE;
};

#endif // BATTLE_UI_H
