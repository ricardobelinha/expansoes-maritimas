/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Navio.h
 *
 * Authors:
 * - Ricardo Belinha nº 21250197
 * - João Fernandes  nº 21250054
 *
 * Created on 29 de Outubro de 2018, 17:26
 */

#ifndef NAVIO_H
#define NAVIO_H
#include <string>
#include "Porao.h"
#include "Posicao.h"
using namespace std;

class Jogador;
class Mundo;

class Navio {
    bool podeSerConquistado=false;
    const int id; // Identificação única do navio
    bool autoComportamento = true; // Indicação se possui comportamento automatico ou nao
    Posicao destino; // Posição de destino do navio
    Posicao pos; // Posição na grelha retangular de células
    static int conta; // Variável contadora
    Porao porao; // Quantidade de Toneladas no porao
    int tripulacao; // Se navio perdeu toda a sua tripulação, navega de forma aleatória.
    int agua; // Quantidade de água que o Navio possui em Litros
    bool perdeuUltimoCombate = false;
    bool vivo=true;
protected:
    Navio(int x, int y, int agua, int sold);
public:
    Navio() = delete;
    void procuraPosicaoLivreDentroRaio(Mundo &m);
    virtual void encheDepositoAgua() = 0;
    Posicao getDestino()const;
    Posicao getPos()const;
    void setDestino(Posicao a);
    void setPos(Posicao a);
    int getId()const;
    virtual char getTipo()const = 0;
    bool getAutoComportamento();
    void setAutoComportamento(bool a);
    int getTripulacao()const;
    void addTripulacao(int a);
    virtual void addAgua(int a);
    int getAgua();
    void setAgua(int a);
    virtual int getMaxTripulacao()const = 0;
    virtual bool temEspacoNoPorao()const = 0;
    bool temAlgoNoPorao()const;
    void move(Mundo &m, int a, int b);
    virtual Navio * clone() = 0;
    virtual ~Navio();
    virtual void movimento(Mundo &m) = 0;
    Porao getPorao()const;
    virtual int enchePorao(int a)=0;
    virtual void verificaDanosTempestade(Mundo &m)=0;
    void custoDeAguaPorTurno(Mundo &m);
    void afundei(Mundo &m);
    bool getPodeSerConquistado()const;
    void setPodeSerConquistado(bool a);
    void setTripulacao(int a);
    bool getPerdeuUltimoCombate();
    void setPerdeuUltimoCombate(bool a);
    bool verificaFimCalmaria(Mundo &m);
    bool getVivo()const;
};
#endif /* NAVIO_H */
