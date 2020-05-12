/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Porto.cpp
 * 
 * Authors:
 * - Ricardo Belinha nº 21250197
 * - João Fernandes  nº 21250054
 * 
 * Created on 29 de Outubro de 2018, 17:25
 */

#include "Porto.h"

/**
 * Construtor da Classe Derivada da Classe Terreno - Porto.
 * @param a Posição no Eixo dos X (Colunas)
 * @param b Posição no Eixo dos Y (Linhas)
 * @param c Caractér responsável por identificar o tipo de Porto (principal ou não)
 */
Porto::Porto(int a, int b, char c) : Terreno(a, b), letra(c) {
    if (c >= 'A' && c <= 'Z') {
        amigo = true;
    } else {
        amigo = false;
    }
}

/**
 * Função de consulta responsável por devolver o atributo de tipo boolean que identifica se o Porto é amigo ou não.
 * @return Boolean - Amigo
 */
bool Porto::getAmigo() const {
    return amigo;
}

/**
 * Função de consulta responsável por devolver o atributo de tipo boolean que identifica se o Porto é principal ou não.
 * @return Boolean - Principal
 */
bool Porto::getPrincipal() const {
    if (letra == 'A') return true;
    return false;
}

char Porto::getTipo() const {
    return letra;
}

bool Porto::navegavel(Mundo &m, Navio* n) {
    if(m.navioPertence(n->getId()) && amigo==false)
        return true;
    else{
        if(!m.navioPertence(n->getId()) && amigo==true)
            return true;
        else
            return false;
    }
}

Porto* Porto::clone() {
    return new Porto(*this);
}

Porto::~Porto() {

}

void Porto::avancaDia() {

}

bool Porto::getPeixe() const {
    return false;
}

void Porto::setPeixe(bool a) {

}

void Porto::conquistado() {
    amigo = !amigo;
}
