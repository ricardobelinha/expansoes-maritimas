/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * 
 * Authors:
 * - Ricardo Belinha nº 21250197
 * - João Fernandes  nº 21250054
 * 
 * Created on 18 de Dezembro de 2018, 21:33
 */

#ifndef POSICAO_H
#define POSICAO_H

class Posicao {
    int x;
    int y;
public:
    int getX()const;
    int getY()const;
    void setX(int a);
    void setY(int a);
    void corrige(int maxX, int maxY);
    bool operator!=(Posicao a);
    bool operator==(Posicao a);
};
#endif /* POSICAO_H */
