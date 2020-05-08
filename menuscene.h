#ifndef MENUSCENE_H
#define MENUSCENE_H


#include <QObject>
#include <QGraphicsScene>
#include <QPainter>


class MenuScene : public QGraphicsScene
{

public:
    MenuScene();
    void setImg(QString str);
    QImage img;


Q_OBJECT


protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;
};

#endif // MENUSCENE_H
