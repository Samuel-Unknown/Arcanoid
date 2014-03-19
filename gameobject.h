#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QImage>
#include <math.h>

class GameObject
{
protected:
    QImage img; // изображение объекта

    float coordX; // координата x левой верхней точки прямоугольника с ихображением
    float coordY; // координата y

    float width;  // ширина объекта
    float height; // высота объекта

    float velocity;       // модуль вектора скорости
    float angle;           // угол вектора скорости относительно оси x (в градусах)
    float acceleration; // ускорение

public:
    GameObject();
    QImage getImage(); // возвращает изображение

    float getWidth();       // возвращает высоту объекта
    float getHeight();      // возвращает ширину объекта

    float getCoordX();      // возвращает координату "x" объекта
    float getCoordY();      // возвращает координату "y" объекта

    void setCoordX(float x); // изменяет координату "x" объекта
    void setCoordY(float y); // изменяет координату "y" объекта

    void setVelocity(float v); // изменить модуль вектора скорости
    float getVelocity();         // возвращает модуль вектора скорости
    float getVelocityX();       // возвращает иксовую компоненту скорости
    float getVelocityY();       // возвращает игриковую компоненту скорости


    void setAngle(float a); // изменить угол
    float getAngle();         // возвращает угол в градусах

    float getAcceleration(); // возвращает ускорение объекта

};

#endif // GAMEOBJECT_H
