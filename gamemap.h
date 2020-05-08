#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "gameobject.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QFile>
#include <QString>

class GameMap
{
public:
    void setSize(int width, int height);
    static GameMap *getInstance();
    int width();
    int height();
    GameObject *getObject(int x, int y);
    void removeObject(int x, int y);
    void spawn_skillbook(int x, int y, int sprite_index, QString name, int type, float points = 0.1f, bool aboutResist = false);
    void spawn_potion(int x, int y, int sprite_index, QString name, int effect_type, float effect_power);
    void spawn_portal(int x, int y, int toX, int toY, std::function<void()> onTp);
    void spawn_enemy(
            int x,
            int y,
            int sprite_index,
            QString name,
            std::function<void()> onDead,
            float fire_skill = 0.1f,
            float ice_skill = 0.1f,
            float lightning_skill = 0.1f,
            float fire_resist = 0.1f,
            float ice_resist = 0.1f,
            float lightning_resist = 0.1f,
            float will = 0.1f
            );
    void restart();
private:
    GameMap();
    static GameMap* instance;
    GameObject*** objects_map = nullptr;
    //size in tiles
    int m_width = 0;
    int m_height = 0;
};

#endif // GAMEMAP_H
