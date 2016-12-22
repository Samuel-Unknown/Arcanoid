#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>

#include "screen.h"
#include "board.h"
#include "ball.h"
#include "brick.h"

const int M = 7; // строк кирпичей
const int N = 6; // столбцов кирпичей

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void checkCollision();      // проверка столкновений
    bool collisionBallBoard(); // столкновение мяча с платформой

public slots:
    void mainLoop(); // содержит в себе расчёт столкновений и отрисовку
                            // вызывается циклически по таймеру

private:
    Ui::MainWindow *ui;
    bool endGame;        // индикатор того что игра завершилась
    bool lockingBroad;  // индикатор блокировки платформы
    bool victory;           // индикатор победы


protected:
    virtual void paintEvent(QPaintEvent *);                  // отвечает за отрисовку
    virtual void keyPressEvent(QKeyEvent *e);              // отлаливает события клавиатуры
    virtual void mouseMoveEvent(QMouseEvent *e);      // срабатывает при перемещении мыши если хотя бы одна из кнопок на ней нажаты
    virtual void mouseReleaseEvent(QMouseEvent *e);   // срабатывает при отпускании мыши

public: // объекты игры
    Screen screenObj;
    Board boardObj;
    Ball ballObj;
    Brick bricksMassiv[M][N];
    QTimer *timer;

    float d;    // максимальная глубина проникновения мяча в кирпичик при соударении с ним (в пикселях)

    void newGame(); // возвращает объекты игры в исходное состояние

signals:
    void timeOut();
};

#endif // MAINWINDOW_H
