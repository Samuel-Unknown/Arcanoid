#include "ball.h"

Ball::Ball()
{
    img.load("images/ball.png");

    width = img.width();
    height = img.height();

    coordX = 320 - (width / 2);
    coordY = 420;

    velocity = 3;
    angle = 90;
    acceleration = 0.1;
}
