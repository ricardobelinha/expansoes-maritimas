/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Fragata.h
 *
 * Authors:
 * - Ricardo Belinha nº 21250197
 * - João Fernandes  nº 21250054
 *
 * Created on 13 de Novembro de 2018, 18:46
 */

#ifndef FRAGATA_H
#define FRAGATA_H
#include "Navio.h"

class Fragata : public Navio {
    const static int max_agua = 500;
    const static int max_soldados = 50;
    const static int temp_afundar = 20; // %
    const static int temp_perda = 15; // %
public:
    Fragata(int x, int y);
    char getTipo() const override;
    int getMaxTripulacao() const override;
    void movimento(Mundo& m) override;
    Fragata * clone() override;
    ~Fragata() override;
    int enchePorao(int a) override;
    bool temEspacoNoPorao() const override;
    void verificaDanosTempestade(Mundo &m) override;
    void encheDepositoAgua() override;
    void addAgua(int a) override;

};
#endif /* FRAGATA_H */
