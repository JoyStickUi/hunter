#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <QKeyEvent>
#include <QTimer>
#include "textures.h"

#include "button.h"
#include "menuscene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void updateFrame();
private slots:
    /* Слот для обработки сигнала из точки */
    void slotFromStart();
    void slotFromMenu();
    void slotFromInstruction();
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();    
private:
    Ui::MainWindow *ui;
    QTimer* timer;

    MenuScene *scene;
    Button *btn_startGame;
    Button *btn_toInstruction;
    Button *btn_toMenu;
};

#endif // MAINWINDOW_H
