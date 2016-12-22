#include "board.h"

Board::Board()
{
    img = QImage(":images/board.png");

    width = img.width();
    height = img.height();

    coordX = 320 - (width / 2);
    coordY = 445;
    previousCoordX = coordX;

    mDeviation = 5000;
}

void Board::move(float x, float leftBorder, float rightBorder) {

    previousCoordX = getCoordX();

    if (x < leftBorder)
        setCoordX(0);
    else if (x > rightBorder - getWidth())
        setCoordX(rightBorder - getWidth());
    else
        setCoordX(x);
}
