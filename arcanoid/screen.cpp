#include "screen.h"

Screen::Screen()
{
    img = QImage(":images/screen.png");

    coordX =0;
    coordY = 0;

    height = 480;
    width = 640;

    FPS = 60;
}
