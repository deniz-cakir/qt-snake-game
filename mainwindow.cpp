#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Config.h"
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QRandomGenerator>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{

    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setScene(scene);

    ui->graphicsView->setBackgroundBrush(backgroundBrush);

    timer = new QTimer (this);
    area = new SegmentedArea();
    snake = new Snake();
    element = new Element (0, 0);

    snake->setFocus();

    scene->addItem(area);
    scene->addItem(snake);

    connect(timer, SIGNAL(timeout()), this, SLOT(advanceSnake()));
    connect(ui->restart, SIGNAL(clicked()), this, SLOT(restart()));
    timer->start(pace);

    addRandomElement();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete area;
    delete snake;
    delete element;
}

void MainWindow::advanceSnake()
{
    snake->advanceSnake();
    checkCollision();
    scene->update();
    qInfo () << snake->getCakeStat();
}

void MainWindow::addRandomElement()
{
    delete element;

    int randX = QRandomGenerator::global()->bounded(1, elementCount - 1);
    int randY = QRandomGenerator::global()->bounded(1, elementCount - 1);

    element = new Element (randX * elementSize, randY * elementSize);
    scene ->addItem(element);
}

void MainWindow::checkCollision()
{
    if (snake->collidesWithItem(area))
    {
        timer->stop();
        qInfo () << "Oyun bitti";
    }
    if (snake->collidesWithItem(element))
    {
        addRandomElement();
        snake->cakeEaten();

        int score = ui->score->text().toInt();

        score += 100;

        ui->score->setText(QString::number(score));
        qInfo () << snake->getCakeStat();
    }
}

void MainWindow::restart()
{
    delete snake;
    snake = new Snake();
    scene->addItem(snake);

    ui->score->setText(QString::number(0));

    snake->setFocus();

    addRandomElement();
    timer->start(pace);
}











