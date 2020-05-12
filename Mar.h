/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Mar.h
 *
 * Authors:
 * - Ricardo Belinha nº 21250197
 * - João Fernandes  nº 21250054
 *
 * Created on 30 de Outubro de 2018, 19:29
 */

#ifndef MAR_H
#define MAR_H
#include "Terreno.h"

class Mar : public Terreno {
    bool peixe=true;
    int dia;
public:
    Mar(int a, int b);
    bool getAmigo()const override;
    bool getPrincipal()const override;
    char getTipo() const override;
    bool navegavel(Mundo &m, Navio* n) override;
    Mar * clone() override;
    virtual ~Mar();
    bool getPeixe()const override;
    void avancaDia() override;
    void setPeixe(bool a) override;
    void conquistado() override;

};
#endif /* MAR_H */
