#include "battle_ui.h"

#include "game.h"
#include <QApplication>
#include <QDesktopWidget>
#include "player.h"
#include "vector"
#include "textures.h"

#include <iostream>

Battle_UI::Battle_UI() : QGraphicsPixmapItem()
{

}

Battle_UI* Battle_UI::instance = nullptr;

Battle_UI *Battle_UI::getInstance()
{
    if(instance == nullptr)
        instance = new Battle_UI();
    return instance;
}

void Battle_UI::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(Game::getInstance()->gameState == Game::Battle){
        painter->setFont(QFont("Rubik", 16));
        painter->setPen(QPen(QColor(Qt::white)));
        painter->setBrush(QBrush(QColor(Qt::black)));
        painter->drawRect(0, 0, Game::getInstance()->items_scale, Game::getInstance()->items_scale * 0.2);
        painter->drawText(QRect(0, 0, Game::getInstance()->items_scale, Game::getInstance()->items_scale * 0.2), "Назад (Q)", QTextOption(Qt::AlignmentFlag::AlignCenter));
        painter->setBrush(QBrush(QColor(105, 106, 106)));
        painter->drawRect(0, QApplication::desktop()->height() - Game::getInstance()->items_scale, QApplication::desktop()->width(), Game::getInstance()->items_scale);        
        int padding = 10;
        painter->drawImage(
                    QRect(
                        padding,
                        QApplication::desktop()->height() - Game::getInstance()->items_scale + padding,
                        QApplication::desktop()->width() * 0.3,
                        Game::getInstance()->items_scale - (padding * 2.5)
                        ),
                    QImage("://img/Ibattle_control.png")
                    );

        painter->setBrush(QBrush(QColor(200, 200, 200)));
        painter->drawRect(QApplication::desktop()->width() - (QApplication::desktop()->width() * 0.15),
                          QApplication::desktop()->height() - Game::getInstance()->items_scale + padding,
                          QApplication::desktop()->width() * 0.15,
                          Game::getInstance()->items_scale - (padding * 2.5));

        std::vector<Item*>* inventory = Player::getInstance()->getInventory();
        int counter = 0;
        for(auto it = inventory->cbegin(); it != inventory->cend(); ++it){
            QRect* rect;
            if(counter < 3){
                rect = new QRect(
                            QApplication::desktop()->width() - (QApplication::desktop()->width() * 0.15) + (counter * ((QApplication::desktop()->width() * 0.15) * 0.33)),
                            (QApplication::desktop()->height() - Game::getInstance()->items_scale + padding),
                            (QApplication::desktop()->width() * 0.15) * 0.33,
                            (Game::getInstance()->items_scale - (padding * 2.5)) * 0.5
                            );
            }else{
                rect = new QRect(
                            QApplication::desktop()->width() - (QApplication::desktop()->width() * 0.15)  + ((counter - 3) * ((QApplication::desktop()->width() * 0.15) * 0.33)),
                            (QApplication::desktop()->height() - (Game::getInstance()->items_scale / 2)),
                            (QApplication::desktop()->width() * 0.15) * 0.33,
                            (Game::getInstance()->items_scale - (padding * 2.5)) * 0.5
                            );
            }
            painter->drawImage(
                        *rect,
                        Textures::getInstance()->getTexture((*it)->getSlotImage())->toImage()
                        );
            delete rect;
            ++counter;
        }

        painter->drawImage(
                    QRect(
                        QApplication::desktop()->width() - (QApplication::desktop()->width() * 0.15),
                        QApplication::desktop()->height() - Game::getInstance()->items_scale + padding,
                        QApplication::desktop()->width() * 0.15,
                        Game::getInstance()->items_scale - (padding * 2.5)
                        ),
                    QImage("://img/items_border.png")
                    );

        if(this->active_skill != NONE){
            switch (this->active_skill) {
                case FIRE:
                {
                    painter->setBrush(QBrush(QColor(255, 0, 0, 100)));
                    painter->setPen(QPen(QColor(255, 0, 0, 100)));
                    painter->drawRect(
                                (padding * 1.5),
                                QApplication::desktop()->height() - Game::getInstance()->items_scale + (padding * 2),
                                ((QApplication::desktop()->width() * 0.3) * 0.25),
                                Game::getInstance()->items_scale - (padding * 4.5)
                                );
                }
                break;
                case ICE:
                {
                    painter->setBrush(QBrush(QColor(0, 0, 255, 100)));
                    painter->setPen(QPen(QColor(0, 0, 255, 100)));
                    painter->drawRect(
                                (padding * 1.5) + ((QApplication::desktop()->width() * 0.3) * 0.25),
                                QApplication::desktop()->height() - Game::getInstance()->items_scale + (padding * 2),
                                ((QApplication::desktop()->width() * 0.3) * 0.25) - (padding * 0.5),
                                Game::getInstance()->items_scale - (padding * 4.5)
                                );
                }
                break;
                case LIGHTNING:
                {
                    painter->setBrush(QBrush(QColor(255, 255, 0, 100)));
                    painter->setPen(QPen(QColor(255, 255, 0, 100)));
                    painter->drawRect(
                                padding + ((QApplication::desktop()->width() * 0.3) * 0.25) * 2,
                                QApplication::desktop()->height() - Game::getInstance()->items_scale + (padding * 2),
                                ((QApplication::desktop()->width() * 0.3) * 0.25) - (padding * 0.5),
                                Game::getInstance()->items_scale - (padding * 4.5)
                                );
                }
                break;
                case INTIMIDATION:
                {
                    painter->setBrush(QBrush(QColor(128, 0, 128, 100)));
                    painter->setPen(QPen(QColor(128, 0, 128, 100)));
                    painter->drawRect(
                                (padding * 0.5) + ((QApplication::desktop()->width() * 0.3) * 0.25) * 3,
                                QApplication::desktop()->height() - Game::getInstance()->items_scale + (padding * 2),
                                ((QApplication::desktop()->width() * 0.3) * 0.25),
                                Game::getInstance()->items_scale - (padding * 4.5)
                                );
                }
                break;
            }
        }
        painter->setBrush(QBrush(QColor(0, 0, 0, 100)));
        painter->setPen(QPen(QColor(0, 0, 0, 100)));
        if(Player::getInstance()->getManaValue() < 0.1f){
            painter->drawRect(
                        (padding * 1.5),
                        QApplication::desktop()->height() - Game::getInstance()->items_scale + (padding * 2),
                        ((QApplication::desktop()->width() * 0.3) * 0.25),
                        Game::getInstance()->items_scale - (padding * 4.5)
                        );
        }
        if(Player::getInstance()->getManaValue() < 0.15f){
            painter->drawRect(
                        (padding * 1.5) + ((QApplication::desktop()->width() * 0.3) * 0.25),
                        QApplication::desktop()->height() - Game::getInstance()->items_scale + (padding * 2),
                        ((QApplication::desktop()->width() * 0.3) * 0.25) - (padding * 0.5),
                        Game::getInstance()->items_scale - (padding * 4.5)
                        );
        }
        if(Player::getInstance()->getManaValue() < 0.25f){
            painter->drawRect(
                        padding + ((QApplication::desktop()->width() * 0.3) * 0.25) * 2,
                        QApplication::desktop()->height() - Game::getInstance()->items_scale + (padding * 2),
                        ((QApplication::desktop()->width() * 0.3) * 0.25) - (padding * 0.5),
                        Game::getInstance()->items_scale - (padding * 4.5)
                        );
        }
        if(Player::getInstance()->getManaValue() < 0.5f){
            painter->drawRect(
                        (padding * 0.5) + ((QApplication::desktop()->width() * 0.3) * 0.25) * 3,
                        QApplication::desktop()->height() - Game::getInstance()->items_scale + (padding * 2),
                        ((QApplication::desktop()->width() * 0.3) * 0.25),
                        Game::getInstance()->items_scale - (padding * 4.5)
                        );
        }
        painter->drawImage(
                    QRect(
                        padding,
                        QApplication::desktop()->height() - Game::getInstance()->items_scale + padding,
                        QApplication::desktop()->width() * 0.3,
                        Game::getInstance()->items_scale - (padding * 2.5)
                        ),
                    QImage("://img/Ibattle_control_FG.png")
                    );
    }
}

void Battle_UI::setActiveSkill(int type)
{
    this->active_skill = type;
}
