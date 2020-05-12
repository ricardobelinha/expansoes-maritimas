/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Porto.h
 *
 * Authors:
 * - Ricardo Belinha nº 21250197
 * - João Fernandes  nº 21250054
 *
 * Created on 29 de Outubro de 2018, 17:25
 */

#ifndef PORTO_H
#define PORTO_H
#include "Terreno.h"

class Porto : public Terreno {
    char letra;
    bool amigo;
public:
    Porto(int a, int b, char c);
    bool getAmigo()const override;
    bool getPrincipal()const override;
    char getTipo() const override;
    bool navegavel(Mundo &m, Navio * n) override;
    Porto * clone() override;
    virtual ~Porto();
    bool getPeixe()const override;
    void setPeixe(bool a) override;
    void avancaDia() override;
    void conquistado() override;

};
#endif /* PORTO_H */
