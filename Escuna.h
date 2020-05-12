/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Escuna.h
 *
 * Authors:
 * - Ricardo Belinha nº 21250197
 * - João Fernandes  nº 21250054
 *
 * Created on 13 de Novembro de 2018, 18:45
 */

#ifndef ESCUNA_H
#define ESCUNA_H
#include "Navio.h"

class Escuna : public Navio {
    const static int max_agua = 100;
    const static int max_soldados = 10;
    const static int max_carga = 20;
    const static int min_agua = 25;
    const static int temp_afundar = 35; // %
    const static int temp_perda = 20; // %
public:
    Escuna(int x, int y);
    char getTipo() const override;
    int getMaxTripulacao() const override;
    void movimento(Mundo& m) override;
    Escuna * clone() override;
    ~Escuna() override;
    int enchePorao(int a) override;
    bool temEspacoNoPorao() const override;
    void verificaDanosTempestade(Mundo &m) override;
    void encheDepositoAgua() override;
    void addAgua(int a) override;

};
#endif /* ESCUNA_H */
