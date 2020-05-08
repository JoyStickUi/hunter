#ifndef INVENTORY_UI_H
#define INVENTORY_UI_H

#include <QGraphicsPixmapItem>
#include <QPainter>

class Inventory_UI : public QGraphicsPixmapItem
{
public:
    static Inventory_UI* getInstance();
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    bool visiability = false;
private:
    static Inventory_UI* instance;
    Inventory_UI();
};

#endif // INVENTORY_UI_H
