#ifndef DESCONTOSTRATEGY_H
#define DESCONTOSTRATEGY_H


#include <string>
using namespace std;
class DescontoStrategy{
    public:
        //destrutor virtual
        virtual ~DescontoStrategy(){}
        
        virtual double calcularValorComDesconto(double valorBruto) const = 0;
        virtual string getNome() const = 0;

        double calcularEntrada(double valorComDesconto) const {
            return valorComDesconto / 3.0;
        }

};

//classe de desconto vip
class DescontoVip: public DescontoStrategy{
    public:
        virtual double calcularValorComDesconto(double valorBruto)const override{
            //conta pro cliente pagar 90%, ja que ele tem 10% de desconto
            return valorBruto * 0.90;
        }
        virtual string getNome() const override{
            return "Cliente vip(10% de desconto)";
        }

};
//class sem desconto nenhum
class SemDesconto : public DescontoStrategy{
    public:
        virtual double calcularValorComDesconto(double valorBruto) const override{
            return valorBruto;
        }
        virtual string getNome()const override{
            return "Cliente sem desconto";
        }

};
//class baixa temporada 20%
class DescontoTemporada : public DescontoStrategy{
    public:
        virtual double calcularValorComDesconto(double valorBruto)const override{
            return valorBruto * 0.80;
        }
        virtual string getNome()const override{
            return "Cliente baixa temporada(20%)";
        }
};
//desconto promocao de feriado 15%
class DescontoPromoFeriado : public DescontoStrategy{
    public:
        virtual double calcularValorComDesconto(double valorBruto)const override{
            return valorBruto * 0.85;
        }
        virtual string getNome()const override{
            return "Cliente com promocao de feriado(15%)";
        }
};

#endif 