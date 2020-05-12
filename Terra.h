/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Terra.h
 *
 * Authors:
 * - Ricardo Belinha nº 21250197
 * - João Fernandes  nº 21250054
 *
 * Created on 30 de Outubro de 2018, 19:28
 */

#ifndef TERRA_H
#define TERRA_H
#include "Terreno.h"

class Terra : public Terreno {
public:
    Terra(int a, int b);
    bool getAmigo()const override;
    bool getPrincipal()const override;
    char getTipo() const override;
    bool navegavel(Mundo &m, Navio* n) override;
    Terra * clone() override;
    virtual ~Terra();
    bool getPeixe()const override;
    void setPeixe(bool a) override{
        
    }
    void avancaDia() override;
    void conquistado() override;


};
#endif /* TERRA_H */
