#ifndef NOTIFICATIONS_H
#define NOTIFICATIONS_H

#include <QGraphicsPixmapItem>
#include <QPainter>

class Notifications : public QGraphicsPixmapItem
{
public:
    static Notifications* getInstance();
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void makeNotification(QString string);
private:
    Notifications();
    static Notifications* instance;
    int previous_game_mode = 0;
    //notification timer
    int counter = 0;
    QString notification;
};

#endif // NOTIFICATIONS_H
