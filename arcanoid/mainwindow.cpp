#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // устанавливаем размеры окна
    this->setFixedWidth( screenObj.getWidth() );
    this->setFixedHeight( screenObj.getHeight() );

    endGame = false;
    lockingBroad = false;
    victory = false;

    d = 5;

    timer = new QTimer;
    // метод mainLoop() будет вызываться каждый раз когда переполняется таймер
    connect( timer, SIGNAL(timeout()), this, SLOT(mainLoop()) );

    //все блоки делаются видимыми и им присваиваются определённые координаты
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++) {
            bricksMassiv[i][j].visible = true;
            bricksMassiv[i][j].setCoordX( bricksMassiv[i][j].getCoordX() + (bricksMassiv[i][j].getWidth() + 10) * (i + 1) );
            bricksMassiv[i][j].setCoordY( bricksMassiv[i][j].getCoordY() + (bricksMassiv[i][j].getHeight() + 10) * (j + 1) );
        }
}

MainWindow::~MainWindow()
{
    delete ui;
    QApplication::instance()->quit();
}

void MainWindow::paintEvent(QPaintEvent *) {

    QPainter painter(this);
    painter.drawImage(0, 0, screenObj.getImage());
    painter.drawImage(boardObj.getCoordX(), boardObj.getCoordY(), boardObj.getImage());
    painter.drawImage(ballObj.getCoordX(), ballObj.getCoordY(), ballObj.getImage());


    victory = true; // делаем временно индикатор победы истинным,
                          // а дальше он станет ложным в случае если нарисуется хоть один из кирпичиков
    // рисуем те кирпичики которые не были разрушены
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            if ( bricksMassiv[i][j].visible ) {
                painter.drawImage( bricksMassiv[i][j].getCoordX(), bricksMassiv[i][j].getCoordY(), bricksMassiv[i][j].getImage() );
                victory = false; // если хоть один из кирпичиков нарисовали, то пока что не победили
            }

    QFont font;
    font.setPointSize(35);
    painter.setFont(font);

    if ( (endGame) && (!victory) ) {
        painter.setPen(qRgb(255, 0, 0));    // красный цвет
        painter.drawText(200, 300,  "GAME OVER");
        lockingBroad = false;
    }
    if (victory) {
        painter.setPen(qRgb(0, 255, 0));    // зелёный цвет
        painter.drawText(200, 300,  "WIN ! :)");
        endGame = true;
        lockingBroad = false;
    }

}

void MainWindow::keyPressEvent(QKeyEvent *e) {

    if ( (e->key() == Qt::Key_Space) ) {
        newGame();
        timer->start( (int)(1000 / screenObj.FPS) ); // запускаем таймер, а с ним и mainLoop()
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *e) {

    if ( (lockingBroad) && (e->buttons().testFlag(Qt::LeftButton)) ) { // если игра уже началась и при этом зажата левая клавиша мыши
        setCursor(Qt::BlankCursor); // делаем курсор не видимым

        // перемещаем платформу в пределах экрана
        boardObj.move(e->x(), screenObj.getCoordX(), screenObj.getWidth());
    }

}

void MainWindow::mouseReleaseEvent(QMouseEvent *e) {
    setCursor(Qt::ArrowCursor); // делаем курсор видимым
}

void MainWindow::mainLoop() {

        if (endGame)
            timer->stop();

        // перемещаем шарик
        ballObj.setCoordX( ballObj.getCoordX() + ballObj.getVelocityX() );
        ballObj.setCoordY( ballObj.getCoordY() + ballObj.getVelocityY() );

        QApplication::processEvents();
        checkCollision();

        this->repaint(); // отобразить изменения
}

void MainWindow::checkCollision() {

    // столкновение с левой стенкой экрана
    if (ballObj.getCoordX() <= 0) {
        ballObj.setAngle( 180 - ballObj.getAngle() );
    } else
    // столкновение с правой стенкой экрана
    if (ballObj.getCoordX() + ballObj.getWidth() >= screenObj.getWidth()) {
        ballObj.setAngle( 180 - ballObj.getAngle() );
    } else
    // столкновение с верхней стенкой экрана
    if (ballObj.getCoordY() <= 0) {
        ballObj.setAngle( 360 - ballObj.getAngle() );
    } else
    // столкновение с нижней стенкой экрана
    if (ballObj.getCoordY() + ballObj.getHeight() >= screenObj.getHeight()) {
        endGame = true;
    } else
    // столкновение мяча с платформой
    if ( collisionBallBoard() ) {
            ballObj.setAngle( 360 - ballObj.getAngle() );
    } else
    // столкновение с кирпичами
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            if (bricksMassiv[i][j].visible) { // если этот блок есть (т.е. видимый) проверяем на столкновение с ним
                // с верхней гранью кирпичика
                if ( (ballObj.getCoordX() + ballObj.getWidth() >= bricksMassiv[i][j].getCoordX()) &&
                     (ballObj.getCoordX() <= bricksMassiv[i][j].getCoordX() + bricksMassiv[i][j].getWidth()) &&
                     (ballObj.getCoordY() + ballObj.getHeight() >= bricksMassiv[i][j].getCoordY()) &&
                     (ballObj.getCoordY() + ballObj.getHeight() <= bricksMassiv[i][j].getCoordY() + d) &&
                     (ballObj.getVelocityY() > 0) ) {

                   bricksMassiv[i][j].visible = false;

                   ballObj.setAngle( 360 - ballObj.getAngle() );
                   ballObj.setVelocity( ballObj.getVelocity() + ballObj.getAcceleration());
                   continue;
                }
              // с нижней гранью кирпичика
              if ( (ballObj.getCoordX() + ballObj.getWidth() >= bricksMassiv[i][j].getCoordX()) &&
                   (ballObj.getCoordX() <= bricksMassiv[i][j].getCoordX() + bricksMassiv[i][j].getWidth()) &&
                   (ballObj.getCoordY() <= bricksMassiv[i][j].getCoordY() + bricksMassiv[i][j].getHeight()) &&
                   (ballObj.getCoordY()  >= bricksMassiv[i][j].getCoordY() + d) &&
                   (ballObj.getVelocityY() < 0) ) {

                  bricksMassiv[i][j].visible = false;

                  ballObj.setAngle( 360 - ballObj.getAngle() );
                  ballObj.setVelocity( ballObj.getVelocity() + ballObj.getAcceleration());
                  continue;
              }
              // с левой гранью кирпичика
              if ( (ballObj.getCoordX() + ballObj.getWidth() >= bricksMassiv[i][j].getCoordX()) &&
                   (ballObj.getCoordX() <= bricksMassiv[i][j].getCoordX() + d) &&
                   (ballObj.getCoordY() <= bricksMassiv[i][j].getCoordY() + bricksMassiv[i][j].getHeight()) &&
                   (ballObj.getCoordY() + ballObj.getHeight() >= bricksMassiv[i][j].getCoordY()) &&
                   (ballObj.getVelocityX() > 0) ) {

                  bricksMassiv[i][j].visible = false;

                  ballObj.setAngle( 180 - ballObj.getAngle() );
                  ballObj.setVelocity( ballObj.getVelocity() + ballObj.getAcceleration());
                  continue;
              }
              // с правой гранью кирпичика
              if ( (ballObj.getCoordX() + ballObj.getWidth() >= bricksMassiv[i][j].getCoordX() + d) &&
                   (ballObj.getCoordX() <= bricksMassiv[i][j].getCoordX() + bricksMassiv[i][j].getWidth()) &&
                   (ballObj.getCoordY() <= bricksMassiv[i][j].getCoordY() + bricksMassiv[i][j].getHeight()) &&
                   (ballObj.getCoordY() + ballObj.getHeight() >= bricksMassiv[i][j].getCoordY()) &&
                   (ballObj.getVelocityX() < 0) ) {

                  bricksMassiv[i][j].visible = false;

                  ballObj.setAngle( 180 - ballObj.getAngle() );
                  ballObj.setVelocity( ballObj.getVelocity() + ballObj.getAcceleration() );
                  continue;
              }
            }
}

bool MainWindow::collisionBallBoard() {
    if ( (ballObj.getCoordX() + ballObj.getWidth() >= boardObj.getCoordX()) &&
         (ballObj.getCoordX() <= boardObj.getCoordX() + boardObj.getWidth()) &&
         (ballObj.getCoordY() + ballObj.getHeight() >= boardObj.getCoordY()) &&
         (ballObj.getCoordY() + ballObj.getHeight() <= boardObj.getCoordY() + boardObj.getHeight()) &&
         (ballObj.getVelocityY() > 0) ) {

        // поправка угла движения мяча в зависимости от того, как двигалась платформа (чем быстрее, тем больше поправка)
        float coefficient;
        coefficient = ( boardObj.getCoordX() - boardObj.previousCoordX ) / (screenObj.getWidth() - boardObj.getWidth()); // деление нееобходимо для нормализации ( величина всегда будет меньше 1 )

        ballObj.setAngle( ballObj.getAngle() + coefficient * boardObj.mDeviation);

        return true;
    }
    return false;
}

void MainWindow::newGame() {

    endGame = false;
    lockingBroad = true;
    victory = false;

    // все блоки делаются видимыми и им присваиваются определённые координаты
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            bricksMassiv[i][j].visible = true;

    // перемещаем шарик и платформу в исходное состояние
    boardObj.setCoordX( screenObj.getWidth() / 2 - boardObj.getWidth() / 2 );
    boardObj.previousCoordX = boardObj.getCoordX();
    ballObj.setCoordX( screenObj.getWidth() / 2 - ballObj.getWidth() / 2 );
    ballObj.setCoordY( screenObj.getHeight() - 60);

    // устанавливаем вектор скорости шарика
    ballObj.setAngle(90);
    ballObj.setVelocity(4);
}
