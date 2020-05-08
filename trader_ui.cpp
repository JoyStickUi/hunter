#include "trader_ui.h"

#include "game.h"
#include "textures.h"
#include "player.h"
#include "trader.h"
#include <QApplication>
#include <QDesktopWidget>

Trader_UI::Trader_UI() : QGraphicsPixmapItem()
{

}

Trader_UI* Trader_UI::instance = nullptr;

Trader_UI *Trader_UI::getInstance()
{
    if(instance == nullptr)
        instance = new Trader_UI();
    return instance;
}

void Trader_UI::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(Game::getInstance()->gameState == Game::Trade){
        int padding = Game::getInstance()->items_scale * 0.1;
        int width = (QApplication::desktop()->width() / 2) - (padding * 1.5);
        int height = (QApplication::desktop()->height() / 2) - (padding * 2);

        painter->setBrush(QBrush(QColor(0, 0, 0, 200)));
        painter->drawRect(padding, QApplication::desktop()->height() - padding - height, width, height);
        painter->drawRect(QApplication::desktop()->width() - padding - width, QApplication::desktop()->height() - padding - height, width, height);

        painter->setFont(QFont("Rubik", 16));

        if(this->state == TRADER)
        {
            painter->setPen(QPen(QColor(Qt::red)));
        }
        else{
            painter->setPen(QPen(QColor(Qt::white)));
        }
        painter->drawText(QRect(padding, QApplication::desktop()->height() - padding - height, width, Game::getInstance()->items_scale * 0.5), "Купить (T)", QTextOption(Qt::AlignmentFlag::AlignCenter));

        if(this->state == PLAYER)
        {
            painter->setPen(QPen(QColor(Qt::red)));
        }
        else{
            painter->setPen(QPen(QColor(Qt::white)));
        }
        painter->drawText(QRect(QApplication::desktop()->width() - padding - width, QApplication::desktop()->height() - padding - height, width, Game::getInstance()->items_scale * 0.5), "Инвентарь (I)", QTextOption(Qt::AlignmentFlag::AlignCenter));


        painter->setPen(QPen(QColor(Qt::white)));

        QString money("Деньги: ");
        money.append(QString::number(Player::getInstance()->getMoney()));

        painter->drawRect(0, 0, Game::getInstance()->items_scale, Game::getInstance()->items_scale * 0.2);
        painter->drawText(QRect(0, 0, Game::getInstance()->items_scale, Game::getInstance()->items_scale * 0.2), money, QTextOption(Qt::AlignmentFlag::AlignCenter));
        painter->drawRect(0, (Game::getInstance()->items_scale * 0.2 + padding), Game::getInstance()->items_scale, Game::getInstance()->items_scale * 0.2);
        painter->drawText(QRect(0, (Game::getInstance()->items_scale * 0.2 + padding), Game::getInstance()->items_scale, Game::getInstance()->items_scale * 0.2), "Назад (Space)", QTextOption(Qt::AlignmentFlag::AlignCenter));

        std::vector<Item*>* inventory = Player::getInstance()->getInventory();

        painter->setFont(QFont("Rubik", 14));
        painter->drawText(QRect(QApplication::desktop()->width() - width, QApplication::desktop()->height() - padding - height + ((Game::getInstance()->items_scale * 0.2)), width, Game::getInstance()->items_scale * 0.5), "Название", QTextOption(Qt::AlignmentFlag::AlignVCenter));
        painter->setPen(QPen(QColor(Qt::red)));
        painter->drawText(QRect(QApplication::desktop()->width() - width, QApplication::desktop()->height() - padding - height + ((Game::getInstance()->items_scale * 0.2)), width - (padding * 2), Game::getInstance()->items_scale * 0.5), "Кол-во очков", QTextOption(Qt::AlignmentFlag::AlignCenter));
        painter->setPen(QPen(QColor(Qt::yellow)));
        painter->drawText(QRect(QApplication::desktop()->width() - width, QApplication::desktop()->height() - padding - height + ((Game::getInstance()->items_scale * 0.2)), width - (padding * 2), Game::getInstance()->items_scale * 0.5), "Цена", QTextOption(Qt::AlignmentFlag::AlignRight | Qt::AlignmentFlag::AlignVCenter));


        painter->setFont(QFont("Rubik", 12));
        int counter = 2;
        for(auto it = inventory->cbegin(); it != inventory->cend(); ++it){
            QString item_title(QString::number(counter - 1));
            item_title.append(": ");
            item_title.append((*it)->getName());
            painter->setPen(QPen(QColor(Qt::white)));
            painter->drawText(QRect(QApplication::desktop()->width() - width, QApplication::desktop()->height() - padding - height + ((Game::getInstance()->items_scale * 0.2) * counter), width, Game::getInstance()->items_scale * 0.5), item_title, QTextOption(Qt::AlignmentFlag::AlignVCenter));
            painter->setPen(QPen(QColor(Qt::red)));
            painter->drawText(QRect(QApplication::desktop()->width() - width, QApplication::desktop()->height() - padding - height + ((Game::getInstance()->items_scale * 0.2) * counter), width - (padding * 2), Game::getInstance()->items_scale * 0.5), QString::number(static_cast<int>((*it)->getEffectPower() * 100)), QTextOption(Qt::AlignmentFlag::AlignCenter));
            painter->setPen(QPen(QColor(Qt::yellow)));
            painter->drawText(QRect(QApplication::desktop()->width() - width, QApplication::desktop()->height() - padding - height + ((Game::getInstance()->items_scale * 0.2) * counter), width - (padding * 2), Game::getInstance()->items_scale * 0.5), QString::number(static_cast<int>((*it)->price / 2)), QTextOption(Qt::AlignmentFlag::AlignRight | Qt::AlignmentFlag::AlignVCenter));
            ++counter;
        }

        std::vector<Item*>* trader_inventory = Trader::getInstance()->getInventory();

        painter->setPen(QPen(QColor(Qt::white)));
        painter->setFont(QFont("Rubik", 14));
        painter->drawText(QRect(padding * 2, QApplication::desktop()->height() - padding - height + ((Game::getInstance()->items_scale * 0.2)), width, Game::getInstance()->items_scale * 0.5), "Название", QTextOption(Qt::AlignmentFlag::AlignVCenter));
        painter->setPen(QPen(QColor(Qt::red)));
        painter->drawText(QRect(padding * 2, QApplication::desktop()->height() - padding - height + ((Game::getInstance()->items_scale * 0.2)), width - (padding * 2), Game::getInstance()->items_scale * 0.5), "Кол-во очков", QTextOption(Qt::AlignmentFlag::AlignCenter));
        painter->setPen(QPen(QColor(Qt::yellow)));
        painter->drawText(QRect(padding * 2, QApplication::desktop()->height() - padding - height + ((Game::getInstance()->items_scale * 0.2)), width - (padding * 2), Game::getInstance()->items_scale * 0.5), "Цена", QTextOption(Qt::AlignmentFlag::AlignRight | Qt::AlignmentFlag::AlignVCenter));

        painter->setFont(QFont("Rubik", 12));
        counter = 2;
        for(auto it = trader_inventory->cbegin(); it != trader_inventory->cend(); ++it){
            QString item_title(QString::number(counter - 1));
            item_title.append(": ");
            item_title.append((*it)->getName());
            painter->setPen(QPen(QColor(Qt::white)));
            painter->drawText(QRect(padding * 2, QApplication::desktop()->height() - padding - height + ((Game::getInstance()->items_scale * 0.2) * counter), width, Game::getInstance()->items_scale * 0.5), item_title, QTextOption(Qt::AlignmentFlag::AlignVCenter));
            painter->setPen(QPen(QColor(Qt::red)));
            painter->drawText(QRect(padding * 2, QApplication::desktop()->height() - padding - height + ((Game::getInstance()->items_scale * 0.2) * counter), width - (padding * 2), Game::getInstance()->items_scale * 0.5), QString::number(static_cast<int>((*it)->getEffectPower() * 100)), QTextOption(Qt::AlignmentFlag::AlignCenter));
            painter->setPen(QPen(QColor(Qt::yellow)));
            painter->drawText(QRect(padding * 2, QApplication::desktop()->height() - padding - height + ((Game::getInstance()->items_scale * 0.2) * counter), width - (padding * 2), Game::getInstance()->items_scale * 0.5), QString::number(static_cast<int>((*it)->price)), QTextOption(Qt::AlignmentFlag::AlignRight | Qt::AlignmentFlag::AlignVCenter));
            ++counter;
        }
    }
}
