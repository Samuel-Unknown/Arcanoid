#include "gameobject.h"

GameObject::GameObject()
{
}

QImage GameObject::getImage() {
    return img;
}

void GameObject::setCoordX(float x) {
    coordX = x;
}

void GameObject::setCoordY(float y) {
    coordY = y;
}

float GameObject::getCoordX() {
    return coordX;
}

float GameObject::getCoordY() {
    return coordY;
}

float GameObject::getVelocityX() {
    return cos(angle * pi / 180) * velocity;
}

float GameObject::getVelocityY() {
    return -sin(angle * pi / 180) * velocity;
}

void GameObject::setAngle(float a) {
    angle = a;
}

float GameObject::getAngle() {
    return angle;
}

void GameObject::setVelocity(float v) {
    velocity = v;
}

float GameObject::getVelocity() {
    return velocity;
}

float GameObject::getWidth() {
    return width;
}

float GameObject::getHeight() {
    return height;
}

float GameObject::getAcceleration() {
    return acceleration;
}
