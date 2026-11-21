#ifndef RESERVA_H
#define RESERVA_H

#include <string>
#include "pessoa.h"
#include "quarto.h"
#include "data.h"
#include "descontostrategy.h"

using namespace std;

//os 3 estados possiveis de uma reserva
enum StatusReserva { PENDENTE, CONFIRMADA, CANCELADA };

class Reserva{
    private:
        int id;                     //numero da reserva (quem preenche e o gerenciador)
        Cliente hospede;            
        Atendente atendente;        //quem fez a reserva
        string localidade;          //Jericoacoara, Canoa Quebrada ou Cumbuco
        Quarto quarto;
        Data checkIn;
        int diarias;
        DescontoStrategy* desconto;
        StatusReserva status;       

        //um "SemDesconto" que existe o programa todo,
        //usado quando nao passam nenhum desconto (evita ponteiro nulo)
        static DescontoStrategy* semDescontoPadrao(){
            static SemDesconto padrao;
            return &padrao;
        }

    public:
        //construtor
        //OBS: o objeto de desconto NAO e apagado pela Reserva. Crie as estrategias uma vez so
        //(ex: no gerenciador) e nao de delete nelas enquanto o programa roda.
        Reserva(Cliente h, Atendente a, string loc, Quarto q, Data check, int di, DescontoStrategy* desc)
            : id(0), hospede(h), atendente(a), localidade(loc), quarto(q), checkIn(check),
              diarias(di), desconto(desc), status(PENDENTE){
            if(desconto == nullptr) desconto = semDescontoPadrao();//MUDANCA: protecao contra nullptr
        }

        
        //valor sem desconto: diaria x numero de diarias
        double calcularValorBruto() const{
            return quarto.getDiaria() * diarias;
        }

        //valor final com a regra de desconto escolhida
        double calcularValorTotal() const{
            //Polimorfismo (Strategy): o ponteiro 'desconto' chama sozinho a conta
            //da classe certa (VIP, Temporada, SemDesconto, etc.) sem precisarmos de 'if'
            return desconto->calcularValorComDesconto(calcularValorBruto());
        }

        
        double calcularEntrada() const{
            return calcularValorTotal() / 3.0;
        }

        //datas 
        Data getCheckIn() const { return checkIn; }

        //era o antigo getCheckIn() que somava os dias. Agora tem o nome certo:
        //o dia da saida (o hospede sai nesse dia, entao ele fica livre pra outra reserva)
        Data getCheckOut() const { return checkIn.adicionarDias(diarias); }

        //verifica se esta reserva ocupa o mesmo quarto, na mesma unidade, em algum dia do periodo
        //regra: dois periodos se cruzam se inicioA < fimB  E  inicioB < fimA
        bool conflitaCom(string loc, string tipoQuarto, Data inicio, int dias) const{
            if(status == CANCELADA) return false;//reserva cancelada nao ocupa o quarto
            if(localidade != loc || quarto.getTipo() != tipoQuarto) return false;
            Data fim = inicio.adicionarDias(dias);
            return checkIn < fim && inicio < getCheckOut();
        }
        bool conflitaCom(const Reserva& outra) const{
            return outra.status != CANCELADA &&
                   conflitaCom(outra.localidade, outra.quarto.getTipo(), outra.checkIn, outra.diarias);
        }

        //confirma o pagamento. Retorna false se a reserva nao estava pendente
        bool confirmarPagamento(){
            if(status != PENDENTE) return false;
            status = CONFIRMADA;
            return true;
        }
        //cancela a reserva (usado quando outra reserva paga ocupa o mesmo quarto)
        void cancelar(){ status = CANCELADA; }

        StatusReserva getStatus() const { return status; }
        bool estaConfirmada() const { return status == CONFIRMADA; }

        //status em texto, pra mostrar no resumo, na tabela e no arquivo
        string getStatusTexto() const{
            if(status == CONFIRMADA) return "Confirmada";
            if(status == CANCELADA) return "Cancelada";
            return "Pendente de confirmacao";
        }

        // getters e setters
        int getId() const { return id; }
        void setId(int novoId){ id = novoId; }
        int getDiarias() const { return diarias; }
        Quarto getQuarto() const { return quarto; }
        Cliente getHospede() const { return hospede; }
        Atendente getAtendente() const { return atendente; }
        string getLocalidade() const { return localidade; }
        string getNomeDesconto() const { return desconto->getNome(); }
};

#endif
