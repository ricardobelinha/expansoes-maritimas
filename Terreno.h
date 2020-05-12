/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Terreno.h
 *
 * Authors:
 * - Ricardo Belinha nº 21250197
 * - João Fernandes  nº 21250054
 *
 * Created on 30 de Outubro de 2018, 18:07
 */

#ifndef TERRENO_H
#define TERRENO_H
#include "Navio.h"
#include "Mundo.h"
#include "Posicao.h"

using namespace std;

class Terreno {
    Posicao pos;
    bool tempestade=false;
    bool calmaria=false;
public:
    Terreno(int a, int b);
    Posicao getPosicao()const;
    virtual bool getAmigo()const=0;
    virtual bool getPrincipal()const=0;
    virtual char getTipo()const=0;
    virtual bool navegavel(Mundo &m, Navio * n)=0;
    virtual Terreno * clone()=0;
    virtual ~Terreno();
    bool getTempestade()const;
    void setTempestade(bool a);
    virtual bool getPeixe()const =0;
    virtual void setPeixe(bool a)=0;
    virtual void avancaDia()=0;
    void setCalmaria(bool a);
    bool getCalmaria()const;
    virtual void conquistado()=0;
};
#endif /* TERRENO_H */
