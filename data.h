#ifndef DATA_H
#define DATA_H
#include <string>
using namespace std;

class Data{
    private:
        int dia;
        int mes;
        int ano;
    public:
        //construtor
        Data(int d = 1,int m = 1, int a = 1): dia(d),mes(m),ano(a){}
        //metodo pra pode calcular a data e verifica-la se tem igual
        int toInt()const{
            return ano * 10000 + mes * 100 + dia;//ex: 10/06/2025 viraria 20250610
        }
        //metodo pra formatar a data para DD/MM/AAAA
        string toString()const{
            //nao vou usar const porque alem de eu precisa retornar a data, nao daria muito certo com o qtcreate
            //logo vou fazze os numeros vira texto ,usanto to_string, que funciona para trasformar um numero em string
            string d = to_string(dia);
            string m = to_string(mes);
            string a = to_string(ano);
            //agora um if, pra verificar se o mes ou dia e menor que 10, se for, ele adiciona um 0 antes
            //ex: for mes 5, vira 05
            if(dia < 10) d = "0" + d;
            if(mes < 10) m = "0" + m;

            return d + "/" + m + "/" + a; 
        }

        //metodo adicionarDias
/*a ideia aqui do metodo, e quando chega num dia 31, ele nao pode ir pro dia 32*/
        Data adicionarDias(int dias)const{
            //abaixo temos um "mapa" dos dias dos meses, aonde cada mes, por ex: mes 1 tem 31 dias, e assim vai
            int diaMes[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            //como nao quero apagar a data do chekin, vou cria variaveis para verificar se passo do mes ou nao
            int novoDia = dia;
            int novoMes = mes;
            int novoAno = ano;
            //um for, e dentro dele, um if, pra verificar se o novo dia vai ser maior que dianovo(novoMes), se passa, ele da um dianovo++
            for (int i = 0; i < dias; i++){
                novoDia++;
                //se passa do ultimo dia do mes atual, ele vira o mes
                if(novoDia > diaMes[novoMes]){
                    novoDia = 1;
                    novoMes++;
                    //se passou de dezembro, mes 12, , vira o ano
                    if (novoMes > 12){
                        novoMes = 1;
                        novoAno++;
                    }
                    
                }
                
            }
            return Data(novoDia,novoMes,novoAno);
        }       
                  
};

#endif 