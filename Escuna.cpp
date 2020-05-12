/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Escuna.cpp
 *
 * Authors:
 * - Ricardo Belinha nº 21250197
 * - João Fernandes  nº 21250054
 *
 * Created on 13 de Novembro de 2018, 18:45
 */

#include "Escuna.h"
#include "Auxiliar.h"
#include "Mundo.h"

/** Descrição - Escuna
 * Consegue levar até 10 soldados. Tem capacidade para 100 litros de água. Pode
 * deslocar-se uma posição em cada turno. Consegue carregar até 20 toneladas de
 * carga (em princípio será peixe).
 * Se estiver numa posição do mapa com peixe, recolhe automaticamente uma
 * tonelada, respeitando a questão acerca da forma como o peixe é reposto nas
 * células do mapa com peixe.
 * Em navegação automática desloca-se para uma posição com peixe que esteja até
 * duas células de distância. Se tiver com a carga máxima de peixe desloca-se
 * para um porto amigo (um qualquer). O jogo deverá ter a informação acerca de
 * quais os portos que são amigos do jogador de forma a que a escuna possa
 * consultar e decidir onde se dirigir. Se tiver a 25% da capacidade de água
 * desloca-se para um porto.
 * Tem 20% de hipóteses de perder a carga se apanhar uma tempestade e 35% de se
 * afundar.
 */

/**
 * Construtor da Classe Derivada da Classe Navio - Escuna.
 * @param x Posição no Eixo dos X (Colunas)
 * @param y Posição no Eixo dos Y (Linhas)
 */
Escuna::Escuna(int x, int y) : Navio(x, y, max_agua, max_soldados) {
    Navio::getPorao().setMaxPeixe(max_carga);
    Navio::getPorao().setMaxMercadoria(max_carga);
}

char Escuna::getTipo() const {
    return 'E';
}

int Escuna::getMaxTripulacao() const {
    return max_soldados;
}

void Escuna::movimento(Mundo& m) {
    Terreno *t = nullptr;

    // Verifica se a célula onde está possui peixe
    t = m.getTerreno(Navio::getPos());
    if (t->getPeixe()) {
        t->setPeixe(false);
        enchePorao(1);
    }

    if (Navio::getAutoComportamento()) {
        // Navegação automática
        if ((Navio::getAgua()*100 / max_agua) <= 25) {
            t = m.getPortoMaisPerto(getPos(), getId());
            if (t != nullptr) {
                Navio::setPos(m.achaPosicaoMaisPertoDoAlvoDentroDoRaio(this, t->getPosicao()));
            } else {
                Navio::procuraPosicaoLivreDentroRaio(m);
            }
        } else {
            t = m.getCelulaLivreAleatoriaComPeixe(getPos(), this);
            if (t != nullptr) {
                Navio::setPos(t->getPosicao());
            } else {
                Navio::procuraPosicaoLivreDentroRaio(m);
            }
        }
    }

    // Verifica se a célula onde está possui peixe
    if (m.getTerreno(Navio::getPos())->getPeixe()) {
        t->setPeixe(false);
        enchePorao(1);
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

    m.conquistaEBatalhas(this);
}

Escuna* Escuna::clone() {
    return new Escuna(*this);
}

Escuna::~Escuna() {

}

bool Escuna::temEspacoNoPorao() const {
    if (Navio::getPorao().getCarga() < max_carga)
        return true;
    return false;
}

int Escuna::enchePorao(int a) {
    int mercadoria = max_carga - Navio::getPorao().getCarga();
    if (a < mercadoria) mercadoria = a;
    Navio::getPorao().addPeixe(mercadoria);
    return mercadoria;
}

void Escuna::verificaDanosTempestade(Mundo &m) {
    int prob = Auxiliar::geraNumerosInteirosAleatorios(1, 100);
    if (prob <= 35) {
        afundei(m);
    } else {
        prob = Auxiliar::geraNumerosInteirosAleatorios(1, 100);
        if (prob <= 20) {
            Navio::getPorao().setCarga(0);
        }
        encheDepositoAgua();
    }
}

void Escuna::encheDepositoAgua() {
    Navio::setAgua(max_agua);
}

void Escuna::addAgua(int a) {
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
