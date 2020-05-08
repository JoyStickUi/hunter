#include "objectsdrawer.h"

#include "game.h"
#include "player.h"
#include "gamemap.h"
#include "textures.h"

ObjectsDrawer::ObjectsDrawer()
{

}

void ObjectsDrawer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    switch (Game::getInstance()->gameState) {
        case Game::Adventure:
        {
            Player* player = Player::getInstance();
            Textures* textures = Textures::getInstance();
            Game* game_scene = Game::getInstance();

            int x = (player->x() + (player->width() / 2)) / game_scene->items_scale;
            int y = (player->y() + (player->height() / 2)) / game_scene->items_scale;
            int delta_x = (player->x() + (player->width() / 2)) % game_scene->items_scale;
            int delta_y = (player->y() + (player->height() / 2)) % game_scene->items_scale;
            int x_counter = 0;
            int y_counter = 0;

            for(int px = x - 5; px < x + 6; ++px){
                y_counter = 0;
                for(int py = y - 3; py < y + 4; ++py){
                    GameObject* obj = GameMap::getInstance()->getObject(px, py);
                    if(obj->visiability){
                        int sp_indx = obj->getSpriteIndex();
                        if(sp_indx)
                            painter->drawPixmap(
                                        QPoint(0 + (x_counter * game_scene->items_scale) - delta_x, 0 + (y_counter * game_scene->items_scale) - delta_y),
                                        textures->getTexture(sp_indx)->scaled(game_scene->items_scale, game_scene->items_scale)
                                        );
                    }
                    ++y_counter;
                }
                ++x_counter;
            }
        }
        break;
        case Game::Battle:
        {
        }
        break;
        case Game::Paused:
        {

        }
        break;
    }
}
