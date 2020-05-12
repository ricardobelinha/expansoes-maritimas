/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * 
 * Authors:
 * - Ricardo Belinha nº 21250197
 * - João Fernandes  nº 21250054
 * 
 * Created on 18 de Dezembro de 2018, 21:33
 */

#include "Posicao.h"

int Posicao::getX() const {
    return x;
}

int Posicao::getY() const {
    return y;
}

void Posicao::setX(int a) {
    x = a;
}

void Posicao::setY(int a) {
    y = a;
}

void Posicao::corrige(int maxX, int maxY) {
    if (x >= maxX) {
        x -= maxX;
    }

    if (x < 0) {
        x += maxX;
    }

    if (y >= maxY) {
        y -= maxY;
    }

    if (y < 0) {
        y += maxY;
    }
}

bool Posicao::operator!=(Posicao a) {
    return !(*this==a);
}

bool Posicao::operator==(Posicao a) {
    if (a.x == x && a.y == y) return true;
    return false;
}

