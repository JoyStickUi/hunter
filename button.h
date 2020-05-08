#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsItem>
#include <QPainter>

class Button : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    QString ButtonText;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    explicit Button(QObject *parent = 0);

signals:
    /* Сигнал, который будет посылаться в том случае,
     * если произошел клик мышью по объекту
     * */
    void clickSignal();

protected:
    /* Перегружаем метод нажатия мышью, для его перехвата
     * */
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

};

#endif // BUTTON_H
