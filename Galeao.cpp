/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Galeao.cpp
 *
 * Authors:
 * - Ricardo Belinha nº 21250197
 * - João Fernandes  nº 21250054
 *
 * Created on 13 de Novembro de 2018, 18:44
 */

#include "Galeao.h"
#include "Mundo.h"
#include "Auxiliar.h"

/** Descrição - Galeão
 * Lento, mas enorme. Só pode andar uma posição em cada turno. Consegue
 * transportar até 70 toneladas e até 40 soldados. Tem capacidade para 400
 * litros de água.
 * Este navio fica parado se estiver em navegação automática. Recorde-se que
 * navegação automática é diferente de cumprir uma ordem tal como "ir para
 * o porto tal".
 * Se estiver numa célula adjacente a uma escuna, transfere para si o
 * peixe dessa escuna que ainda caiba no seu porão.
 * Numa tempestade perde sempre 10% dos soldados e tem 40% de hipótese de se
 * afundar.
 */

/**
 * Construtor da Classe Derivada da Classe Navio - Galeão.
 * @param x Posição no Eixo dos X (Colunas)
 * @param y Posição no Eixo dos Y (Linhas)
 */
Galeao::Galeao(int x, int y) : Navio(x, y, max_agua, max_soldados) {
    Navio::getPorao().setMaxPeixe(max_peixe);
}

char Galeao::getTipo() const {
    return 'G';
}

int Galeao::getMaxTripulacao() const {
    return max_soldados;
}

void Galeao::movimento(Mundo& m) {
    if (Navio::getPodeSerConquistado()) {
        Navio::procuraPosicaoLivreDentroRaio(m);
    } else {
        if (!Navio::getAutoComportamento()) {
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
    m.verificaAdjacencia(this, 'E');
    if (m.verificaSeEstaEmTempestade(getPos()))
        verificaDanosTempestade(m);
    Navio::custoDeAguaPorTurno(m);
    if (m.isNavioNoPortoAmigo(this)) {
        if (!m.navioPertence(Navio::getId())) {
            m.comandoVende(Navio::getId());
        }
        encheDepositoAgua();
    }
    m.conquistaEBatalhas(this);
}

Galeao* Galeao::clone() {
    return new Galeao(*this);
}

Galeao::~Galeao() {

}

bool Galeao::temEspacoNoPorao() const {
    if (Navio::getPorao().getPeixe() < max_peixe)
        return true;
    return false;
}

int Galeao::enchePorao(int a) {
    int mercadoria = max_peixe - Navio::getPorao().getPeixe();
    if (a < mercadoria) mercadoria = a;
    Navio::getPorao().addPeixe(mercadoria);
    return mercadoria;
}

void Galeao::verificaDanosTempestade(Mundo &m) {
    Navio::setTripulacao(Navio::getTripulacao()*0.9);
    int prob = Auxiliar::geraNumerosInteirosAleatorios(1, 100);
    if (prob <= temp_afundar) {
        afundei(m);
    } else {
        encheDepositoAgua();
    }
}

void Galeao::encheDepositoAgua() {
    Navio::setAgua(max_agua);
}

void Galeao::addAgua(int a) {
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
