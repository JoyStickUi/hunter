#include "stat_ui.h"

#include "player.h"
#include "game.h"
#include <QApplication>
#include <QDesktopWidget>

Stat_UI* Stat_UI::instance = nullptr;

Stat_UI *Stat_UI::getInstance()
{
    if(instance == nullptr)
        instance = new Stat_UI();
    return instance;
}

void Stat_UI::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(this->visiability){
        painter->setBrush(QBrush(QColor(0, 0, 0, 200)));
        int item_scale = Game::getInstance()->items_scale;
        painter->drawRect(item_scale, item_scale, QApplication::desktop()->width() - (item_scale * 2), QApplication::desktop()->height() - (item_scale * 2));
        painter->setPen(QPen(QColor(Qt::white)));
        painter->setFont(QFont("Rubik", item_scale * 0.1f));
        painter->drawText(QPoint(item_scale + ((QApplication::desktop()->width() - (item_scale * 2)) / 2) - ((item_scale * 0.1f) * 4.5), item_scale + 20), "Характеристика");

        //fire skill
        painter->setPen(QPen(QColor(Qt::white)));
        painter->drawText(QPoint(20 + item_scale, (item_scale * 1.5) + 20), "Огненная магия: ");
        for(int i = 1; i < 11; ++i){
            painter->setBrush(QBrush(QColor(Qt::black)));
            painter->drawRect(20 + (item_scale * 2.5) + (i * (item_scale * 0.1f)), item_scale * 1.53f, item_scale * 0.05f, item_scale * 0.1f);
            if(i <= (10 * Player::getInstance()->getSkillValue(FIRE))){
                painter->setBrush(QBrush(QColor(Qt::red)));
                painter->drawRect(20 + (item_scale * 2.5) + (i * (item_scale * 0.1f)), item_scale * 1.53f, item_scale * 0.05f, item_scale * 0.1f);
                if(i == 10){
                    painter->setPen(QPen(QColor(Qt::red)));
                    painter->drawText(QPoint(20 + (item_scale * 2.5) + ((i + 1) * (item_scale * 0.1f)), (item_scale * 1.5) + 20), "MAX");
                }
            }
        }

        //fire resist
        painter->setPen(QPen(QColor(Qt::white)));
        painter->drawText(QPoint(20 + (item_scale * 4), (item_scale * 1.5) + 20), "Сопротивление огню: ");
        for(int i = 1; i < 6; ++i){
            painter->setBrush(QBrush(QColor(Qt::black)));
            painter->drawRect(20 + (item_scale * 6) + (i * (item_scale * 0.1f)), item_scale * 1.53f, item_scale * 0.05f, item_scale * 0.1f);
            if(i <= (10 * Player::getInstance()->getResistValue(FIRE))){
                painter->setBrush(QBrush(QColor(Qt::red)));
                painter->drawRect(20 + (item_scale * 6) + (i * (item_scale * 0.1f)), item_scale * 1.53f, item_scale * 0.05f, item_scale * 0.1f);
                if(i == 5){
                    painter->setPen(QPen(QColor(Qt::red)));
                    painter->drawText(QPoint(20 + (item_scale * 6) + ((i + 1) * (item_scale * 0.1f)), (item_scale * 1.5) + 20), "MAX");
                }
            }
        }

        //ice skill
        painter->setPen(QPen(QColor(Qt::white)));
        painter->drawText(QPoint(20 + item_scale, (item_scale * 1.74) + 20), "Ледяная магия: ");        
        for(int i = 1; i < 11; ++i){
            painter->setBrush(QBrush(QColor(Qt::black)));
            painter->drawRect(20 + (item_scale * 2.5) + (i * (item_scale * 0.1f)), item_scale * 1.77f, item_scale * 0.05f, item_scale * 0.1f);
            if(i <= (10 * Player::getInstance()->getSkillValue(ICE))){
                painter->setBrush(QBrush(QColor(Qt::blue)));
                painter->drawRect(20 + (item_scale * 2.5) + (i * (item_scale * 0.1f)), item_scale * 1.77f, item_scale * 0.05f, item_scale * 0.1f);
                if(i == 10){
                    painter->setPen(QPen(QColor(Qt::blue)));
                    painter->drawText(QPoint(20 + (item_scale * 2.5) + ((i + 1) * (item_scale * 0.1f)), (item_scale * 1.76) + 20), "MAX");
                }
            }
        }

        //ice resist
        painter->setPen(QPen(QColor(Qt::white)));
        painter->drawText(QPoint(20 + (item_scale * 4), (item_scale * 1.74) + 20), "Сопротивление льду: ");
        for(int i = 1; i < 6; ++i){
            painter->setBrush(QBrush(QColor(Qt::black)));
            painter->drawRect(20 + (item_scale * 6) + (i * (item_scale * 0.1f)), item_scale * 1.77f, item_scale * 0.05f, item_scale * 0.1f);
            if(i <= (10 * Player::getInstance()->getResistValue(ICE))){
                painter->setBrush(QBrush(QColor(Qt::blue)));
                painter->drawRect(20 + (item_scale * 6) + (i * (item_scale * 0.1f)), item_scale * 1.77f, item_scale * 0.05f, item_scale * 0.1f);
                if(i == 5){
                    painter->setPen(QPen(QColor(Qt::blue)));
                    painter->drawText(QPoint(20 + (item_scale * 6) + ((i + 1) * (item_scale * 0.1f)), (item_scale * 1.76) + 20), "MAX");
                }
            }
        }

        //lightning skill
        painter->setPen(QPen(QColor(Qt::white)));
        painter->drawText(QPoint(20 + item_scale, (item_scale * 1.98) + 20), "Магия молний: ");        
        for(int i = 1; i < 11; ++i){
            painter->setBrush(QBrush(QColor(Qt::black)));
            painter->drawRect(20 + (item_scale * 2.5) + (i * (item_scale * 0.1f)), item_scale * 2.01, item_scale * 0.05f, item_scale * 0.1f);
            if(i <= (10 * Player::getInstance()->getSkillValue(LIGHTNING))){
                painter->setBrush(QBrush(QColor(Qt::yellow)));
                painter->drawRect(20 + (item_scale * 2.5) + (i * (item_scale * 0.1f)), item_scale * 2.01, item_scale * 0.05f, item_scale * 0.1f);
                if(i == 10){
                    painter->setPen(QPen(QColor(Qt::yellow)));
                    painter->drawText(QPoint(20 + (item_scale * 2.5) + ((i + 1) * (item_scale * 0.1f)), (item_scale * 2) + 20), "MAX");
                }
            }
        }

        //lightning resist
        painter->setPen(QPen(QColor(Qt::white)));
        painter->drawText(QPoint(20 + (item_scale * 4), (item_scale * 1.98) + 20), "Сопротивление мольниям: ");
        for(int i = 1; i < 6; ++i){
            painter->setBrush(QBrush(QColor(Qt::black)));
            painter->drawRect(20 + (item_scale * 6) + (i * (item_scale * 0.1f)), item_scale * 2.01, item_scale * 0.05f, item_scale * 0.1f);
            if(i <= (10 * Player::getInstance()->getResistValue(LIGHTNING))){
                painter->setBrush(QBrush(QColor(Qt::yellow)));
                painter->drawRect(20 + (item_scale * 6) + (i * (item_scale * 0.1f)), item_scale * 2.01, item_scale * 0.05f, item_scale * 0.1f);
                if(i == 5){
                    painter->setPen(QPen(QColor(Qt::yellow)));
                    painter->drawText(QPoint(20 + (item_scale * 6) + ((i + 1) * (item_scale * 0.1f)), (item_scale * 2) + 20), "MAX");
                }
            }
        }

        //intimidation skill
        painter->setPen(QPen(QColor(Qt::white)));
        painter->drawText(QPoint(20 + item_scale, (item_scale * 2.22) + 20), "Магия страха: ");        
        for(int i = 1; i < 11; ++i){
            painter->setBrush(QBrush(QColor(Qt::black)));
            painter->drawRect(20 + (item_scale * 2.5) + (i * (item_scale * 0.1f)), item_scale * 2.25, item_scale * 0.05f, item_scale * 0.1f);
            if(i <= (10 * Player::getInstance()->getSkillValue(INTIMIDATION))){
                painter->setBrush(QBrush(QColor(Qt::darkMagenta)));
                painter->drawRect(20 + (item_scale * 2.5) + (i * (item_scale * 0.1f)), item_scale * 2.25, item_scale * 0.05f, item_scale * 0.1f);
                if(i == 10){
                    painter->setPen(QPen(QColor(Qt::darkMagenta)));
                    painter->drawText(QPoint(20 + (item_scale * 2.5) + ((i + 1) * (item_scale * 0.1f)), (item_scale * 2.24) + 20), "MAX");
                }
            }
        }        

        painter->setPen(QPen(QColor(Qt::white)));
        QString kills("Побежденно монстров:  ");
        kills.append(QString::number(Player::getInstance()->kills));
        painter->drawText(QPoint(20 + item_scale, (item_scale * 2.46) + 20), kills);

        QString money("Деньги:  ");
        money.append(QString::number(Player::getInstance()->getMoney()));
        painter->drawText(QPoint(20 + (item_scale * 3), (item_scale * 2.46) + 20), money);
    }
}

Stat_UI::Stat_UI()
{

}
