/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Iteracao.cpp
 *
 * Authors:
 * - Ricardo Belinha nº 21250197
 * - João Fernandes  nº 21250054
 *
 * Created on 31 de Outubro de 2018, 16:40
 */

#include "Interacao.h"
#include "Consola.h"
#include "Jogador.h"
#include "Auxiliar.h"
#include <iostream>
#include <sstream>
#include <fstream>

/**
 * Construtor da Classe Interação.
 */
Interacao::Interacao() {
    m = nullptr;
    estado = 0;
    listaComandos = criaComandos();
}

/**
 * Função responsável por abrir um ficheiro, e extrair toda a informação do mesmo para um vetor de string.
 * @param nomeFicheiro Nome do Ficheiro
 * @return Vetor de String - Texto do Ficheiro
 */
vector<string> getInfoFromFile(string nomeFicheiro) {
    vector<string>linhas;
    string line;
    ifstream myfile(nomeFicheiro); // ifstream = padrão ios:in
    if (myfile.is_open()) {
        while (!myfile.eof()) {//enquanto end of file for false continua
            getline(myfile, line); // como foi aberto em modo texto(padrão)
            //e não binário(ios::bin) pega cada linha
            linhas.push_back(line);
        }
        myfile.close();
    } else cout << "O ficheiro nao existe!" << endl;
    return linhas;
}

/**
 * Função responsável por criar uma lista de comandos de acordo com a fase do jogo, devolvendo essa lista.
 * @return Lista de Comandos
 */
vector<string> Interacao::criaComandos() {
    vector<string> listaComandos;
    switch (estado) {
        case 0: // Fase 1
            listaComandos.push_back("config");
            listaComandos.push_back("sair");
            break;
        case 1: // Fase 2
            listaComandos.push_back("exec");
            listaComandos.push_back("prox");
            listaComandos.push_back("compranav");
            listaComandos.push_back("vendenav");
            listaComandos.push_back("lista");
            listaComandos.push_back("compra");
            listaComandos.push_back("vende");
            listaComandos.push_back("move");
            listaComandos.push_back("auto");
            listaComandos.push_back("stop");
            listaComandos.push_back("pirata");
            listaComandos.push_back("evpos");
            listaComandos.push_back("evnav");
            listaComandos.push_back("moedas");
            listaComandos.push_back("vaipara");
            listaComandos.push_back("comprasold");
            listaComandos.push_back("saveg");
            listaComandos.push_back("loadg");
            listaComandos.push_back("delg");
            listaComandos.push_back("sair");
            break;
        case 2: // Fase 3
            break;
    }
    return listaComandos;
}

/**
 * Função responsável por iniciar o ciclo do jogo.
 * @param ficheiro Istream (Exemplo: cin)
 */
void Interacao::iniciaCiclo(istream& ficheiro) {
    int sair;
    do {
        sair = leituraComandos(ficheiro);
        if (m != nullptr && !m->getEstadoServidor()) {
            sair = 0;
            m->finalizouJogo();
            e.finalizouJogo(m);
        }
        if (sair && estado > 0) e.desenhaTerreno(m, listaComandos);
    } while (sair);
}

/**
 * Função responsável por efetuar a leitura dos comandos de um determinado ficheiro..
 * @param ficheiro Istream (Exemplo: cin)
 */
int Interacao::leituraComandos(istream& ficheiro) {
    string comando, nomeComando;

    if (&ficheiro == &cin)
        cout << "Indique o comando: ";
    getline(ficheiro, comando);

    istringstream iss(comando);
    iss >> nomeComando;
    if (!iss) return 1;

    return interpretaComandos(nomeComando, comando);
}

/**
 * Função responsável por verificar se um determinado comando existe na lista de comandos que foi criada previamente.
 * @param a Comando
 * @return Verdadeiro caso encontre, Falso caso contrário
 */
bool Interacao::encontraStringNoVector(string a) {
    for (int i = 0; i < listaComandos.size(); i++) {
        if (a == listaComandos[i]) {
            return true;
        }
    }
    return false;
}

/**
 * Função responsável por interpretar um comando existente e tratá-lo.
 * @param nomeComando Comando
 * @param comando Comando e argumentos
 * @return
 */
int Interacao::interpretaComandos(string nomeComando, string comando) {
    if (encontraStringNoVector(nomeComando)) {
        // Comando - config
        if (nomeComando == "config") {
            trataConfig(comando);
            return 1;
        }
        // Comando - exec
        if (nomeComando == "exec") {
            trataExec(comando);
            return 1;
        }
        // Comando - prox
        if (nomeComando == "prox") {
            trataProx();
            return 1;
        }
        // Comando - compranav
        if (nomeComando == "compranav") {
            trataCompraNav(comando);
            return 1;
        }
        // Comando - vendenav
        if (nomeComando == "vendenav") {
            trataVendeNav(comando);
            return 1;
        }
        // Comando - lista
        if (nomeComando == "lista") {
            trataLista();
            return 1;
        }
        // Comando - compra
        if (nomeComando == "compra") {
            trataCompra(comando);
            return 1;
        }
        // Comando - vende
        if (nomeComando == "vende") {
            trataVende(comando);
            return 1;
        }
        // Comando - move
        if (nomeComando == "move") {
            trataMove(comando);
            return 1;
        }
        // Comando - auto
        if (nomeComando == "auto") {
            trataAuto(comando);
            return 1;
        }
        // Comando - stop
        if (nomeComando == "stop") {
            trataStop(comando);
            return 1;
        }
        // Comando - pirata
        if (nomeComando == "pirata") {
            trataPirata(comando);
            return 1;
        }
        // Comando - evpos
        if (nomeComando == "evpos") {
            cout << "Comando nao implementado!" << endl;
            return 1;
        }
        // Comando - evnav
        if (nomeComando == "evnav") {
            cout << "Comando nao implementado!" << endl;
            return 1;
        }
        // Comando - moedas
        if (nomeComando == "moedas") {
            trataMoedas(comando);
            return 1;
        }
        // Comando - vaipara
        if (nomeComando == "vaipara") {
            trataVaiPara(comando);
            return 1;
        }
        // Comando - comprasold
        if (nomeComando == "comprasold") {
            trataCompraSold(comando);
            return 1;
        }
        // Comando - saveg
        if (nomeComando == "saveg") {
            trataSaveG(comando);
            return 1;
        }
        // Comando - loadg
        if (nomeComando == "loadg") {
            trataLoadG(comando);
            return 1;
        }
        // Comando - delg
        if (nomeComando == "delg") {
            trataDelG(comando);
            return 1;
        }
        // Comando - sair
        if (nomeComando == "sair") {
            trataSair();
            return 0;
        }
    }
    cout << "Este comando e invalido ou nao pode ser usado nesta fase!" << endl << endl;
    return 1;
}

/**
 * Função responsável por tratar do comando config.
 * @param comando Comando e argumentos
 */
void Interacao::trataConfig(string comando) {
    istringstream iss(comando);
    string nomeFicheiro;
    iss >> nomeFicheiro;
    if (!iss) return;
    if (iss >> nomeFicheiro) {
        if (!Auxiliar::ifFileExists(nomeFicheiro))
            return;
        vector<string> infoFicheiro = getInfoFromFile(nomeFicheiro);
        m = new Mundo(infoFicheiro);
        estado = 1;
        listaComandos = criaComandos();
        return;
    }
}

/**
 * Função responsável por tratar do comando exec.
 * @param comando Comando e argumentos
 */
void Interacao::trataExec(string comando) {
    istringstream iss(comando), fich;
    string nomeFicheiro;
    iss >> nomeFicheiro;
    if (!iss) return;
    if (iss >> nomeFicheiro) {
        vector<string> infoFicheiro = getInfoFromFile(nomeFicheiro);
        for (auto x : infoFicheiro) {
            fich.clear();
            fich.str(x);
            leituraComandos(fich);
            //if (estado > 0) e.desenhaTerreno(m, listaComandos);
        }
        return;
    }
}

/**
 * Função responsável por tratar do comando prox.
 */
void Interacao::trataProx() {
    m->novoTurno();
}

/**
 * Função responsável por tratar do comando moedas.
 * @param comando Comando e argumentos
 */
void Interacao::trataMoedas(string comando) {
    istringstream iss(comando);
    string temp;
    int moedas;
    iss >> temp >> moedas;
    if (!iss) return;
    m->getJogador()->addMoedas(moedas);
}

/**
 * Função responsável por tratar do comando compranav.
 * @param comando Comando e argumentos
 */
void Interacao::trataCompraNav(string comando) {
    istringstream iss(comando);
    string temp;

    iss >> temp >> temp;
    if (!iss) return;

    if (temp == "V" || temp == "G" || temp == "E" || temp == "F" || temp == "I") {
        m->compraNavio(temp);
    }
}

/**
 * Função responsável por tratar do comando sair.
 */
void Interacao::trataSair() {
    if (m != nullptr)
        m->finalizouJogo();
    e.finalizouJogo(m);
}

void Interacao::trataPirata(string comando) {
    istringstream iss(comando);
    string temp;
    int x, y;
    iss >> temp >> x >> y >> temp;
    if (!iss) return;
    m->criaNavioPirata(x, y, temp);
}

void Interacao::trataAuto(string comando) {
    istringstream iss(comando);
    string temp;
    int id;
    iss >> temp >> id;
    if (!iss) return;
    m->mudaComportamentoAutomatico(id, true);
}

void Interacao::trataStop(string comando) {
    istringstream iss(comando);
    string temp;
    int id;
    iss >> temp >> id;
    if (!iss) return;
    m->mudaComportamentoAutomatico(id, false);
}

void Interacao::trataCompraSold(string comando) {
    istringstream iss(comando);
    string temp;
    int id, quantSold;
    iss >> temp >> id >> quantSold;
    if (!iss) return;
    m->compraSoldados(id, quantSold);
}

void Interacao::trataMove(string comando) {
    istringstream iss(comando);
    string temp;
    int id;
    iss >> temp >> id >> temp;
    if (!iss) return;
    if (temp == "D" || temp == "E" || temp == "C" || temp == "B" || temp == "CE" || temp == "CD" || temp == "BE" || temp == "BD")
        m->moverNaviosComando(id, temp);
}

void Interacao::trataVendeNav(string comando) {
    istringstream iss(comando);
    string temp;
    int id;
    iss >> temp >> id;
    if (!iss) return;
    m->vendeNavio(id);
}

void Interacao::trataDelG(string comando) {
    istringstream iss(comando);
    string nomeFicheiro;
    iss >> nomeFicheiro >> nomeFicheiro;
    if (!iss) return;
    for (auto it = g.begin(); it < g.end(); it++) {
        if ((*it).getNome() == nomeFicheiro) {
            it = g.erase(it);
        }
    }
}

void Interacao::trataLoadG(string comando) {
    istringstream iss(comando);
    string nomeFicheiro;
    iss >> nomeFicheiro >> nomeFicheiro;
    if (!iss) return;
    for (auto a : g) {
        if (a.getNome() == nomeFicheiro) {
            delete m;
            m = new Mundo(*(a.getMundo()));
        }
    }
}

void Interacao::trataSaveG(string comando) {
    istringstream iss(comando);
    string nomeFicheiro;
    iss >> nomeFicheiro >> nomeFicheiro;
    if (!iss) return;
    for (auto a : g) {
        if (a.getNome() == nomeFicheiro) {
            cout << "Ja existe uma gravacao com esse nome!" << endl;
            return;
        }
    }
    g.push_back(Gravacoes(nomeFicheiro, new Mundo(*m)));
}

void Interacao::trataVaiPara(string comando) {
    istringstream iss(comando);
    string temp;
    char letra;
    Terreno * t = nullptr;
    int id, x = -1, y = -1;
    iss >> temp >> id >> x >> y;
    if (!iss) {
        iss.clear();
        iss.str(comando);
        iss >> temp >> id >> letra;
        if (!iss) return;
        t = m->encontraPorto(letra);
    } else {
        if (x > 0 && y > 0) {
            Posicao a;
            a.setX(x);
            a.setY(y);
            t = m->getTerreno(a);
        } else return;
    }
    if (t == nullptr) return;
    if (!m->navioPertence(id) && t->navegavel(*m, m->encontraNavio(id)) && (t->getPosicao().getX() > 0 && t->getPosicao().getY() > 0))
        m->navioVaiPara(id, t->getPosicao());
}

void Interacao::trataLista() {
    e.setListaPrecosPortos(true);
}

void Interacao::trataCompra(string comando) {
    istringstream iss(comando);
    string temp;
    int id, valor;
    iss >> temp >> id >> valor;
    if (!iss) return;
    m->comandoCompra(id, valor);
}

void Interacao::trataVende(string comando) {
    istringstream iss(comando);
    string temp;
    int id;
    iss >> temp >> id;
    if (!iss) return;
    m->comandoVende(id);
}

/**
 * Destrutor da Classe Interação.
 */
Interacao::~Interacao() {
    delete m;
}
