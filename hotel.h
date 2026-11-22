#ifndef HOTEL_H
#define HOTEL_H

#include <string>
#include <vector>
#include "quarto.h"

using namespace std;

//MUDANCA: o Hotel guarda so a unidade e os quartos.
//As reservas NAO ficam aqui: ficam todas no gerenciador central (Singleton),
//senao cada unidade teria a sua propria base de reservas.
class Hotel{
    private:
        string localidade;
        vector<Quarto> quartos;

    public:
        //construtor: todas as unidades tem a mesma estrutura de quartos (1 de cada tipo)
        Hotel(string loc = ""): localidade(loc){
            quartos.push_back(Quarto("Solteiro",  200.0, "Ideal para viajantes individuais"));
            quartos.push_back(Quarto("Duplo",     300.0, "Duas camas separadas, para amigos ou colegas"));
            quartos.push_back(Quarto("Casal",     350.0, "Uma cama de casal, ideal para casais ou familias pequenas"));
            quartos.push_back(Quarto("Triplo",    450.0, "Tres camas (uma de casal e uma de solteiro, ou tres de solteiro)"));
            quartos.push_back(Quarto("Quadruplo", 550.0, "Quatro camas (duas de casal ou quatro de solteiro)"));
        }

        string getLocalidade() const { return localidade; }
        vector<Quarto> getQuartos() const { return quartos; }

        //procura o quarto pelo tipo. Retorna false se o tipo nao existir
        bool buscarQuarto(string tipo, Quarto& encontrado) const{
            for(const Quarto& q : quartos){
                if(q.getTipo() == tipo){
                    encontrado = q;
                    return true;
                }
            }
            return false;
        }
};

#endif
