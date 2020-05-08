#include "menuscene.h"
#include <QApplication>
#include <QDesktopWidget>

MenuScene::MenuScene()
{

}

void MenuScene::setImg(QString str){
    if (str == "menu"){
        QImage resurs("://img/StartWindow.jpg");
        this->img = resurs;
    }else{
        QImage resurs("://img/Control.jpg");
        this->img = resurs;
    };
    this->update();
}



void MenuScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QRect recrangle(-(QApplication::desktop()->width()/2), -(QApplication::desktop()->height()/2), QApplication::desktop()->width(), QApplication::desktop()->height() + 100);
    painter->drawImage(recrangle, this->img);

    QGraphicsScene::drawBackground(painter, rect);
}
