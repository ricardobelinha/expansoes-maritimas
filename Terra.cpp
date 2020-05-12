/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Terra.cpp
 * 
 * Authors:
 * - Ricardo Belinha nº 21250197
 * - João Fernandes  nº 21250054
 * 
 * Created on 30 de Outubro de 2018, 19:28
 */

#include "Terra.h"

/**
 * Construtor da Classe Derivada da Classe Terreno - Terra.
 * @param a Posição no Eixo dos X (Colunas)
 * @param b Posição no Eixo dos Y (Linhas)
 */
Terra::Terra(int a, int b) : Terreno(a, b) {

}

char Terra::getTipo() const {
    return '+';
}

bool Terra::getAmigo() const {
    return false;
}

bool Terra::getPrincipal() const {
    return false;
}

bool Terra::navegavel(Mundo &m, Navio* n) {
    return false;
}

Terra* Terra::clone() {
    return new Terra(*this);
}

Terra::~Terra() {

}

bool Terra::getPeixe() const {
    return false;
}

void Terra::avancaDia() {

}

void Terra::conquistado() {

}
