#include "button.h"

Button::Button(QObject *parent)
    : QObject(parent), QGraphicsItem()
{

}

QRectF Button::boundingRect() const
{
    /* возвращаем координаты расположения кнопки
     * по ним будет определяться нажатие кнопки
     * */
    return QRectF(-150,-30,300,60);
}

void Button::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QFont font = painter->font() ;
    font.setPixelSize(40);
    // Устанавливаем кисть в QPainter и отрисовываем кнопку
    painter->setBrush(Qt::black);
    painter->setPen(Qt::white);
    painter->drawRect(QRectF(-150, -30, 300, 60));
    painter->setFont(font);
    painter->drawText(QRectF(-100, -25, 250, 60), this->ButtonText);
        Q_UNUSED(option);
        Q_UNUSED(widget);
}

/* Переопределив метод перехвата события нажатия кнопки мыши,
 * добавляем посылку СИГНАЛА от объекта
 * */
void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clickSignal();
    // Вызываем родительскую функцию события нажатия кнопки мыши
    QGraphicsItem::mousePressEvent(event);
}
