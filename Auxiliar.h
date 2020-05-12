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
 * Created on 28 de Novembro de 2018, 12:47
 */

#ifndef AUXILIAR_H
#define AUXILIAR_H
#include <vector>
#include <string>
using namespace std;
class Posicao;

class Auxiliar {
public:
    Auxiliar();
    static int geraNumerosInteirosAleatorios(int a, int b);
    static vector<int> getVetorInteirosAleatoriosNaoRepetidos(int num, int limiteInf, int limiteSup);
    static float calculaDistanciaEntreDoisPontos(Posicao a, Posicao b);
    static int moduloDeUmInteiro(int a);
    static bool isAdjacente(Posicao a, Posicao b);
    static bool ifFileExists(string fileName);
};
#endif /* AUXILIAR_H */
