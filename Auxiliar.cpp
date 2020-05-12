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

#include "Auxiliar.h"
#include "Posicao.h"
#include <cstdlib>
#include <random>
#include <ctime>
#include <cmath>
#include <fstream>
using namespace std;

Auxiliar::Auxiliar() {

}

/**
 * Função responsável por gerar números inteiros aleatórios entre dois inteiros.
 * @param a Inteiro limite mínimo
 * @param b Inteiro limite máximo
 * @return Inteiro random entre os dois limites
 */
int Auxiliar::geraNumerosInteirosAleatorios(int a, int b) {
    static default_random_engine e(time(0));
    uniform_int_distribution<int> d(a, b);
    return d(e);
}

bool verificaSeExisteNumeroNoArray(vector<int> numeros, int num) {
    for (auto n : numeros) {
        if (n == num) return true;
    }
    return false;
}

vector<int> Auxiliar::getVetorInteirosAleatoriosNaoRepetidos(int num, int limiteInf, int limiteSup) {
    vector<int> numeros;
    int numeroAleatorio;

    for (int i = 0; i < num; i++) {
        numeroAleatorio = geraNumerosInteirosAleatorios(limiteInf, limiteSup);
        if (verificaSeExisteNumeroNoArray(numeros, numeroAleatorio))
            i--;
        else
            numeros.push_back(numeroAleatorio);
    }
    return numeros;
}

/**
 * Função responsável por calcular a distancia entre dois pontos do plano cartesiano.
 * @param a Posicao (X, Y)
 * @param b Posicao (X, Y)
 * @return distância
 */
float Auxiliar::calculaDistanciaEntreDoisPontos(Posicao a, Posicao b) {
    return sqrt(((b.getX() - a.getX())*(b.getX() - a.getX()))+((b.getY() - a.getY())*(b.getY() - a.getY())));
}

int Auxiliar::moduloDeUmInteiro(int a) {
    if (a < 0) return a*-1;
    return a;
}

bool Auxiliar::isAdjacente(Posicao a, Posicao b) {
    if (moduloDeUmInteiro(a.getX() - b.getX()) <= 1 && moduloDeUmInteiro(a.getY() - b.getY()) <= 1)
        return true;
    return false;
}

bool Auxiliar::ifFileExists(string fileName) {
    ifstream infile(fileName);
    return infile.good();
}
