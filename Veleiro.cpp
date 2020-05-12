/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Veleiro.cpp
 *
 * Authors:
 * - Ricardo Belinha nº 21250197
 * - João Fernandes  nº 21250054
 *
 * Created on 13 de Novembro de 2018, 18:37
 */

#include "Veleiro.h"
#include "Mundo.h"
#include "Auxiliar.h"

/** Descrição - Veleiro
 * Muito rápido, mas fraco. É bom para transportar mercadorias e peixe. Pode
 * deslocar-se uma ou duas posições em cada turno. Consegue transportar até 20
 * soldados e 40 toneladas de peixe. Tem ainda capacidade para 200 litros de
 * água.
 * Se estiver numa célula adjacente a uma escuna, transfere para si o peixe
 * dessa escuna que ainda caiba no seu porão. O veleiro é rápido e facilmente
 * vende esse peixe num porto, libertando a escuna para continuar a pescar.
 * Se estiver a navegar de forma autónoma, tenta manter-se ao lado de uma escuna
 * (uma qualquer) de forma a ficar com o peixe que a escuna apanha e mais
 * rapidamente o vender.
 * Se for apanhado por uma tempestade tem 35% de hipóteses de se afundar se
 * tiver mais do que 50% da sua capacidade de carga ocupada, 20% se tiver menos.
 */

/**
 * Construtor da Classe Derivada da Classe Navio - Veleiro.
 * @param x Posição no Eixo dos X (Colunas)
 * @param y Posição no Eixo dos Y (Linhas)
 */
Veleiro::Veleiro(int x, int y) : Navio(x, y, max_agua, max_soldados) {
    Navio::getPorao().setMaxPeixe(max_peixe);
}

char Veleiro::getTipo() const {
    return 'V';
}

int Veleiro::getMaxTripulacao() const {
    return max_soldados;
}

void Veleiro::movimento(Mundo& m) {
    int vezes = Auxiliar::geraNumerosInteirosAleatorios(1, 2);
    // Movimentar 2 casas ou 1 casa
    for (int i = 0; i < vezes; i++) {
        if (Navio::getPodeSerConquistado()) {
            Navio::procuraPosicaoLivreDentroRaio(m);
        } else {
            // Verifica se pode efetuar movimento ou não
            if (Navio::getAutoComportamento()) {
                Navio * target = nullptr;
                // Movimenta-se à procura de um Escuna
                target = m.getNavioEspecificoMaisPerto('E', getPos(), getId());
                if (target == nullptr) {
                    // Caso não tenha encontrado nenhum
                    Navio::procuraPosicaoLivreDentroRaio(m);
                } else {
                    // Caso tenha encontrado, e não estejam no mesmo sítio
                    if (target->getPos() != getPos()) {
                        Navio::setPos(m.achaPosicaoMaisPertoDoAlvoDentroDoRaio(this, target->getPos()));
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
    m.verificaAdjacencia(this, 'E');
    if (m.verificaSeEstaEmTempestade(getPos()))
        verificaDanosTempestade(m);
    Navio::custoDeAguaPorTurno(m);

    m.conquistaEBatalhas(this);
}

Veleiro* Veleiro::clone() {
    return new Veleiro(*this);
}

Veleiro::~Veleiro() {

}

bool Veleiro::temEspacoNoPorao() const {
    if (Navio::getPorao().getPeixe() < max_peixe)
        return true;
    return false;
}

int Veleiro::enchePorao(int a) {
    int mercadoria = max_peixe - Navio::getPorao().getPeixe();
    if (a < mercadoria) mercadoria = a;
    Navio::getPorao().addPeixe(mercadoria);
    return mercadoria;
}

void Veleiro::verificaDanosTempestade(Mundo& m) {
    int prob = Auxiliar::geraNumerosInteirosAleatorios(1, 100);
    if (Navio::getPorao().getPeixe() > (max_peixe / 2)) {
        if (prob <= temp_afundar) {
            afundei(m);
        } else {
            encheDepositoAgua();
        }
    } else {
        if (prob <= temp_min_perda) {
            afundei(m);
        } else {
            encheDepositoAgua();
        }
    }
}

void Veleiro::encheDepositoAgua() {
    Navio::setAgua(max_agua);
}

void Veleiro::addAgua(int a) {
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

