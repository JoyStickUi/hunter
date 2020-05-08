#include "gamemap.h"

#include "game.h"
#include "player.h"
#include "textures.h"
#include "skillbook.h"
#include "portal.h"
#include "potion.h"
#include "trader.h"
#include "notifications.h"

GameMap* GameMap::instance = nullptr;

void GameMap::setSize(int width, int height)
{
    this->m_width = width;
    this->m_height = height;

    this->objects_map = new GameObject**[width];

    for(int i = 0; i < width; ++i){
        this->objects_map[i] = new GameObject*[height];
        for(int j = 0; j < height; ++j){
            this->objects_map[i][j] = new GameObject();
        }
    }

    QFile mapJson;
    mapJson.setFileName("://json/objects_map.json");

    //add try catch
    mapJson.open(QIODevice::ReadOnly);

    QJsonDocument dom = QJsonDocument::fromJson(mapJson.readAll());
    QJsonObject obj = dom.object();
    QJsonArray array = obj.take("map").toArray();

    QJsonArray x;
    for(int i = 0; i < array.size(); ++i){
        x = array.at(i).toArray();
        for(int j = 0; j < array.at(0).toArray().size(); ++j){
            int index = x.at(j).toInt();
            if(index){
                this->objects_map[j][i]->setCollidable(true);
                this->objects_map[j][i]->setSpriteIndex(index);
            }
        }
    }

    this->objects_map[15][11] = Trader::getInstance();
}

GameMap *GameMap::getInstance()
{
    if(instance == nullptr)
        instance = new GameMap();
    return instance;
}

int GameMap::width()
{
    return this->m_width;
}

int GameMap::height()
{
    return this->m_height;
}

GameObject *GameMap::getObject(int x, int y)
{
    return this->objects_map[x][y];
}

void GameMap::removeObject(int x, int y)
{
    this->objects_map[x][y]->setActivatable(false);
    this->objects_map[x][y]->visiability = false;
}

void GameMap::spawn_skillbook(int x, int y, int sprite_index, QString name, int type, float points, bool aboutResist)
{
    this->objects_map[x][y] = new SkillBook(x, y, sprite_index, name, type, points, aboutResist);
}

void GameMap::spawn_potion(int x, int y, int sprite_index, QString name, int effect_type, float effect_power)
{
    this->objects_map[x][y] = new Potion(x, y, sprite_index, name, effect_type, effect_power);
}

void GameMap::spawn_portal(int x, int y, int toX, int toY, std::function<void()> onTp)
{
    this->objects_map[x][y] = new Portal(toX, toY, onTp);
}

void GameMap::spawn_enemy(int x, int y, int sprite_index, QString name, std::function<void()> onDead, float fire_skill, float ice_skill, float lightning_skill, float fire_resist, float ice_resist, float lightning_resist, float will)
{
    Enemy* enemy = new Enemy(x, y, sprite_index, name, onDead);
    enemy->setProperties(fire_skill, ice_skill, lightning_skill, fire_resist, ice_resist, lightning_resist, will);
    this->objects_map[x][y] = enemy;
}

void GameMap::restart()
{
    for(int x = 0; x < this->m_width; ++x){
        for(int y = 0; y < this->m_height; ++y){
            if(this->objects_map[x][y]->isRestartable)
            {
                this->objects_map[x][y]->setActivatable(true);
                this->objects_map[x][y]->visiability = true;
            }
            if(this->objects_map[x][y]->isEnemy){
                ((Enemy*)this->objects_map[x][y])->restoreHp();
                ((Enemy*)this->objects_map[x][y])->restoreWill();
            }
        }
    }
}


GameMap::GameMap()
{

}
