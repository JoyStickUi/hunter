#ifndef STAT_UI_H
#define STAT_UI_H

#include <QGraphicsPixmapItem>
#include <QPainter>

class Stat_UI : public QGraphicsPixmapItem
{
public:
    static Stat_UI* getInstance();
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    bool visiability = false;
private:
    Stat_UI();
    static Stat_UI* instance;
};

#endif // STAT_UI_H
