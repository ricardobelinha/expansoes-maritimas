/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Jogador.cpp
 * 
 * Authors:
 * - Ricardo Belinha nº 21250197
 * - João Fernandes  nº 21250054
 * 
 * Created on 30 de Outubro de 2018, 22:02
 */

#include "Jogador.h"
#include <sstream>
#include "Navio.h"

/**
 * Construtor da Classe Jogador.
 * @param a Nome do Jogador
 * @param b Quantidade de Moedas
 */
Jogador::Jogador(string a, int b) : nome(a), moedas(b) {

}

Jogador::Jogador(const Jogador& a) {
    moedas = a.moedas;
    nome = a.nome;
    pontuacao = a.pontuacao;
    for (auto n : a.navios) {
        navios.push_back(n->clone());
    }
}

Jogador* Jogador::clone() {
    return new Jogador(*this);
}

/**
 * Função responsável por devolver o texto responsável por descrever a Classe Jogador.
 * @return String - Texto completo
 */
string Jogador::getAsString() const {
    ostringstream os;
    os << "Nome de Utilizador: " << nome << endl << "Moedas: " << moedas << endl << "Pontuacao: " << pontuacao << endl;
    return os.str();
}

/**
 * Função responsável por incrementar o número de moedas do Jogador.
 * @param a Inteiro a adicionar ao atributo Moedas
 */
void Jogador::addMoedas(int a) {
    moedas += a;
}

/**
 * Função de consulta responsável por devolver a pontuação do Jogador.
 * @return Inteiro - Pontuação do Jogador
 */
int Jogador::getPontuacao() const {
    return pontuacao;
}

/**
 * Função responsável por adicionar um Ponteiro para Navio no vetor de Ponteiros para Navio na Classe Jogador. Ou seja, após o Ponteiro estar neste vetor, o jogador é quem controla os navios.
 * @param n Ponteiro para Navio
 */
void Jogador::addNavio(Navio* n) {
    navios.push_back(n);
}

/**
 * Função de consulta responsável por devolver a quantia de moedas.
 * @return moedas
 */
int Jogador::getMoedas() const {
    return moedas;
}

vector<Navio*> Jogador::getNavios() {
    return navios;
}

string Jogador::getNome() const {
    return nome;
}

bool Jogador::apagaNavio(int id) {
    for (auto it = navios.begin(); it != navios.end(); it++) {
        if ((*it)->getId() == id) {
            delete *it;
            it = navios.erase(it);
            return true;
        }
    }
    return false;
}

Jogador::~Jogador() {
    for (auto n : navios) {
        delete n;
    }
}

void Jogador::perdiNavio(Navio* n) {
    for (auto it = navios.begin(); it != navios.end(); it++) {
        if ((*it)->getId() == n->getId()) {
            it = navios.erase(it);
            return;
        }
    }
}

void Jogador::eliminaMortos() {
    for (auto it = navios.begin(); it != navios.end();) {
        if (!((*it)->getVivo())) {
            delete *it;
            it = navios.erase(it);
        } else {
            ++it;
        }
    }
}

void Jogador::addPontuacao(int a) {
    pontuacao += a;
}
