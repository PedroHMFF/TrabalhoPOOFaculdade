#ifndef DATA_H
#define DATA_H

#include <string>
#include <ctime>

using namespace std;

class Data{
    private:
        int dia;
        int mes;
        int ano;

    public:
        //construtor
        Data(int d = 1, int m = 1, int a = 2000): dia(d), mes(m), ano(a){}

        //getters
        int getDia() const { return dia; }
        int getMes() const { return mes; }
        int getAno() const { return ano; }

        //aqui ele verifica se o ano e bissexto (fevereiro com 29 dias)
        //a regra e, divisivel por 4, mas nao por 100, a nao ser que seja por 400
        static bool ehBissexto(int a){
            return (a % 4 == 0 && a % 100 != 0) || (a % 400 == 0);
        }

        //quantos dias tem o mes m no ano a
        static int diasNoMes(int m, int a){
            int diaMes[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            if(m == 2 && ehBissexto(a)) return 29;
            return diaMes[m];
        }

        //verifica se a data existe (ex: 31/02 e invalida)
        bool valida() const{
            if(ano < 1900 || mes < 1 || mes > 12) return false;
            if(dia < 1 || dia > diasNoMes(mes, ano)) return false;
            return true;
        }

        //aqui transforma o texto "DD/MM/AAAA" em uma Data
        //se o formato estiver errado, devolve Data(0,0,0), que da false no valida()
        static Data fromString(const string& texto){
            if(texto.size() != 10 || texto[2] != '/' || texto[5] != '/') return Data(0, 0, 0);
            for(int i = 0; i < 10; i++){
                if(i == 2 || i == 5) continue;
                if(texto[i] < '0' || texto[i] > '9') return Data(0, 0, 0);//so aceita numeros
            }
            //stoi = Transforma um texto em número inteiro
            //ex"10" -> 10
            int d = stoi(texto.substr(0, 2));
            int m = stoi(texto.substr(3, 2));
            int a = stoi(texto.substr(6, 4));
            return Data(d, m, a);
        }

        //devolve a data de hoje (pega do relogio do computador)
        static Data hoje(){
            time_t agora = time(nullptr);
            tm* local = localtime(&agora);
            return Data(local->tm_mday, local->tm_mon + 1, local->tm_year + 1900);
        }

        //regra do enunciado -> so aceita reserva do mes corrente ate os proximos 12 meses
        //aceitamos de hoje ate o ultimo dia do 12 mes a frente (ex: hoje 21/11/2026 -> ate 30/11/2027)
        bool dentroDaJanelaDeReserva() const{
            Data h = hoje();
            Data limite(diasNoMes(h.mes, h.ano + 1), h.mes, h.ano + 1);
            return valida() && toInt() >= h.toInt() && toInt() <= limite.toInt();
        }

        //metodo pra comparar datas
        int toInt() const{
            return ano * 10000 + mes * 100 + dia;//ex: 10/06/2025 viraria 20250610
        }

        //operadores de comparacao (usados pra ordenar e verificar conflito)
        bool operator<(const Data& outra) const { return toInt() < outra.toInt(); }
        bool operator==(const Data& outra) const { return toInt() == outra.toInt(); }

        //metodo pra formatar a data para DD/MM/AAAA
        string toString() const{
            string d = to_string(dia);
            string m = to_string(mes);
            string a = to_string(ano);
            //se o dia ou mes for menor que 10, adiciona um 0 antes (ex: 5 vira 05)
            if(dia < 10) d = "0" + d;
            if(mes < 10) m = "0" + m;
            return d + "/" + m + "/" + a;
        }

        //metodo adicionarDias, quando chega no ultimo dia do mes, vira o mes (e o ano)
        Data adicionarDias(int dias) const{
            //como nao quero alterar a data original, uso variaveis novas
            int novoDia = dia;
            int novoMes = mes;
            int novoAno = ano;
            for(int i = 0; i < dias; i++){
                novoDia++;
                //usa diasNoMes(), que ja considera fevereiro com 29 dias
                if(novoDia > diasNoMes(novoMes, novoAno)){
                    novoDia = 1;
                    novoMes++;
                    //se passou de dezembro, vira o ano
                    if(novoMes > 12){
                        novoMes = 1;
                        novoAno++;
                    }
                }
            }
            return Data(novoDia, novoMes, novoAno);
        }
};

#endif
