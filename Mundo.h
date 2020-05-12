/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Mundo.h
 *
 * Authors:
 * - Ricardo Belinha nº 21250197
 * - João Fernandes  nº 21250054
 *
 * Created on 29 de Outubro de 2018, 22:20
 */

#ifndef MUNDO_H
#define MUNDO_H
#include "Navio.h"
#include "Terreno.h"
#include <vector>
class Jogador;
class Terreno;

class Mundo {
    vector<vector<Terreno*>> mapa;
    vector<Navio*> navios;
    Jogador * jogador = nullptr;
    int linhas = 0;
    int colunas = 0;
    int moedas = 0;
    int probPirata = 0;
    int precoNavio = 0;
    int precoSoldado = 0;
    int precoVendPeixe = 0;
    int precoCompMercad = 0;
    int precoVendMercad = 0;
    int soldadosPorto = 0;
    int probEvento = 0;
    int probTempestade = 0;
    int probSereias = 0;
    int probCalmaria = 0;
    int probMotim = 0;
    // Log de combate
    vector<string> logCombate;
    // Eventos
    bool motim = false;
    bool sereias = false;
    bool calmaria = false;
    bool tempestade = false;
    int dias;
    int navioMotim = 0;
    // Controlo
    bool ligado = true;
    // Funcoes
    void setConfiguracoes(vector<string> ficheiro);
    Terreno* criaTerreno(char let, int x, int y);
    Navio* verificaTipoNavio(string tipo, int x, int y);
    Terreno* getCelulaTipo(int id, Posicao atual);
    Terreno* achaPortoPrincipal()const;
    Posicao achaNovaPosicao(int id, Posicao pos);
    bool verificaSeNavioEPirata(int id);
    float distanciaEntreDoisNavios(Posicao a, Posicao b);
    void movimentaNavios();
    void geraPiratas();
    bool possuiNaviosNosPortos();
    void transportaDeUmNavioParaOutro(Navio * navio, Navio * outro);
    void conquistaNavio(Navio* n, Navio * conquista);
    void perdiNavio(Navio * n);
    void geraEvento();
    void geraTempestade();
    void geraSereias();
    void geraCalmaria();
    void geraMotim();
    void diaSeguinte();
    void eliminaMortos();
public:
    Mundo(vector<string> ficheiro);
    Mundo(const Mundo& a);
    Mundo& operator=(const Mundo& a);
    string getAsString()const;
    Jogador* getJogador();
    vector<vector<Terreno*>> getMapa()const;
    int getLinhas()const;
    int getColunas()const;
    string getMapaCarac()const;
    void compraNavio(string tipo);
    Terreno* getCelulaLivreAleatoria(Posicao atual, Navio * n);
    vector<Navio*> getNavios()const;
    bool verificaSeExisteNaviosPiratasNoMar(Terreno * a);
    bool verificaSeExisteNaviosNoMar(Terreno * a);
    bool navioPertence(int id);
    void criaNavioPirata(int x, int y, string tipo);
    void mudaComportamentoAutomatico(int id, bool comp);
    void compraSoldados(int id, int quant);
    bool isNavioNoPortoAmigo(Navio * n);
    Navio* encontraNavio(int id);
    Terreno* getTerreno(Posicao pos);
    void moverNaviosComando(int id, string direcao);
    void vendeNavio(int id);
    Navio* getNavioEspecificoMaisPerto(char tipo, Posicao atual, int id);
    Posicao achaPosicaoMaisPertoDoAlvoDentroDoRaio(Navio * n, Posicao alvo);
    void navioVaiPara(int id, Posicao dest);
    Terreno* encontraPorto(char tipo);
    void verificaAdjacencia(Navio* n, char alvo);
    bool verificaSeEstaEmTempestade(Posicao a);
    void navioAfundou(Navio * n);
    void comandoCompra(int id, int mercadoria);
    void comandoVende(int id);
    Terreno* getPortoMaisPerto(Posicao nav, int id);
    Terreno* getCelulaLivreAleatoriaComPeixe(Posicao atual, Navio * n);
    Navio* getNavioInimigoMaisPerto(Posicao atual, int id);
    void comecaCombate(Navio* iniciante, Navio* alvo);
    void conquistaEBatalhas(Navio* nav);
    void batalhaImplacavel(Navio* n);
    Navio* getNavioAmigoMaisPerto(Posicao atual, int id);
    void novoTurno();
    void verificaMotim();
    void verificaCalmaria();
    bool getTempestade();
    bool getCalmaria();
    bool getMotim();
    bool getSereias();
    vector<string> getLogCombate()const;
    void batalhaEntreNavioEPorto(Terreno * porto, Navio * nav);
    void finalizouJogo();
    bool getEstadoServidor()const;
    ~Mundo();
};
#endif /* MUNDO_H */
