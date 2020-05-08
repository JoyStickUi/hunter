#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QApplication>
#include <QDesktopWidget>
#include <QKeyEvent>

#include "player.h"

class GameScene : public QGraphicsScene
{
public:
    static GameScene *getInstance();
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void keyPressEvent(QKeyEvent *keyEvent) override;
private:
    GameScene();
    static GameScene* instance;
    Player* player;
};

#endif // GAMESCENE_H
