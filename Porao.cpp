/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Porao.cpp
 * Author: Ricardo Belinha
 * 
 * Created on 28 de Dezembro de 2018, 0:32
 */

#include "Porao.h"

Porao::Porao(){

}

Porao::Porao(const Porao& orig) {
}

Porao::~Porao() {
}

int Porao::getPeixe() const {
    return peixe;
}

int Porao::getMercadoria() const {
    return mercadoria;
}

void Porao::addPeixe(int a) {
    peixe += a;
    if (peixe < 0)
        peixe = 0;
    else {
        if (peixe > max_peixe)
            peixe = max_peixe;
    }
}

void Porao::addMercadoria(int a) {
    mercadoria += a;
    if (mercadoria < 0)
        mercadoria = 0;
    else {
        if (mercadoria > max_mercadoria)
            mercadoria = max_mercadoria;
    }
}

void Porao::setMercadoria(int a) {
    mercadoria = a;
}

void Porao::setPeixe(int a) {
    peixe = a;
}

void Porao::setCarga(int a) {
    peixe = a;
    mercadoria = a;
}

int Porao::getCarga() const {
    return peixe + mercadoria;
}

int Porao::getMaxMercadoria() const {
    return max_mercadoria;
}

int Porao::getMaxPeixe() const {
    return max_peixe;
}

void Porao::setMaxMercadoria(int a) {
    max_mercadoria = a;
}

void Porao::setMaxPeixe(int a) {
    max_peixe = a;
}
