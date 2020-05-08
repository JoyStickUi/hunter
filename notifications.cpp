#include "notifications.h"

#include <QTextItem>
#include <QApplication>
#include <QDesktopWidget>
#include "game.h"

Notifications* Notifications::instance = nullptr;

Notifications::Notifications() : QGraphicsPixmapItem()
{

}

Notifications *Notifications::getInstance()
{
    if(instance == nullptr)
        instance = new Notifications();
    return instance;
}

void Notifications::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{    
    if(previous_game_mode != Game::getInstance()->gameState)
        counter = 0;
    if(counter != 0){
        int fSize = (Game::getInstance()->items_scale * 0.1);
        int padding = 5;
        painter->setBrush(QBrush(QColor(Qt::black)));
        painter->drawRect((QApplication::desktop()->width() / 2) - ((this->notification.size() * fSize) / 2) - (padding * 1.2), Game::getInstance()->items_scale - fSize - (padding * 1.2), this->notification.size() * fSize + (2.4 * padding), fSize + (2.4 * padding));
        painter->setBrush(QBrush(QColor(Qt::white)));
        painter->drawRect((QApplication::desktop()->width() / 2) - ((this->notification.size() * fSize) / 2) - padding, Game::getInstance()->items_scale - fSize - padding, this->notification.size() * fSize + (2 * padding), fSize + (2 * padding));
        painter->setPen(QPen(QColor(Qt::black)));
        painter->setFont(QFont("Rubik", fSize));
        painter->drawText(
                    QRect(
                        (QApplication::desktop()->width() / 2) - ((this->notification.size() * fSize) / 2) - padding, Game::getInstance()->items_scale - fSize - padding, this->notification.size() * fSize + (2 * padding), fSize + (2 * padding)
                        ),
                    this->notification,
                    QTextOption(Qt::AlignmentFlag::AlignCenter)
                    );
        --counter;
    }
    previous_game_mode = Game::getInstance()->gameState;
}

void Notifications::makeNotification(QString string)
{
    this->notification = string;
    this->counter = 100;
}
