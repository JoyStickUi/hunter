#ifndef TRADER_UI_H
#define TRADER_UI_H

#include <QGraphicsPixmapItem>
#include <QPainter>

class Trader_UI : public QGraphicsPixmapItem
{
public:
    enum STATE{
        NONE,
        TRADER,
        PLAYER
    };
    static Trader_UI* getInstance();
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    int state = NONE;
private:
    Trader_UI();
    static Trader_UI* instance;
};

#endif // TRADER_UI_H
