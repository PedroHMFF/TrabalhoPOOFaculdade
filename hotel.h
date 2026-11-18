#ifndef HOTEL_H
#define HOTEL_H

#include "pessoa.h"
#include "quarto.h"
#include "data.h"
#include "descontostrategy.h"
#include "reserva.h"
#include <vector>

using namespace std;

class Hotel{
    private:
        vector<Quarto> quartos;
        vector<Pessoa> hospedes;
        vector<Reserva> reservas;
    


};
#endif