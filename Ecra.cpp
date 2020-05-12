/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Grafica.cpp
 * 
 * Authors:
 * - Ricardo Belinha nº 21250197
 * - João Fernandes  nº 21250054
 * 
 * Created on 8 de Novembro de 2018, 15:18
 */

#include "Ecra.h"
#include "Consola.h"
#include "Mundo.h"
#include "Jogador.h"
#include "Terreno.h"
#include <iostream>

/**
 * Construtor da Classe Ecra.
 */
Ecra::Ecra() {
    Consola::setTextColor(Consola::PRETO);
    Consola::setTextSize(30, 20);
    Consola::setScreenSize(width, height);
    Consola::setBackgroundColor(Consola::CYAN_CLARO);
    Consola::clrscr();
    desenhaHeader();
}

/**
 * Função responsável por desenhar o mapa (células).
 * @param m Ponteiro para mundo
 * @param listaComandos Vetor de strings
 */
void Ecra::desenhaTerreno(Mundo * m, vector<string> listaComandos) {
    Consola::clrscr();
    for (int i = 0; i < m->getLinhas(); i++) {
        for (int k = 0; k < tam_celula; k++) {
            Consola::setBackgroundColor(Consola::CYAN_CLARO);
            cout << endl;
            cout << "  ";
            for (int j = 0; j < m->getColunas(); j++) {
                descobreCorCelula(j, i, m);
                colocaCaracterNaCelula(j, i);
            }
        }
    }
    desenhaNavios(m);
    Consola::setBackgroundColor(Consola::CYAN_CLARO);
    desenhaComandos(m, listaComandos);
    desenhaStatusJogador(m);
    desenhaListaPrecosPortos(m);
    Consola::gotoxy(2, m->getLinhas()*2 + 2);
}

/**
 * Função responsável por colocar um caractér na célula posicionada de acordo com os parâmetros de entradas.
 * @param x Posição no Eixo dos X (Colunas)
 * @param y Posição no Eixo dos Y (Linhas)
 */
void Ecra::colocaCaracterNaCelula(int x, int y)const {
    for (int i = 0; i < tam_celula; i++) {
        cout << celula;
    }
}

/**
 * Função responsável por descobrir a cor de acordo com o tipo de célula. (Mar - Azul | Porto Amigo Principal - Preto | Porto Amigo - Branco | Porto Inimigo - Vermelho)
 * @param x Posição no Eixo dos X (Colunas)
 * @param y Posição no Eixo dos Y (Linhas)
 * @param m Ponteiro para mundo
 */
void Ecra::descobreCorCelula(int x, int y, Mundo * m)const {
    if (m->getMapa()[y][x]->getTipo() == '.') {
        if (m->getMapa()[y][x]->getTempestade()) {
            Consola::setBackgroundColor(Consola::ROXO);
            return;
        }
        if (m->getMapa()[y][x]->getCalmaria()) {
            Consola::setBackgroundColor(Consola::AMARELO);
            return;
        }

        if (!m->getMapa()[y][x]->getPeixe()) {
            Consola::setBackgroundColor(Consola::CYAN);
        } else {
            if (y % 2 == 0 && x % 2 == 0 || y % 2 != 0 && x % 2 != 0) {
                Consola::setBackgroundColor(Consola::AZUL);
            } else {
                Consola::setBackgroundColor(Consola::AZUL_CLARO);
            }
        }
    } else {
        if (m->getMapa()[y][x]->getPrincipal() && m->getMapa()[y][x]->getAmigo()) {
            Consola::setBackgroundColor(Consola::PRETO);
        } else {
            if (m->getMapa()[y][x]->getTipo() != '+' && m->getMapa()[y][x]->getTipo() != '.' && m->getMapa()[y][x]->getAmigo()) {
                if (y % 2 == 0 && x % 2 == 0 || y % 2 != 0 && x % 2 != 0) {
                    Consola::setBackgroundColor(Consola::AMARELO);
                } else {
                    Consola::setBackgroundColor(Consola::AMARELO_CLARO);
                }
            } else {
                if (m->getMapa()[y][x]->getTipo() != '+' && m->getMapa()[y][x]->getTipo() != '.') {
                    if (y % 2 == 0 && x % 2 == 0 || y % 2 != 0 && x % 2 != 0) {
                        Consola::setBackgroundColor(Consola::VERMELHO);
                    } else {
                        Consola::setBackgroundColor(Consola::VERMELHO_CLARO);
                    }
                } else {
                    if (m->getMapa()[y][x]->getTipo() == '+') {
                        if (y % 2 == 0 && x % 2 == 0 || y % 2 != 0 && x % 2 != 0) {
                            Consola::setBackgroundColor(Consola::VERDE);
                        } else {
                            Consola::setBackgroundColor(Consola::VERDE_CLARO);
                        }
                    }
                }
            }
        }
    }
}

/**
 * Função responsável por desenhar todos os Navios no mapa.
 * @param m Ponteiro para mundo
 */
void Ecra::desenhaNavios(Mundo * m) const {
    int x, y;
    Consola::setTextColor(Consola::BRANCO);
    // Desenho navios piratas
    for (auto n : m->getNavios()) {
        x = n->getPos().getX();
        y = n->getPos().getY();
        descobreCorCelula(x, y, m);
        Consola::gotoxy(x * 2 + 2, y * 2 + 1);
        cout << n->getId();
    }
    Consola::setTextColor(Consola::VERDE_CLARO);
    // Desenho navios jogador
    for (auto n : m->getJogador()->getNavios()) {
        x = n->getPos().getX();
        y = n->getPos().getY();
        descobreCorCelula(x, y, m);
        Consola::gotoxy(x * 2 + 2, y * 2 + 1);
        cout << n->getId();
    }
    Consola::setTextColor(Consola::PRETO);
}

/**
 * Função responsável por escrever a lista dos comandos disponíveis ao lado do mapa.
 * @param m Ponteiro para mundo
 * @param listaComandos Vetor de string
 */
void Ecra::desenhaComandos(Mundo * m, vector<string> listaComandos) const {
    if (m != nullptr) {
        int x = m->getColunas() - 1, y = 0, maior = 0;
        Consola::gotoxy(x * 2 + 15, y * 2 + 1);
        cout << "Lista de Comandos disponiveis:";
        for (int i = 0; i < listaComandos.size(); i++) {
            if (listaComandos[i].size() > maior) {
                maior = listaComandos[i].size();
            }
        }
        for (int i = 0; i < listaComandos.size(); i++) {
            if (i < m->getLinhas()*2 - 2) {
                Consola::gotoxy(x * 2 + 15, y * 2 + 3 + i);
                cout << "- " << listaComandos[i];
            } else {
                Consola::gotoxy(x * 2 + 15 + maior + 7, y * 2 + 3 + i - (m->getLinhas()*2 - 2));
                cout << "- " << listaComandos[i];
            }
        }
    }
}

void Ecra::desenhaStatusJogador(Mundo* m) {
    if (m != nullptr) {
        int x = m->getColunas() - 1, y = 0;
        Consola::gotoxy(x * 2 + 50, y * 2 + 1);
        cout << "Informacoes do Jogador:";
        Consola::gotoxy(x * 2 + 50, y * 2 + 2);
        cout << "- Nome: " << m->getJogador()->getNome();
        Consola::gotoxy(x * 2 + 50, y * 2 + 3);
        cout << "- Moedas: " << m->getJogador()->getMoedas();
        Consola::gotoxy(x * 2 + 50, y * 2 + 4);
        cout << "- Pontuacao: " << m->getJogador()->getPontuacao();
        Consola::gotoxy(x * 2 + 50, y * 2 + 7);
        cout << "Evento Ocorrido: ";
        if (m->getMotim())
            cout << "Motim";
        else if (m->getTempestade())
            cout << "Tempestade";
        else if (m->getCalmaria())
            cout << "Calmaria";
        else if (m->getSereias())
            cout << "Sereias";
        else
            cout << "Nenhum";
        Consola::gotoxy(x * 2 + 35, y * 2 + 9);
        cout << "Logs de batalha:";
        for (int i = 0; i < m->getLogCombate().size(); i++) {
            Consola::gotoxy(x * 2 + 35, y * 2 + 10 + i);
            cout << " - " << m->getLogCombate()[i];
        }
    }
}

/**
 * Função responsável por desenhar o cabeçalho no início do programa.
 */
void Ecra::desenhaHeader() {
    string header;
    for (int i = 0; i < width * 1.20; i++) {
        header += "-";
    }
    cout << header << endl;
    Consola::gotoxy(width / 4, 1);
    cout << "                     EXPANSOES MARITIMAS                       " << endl;
    Consola::gotoxy(width / 4, 2);
    cout << "                              by                               " << endl;
    Consola::gotoxy(width / 4, 3);
    cout << "   Ricardo Belinha - 21250197  |   Joao Fernandes - 21250054   " << endl;
    Consola::gotoxy(0, 4);
    cout << header << endl;
    Consola::gotoxy(2, 6);
}

void Ecra::setListaPrecosPortos(bool a) {
    listaPrecosPortos = a;
}

void Ecra::desenhaListaPrecosPortos(Mundo* m) {
    if (m != nullptr && listaPrecosPortos) {
        int x = 1, y = 0;
        int linha = m->getLinhas()*2 + 4;
        for (auto a : m->getMapa()) {
            for (auto b : a) {
                if ((b->getTipo() >= 'a' && b->getTipo() <= 'z') || (b->getTipo() >= 'A' && b->getTipo() <= 'Z')) {
                    Consola::gotoxy(x * 2, y * 2 + linha);
                    cout << "Porto: \"" << b->getTipo() << "\" | Coordenadas: (" << b->getPosicao().getX() << ", " << b->getPosicao().getY() << ") | Preco: Normais do mundo | Principal: ";
                    if (b->getPrincipal())
                        cout << "Sim";
                    else
                        cout << "Nao";
                    if (b->getAmigo())
                        cout << " | Amigo";
                    else
                        cout << " | Inimigo";
                    linha++;
                }
            }
        }
        listaPrecosPortos = false;
    }
}

void Ecra::finalizouJogo(Mundo * m) {
    Consola::clrscr();
    desenhaHeader();
    if (m != nullptr && m->getJogador() != nullptr)
        cout << endl << " Pontuacao: " << m->getJogador()->getPontuacao() << endl;
}
