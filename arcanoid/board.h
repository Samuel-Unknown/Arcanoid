#ifndef BOARD_H
#define BOARD_H

#include "gameobject.h"

class Board : public GameObject
{
public:
    Board();
    float mDeviation;    // множитель для расчёта отклонение угла при соударении с платформой
    float previousCoordX; // предыдущее значение координаты X
    void move(float x, float leftBorder, float rightBorder); // подвинуть платформу на x пикселей,
                                                                             // leftBorder и rightBorder это границы в которых может перемещаться платформа
                                                                             // по сути границы экрана
};

#endif // BOARD_H
