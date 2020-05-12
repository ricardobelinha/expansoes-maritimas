/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Gravacoes.h
 * Author: Ricardo Belinha
 *
 * Created on 27 de Dezembro de 2018, 17:05
 */

#ifndef GRAVACOES_H
#define GRAVACOES_H
#include "Mundo.h"

class Gravacoes {
    string nome;
    Mundo * m;
public:
    Gravacoes(string a, Mundo *b);
    string getNome()const;
    Mundo* getMundo();
    ~Gravacoes();
private:

};

#endif /* GRAVACOES_H */

