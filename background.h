#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QFile>
#include <QString>

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsPixmapItem>

class Background : public QGraphicsPixmapItem
{
public:
    static Background *getInstance();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
    Background();
    static Background* instance;
    int** tilemap;
};

#endif // BACKGROUND_H
