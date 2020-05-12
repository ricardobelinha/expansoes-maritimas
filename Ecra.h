/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Grafica.h
 * 
 * Authors:
 * - Ricardo Belinha nº 21250197
 * - João Fernandes  nº 21250054
 * 
 * Created on 8 de Novembro de 2018, 15:18
 */

#ifndef GRAFICA_H
#define GRAFICA_H
#include <string>
#include <vector>
using namespace std;

class Mundo;
class Terreno;
class Jogador;

class Ecra {
    const static int width = 100;
    const static int height = 100;
    const static int tam_celula = 2;
    const static char celula = ' ';
    bool listaPrecosPortos=false;
    void desenhaHeader();
    void colocaCaracterNaCelula(int x, int y)const;
    void descobreCorCelula(int x, int y, Mundo * m)const;
    void desenhaNavios(Mundo * m)const;
    void desenhaComandos(Mundo * m, vector<string> listaComandos)const;
    void desenhaStatusJogador(Mundo * m);
    void desenhaListaPrecosPortos(Mundo * m);
public:
    Ecra();
    void desenhaTerreno(Mundo * m, vector<string> listaComandos);
    void setListaPrecosPortos(bool a);
    void finalizouJogo(Mundo * m);
};
#endif /* GRAFICA_H */
