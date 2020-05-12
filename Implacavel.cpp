/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Especial.cpp
 * 
 * Authors:
 * - Ricardo Belinha nº 21250197
 * - João Fernandes  nº 21250054
 * 
 * Created on 13 de Novembro de 2018, 18:50
 */

#include "Implacavel.h"
#include "Mundo.h"
#include "Auxiliar.h"

/**
 * Construtor da Classe Derivada da Classe Navio - Bombardeiro.
 * @param x Posição no Eixo dos X (Colunas)
 * @param y Posição no Eixo dos Y (Linhas)
 */
Implacavel::Implacavel(int x, int y) : Navio(x, y, max_agua, max_soldados) {

}

char Implacavel::getTipo() const {
    return 'I';
}

int Implacavel::getMaxTripulacao() const {
    return max_soldados;
}

void Implacavel::movimento(Mundo& m) {
    Navio * target = nullptr;
    target = m.getNavioAmigoMaisPerto(Navio::getPos(), Navio::getId());
    if (target != nullptr) {
        Navio::setPos(m.achaPosicaoMaisPertoDoAlvoDentroDoRaio(this, target->getPos()));
    }
    if (m.verificaSeEstaEmTempestade(getPos()))
        verificaDanosTempestade(m);
    Navio::custoDeAguaPorTurno(m);
    if (m.isNavioNoPortoAmigo(this)) {
        if (!m.navioPertence(Navio::getId())) {
            m.comandoVende(Navio::getId());
        }
        encheDepositoAgua();
    }
    m.batalhaImplacavel(this);
}

Implacavel * Implacavel::clone() {
    return new Implacavel(*this);
}

Implacavel::~Implacavel() {

}

bool Implacavel::temEspacoNoPorao() const {
    return false;
}

int Implacavel::enchePorao(int a) {
    return 0;
}

void Implacavel::verificaDanosTempestade(Mundo &m) {
    encheDepositoAgua();
}

void Implacavel::encheDepositoAgua() {
    Navio::setAgua(max_agua);
}

void Implacavel::addAgua(int a) {
    if (Navio::getAgua() + a >= max_agua) {
        Navio::setAgua(max_agua);
    } else {
        if (Navio::getAgua() + a <= 0) {
            Navio::setAgua(0);
        } else {
            Navio::addAgua(a);
        }
    }
}
