#include "questlogger.h"

#include "game.h"
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>

QuestLogger* QuestLogger::instance = nullptr;

QuestLogger *QuestLogger::getInstance()
{
    if(instance == nullptr)
        instance = new QuestLogger();
    return instance;
}

void QuestLogger::addQuest(QString header, QString description)
{
    Quest* quest = new Quest();
    quest->header = header;
    quest->description = description;
    this->quests.push_back(quest);
}

void QuestLogger::removeQuest(int index)
{
    if(this->quests.size() > index){
        this->quests.erase(this->quests.begin() + index);
    }
}

void QuestLogger::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(this->quests.size() && Game::getInstance()->gameState == Game::Adventure){
        Quest* quest = (*this->quests.begin());
        painter->setFont(QFont("Rubik", 16));
        painter->setPen(QPen(QColor(255, 255, 255, 180)));
        painter->setBrush(QBrush(QColor(0, 0, 0, 150)));
        int width = Game::getInstance()->items_scale * 1.5;
        int height = Game::getInstance()->items_scale;
        int x = QApplication::desktop()->width() - width;
        int y = (QApplication::desktop()->height() / 2) - (height / 2);
        int padding = 10;
        painter->drawRoundRect(QRect(x, y, width, height), 5, 5);
        painter->drawText(QRect(x + padding, y + padding, width - (padding * 2), height  - (height * 0.7) - (padding * 2)), quest->header, QTextOption(Qt::AlignmentFlag::AlignLeft));
        painter->setFont(QFont("Rubik", 14));
        painter->drawText(QRect(x + padding, y + (height * 0.2) + padding, width - (padding * 2), height  - (height * 0.3) - (padding * 2)), Qt::TextWordWrap, quest->description);
    }
}

QuestLogger::QuestLogger()
{

}
