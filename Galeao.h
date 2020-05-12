/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Galeao.h
 *
 * Authors:
 * - Ricardo Belinha nº 21250197
 * - João Fernandes  nº 21250054
 *
 * Created on 13 de Novembro de 2018, 18:44
 */

#ifndef GALEAO_H
#define GALEAO_H
#include "Navio.h"

class Galeao : public Navio {
    const static int max_agua = 400;
    const static int max_soldados = 40;
    const static int max_peixe = 70;
    const static int temp_afundar = 40; // %
public:
    Galeao(int x, int y);
    char getTipo() const override;
    int getMaxTripulacao() const override;
    void movimento(Mundo& m) override;
    Galeao * clone() override;
    ~Galeao() override;
    int enchePorao(int a) override;
    bool temEspacoNoPorao() const override;
    void verificaDanosTempestade(Mundo &m) override;
    void encheDepositoAgua() override;
    void addAgua(int a) override;

};
#endif /* GALEAO_H */
