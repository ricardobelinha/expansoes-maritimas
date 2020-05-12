/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Fragata.cpp
 *
 * Authors:
 * - Ricardo Belinha nº 21250197
 * - João Fernandes  nº 21250054
 *
 * Created on 13 de Novembro de 2018, 18:46
 */

#include "Fragata.h"
#include "Mundo.h"
#include "Auxiliar.h"
/** Descrição - Fragata
 * Muito rápida, não transporta carga e serve apenas para combates. Pode
 * deslocar-se uma ou duas posições em cada turno. Pode levar até 50 soldados.
 * Tem capacidade para 500 litros de água.
 * Quando a navegar de forma autónoma tenta deslocar-se em direcção a um inimigo
 * que vir, para o combater. Se não houver nenhum, tenta manter-se perto do
 * outro navio que seja escuna ou galeão para o proteger, ou seja, tenta
 * manter-se perto de outro navio que seja escuna ou galeão para o proteger, ou
 * seja, tenta manter-se a não mais do que duas posições de distância desse
 * outro navio (qual é esse outro navio? Um deles, o primeiro que a fragata
 * "vir").
 * Numa tempestade perde sempre 15% dos soldados e tem 20% de hipóteses de se
 * afundar.
 */

/**
 * Construtor da Classe Derivada da Classe Navio - Fragata.
 * @param x Posição no Eixo dos X (Colunas)
 * @param y Posição no Eixo dos Y (Linhas)
 */
Fragata::Fragata(int x, int y) : Navio(x, y, max_agua, max_soldados) {

}

char Fragata::getTipo() const {
    return 'F';
}

int Fragata::getMaxTripulacao() const {
    return max_soldados;
}

void Fragata::movimento(Mundo& m) {
    int vezes = Auxiliar::geraNumerosInteirosAleatorios(1, 2);
    // Movimentar 2 casas ou 1 casa
    for (int i = 0; i < vezes; i++) {
        if (Navio::getPodeSerConquistado()) {
            Navio::procuraPosicaoLivreDentroRaio(m);
        } else {
            // Verifica se pode efetuar movimento ou não
            if (Navio::getAutoComportamento()) {
                // Movimenta-se à procura de um Escuna
                Navio * target = nullptr;
                // ENCONTRA INIMIGO
                target = m.getNavioInimigoMaisPerto(getPos(), getId());
                if (target == nullptr) {
                    // Caso não tenha encontrado nenhum
                    target = m.getNavioEspecificoMaisPerto('E', getPos(), getId());
                    if (target == nullptr) {
                        target = m.getNavioEspecificoMaisPerto('G', getPos(), getId());
                    }
                    if (target == nullptr || (target->getPos() == Navio::getPos())) {
                        Navio::procuraPosicaoLivreDentroRaio(m);
                    } else {
                        // Caso tenha encontrado Escuna / Galeao, e não estejam no mesmo sítio
                        if (target->getPos() != getPos()) {
                            Navio::setPos(m.achaPosicaoMaisPertoDoAlvoDentroDoRaio(this, target->getPos()));
                        }
                    }
                } else {
                    // Caso tenha encontrado inigmigo, e não estejam no mesmo sítio
                    if (Auxiliar::isAdjacente(Navio::getPos(), Navio::getDestino())) {
                        if (!Navio::getPerdeuUltimoCombate())
                            m.comecaCombate(this, target);
                        else {
                            Navio::procuraPosicaoLivreDentroRaio(m);
                        }
                    } else {
                        if (target->getPos() != getPos()) {
                            Navio::setPos(m.achaPosicaoMaisPertoDoAlvoDentroDoRaio(this, target->getPos()));
                        }
                    }
                }
            } else {
                // Verifica se possui um destino (ação pendente)
                if (!m.navioPertence(Navio::getId())) {
                    // Verifica se está a 1 casa do destino
                    if (Auxiliar::isAdjacente(Navio::getPos(), Navio::getDestino())) {
                        Navio::setPos(Navio::getDestino());
                        Navio::setAutoComportamento(true);
                    } else {
                        // Procura uma posição mais perto do destino
                        Navio::setPos(m.achaPosicaoMaisPertoDoAlvoDentroDoRaio(this, Navio::getDestino()));
                    }
                }
            }
        }
        if (m.isNavioNoPortoAmigo(this)) {
            if (!m.navioPertence(Navio::getId())) {
                m.comandoVende(Navio::getId());
            }
            encheDepositoAgua();
        }
    }
    if (m.verificaSeEstaEmTempestade(getPos()))
            verificaDanosTempestade(m);
        Navio::custoDeAguaPorTurno(m);
        
        m.conquistaEBatalhas(this);
}

Fragata* Fragata::clone() {
    return new Fragata(*this);
}

Fragata::~Fragata() {

}

bool Fragata::temEspacoNoPorao() const {
    return false;
}

int Fragata::enchePorao(int a) {
    return 0;
}

void Fragata::verificaDanosTempestade(Mundo &m) {
    int prob = Auxiliar::geraNumerosInteirosAleatorios(1, 100);
    Navio::setTripulacao(Navio::getTripulacao()*(1 - (temp_perda * 0.01)));
    if (prob <= temp_afundar)
        Navio::afundei(m);
    else
        encheDepositoAgua();
}

void Fragata::encheDepositoAgua() {
    Navio::setAgua(max_agua);
}

void Fragata::addAgua(int a) {
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
