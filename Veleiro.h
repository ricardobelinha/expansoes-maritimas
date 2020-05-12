/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Veleiro.h
 *
 * Authors:
 * - Ricardo Belinha nº 21250197
 * - João Fernandes  nº 21250054
 *
 * Created on 13 de Novembro de 2018, 18:37
 */

#ifndef VELEIRO_H
#define VELEIRO_H
#include "Navio.h"
#include "Mundo.h"

class Veleiro : public Navio {
    const static int max_agua = 200;
    const static int max_soldados = 20;
    const static int max_peixe = 40;
    const static int temp_afundar = 35; // %
    const static int temp_min_perda = 20; // %
public:
    Veleiro(int x, int y);
    char getTipo() const override;
    int getMaxTripulacao() const override;
    bool temEspacoNoPorao() const override;
    Veleiro * clone() override;
    void movimento(Mundo& m) override;
    int enchePorao(int a) override;
    ~Veleiro() override;
    void verificaDanosTempestade(Mundo &m) override;
    void encheDepositoAgua() override;
    void addAgua(int a) override;


};
#endif /* VELEIRO_H */
