#include "brick.h"

Brick::Brick()
{
    img = QImage(":images/brick.png");

    width = img.width();
    height = img.height();

    coordX = 10;
    coordY = 30;

    visible = true;
}
