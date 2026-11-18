#ifndef QUARTO_H
#define QUARTO_H
#include <string>
using namespace std;

class Quarto{
    private:
        string tipo;        // Solteiro, Duplo, Casal, Triplo, Quadruplo
        double valorDiaria;
        string descricao;
    public:
        Quarto(string ti = "", double diaria = 0.0, string desc = "")
            : tipo(ti), valorDiaria(diaria), descricao(desc) {}

        string getTipo() const { return tipo; }
        double getDiaria() const { return valorDiaria; }
        string getDescricao() const { return descricao; }
};


#endif