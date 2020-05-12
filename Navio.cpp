/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Navio.cpp
 *
 * Authors:
 * - Ricardo Belinha nº 21250197
 * - João Fernandes  nº 21250054
 *
 * Created on 29 de Outubro de 2018, 17:26
 */

#include "Navio.h"
#include "Mundo.h"
#include "Terreno.h"
#include "Auxiliar.h"
int Navio::conta = 0;

/**
 * Construtor da Classe Base - Navio.
 * @param x Posição no Eixo dos X (Colunas)
 * @param y Posição no Eixo dos Y (Linhas)
 * @param agua Quantidade de Água
 * @param sold Quantidade de Soldados
 */
Navio::Navio(int x, int y, int agua, int sold) : id(++conta), agua(agua), tripulacao(sold) {
    pos.setX(x);
    pos.setY(y);
}

/**
 * Função responsável por atualizar as coordenadas do Navio com as coordenadas da célula livre.
 * @param m Referência para o objeto Mundo
 */
void Navio::procuraPosicaoLivreDentroRaio(Mundo &m) {
    Terreno* t = m.getCelulaLivreAleatoria(pos, this);
    if (t != nullptr) {
        pos = t->getPosicao();
    }
}

Posicao Navio::getDestino() const {
    return destino;
}

/**
 * Função de consulta responsável por devolver o ID do Navio.
 * @return ID do Navio
 */
int Navio::getId() const {
    return id;
}

bool Navio::getAutoComportamento() {
    return autoComportamento;
}

void Navio::setAutoComportamento(bool a) {
    autoComportamento = a;
}

int Navio::getTripulacao() const {
    return tripulacao;
}

void Navio::addTripulacao(int a) {
    tripulacao += a;
}

void Navio::move(Mundo& m, int a, int b) {
    Posicao nova = pos;
    nova.setX(pos.getX() + a);
    nova.setY(pos.getY() + b);
    nova.corrige(m.getColunas(), m.getLinhas());
    Terreno * t = m.getTerreno(nova);
    if (t != nullptr) {
        if (t->navegavel(m, this)) {
            pos = t->getPosicao();
        }
    }
}

Posicao Navio::getPos() const {
    return pos;
}

void Navio::setPos(Posicao a) {
    pos = a;
}

void Navio::setDestino(Posicao a) {
    destino = a;
}

Navio::~Navio() {

}

Porao Navio::getPorao() const {
    return porao;
}

bool Navio::temAlgoNoPorao() const {
    if (porao.getCarga() > 0)
        return true;
    return false;
}

void Navio::afundei(Mundo &m) {
    vivo=false;
}

int Navio::getAgua() {
    return agua;
}

void Navio::custoDeAguaPorTurno(Mundo &m) {
    if (agua <= 0) {
        if (tripulacao > 0) tripulacao--;
    }
    if (!m.isNavioNoPortoAmigo(this)) {
        if (agua >= tripulacao) agua -= tripulacao;
        else
            agua = 0;
    }
    if (tripulacao <= 0)
        podeSerConquistado = true;
}

void Navio::setAgua(int a) {
    agua = a;
}

bool Navio::getPodeSerConquistado() const {
    return podeSerConquistado;
}

void Navio::setPodeSerConquistado(bool a) {
    podeSerConquistado = a;
}

void Navio::addAgua(int a) {
    agua += a;
}

void Navio::setTripulacao(int a) {
    tripulacao = a;
}

bool Navio::getPerdeuUltimoCombate() {
    return perdeuUltimoCombate;
}

void Navio::setPerdeuUltimoCombate(bool a) {
    perdeuUltimoCombate = a;
}

bool Navio::verificaFimCalmaria(Mundo &m) {
    return m.getTerreno(pos)->getCalmaria();
}

bool Navio::getVivo() const {
    return vivo;
}
