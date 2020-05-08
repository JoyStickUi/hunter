#include "inventory_ui.h"
#include "game.h"
#include "player.h"
#include <QApplication>
#include <QDesktopWidget>

Inventory_UI* Inventory_UI::instance = nullptr;

Inventory_UI* Inventory_UI::getInstance(){
    if(instance == nullptr)
        instance = new Inventory_UI();
        return instance;
}

void Inventory_UI::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(this->visiability){
        int item_scale = Game::getInstance()->items_scale;
        int padding = Game::getInstance()->items_scale * 0.1;
        int width = (item_scale * 2);
        int height = QApplication::desktop()->height() - (item_scale * 2);
        int x = (QApplication::desktop()->width() / 2) - (width  / 2);

        painter->setBrush(QBrush(QColor(0, 0, 0, 200)));
        painter->drawRect(x, item_scale, width, height);
        painter->setPen(QPen(QColor(Qt::white)));
        painter->setFont(QFont("Rubik", item_scale * 0.1f));
        painter->drawText(QRect(x, item_scale, width, item_scale * 0.5), "Инветарь", QTextOption(Qt::AlignmentFlag::AlignCenter));

        std::vector<Item*>* inventory = Player::getInstance()->getInventory();

        painter->setFont(QFont("Rubik", 14));
        painter->drawText(QRect(x + padding, item_scale, width, Game::getInstance()->items_scale), "Название", QTextOption(Qt::AlignmentFlag::AlignVCenter));
        painter->setPen(QPen(QColor(Qt::red)));
        painter->drawText(QRect(x + padding, item_scale, width - (padding * 2), Game::getInstance()->items_scale), "Кол-во очков", QTextOption(Qt::AlignmentFlag::AlignRight | Qt::AlignmentFlag::AlignVCenter));

        painter->setFont(QFont("Rubik", 12));
        int counter = 2;
        for(auto it = inventory->cbegin(); it != inventory->cend(); ++it){
            QString item_title(QString::number(counter - 1));
            item_title.append(": ");
            item_title.append((*it)->getName());
            painter->setPen(QPen(QColor(Qt::white)));
            painter->drawText(QRect(x + padding, item_scale + ((item_scale * 0.1) * counter), width, Game::getInstance()->items_scale), item_title, QTextOption(Qt::AlignmentFlag::AlignVCenter));
            painter->setPen(QPen(QColor(Qt::red)));
            painter->drawText(QRect(x + padding, item_scale + ((item_scale * 0.1) * counter), width - (padding * 2), Game::getInstance()->items_scale), QString::number(static_cast<int>((*it)->getEffectPower() * 100)), QTextOption(Qt::AlignmentFlag::AlignRight | Qt::AlignmentFlag::AlignVCenter));
            ++counter;
        }
    }
}

Inventory_UI::Inventory_UI()
{

}
