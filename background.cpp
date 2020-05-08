#include "background.h"

#include "game.h"
#include "gamemap.h"
#include "player.h"
#include "textures.h"

#include <QApplication>
#include <QDesktopWidget>

Background* Background::instance = nullptr;

Background *Background::getInstance()
{
    if(instance == nullptr)
        instance = new Background();
    return instance;
}

void Background::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
                    painter->drawPixmap(
                                QPoint(0 + (x_counter * game_scene->items_scale) - delta_x, 0 + (y_counter * game_scene->items_scale) - delta_y),
                                textures->getTexture(this->tilemap[px][py])->scaled(game_scene->items_scale, game_scene->items_scale)
                                );
                    ++y_counter;
                }                
                ++x_counter;
            }             
        }
        break;
        case Game::Battle:
        {            
            painter->drawPixmap(
                        QPoint(0, 0),
                        Textures::getInstance()->getTexture(Textures::getBattleBG())->scaled(QApplication::desktop()->width(), QApplication::desktop()->height() - Game::getInstance()->items_scale)
                        );                       
        }
        break;
        case Game::Paused:
        {

        }
        break;
        case Game::DEAD:
        {
            painter->setBrush(QBrush(QColor(Qt::black)));
            painter->setPen(QPen(QColor(Qt::black)));
            painter->drawRect(0, 0, QApplication::desktop()->width(), QApplication::desktop()->height());
            painter->setPen(QPen(QColor(Qt::red)));
            painter->setFont(QFont("Rubik", 32));
            painter->drawText(
                        QRect(
                            (QApplication::desktop()->width() / 2) - ((10 * 32) / 2),
                            (QApplication::desktop()->height() / 2) + 16,
                            (10 * 32),
                            64
                             ),
                        "Вы мертвы!"
                        );
            painter->setPen(QPen(QColor(Qt::white)));
            painter->setFont(QFont("Rubik", 16));
            painter->drawText(
                        QRect(
                            (QApplication::desktop()->width() / 2) - ((25 * 16) / 2),
                            (QApplication::desktop()->height() / 2) + 64,
                            (10 * 32),
                            64
                             ),
                        "Для продолжения нажмите: R"
                        );
        }
        break;
        case Game::END:
        {
            painter->setBrush(QBrush(QColor(Qt::black)));
            painter->setPen(QPen(QColor(Qt::black)));
            painter->drawRect(0, 0, QApplication::desktop()->width(), QApplication::desktop()->height());
            painter->setPen(QPen(QColor(Qt::white)));
            painter->setFont(QFont("Rubik", 20));
            painter->drawText(QRect(0, 0, QApplication::desktop()->width(), QApplication::desktop()->height()), "Конец игры", QTextOption(Qt::AlignmentFlag::AlignCenter));
        }
        break;
        case Game::START:
        {
            painter->setPen(QPen(QColor(Qt::black)));
            painter->setBrush(QBrush(QColor(Qt::black)));
            painter->drawRect(0, 0, QApplication::desktop()->width(), QApplication::desktop()->height());
            painter->setPen(QPen(QColor(Qt::white)));
            painter->setFont(QFont("Rubik", 18));
            painter->drawText(QRect(0, 0, QApplication::desktop()->width(), Game::getInstance()->items_scale / 2), "Том II Эллиот Ооль 'Охота на ведьм'", QTextOption(Qt::AlignmentFlag::AlignCenter));
            painter->setFont(QFont("Rubik", 16));
            QString text(
                        "Почему не поднять голос против злодеев прошлого, знаменитых основоположников суеверия и фанатизма, тех, кто впервые схватил на алтаре нож, чтобы отдать на заклание строптивых, не желающих принять их воззрения?"
                        );
            painter->drawText(QRect(Game::getInstance()->items_scale * 0.3, Game::getInstance()->items_scale / 2, QApplication::desktop()->width() - (Game::getInstance()->items_scale * 0.6), QApplication::desktop()->height() - (Game::getInstance()->items_scale)), Qt::TextWrapAnywhere, text);
            painter->setFont(QFont("Rubik", 12));
            painter->drawText(QRect(0, QApplication::desktop()->height() - (Game::getInstance()->items_scale * 2), QApplication::desktop()->width(),Game::getInstance()->items_scale), "Для продолжения нажмите: SPACE", QTextOption(Qt::AlignmentFlag::AlignCenter));
        }
        break;
        case Game::Trade:
        {
            painter->drawPixmap(
                        QRect(0, 0, QApplication::desktop()->width(), QApplication::desktop()->height()),
                        *Textures::getInstance()->getTexture(Textures::TRADE_BG)
                        );
            painter->drawPixmap(
                        QRect(0, 0, QApplication::desktop()->width(), QApplication::desktop()->height()),
                        *Textures::getInstance()->getTexture(Textures::TRADE_MG)
                        );            
        }
        break;
    }
}

Background::Background() : QGraphicsPixmapItem ()
{
    QFile mapJson;
    mapJson.setFileName("://json/map.json");

    //add try catch
    mapJson.open(QIODevice::ReadOnly);

    QJsonDocument dom = QJsonDocument::fromJson(mapJson.readAll());
    QJsonObject obj = dom.object();
    QJsonArray array = obj.take("map").toArray();

    int mapWidth = array.at(0).toArray().size();
    int mapHeight = array.size();

    GameMap::getInstance()->setSize(mapWidth, mapHeight);

    this->tilemap = new int*[mapWidth];

    for(int i = 0; i < mapWidth; ++i){
        this->tilemap[i] = new int[mapHeight];
    }

    QJsonArray x;
    for(int i = 0; i < mapHeight; ++i){
        x = array.at(i).toArray();
        for(int j = 0; j < mapWidth; ++j){
           this->tilemap[j][i] = x.at(j).toInt();
        }
    }    
}
