#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "gamescene.h"
#include <QShortcut>

void MainWindow::updateFrame()
{
    ui->graphicsView->viewport()->update();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("2D RPG");

    ui->centralWidget->resize(QSize(QApplication::desktop()->width(), QApplication::desktop()->height()));

    //attach esc key to close slot
    QShortcut* ev = new QShortcut(this);
    ev->setKey(Qt::Key_Escape);
    connect(ev, SIGNAL(activated()), this, SLOT(close()));

    ui->graphicsView->move(0, 0);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->resize(ui->centralWidget->size());
    ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    Textures::getInstance();
    GameScene::getInstance()->setSceneRect(0, 0, ui->graphicsView->width(),  ui->graphicsView->height());


        scene = new MenuScene();
        btn_startGame = new Button();
        btn_toInstruction = new Button();
        btn_toMenu = new Button();

        scene->setSceneRect((this->width()/2*(-1))-20, (this->height()/2*(-1))-20, this->width()+40, this->height()+60);
        scene->setImg("menu");

        btn_startGame->ButtonText="   Начать";
        btn_toInstruction->ButtonText="Инструкция";
        btn_toMenu->ButtonText="   В меню";

        /* Подключаем сигналы кнопок к СЛОТам в главном классе */
        connect(btn_startGame, SIGNAL(clickSignal()), this, SLOT(slotFromStart()));
        connect(btn_toInstruction, SIGNAL(clickSignal()), this, SLOT(slotFromInstruction()));
        connect(btn_toMenu, SIGNAL(clickSignal()), this, SLOT(slotFromMenu()));

        /* Устанавливаем графическую сцену в виджет */
        ui->graphicsView->setScene(scene);

        btn_startGame->setPos(0, 40);
        scene->addItem(btn_startGame);
        scene->update(-600,-300,1200,600);
        btn_toInstruction->setPos(0, 140);
        scene->addItem(btn_toInstruction);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotFromStart()
{
    scene->deleteLater();
    ui->graphicsView->setScene(GameScene::getInstance());

    //updating frame timer
    this->timer = new QTimer(this);
    connect(this->timer, SIGNAL(timeout()), this, SLOT(updateFrame()));
    this->timer->start(25);
}

void MainWindow::slotFromInstruction()
{
    scene->setImg("instruction");
    scene->removeItem(btn_toInstruction);
    scene->removeItem(btn_startGame);
    btn_toMenu->setPos(0, 200);
    scene->addItem(btn_toMenu);
}

void MainWindow::slotFromMenu()
{
    scene->removeItem(btn_toMenu);
    scene->addItem(btn_startGame);
    scene->addItem(btn_toInstruction);
    scene->setImg("menu");
}
