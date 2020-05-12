/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Porao.h
 * Author: Ricardo Belinha
 *
 * Created on 28 de Dezembro de 2018, 0:32
 */

#ifndef PORAO_H
#define PORAO_H
using namespace std;

class Porao {
    int max_mercadoria = 0;
    int max_peixe = 0;
    int mercadoria = 0;
    int peixe = 0;
public:
    Porao();
    Porao(const Porao& orig);
    virtual ~Porao();
    int getMercadoria()const;
    int getPeixe()const;
    void addPeixe(int a);
    void addMercadoria(int a);
    void setPeixe(int a);
    void setMercadoria(int a);
    void setCarga(int a);
    int getCarga()const;
    void setMaxMercadoria(int a);
    int getMaxMercadoria()const;
    void setMaxPeixe(int a);
    int getMaxPeixe()const;
private:

};

#endif /* PORAO_H */

