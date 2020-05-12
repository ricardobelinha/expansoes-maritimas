/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Especial.h
 * 
 * Authors:
 * - Ricardo Belinha nº 21250197
 * - João Fernandes  nº 21250054
 * 
 * Created on 13 de Novembro de 2018, 18:50
 */

#ifndef ESPECIAL_H
#define ESPECIAL_H
#include "Navio.h"

/**
 * Este navio encontra o navio amigo mais perto e vai para perto dele, se vir
 * algum inimigo destroi automáticamente, mas se for visto primeiro ocorre uma
 * batalha normal.
 */

class Implacavel : public Navio {
    const static int max_agua = 1000;
    const static int max_soldados = 100;
    const static int max_peixe = 0;
public:
    Implacavel(int x, int y);
    char getTipo() const override;
    int getMaxTripulacao() const override;
    void movimento(Mundo& m) override;
    Implacavel * clone() override;
    ~Implacavel() override;
    int enchePorao(int a) override;
    bool temEspacoNoPorao() const override;
    void verificaDanosTempestade(Mundo &m) override;
    void encheDepositoAgua() override;
    void addAgua(int a) override;

};
#endif /* ESPECIAL_H */
