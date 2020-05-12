/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Mundo.cpp
 *
 * Authors:
 * - Ricardo Belinha nº 21250197
 * - João Fernandes  nº 21250054
 *
 * Created on 29 de Outubro de 2018, 22:20
 */

#include "Mundo.h"
#include "Jogador.h"
#include "Veleiro.h"
#include "Galeao.h"
#include "Escuna.h"
#include "Fragata.h"
#include "Implacavel.h"
#include "Terreno.h"
#include "Terra.h"
#include "Mar.h"
#include "Porto.h"
#include "Auxiliar.h"
#include <iostream>
#include <fstream>
#include <sstream>

/**
 * Construtor da Classe Mundo.
 * @param ficheiro Vetor de String com a informação do ficheiro
 */
Mundo::Mundo(vector<string> ficheiro) {
    setConfiguracoes(ficheiro);
    jogador = new Jogador("Player", moedas);
}

Mundo::Mundo(const Mundo& a) {
    linhas = a.linhas;
    colunas = a.colunas;
    if (linhas > 0 && colunas > 0) {
        for (int i = 0; i < linhas; i++) {
            mapa.push_back(vector<Terreno*>());
            for (int j = 0; j < colunas; j++) {
                mapa[i].push_back(a.mapa[i][j]->clone());
            }
        }
    }
    jogador = a.jogador->clone();
    moedas = a.moedas;
    for (auto n : a.navios) {
        navios.push_back(n->clone());
    }
    precoCompMercad = a.precoCompMercad;
    precoNavio = a.precoNavio;
    precoSoldado = a.precoSoldado;
    precoVendMercad = a.precoVendMercad;
    precoVendPeixe = a.precoVendPeixe;
    probCalmaria = a.probCalmaria;
    probMotim = a.probMotim;
    probPirata = a.probPirata;
    probSereias = a.probSereias;
    probTempestade = a.probTempestade;
    probEvento = a.probEvento;
    soldadosPorto = a.soldadosPorto;
}

Mundo& Mundo::operator=(const Mundo& a) {
    // Destroi o que tem
    for (auto a : jogador->getNavios()) {
        delete a;
    }
    delete jogador;
    for (auto a : mapa) {
        for (auto b : a) {
            delete b;
        }
    }
    for (auto a : navios) {
        delete a;
    }

    // Constroi de novo
    linhas = a.linhas;
    colunas = a.colunas;
    if (linhas > 0 && colunas > 0) {
        for (int i = 0; i < linhas; i++) {
            mapa.push_back(vector<Terreno*>());
            for (int j = 0; j < colunas; j++) {
                mapa[i].push_back(a.mapa[i][j]->clone());
            }
        }
    }
    jogador = a.jogador->clone();
    moedas = a.moedas;
    for (auto n : a.navios) {
        navios.push_back(n->clone());
    }
    precoCompMercad = a.precoCompMercad;
    precoNavio = a.precoNavio;
    precoSoldado = a.precoSoldado;
    precoVendMercad = a.precoVendMercad;
    precoVendPeixe = a.precoVendPeixe;
    probCalmaria = a.probCalmaria;
    probMotim = a.probMotim;
    probPirata = a.probPirata;
    probSereias = a.probSereias;
    probTempestade = a.probTempestade;
    probEvento = a.probEvento;
    soldadosPorto = a.soldadosPorto;
}

/**
 * Função responsável por fazer o tratamento de toda a informação do vetor de string.
 * @param ficheiro Vetor de String
 */
void Mundo::setConfiguracoes(vector<string> ficheiro) {
    string tempString;
    int tempValor, conta = 0;
    istringstream iss;
    for (int i = 0; i < ficheiro.size(); i++) {
        iss.clear();
        iss.str(ficheiro[i]);
        iss >> tempString;
        if (!iss) return;
        if (tempString == "linhas") {
            iss >> tempValor;
            linhas = tempValor;
        } else if (tempString == "colunas") {
            iss >> tempValor;
            colunas = tempValor;
        } else if (tempString == "moedas") {
            iss >> tempValor;
            moedas = tempValor;
        } else if (tempString == "probpirata") {
            iss >> tempValor;
            probPirata = tempValor;
        } else if (tempString == "preconavio") {
            iss >> tempValor;
            precoNavio = tempValor;
        } else if (tempString == "precosoldado") {
            iss >> tempValor;
            precoSoldado = tempValor;
        } else if (tempString == "precovendpeixe") {
            iss >> tempValor;
            precoVendPeixe = tempValor;
        } else if (tempString == "precocompmercad") {
            iss >> tempValor;
            precoCompMercad = tempValor;
        } else if (tempString == "precovendmercad") {
            iss >> tempValor;
            precoVendMercad = tempValor;
        } else if (tempString == "soldadosporto") {
            iss >> tempValor;
            soldadosPorto = tempValor;
        } else if (tempString == "probevento") {
            iss >> tempValor;
            probEvento = tempValor;
        } else if (tempString == "probtempestade") {
            iss >> tempValor;
            probTempestade = tempValor;
        } else if (tempString == "probsereias") {
            iss >> tempValor;
            probSereias = tempValor;
        } else if (tempString == "probcalmaria") {
            iss >> tempValor;
            probCalmaria = tempValor;
        } else if (tempString == "probmotim") {
            iss >> tempValor;
            probMotim = tempValor;
        } else {
            if (linhas > 0 && colunas > 0) {
                mapa.push_back(vector<Terreno*>());
                for (int i = 0; i < colunas; i++) {
                    if (tempString[i] == '+') {
                        mapa[conta].push_back(new Terra(i, conta));
                    } else {
                        if ((tempString[i] >= 'a' && tempString[i] <= 'z') || (tempString[i] >= 'A' && tempString[i] <= 'Z')) {
                            mapa[conta].push_back(new Porto(i, conta, tempString[i]));
                        } else {
                            mapa[conta].push_back(new Mar(i, conta));
                        }
                    }
                }
                conta++;
            }
        }
    }
}

/**
 * Função responsável por devolver o texto responsável por descrever a Classe Mundo.
 * @return String - Texto completo
 */
string Mundo::getAsString() const {
    ostringstream os;
    os << "--------Configuracoes do Mundo--------" << endl;
    os << " Mapa: " << linhas << " linhas e " << colunas << " colunas" << endl;
    os << " Probabilidade Pirata: " << probPirata << endl;
    os << " Preco do navio: " << precoNavio << endl;
    os << " Preco do soldado: " << precoSoldado << endl;
    os << " Preco da venda de peixe: " << precoVendPeixe << endl;
    os << " Preco de comprar no mercado: " << precoCompMercad << endl;
    os << " Preco de vender no mercado: " << precoVendMercad << endl;
    os << " Quantidade de soldados no Porto: " << soldadosPorto << endl;
    os << " Probabilidade de vento: " << probEvento << endl;
    os << " Probabilidade de tempestade: " << probTempestade << endl;
    os << " Probabilidade de sereias: " << probSereias << endl;
    os << " Probabilidade de calmaria: " << probCalmaria << endl;
    os << " Probabilidade de motim: " << probMotim << endl;
    os << "--------------------------------------" << endl;

    return os.str();
}

/**
 * Função de consulta responsável por devolver um Ponteiro para Jogador.
 * @return Ponteiro para Jogador
 */
Jogador * Mundo::getJogador() {
    return jogador;
}

/**
 * Função de consulta responsável por devolver o Mapa.
 * @return Vetor de Vetor de Célula
 */
vector<vector<Terreno*> > Mundo::getMapa() const {
    return mapa;
}

/**
 * Função de consulta responsável por devolver o número de Linhas.
 * @return Linhas
 */
int Mundo::getLinhas() const {
    return linhas;
}

/**
 * Função de consulta responsável por devolver o número de Colunas.
 * @return Colunas
 */
int Mundo::getColunas() const {
    return colunas;
}

/**
 * Função responsável por devolver o mapa mas em caractéres.
 * @return String - Mapa completo
 */
string Mundo::getMapaCarac() const {
    ostringstream oss;
    for (int i = 0; i < linhas; i++) {
        oss << endl;
        for (int j = 0; j < colunas; j++)
            oss << mapa[i][j]->getTipo();
    }
    oss << endl << endl;
    return oss.str();
}

/**
 * Função responsável por criar um Ponteiro para Navio (Classe Derivada) de acordo com o tipo recebido.
 * @param tipo Tipo de Navio
 * @param x Posição no Eixo dos X (Colunas)
 * @param y Posição no Eixo dos Y (Linhas)
 * @return Ponteiro para Navio (Classe Derivada)
 */
Navio* Mundo::verificaTipoNavio(string tipo, int x, int y) {
    if (tipo == "V") return new Veleiro(x, y);
    if (tipo == "G") return new Galeao(x, y);
    if (tipo == "E") return new Escuna(x, y);
    if (tipo == "F") return new Fragata(x, y);
    if (tipo == "I") return new Implacavel(x, y);
}

/**
 * Função responsável por encontrar o Porto Principal Amigo e devolver um Ponteiro para esse mesmo Porto.
 * @return Endereço do Porto Principal Amigo
 */
Terreno * Mundo::achaPortoPrincipal() const {
    for (int i = 0; i < mapa.size(); i++) {
        for (int j = 0; j < mapa[i].size(); j++) {
            if (mapa[i][j]->getPrincipal() && mapa[i][j]->getAmigo()) {
                return mapa[i][j];
            }
        }
    }
    return nullptr; // NAO DEVE ACONTECER
}

/**
 * Função responsável por efetuar a compra do navio(criação e adicionar quer ao mundo, quer ao jogador). Sendo que o navio vai "nascer" no Porto Principal.
 * @param tipo Caractér que identifica o Tipo de Navio
 */
void Mundo::compraNavio(string tipo) {
    if (possuiNaviosNosPortos() || jogador->getNavios().size() == 0) {
        if (navios.size() + jogador->getNavios().size() < 99 && jogador->getMoedas() >= precoNavio) {
            Terreno * t = achaPortoPrincipal();
            if (t != nullptr) { // NAO DEVE ACONTECER
                Navio * a = verificaTipoNavio(tipo, t->getPosicao().getX(), t->getPosicao().getY());
                jogador->addNavio(a);
                jogador->addMoedas(precoNavio*-1);
            }
        }
    }
}

/**
 * Destrutor da Classe Mundo.
 */
Mundo::~Mundo() {
    //    for (auto a : jogador->getNavios()) {
    //        delete a;
    //    }
    delete jogador;
    for (auto a : mapa) {
        for (auto b : a) {
            delete b;
        }
    }
    for (auto a : navios) {
        delete a;
    }
}

Posicao Mundo::achaNovaPosicao(int id, Posicao pos) {
    Posicao nova = pos;
    switch (id) {
        case 1:
            nova.setX(pos.getX() - 1);
            nova.setY(pos.getY() - 1);
            break;
        case 2:
            nova.setY(pos.getY() - 1);
            break;
        case 3:
            nova.setX(pos.getX() + 1);
            nova.setY(pos.getY() - 1);
            break;
        case 4:
            nova.setX(pos.getX() - 1);
            break;
        case 5:
            nova.setX(pos.getX() + 1);
            break;
        case 6:
            nova.setX(pos.getX() - 1);
            nova.setY(pos.getY() + 1);
            break;
        case 7:
            nova.setY(pos.getY() + 1);
            break;
        case 8:
            nova.setX(pos.getX() + 1);
            nova.setY(pos.getY() + 1);
            break;
        default:
            break;
    }

    nova.corrige(colunas, linhas);

    return nova;
}

/**
 * Função responsável por devolver um Ponteiro para a Célula cujo id foi recebido como parâmetro.
 * @param id ID da Célula
 * @param x Posição no Eixo dos X (Colunas)
 * @param y Posição no Eixo dos Y (Linhas)
 * @return Ponteiro para Célula
 */
Terreno* Mundo::getCelulaTipo(int id, Posicao atual) {
    Posicao nova = achaNovaPosicao(id, atual);
    if (nova.getX() == atual.getX() && nova.getY() == atual.getY()) return nullptr;
    return mapa[nova.getY()][nova.getX()];
}

/**
 * Função responsável por verificar se existe algum Navio Pirata naquele Terreno (Mar).
 * @param Celula
 * @return Verdadeiro caso já exista algum Navio naquela célula, Falso caso contrário.
 */
bool Mundo::verificaSeExisteNaviosPiratasNoMar(Terreno * a) {
    int x = a->getPosicao().getX(), y = a->getPosicao().getY();
    for (auto n : navios) {
        if (n->getPos().getX() == x && n->getPos().getY() == y) {
            return true;
        }
    }
    return false;
}

/**
 * Função responsável por verificar se existe algum Navio naquele Terreno (Mar).
 * @param Celula
 * @return Verdadeiro caso já exista algum Navio naquela célula, Falso caso contrário.
 */
bool Mundo::verificaSeExisteNaviosNoMar(Terreno * a) {
    int x = a->getPosicao().getX(), y = a->getPosicao().getY();
    for (auto n : jogador->getNavios()) {
        if (n->getPos().getX() == x && n->getPos().getY() == y) {
            return true;
        }
    }
    return false;
}

/**
 * Função responsável por criar um array com 8 números aleatórios não repetidos, e verificar cada uma dessas células até encontrar uma que esteja livre. Caso não consiga, devolve nullptr.
 * @param x Posição no Eixo dos X (Colunas)
 * @param y Posição no Eixo dos Y (Linhas)
 * @return Ponteiro para Célula
 */
Terreno* Mundo::getCelulaLivreAleatoria(Posicao atual, Navio * n) {
    vector<int> celulas = Auxiliar::getVetorInteirosAleatoriosNaoRepetidos(8, 1, 8);
    Terreno * t = nullptr;
    for (int i = 0; i < celulas.size(); i++) {
        t = getCelulaTipo(celulas[i], atual);
        if (t != nullptr) {
            if (t->navegavel(*this, n)) {
                return t;
            }
        }
    }
    return nullptr;
}

Terreno* Mundo::getCelulaLivreAleatoriaComPeixe(Posicao atual, Navio * n) {
    vector<int> celulas = Auxiliar::getVetorInteirosAleatoriosNaoRepetidos(8, 1, 8);
    Terreno * t = nullptr;
    for (int i = 0; i < celulas.size(); i++) {
        t = getCelulaTipo(celulas[i], atual);
        if (t != nullptr) {
            if (t->navegavel(*this, n) && t->getPeixe()) {
                return t;
            }
        }
    }
    return nullptr;
}

/**
 * Função responsável por fazer com que cada navio desta Classe se movimente.
 */
void Mundo::movimentaNavios() {
    // Movimenta Navios do Mundo
    for (auto n : navios) {
        n->movimento(*this);
    }

    // Movimenta Navios do Jogador
    for (auto n : jogador->getNavios()) {
        n->movimento(*this);
    }
    for (auto a : mapa) {
        for (auto b : a) {
            if (b->getTipo() != '.' && b->getTipo() != '+') {
                if (b->getAmigo()) {
                    for (auto n : navios) {
                        if (Auxiliar::isAdjacente(b->getPosicao(), n->getPos())) {
                            // SE FOR PORTO DO JOGADOR E QUE SEJA UM NAVIO DO INIMIGO
                            batalhaEntreNavioEPorto(b, n);
                        }
                    }
                } else {
                    for (auto n : jogador->getNavios()) {
                        if (Auxiliar::isAdjacente(b->getPosicao(), n->getPos())) {
                            // SE FOR PORTO DO JOGADOR E QUE SEJA UM NAVIO DO INIMIGO
                            batalhaEntreNavioEPorto(b, n);
                        }
                    }
                }
            }
        }
    }
}

/**
 * Função de consulta responsável por devolver um Vetor de Ponteiros para Navios.
 * @return Vetor de Ponteiros para Navios
 */
vector<Navio*> Mundo::getNavios() const {
    return navios;
}

Terreno* Mundo::criaTerreno(char let, int x, int y) {
    if (let == '.') return new Mar(x, y);
    if (let == '+') return new Terra(x, y);
    return new Porto(x, y, let);
}

bool Mundo::navioPertence(int id) {
    for (auto n : navios) {
        if (id == n->getId())
            return true;
    }
    return false;
}

void Mundo::criaNavioPirata(int x, int y, string tipo) {
    if (tipo == "F" || tipo == "V") {
        if (mapa[y][x]->getTipo() != '+' && !mapa[y][x]->getAmigo()) {
            if (!verificaSeExisteNaviosNoMar(mapa[y][x]) && !verificaSeExisteNaviosPiratasNoMar(mapa[y][x])) {
                navios.push_back(verificaTipoNavio(tipo, x, y));
            }
        }
    }
}

void Mundo::mudaComportamentoAutomatico(int id, bool comp) {
    // Navios Piratas
    for (auto a : navios) {
        if (id == a->getId()) {
            a->setAutoComportamento(comp);
            a->setDestino(a->getPos());
        }
    }
    // Navios do Jogador
    for (auto a : jogador->getNavios()) {
        if (id == a->getId()) {
            a->setAutoComportamento(comp);
            a->setDestino(a->getPos());
        }
    }
}

bool Mundo::possuiNaviosNosPortos() {
    for (auto n : jogador->getNavios()) {
        if (isNavioNoPortoAmigo(n))
            return true;
    }
    return false;
}

bool Mundo::isNavioNoPortoAmigo(Navio * n) {
    n->getPos().corrige(colunas, linhas);
    if (n->getPos().getX() >= colunas || n->getPos().getX() < 0 || n->getPos().getY() >= linhas || n->getPos().getY() < 0)
        return false;
    if (mapa[n->getPos().getY()][n->getPos().getX()]->getAmigo())
        return true;
    return false;
}

Navio* Mundo::encontraNavio(int id) {
    // Navios Piratas
    for (auto a : navios) {
        if (a->getId() == id) {
            return a;
        }
    }
    // Navios do Jogador
    for (auto a : jogador->getNavios()) {
        if (a->getId() == id) {
            return a;
        }
    }
    return nullptr;
}

void Mundo::compraSoldados(int id, int quant) {
    Navio * n = encontraNavio(id);
    if (n != nullptr) {
        if (isNavioNoPortoAmigo(n) && (jogador->getMoedas() >= (quant * precoSoldado)) && (n->getMaxTripulacao() >= (n->getTripulacao() + quant))) {
            jogador->addMoedas((quant * precoSoldado)*-1);
            n->addTripulacao(quant);
        }
    }
}

Terreno* Mundo::getTerreno(Posicao pos) {
    if (pos.getY() >= linhas || pos.getX() >= colunas) return nullptr;
    return mapa[pos.getY()][pos.getX()];
}

void Mundo::moverNaviosComando(int id, string direcao) {
    Navio * n = encontraNavio(id);
    if (n != nullptr) {
        if (direcao == "D") n->move(*this, 1, 0);
        else {
            if (direcao == "E") n->move(*this, -1, 0);
            else {
                if (direcao == "C") n->move(*this, 0, -1);
                else {
                    if (direcao == "B") n->move(*this, 0, 1);
                    else {
                        if (direcao == "CE") n->move(*this, -1, -1);
                        else {
                            if (direcao == "CD") n->move(*this, 1, -1);
                            else {
                                if (direcao == "BE") n->move(*this, -1, 1);
                                else {
                                    if (direcao == "BD") n->move(*this, 1, 1);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void Mundo::vendeNavio(int id) {
    Navio * n = encontraNavio(id);
    if (n != nullptr) {
        if (isNavioNoPortoAmigo(n)) {
            int total = 0;
            total += n->getTripulacao() * precoSoldado;
            total += precoNavio;
            if (jogador->apagaNavio(n->getId())) {
                jogador->addMoedas(total);
            }
        }
    }
}

Navio* Mundo::getNavioEspecificoMaisPerto(char tipo, Posicao atual, int id) {
    Navio * alvo = nullptr;
    float distancia, menor = linhas*colunas;
    if (verificaSeNavioEPirata(id)) {
        // NAVIO PIRATA
        for (auto n : navios) {
            if (n->getId() != id && n->getTipo() == tipo) {
                distancia = distanciaEntreDoisNavios(atual, n->getPos());
                if (menor > distancia) {
                    alvo = n;
                    menor = distancia;
                }
            }
        }
    } else {
        // NAVIO DO JOGADOR
        for (auto n : jogador->getNavios()) {
            if (n->getId() != id && n->getTipo() == tipo) {
                distancia = distanciaEntreDoisNavios(atual, n->getPos());
                if (menor > distancia) {
                    alvo = n;
                    menor = distancia;
                }
            }
        }
    }

    return alvo;
}

Terreno* Mundo::getPortoMaisPerto(Posicao nav, int id) {
    float distancia, menor = linhas*colunas;
    Terreno* t = nullptr;
    for (auto a : mapa) {
        for (auto b : a) {
            if (b->getAmigo()) {
                distancia = distanciaEntreDoisNavios(nav, b->getPosicao());
                if (distancia < menor) {
                    menor = distancia;
                    t = b;
                }
            }
        }
    }
    return t;
}

bool Mundo::verificaSeNavioEPirata(int id) {
    for (auto a : navios) {
        if (a->getId() == id)
            return true;
    }
    return false;
}

Posicao Mundo::achaPosicaoMaisPertoDoAlvoDentroDoRaio(Navio * n, Posicao alvo) {
    Posicao proxima = n->getPos();
    Terreno * temp = nullptr;
    float distancia, menor = linhas*colunas;

    for (int i = 0; i < 8; i++) {
        temp = getCelulaTipo(i + 1, n->getPos());
        if (temp != nullptr) {
            if (temp->navegavel(*this, n)) {
                distancia = distanciaEntreDoisNavios(temp->getPosicao(), alvo);
                if (distancia < menor) {
                    menor = distancia;
                    proxima = temp->getPosicao();
                }
            }
        }
    }
    return proxima;
}

float Mundo::distanciaEntreDoisNavios(Posicao a, Posicao b) {
    Auxiliar aux;
    float distanciaMenor = linhas*colunas;
    float distancia;
    Posicao temp;
    distancia = aux.calculaDistanciaEntreDoisPontos(a, b);
    if (distancia < distanciaMenor) distanciaMenor = distancia;
    temp.setX(a.getX() + colunas);
    temp.setY(a.getY());
    distancia = aux.calculaDistanciaEntreDoisPontos(temp, b);
    if (distancia < distanciaMenor) distanciaMenor = distancia;
    temp.setX(a.getX());
    temp.setY(a.getY() + linhas);
    distancia = aux.calculaDistanciaEntreDoisPontos(temp, b);
    if (distancia < distanciaMenor) distanciaMenor = distancia;
    return distanciaMenor;
}

void Mundo::navioVaiPara(int id, Posicao dest) {
    if (!navioPertence(id)) {
        Navio * n = encontraNavio(id);
        if (n != nullptr) {
            n->setAutoComportamento(false);
            n->setDestino(dest);
        }
    }
}

Terreno* Mundo::encontraPorto(char tipo) {
    for (auto a : mapa) {
        for (auto b : a) {
            if (b->getTipo() == tipo)
                return b;
        }
    }
    return nullptr;
}

void Mundo::verificaAdjacencia(Navio* n, char alvo) {
    if (n == nullptr)
        return;

    // TRANSPORTE DE MERCADORIAS E RE-CONQUISTA
    if (navioPertence(n->getId())) {
        for (auto a : navios) {
            if (Auxiliar::isAdjacente(a->getPos(), n->getPos())) {
                if (a->getPodeSerConquistado()) {
                    conquistaNavio(n, a);
                } else {
                    if (a->getTipo() == alvo) {
                        transportaDeUmNavioParaOutro(a, n);
                    }
                }
            }
        }
    } else {
        for (auto a : jogador->getNavios()) {
            if (Auxiliar::isAdjacente(a->getPos(), n->getPos())) {
                if (a->getPodeSerConquistado()) {
                    conquistaNavio(n, a);
                } else {
                    if (a->getTipo() == alvo) {
                        transportaDeUmNavioParaOutro(a, n);
                    }
                }
            }
        }
    }
    conquistaEBatalhas(n);
}

void Mundo::transportaDeUmNavioParaOutro(Navio* navio, Navio* outro) {
    if (navio->temAlgoNoPorao() && outro->temEspacoNoPorao()) {
        navio->getPorao().addPeixe(outro->enchePorao(navio->getPorao().getPeixe())*-1);
    }
}

bool Mundo::verificaSeEstaEmTempestade(Posicao a) {
    for (int i = 0; i < mapa.size(); i++) {
        for (int j = 0; j < mapa[i].size(); j++) {
            if (mapa[i][j]->getPosicao() == a)
                return mapa[i][j]->getTempestade();
        }
    }
    // SUPOSTAMENTE NUNCA DEVE ACONTECER
    return false;
}

void Mundo::navioAfundou(Navio* n) {
    if (n == nullptr)
        return;
    if (navioPertence(n->getId())) {
        for (auto it = navios.begin(); it != navios.end(); it++) {
            if (n->getId() == (*it)->getId()) {
                ostringstream oss;
                oss.clear();
                oss << "O navio " << n->getId() << " afundou!";
                logCombate.push_back(oss.str());
                if (n != nullptr)
                    delete n;
                it = navios.erase(it);
                return;
            }
        }
    } else {
        for (auto it = jogador->getNavios().begin(); it != jogador->getNavios().end(); it++) {
            if (n->getId() == (*it)->getId()) {
                ostringstream oss;
                oss.clear();
                oss << "O navio " << n->getId() << " afundou!";
                logCombate.push_back(oss.str());
                if (n != nullptr)
                    delete n;
                it = jogador->getNavios().erase(it);
                return;
            }
        }
    }
}

void Mundo::comandoCompra(int id, int mercadoria) {
    Navio * n = encontraNavio(id);
    if (n != nullptr) {
        if (isNavioNoPortoAmigo(n) && n->temEspacoNoPorao()) {
            int excesso = n->enchePorao(mercadoria);
            jogador->addMoedas((mercadoria - excesso)*-1);
        }
    }
}

void Mundo::comandoVende(int id) {
    if (navioPertence(id))
        return;
    Navio * n = encontraNavio(id);

    if (n != nullptr && isNavioNoPortoAmigo(n)) {
        int total = 0;
        total += n->getPorao().getPeixe() * precoVendPeixe;
        n->getPorao().setPeixe(0);
        total += n->getPorao().getMercadoria() * precoVendMercad;
        n->getPorao().setMercadoria(0);
        jogador->addMoedas(total);
    }
}

void Mundo::conquistaNavio(Navio* n, Navio* conquista) {
    if (n != nullptr && conquista != nullptr && conquista->getPodeSerConquistado()) {
        if (verificaSeNavioEPirata(n->getId()) && (conquista->getTipo() != 'V' && conquista->getTipo() != 'F')) {
            navioAfundou(conquista);
        } else {
            int num = n->getTripulacao() / 2;
            conquista->addTripulacao(num);
            n->addTripulacao(num*-1);
            num = n->getAgua() / 2;
            conquista->addAgua(num);
            n->addAgua(num*-1);
            conquista->setPodeSerConquistado(false);
            if (verificaSeNavioEPirata(conquista->getId())) {
                jogador->addNavio(conquista);
                perdiNavio(conquista);
            } else {
                navios.push_back(conquista);
                jogador->perdiNavio(conquista);
            }
        }
    }
}

void Mundo::perdiNavio(Navio* n) {
    if (n == nullptr)
        return;
    for (auto it = navios.begin(); it < navios.end(); it++) {
        if ((*it)->getId() == n->getId()) {
            it = navios.erase(it);
            return;
        }
    }
}

Navio* Mundo::getNavioInimigoMaisPerto(Posicao atual, int id) {
    Navio * alvo = nullptr;
    float distancia, menor = linhas*colunas;
    if (verificaSeNavioEPirata(id)) {
        // NAVIO PIRATA
        for (auto n : jogador->getNavios()) {
            distancia = distanciaEntreDoisNavios(atual, n->getPos());
            if (menor > distancia) {
                alvo = n;
                menor = distancia;
            }
        }
    } else {
        // NAVIO DO JOGADOR
        for (auto n : navios) {
            distancia = distanciaEntreDoisNavios(atual, n->getPos());
            if (menor > distancia) {
                alvo = n;
                menor = distancia;
            }
        }
    }

    return alvo;
}

Navio* Mundo::getNavioAmigoMaisPerto(Posicao atual, int id) {
    Navio * alvo = nullptr;
    float distancia, menor = linhas*colunas;
    if (verificaSeNavioEPirata(id)) {
        // NAVIO PIRATA
        for (auto n : navios) {
            distancia = distanciaEntreDoisNavios(atual, n->getPos());
            if (menor > distancia) {
                alvo = n;
                menor = distancia;
            }
        }
    } else {
        // NAVIO DO JOGADOR
        for (auto n : jogador->getNavios()) {
            distancia = distanciaEntreDoisNavios(atual, n->getPos());
            if (menor > distancia) {
                alvo = n;
                menor = distancia;
            }
        }
    }

    return alvo;
}

void Mundo::comecaCombate(Navio* iniciante, Navio* alvo) {
    if (iniciante == nullptr || alvo == nullptr)
        return;
    int numeroIniciante = Auxiliar::geraNumerosInteirosAleatorios(0, iniciante->getTripulacao());
    int numeroAlvo = Auxiliar::geraNumerosInteirosAleatorios(0, alvo->getTripulacao());

    // Atribuição de vencedor e derrotado
    Navio* vencedor = nullptr;
    Navio* derrotado = nullptr;

    if (numeroIniciante >= numeroAlvo) {
        vencedor = iniciante;
        derrotado = alvo;
    } else {
        derrotado = iniciante;
        vencedor = alvo;
    }
    ostringstream logs;
    logs.clear();
    logs << "O navio " << vencedor->getId() << " venceu a batalha contra " << derrotado->getId() << ".";
    logCombate.push_back(logs.str());
    int trip = vencedor->getTripulacao() * 0.2;

    // Vencedor Prejuizos
    vencedor->setTripulacao(vencedor->getTripulacao() - trip);
    vencedor->setPerdeuUltimoCombate(false);
    derrotado->setTripulacao(derrotado->getTripulacao()-(trip * 2));
    derrotado->setPerdeuUltimoCombate(true);

    // Caso Navio derrotado vá afundar
    if (derrotado->getTripulacao() <= 0) {

        vencedor->getPorao().addPeixe(derrotado->getPorao().getPeixe() / 2);
        vencedor->getPorao().addMercadoria(derrotado->getPorao().getMercadoria() / 2);
        vencedor->addAgua(derrotado->getAgua());
        derrotado->afundei(*this);
    }

    // Caso Navio vencedor vá afundar
    if (vencedor->getTripulacao() <= 0) {
        vencedor->afundei(*this);
    }
}

void Mundo::conquistaEBatalhas(Navio* nav) {
    // CONQUISTA E BATALHAS
    if (navioPertence(nav->getId())) {
        for (auto a : jogador->getNavios()) {
            if (Auxiliar::isAdjacente(a->getPos(), nav->getPos())) {
                if (a->getPodeSerConquistado()) {
                    conquistaNavio(nav, a);
                } else {
                    if (!nav->getPerdeuUltimoCombate())
                        comecaCombate(nav, a);
                }
            }
        }
    } else {
        for (auto a : navios) {
            if (Auxiliar::isAdjacente(a->getPos(), nav->getPos())) {
                if (a->getPodeSerConquistado()) {
                    conquistaNavio(nav, a);
                } else {

                    if (!nav->getPerdeuUltimoCombate())
                        comecaCombate(nav, a);
                }
            }
        }
    }
}

void Mundo::batalhaImplacavel(Navio * n) {
    for (auto a : navios) {
        if (Auxiliar::isAdjacente(a->getPos(), n->getPos())) {
            if (a->getPodeSerConquistado()) {
                conquistaNavio(n, a);
            } else {
                if (!n->getPerdeuUltimoCombate()) {

                    n->setPerdeuUltimoCombate(false);
                    ostringstream logs;
                    logs.clear();
                    logs << "O navio " << n->getId() << " destruiu brutalmente o navio " << a->getId() << ".";
                    logCombate.push_back(logs.str());
                    a->afundei(*this);
                }
            }
        }
    }
}

void Mundo::geraEvento() {
    if (sereias || calmaria || tempestade || motim)
        return;
    int prob = Auxiliar::geraNumerosInteirosAleatorios(1, 100);
    if (prob > probEvento)
        return;
    prob = Auxiliar::geraNumerosInteirosAleatorios(1, 100);

    if (prob <= probTempestade) {
        tempestade = true;
        geraTempestade();
    } else {
        if (prob <= probSereias + probTempestade) {
            sereias = true;
            geraSereias();
        } else {
            if (prob <= probSereias + probTempestade + probCalmaria) {
                calmaria = true;
                geraCalmaria();
            } else {

                motim = true;
                geraMotim();
            }
        }
    }
}

void Mundo::geraTempestade() {
    if (tempestade == false)
        return;
    Posicao pos;
    int conta = 0;
    for (auto a : mapa) {
        for (auto b : a) {
            if (b->getTipo() == '.')
                conta++;
        }
    }
    int encontra = Auxiliar::geraNumerosInteirosAleatorios(1, conta);
    conta = 0;
    for (auto a : mapa) {
        for (auto b : a) {
            if (b->getTipo() == '.') {
                conta++;
                if (encontra == conta)
                    pos = b->getPosicao();
            }
        }
    }
    Posicao direita = pos;
    direita.setX(pos.getX() + 1);
    direita.corrige(colunas, linhas);
    Posicao baixo = pos;
    baixo.setY(pos.getY() + 1);
    baixo.corrige(colunas, linhas);
    Posicao dirBaixo = pos;
    dirBaixo.setX(pos.getX() + 1);
    dirBaixo.setY(pos.getY() + 1);
    dirBaixo.corrige(colunas, linhas);

    getTerreno(pos)->setTempestade(true);
    if (getTerreno(direita)->getTipo() == '.')
        getTerreno(direita)->setTempestade(true);

    if (getTerreno(baixo)->getTipo() == '.')
        getTerreno(baixo)->setTempestade(true);

    if (getTerreno(dirBaixo)->getTipo() == '.')
        getTerreno(dirBaixo)->setTempestade(true);

}

void Mundo::geraSereias() {
    if (sereias == false || (navios.size() + jogador->getNavios().size() == 0))
        return;
    int prob = Auxiliar::geraNumerosInteirosAleatorios(1, navios.size() + jogador->getNavios().size());
    int conta = 0;
    if (prob < navios.size()) {
        for (auto a : navios) {
            conta++;
            if (conta == prob)
                a->setTripulacao(a->getTripulacao()*0.9);
        }
    } else {
        prob -= navios.size();
        for (auto a : jogador->getNavios()) {
            conta++;

            if (conta == prob)
                a->setTripulacao(a->getTripulacao()*0.9);
        }

    }
}

void Mundo::geraMotim() {
    if (motim == false || jogador->getNavios().size() == 0)
        return;
    int escolhido;
    escolhido = Auxiliar::geraNumerosInteirosAleatorios(1, jogador->getNavios().size());

    escolhido = jogador->getNavios()[escolhido - 1]->getId();
    Navio * n;
    n = encontraNavio(escolhido);
    if (n == nullptr)
        return;
    if (n->getTipo() != 'F' && n->getTipo() != 'V') {
        n->afundei(*this);
        dias = 0;
        motim = false;
    } else {
        navioMotim = escolhido;
        dias = 0;
        navios.push_back(n);
        jogador->perdiNavio(n);
    }
}

void Mundo::verificaMotim() {
    if (motim == false)
        return;
    if (dias == 3) {
        motim = false;
        dias = 0;
        Navio *n;
        n = encontraNavio(navioMotim);
        jogador->getNavios().push_back(n);
        perdiNavio(n);
    } else
        dias++;
}

void Mundo::verificaCalmaria() {
    if (calmaria == false)
        return;
    bool estado;
    if (dias == 2) {
        calmaria = false;
        for (auto n : jogador->getNavios()) {
            estado = n->verificaFimCalmaria(*this);
            if (estado == true)
                jogador->addMoedas(100);
        }
        for (auto a : mapa) {
            for (auto b : a) {
                b->setCalmaria(false);
            }
        }
        dias = 0;
    } else
        dias++;
}

void Mundo::geraCalmaria() {
    if (calmaria == false)
        return;
    Posicao pos;
    int conta = 0;
    for (auto a : mapa) {
        for (auto b : a) {
            if (b->getTipo() == '.')
                conta++;
        }
    }
    int encontra = Auxiliar::geraNumerosInteirosAleatorios(1, conta);
    conta = 0;
    for (auto a : mapa) {
        for (auto b : a) {
            if (b->getTipo() == '.') {
                conta++;
                if (encontra == conta)
                    pos = b->getPosicao();
            }
        }
    }
    Posicao direita = pos;
    direita.setX(pos.getX() + 1);
    direita.corrige(colunas, linhas);
    Posicao baixo = pos;
    baixo.setY(pos.getY() + 1);
    baixo.corrige(colunas, linhas);
    Posicao dirBaixo = pos;
    dirBaixo.setX(pos.getX() + 1);
    dirBaixo.setY(pos.getY() + 1);
    dirBaixo.corrige(colunas, linhas);

    getTerreno(pos)->setCalmaria(true);
    if (getTerreno(direita)->getTipo() == '.')
        getTerreno(direita)->setCalmaria(true);

    if (getTerreno(baixo)->getTipo() == '.')
        getTerreno(baixo)->setCalmaria(true);

    if (getTerreno(dirBaixo)->getTipo() == '.')
        getTerreno(dirBaixo)->setCalmaria(true);
    dias = 0;
}

void Mundo::diaSeguinte() {
    for (auto a : mapa) {
        for (auto b : a) {

            b->avancaDia();
        }
    }
    verificaCalmaria();
    verificaMotim();
}

void Mundo::novoTurno() {
    logCombate.clear();
    sereias = false;
    tempestade = false;
    for (auto a : mapa) {
        for (auto b : a) {

            b->setTempestade(false);
        }
    }
    movimentaNavios();
    geraEvento();
    geraPiratas();
    diaSeguinte();

    // LIMPA NAVIOS "MORTOS"
    for (auto n : navios) {
        if (!n->getVivo()) {
            // navioAfundou(n);
            ostringstream oss;
            oss.clear();
            oss << "O navio " << n->getId() << " afundou!";
            logCombate.push_back(oss.str());
        }
    }
    eliminaMortos();

    for (auto n : jogador->getNavios()) {
        if (!n->getVivo()) {
            //            navioAfundou(n);
            ostringstream oss;
            oss.clear();
            oss << "O navio " << n->getId() << " afundou!";
            logCombate.push_back(oss.str());
        }
    }
    jogador->eliminaMortos();

    int status = 1;
    for (auto n : jogador->getNavios()) {
        if (n->getVivo())
            status = 0;
    }

    if (status == 1 && jogador->getMoedas() <= 0) {
        ligado = false;
    }
}

void Mundo::geraPiratas() {
    int prob = Auxiliar::geraNumerosInteirosAleatorios(1, 100);
    if (prob <= probPirata) {
        // Descobre Celula Aleatória
        Posicao pirata = encontraPorto('a')->getPosicao();
        int conta = 0;
        for (auto a : mapa) {
            for (auto b : a) {
                if (b->getTipo() == '.' && !verificaSeExisteNaviosNoMar(b) && !verificaSeExisteNaviosPiratasNoMar(b))
                    conta++;
            }
        }
        int encontra = Auxiliar::geraNumerosInteirosAleatorios(1, conta);
        conta = 0;
        for (auto a : mapa) {
            for (auto b : a) {
                if (b->getTipo() == '.' && !verificaSeExisteNaviosNoMar(b) && !verificaSeExisteNaviosPiratasNoMar(b)) {
                    conta++;
                    if (encontra == conta)
                        pirata = b->getPosicao();
                }
            }
        }
        // Cria navio pirata
        prob = Auxiliar::geraNumerosInteirosAleatorios(1, 100);
        if (prob <= 50)
            criaNavioPirata(pirata.getX(), pirata.getY(), "V");

        else
            criaNavioPirata(pirata.getX(), pirata.getY(), "F");
    }
}

bool Mundo::getCalmaria() {

    return calmaria;
}

bool Mundo::getMotim() {

    return motim;
}

bool Mundo::getTempestade() {

    return tempestade;
}

bool Mundo::getSereias() {

    return sereias;
}

vector<string> Mundo::getLogCombate() const {

    return logCombate;
}

void Mundo::batalhaEntreNavioEPorto(Terreno* porto, Navio* nav) {
    nav->setTripulacao(nav->getTripulacao()*0.9);
    int prob = Auxiliar::geraNumerosInteirosAleatorios(0, 100);

    if (prob <= nav->getTripulacao()) {
        porto->conquistado();
    } else {
        nav->afundei(*this);
    }
}

void Mundo::eliminaMortos() {
    for (auto it = navios.begin(); it != navios.end();) {
        if (!((*it)->getVivo())) {
            delete *it;
            it = navios.erase(it);
        } else {
            ++it;
        }
    }
}

void Mundo::finalizouJogo() {
    int total;
    for (auto a : jogador->getNavios()) {
        total = 0;
        if (a != nullptr && a->getVivo()) {
            total += a->getTripulacao() * precoSoldado;
            total += precoNavio;
            if (jogador->apagaNavio(a->getId())) {
                jogador->addMoedas(total);
            }
        }
    }
    jogador->addPontuacao(jogador->getMoedas());
}

bool Mundo::getEstadoServidor() const {
    return ligado;
}
