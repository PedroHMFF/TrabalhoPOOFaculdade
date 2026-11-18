#ifndef RESERVA_H
#define RESERVA_H
#include <string>
#include "pessoa.h"
#include "quarto.h"
#include "data.h"
#include "descontostrategy.h"
using namespace std;
class Reserva{
    private:
        Pessoa hospede;
        Quarto quarto;
        Data checkIn; 
        int diarias;
        DescontoStrategy * desconto;    
    public:
        //metodos
        //calcular o valor final da estadia com a regra de desconto escolhida
        double calcularValorTotal()const {
            // Multiplica o preco da diaria do quarto pela quantidade de dias
           double valorBruto = quarto.getDiaria() * diarias;
            //Polimorfismo (Strategy): o ponteiro 'desconto' chama sozinho a conta
            // da classe certa (VIP, Temporada, SemDesconto, etc.) sem precisarmos de 'if'
            return desconto->calcularValorComDesconto(valorBruto);
        }
        // Calcula o sinal de 1/3 exigido para confirmar a reserva
        double calcularEntradaTotal()const{
            //Pega o total ja com desconto e usa o metodo da classe base para dividir por 3
            return desconto->calcularEntrada(calcularValorTotal());
        }
        Data getCheckIn() const{
            //pega o dia, faz a soma se tiver no data.h, e devolve uma data 
            return checkIn.adicionarDias(diarias);
        }

        //construtor
        Reserva(Pessoa h,Quarto q,Data check,int di,DescontoStrategy* desc)
        :hospede(h),quarto(q),checkIn(check),diarias(di),desconto(desc){}
        //getters e setters, porque estao private
        int getDiarias()const{//colocamos o const no get, pra garantir que o metodo so vai entregar a leitura sem alterar nada
            return diarias;
        }
        Quarto getQuarto()const{
            return quarto;
        }
        Pessoa getHospede()const{
            return hospede;
        }
        Data getCheckin()const{
            return checkIn;
        }
};

#endif