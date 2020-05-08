#ifndef QUESTLOGGER_H
#define QUESTLOGGER_H

#include <QGraphicsPixmapItem>
#include "quest.h"

class QuestLogger : public QGraphicsPixmapItem
{
public:
    static QuestLogger* getInstance();
    void addQuest(QString header, QString description);
    void removeQuest(int index);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
private:
    QuestLogger();
    std::vector<Quest*> quests;
    static QuestLogger* instance;
};

#endif // QUESTLOGGER_H
