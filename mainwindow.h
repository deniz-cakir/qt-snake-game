#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "segmentedarea.h"
#include "snake.h"
#include "element.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    SegmentedArea* area;
    Snake* snake;
    Element* element;

private:
    Ui::MainWindow *ui;
    QTimer* timer;
    QGraphicsScene* scene;

    void addRandomElement();
    void checkCollision();

private slots:
    void restart();
    void advanceSnake();
};
#endif // MAINWINDOW_H
