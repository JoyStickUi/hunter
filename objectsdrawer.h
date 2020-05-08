#ifndef OBJECTSDRAWER_H
#define OBJECTSDRAWER_H

#include <QGraphicsPixmapItem>

class ObjectsDrawer : public QGraphicsPixmapItem
{
public:
    ObjectsDrawer();
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
};

#endif // OBJECTSDRAWER_H
