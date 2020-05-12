/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Gravacoes.cpp
 * Author: Ricardo Belinha
 * 
 * Created on 27 de Dezembro de 2018, 17:05
 */

#include "Gravacoes.h"

Gravacoes::Gravacoes(string a, Mundo *b) : nome(a), m(b) {
}

Gravacoes::~Gravacoes() {
    //delete m;
}

Mundo *  Gravacoes::getMundo() {
    return m;
}

string Gravacoes::getNome() const {
    return nome;
}

