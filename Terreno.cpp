/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Terreno.cpp
 * 
 * Authors:
 * - Ricardo Belinha nº 21250197
 * - João Fernandes  nº 21250054
 *  
 * Created on 30 de Outubro de 2018, 18:07
 */

#include "Terreno.h"

Terreno::Terreno(int a, int b) {
    pos.setX(a);
    pos.setY(b);
}

Posicao Terreno::getPosicao() const {
    return pos;
}

Terreno::~Terreno() {

}

bool Terreno::getTempestade() const {
    return tempestade;
}

void Terreno::setTempestade(bool a) {
    tempestade = a;
}

void Terreno::setCalmaria(bool a) {
    calmaria=a;
}

bool Terreno::getCalmaria() const {
    return calmaria;
}
