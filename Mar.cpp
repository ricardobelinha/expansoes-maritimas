/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Mar.cpp
 *
 * Authors:
 * - Ricardo Belinha nº 21250197
 * - João Fernandes  nº 21250054
 *
 * Created on 30 de Outubro de 2018, 19:29
 */

#include "Mar.h"

/**
 * Construtor da Classe Derivada da Classe Terreno - Mar.
 * @param a Posição no Eixo dos X (Colunas)
 * @param b Posição no Eixo dos Y (Linhas)
 */
Mar::Mar(int a, int b) : Terreno(a, b) {

}

/**
 * Função responsável por retornar o character que identifica o terreno.
 * @return character ponto "."
 */
char Mar::getTipo() const {
    return '.';
}

/**
 * Função responsável por saber se o Porto é principal ou secundário.
 * @return Verdadeiro caso seja o principal, falso caso seja secundário.
 */
bool Mar::getPrincipal() const {
    return false;
}

/**
 * Função responsável por saber se o Porto é amigo ou não.
 * @return Verdadeiro caso seja amigo, falso caso não seja.
 */
bool Mar::getAmigo() const {
    return false;
}

/**
 * Função responsável por saber se este terreno se encontra preparado para receber um navio.
 * @param m Mundo (por referência)
 * @param n Navio (ponteiro)
 * @return Verdadeiro caso seja possível entrar, falso caso contrário.
 */
bool Mar::navegavel(Mundo &m, Navio* n){
    if(m.verificaSeExisteNaviosNoMar(this))
        return false;
    if(m.verificaSeExisteNaviosPiratasNoMar(this))
        return false;
    return true;
}

Mar* Mar::clone() {
    return new Mar(*this);
}

Mar::~Mar() {

}

bool Mar::getPeixe() const {
    return peixe;
}


void Mar::avancaDia() {
    if (dia == 2 && peixe==false){
        peixe = true;
        dia =0;
    }
    else if (dia < 2 && peixe==false)
        dia++;
}


void Mar::setPeixe(bool a) {
    peixe = a;
}

void Mar::conquistado() {

}
