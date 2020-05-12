/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Jogador.h
 * 
 * Authors:
 * - Ricardo Belinha nº 21250197
 * - João Fernandes  nº 21250054
 * 
 * Created on 30 de Outubro de 2018, 22:02
 */

#ifndef JOGADOR_H
#define JOGADOR_H
#include <string>
#include <vector>
using namespace std;
class Navio;

class Jogador {
    string nome;
    int pontuacao = 0;
    int moedas;
    vector<Navio*> navios;
    
public:
    Jogador(string a, int b);
    Jogador(const Jogador& a);
    string getAsString()const;
    void addMoedas(int a);
    int getPontuacao()const;
    void addNavio(Navio * n);
    int getMoedas()const;
    string getNome()const;
    vector<Navio*> getNavios();
    bool apagaNavio(int id);
    Jogador * clone();
    ~Jogador();
    void perdiNavio(Navio* n);
    void eliminaMortos();
    void addPontuacao(int a);
};
#endif /* JOGADOR_H */
