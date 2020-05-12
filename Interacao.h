/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Iteracao.h
 * 
 * Authors:
 * - Ricardo Belinha nº 21250197
 * - João Fernandes  nº 21250054
 * 
 * Created on 31 de Outubro de 2018, 16:40
 */

#ifndef ITERACAO_H
#define ITERACAO_H
#include "Gravacoes.h"
#include "Ecra.h"
#include <string>

using namespace std;

class Interacao {
    Mundo * m;
    Ecra e;
    int estado;
    vector<Gravacoes> g;
    vector<string> listaComandos;
    vector<string> criaComandos();
    int leituraComandos(istream& ficheiro);
    bool encontraStringNoVector(string a);
    int interpretaComandos(string nomeComando, string comando);
    void trataConfig(string comando);
    void trataExec(string comando);
    void trataProx();
    void trataCompraNav(string comando);
    void trataMoedas(string comando);
    void trataSair();
    void trataPirata(string comando);
    void trataStop(string comando);
    void trataAuto(string comando);
    void trataCompraSold(string comando);
    void trataMove(string comando);
    void trataVendeNav(string comando);
    void trataSaveG(string comando);
    void trataLoadG(string comando);
    void trataDelG(string comando);
    void trataVaiPara(string comando);
    void trataLista();
    void trataCompra(string comando);
    void trataVende(string comando);
public:
    Interacao();
    ~Interacao();
    void iniciaCiclo(istream& ficheiro);
};
#endif /* ITERACAO_H */
