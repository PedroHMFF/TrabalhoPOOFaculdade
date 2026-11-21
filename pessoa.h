#ifndef PESSOA_H
#define PESSOA_H

#include <fstream>
#include <string>

using namespace std;

class Pessoa{
    protected:
        string nome;
        string cpf;
    public:
        //construtor padrao
        Pessoa(string n = "", string c = ""): nome(n), cpf(c){}

        //destrutor virtual porque outras classes vao herda-la
        virtual ~Pessoa(){}

        //getters e setters

        void setNome(string nom){ nome = nom; }
        string getNome() const { return nome; }

        void setCpf(string c){ cpf = c; }
        string getCpf() const { return cpf; }


};

//criando a classe Atendente
class Atendente : public Pessoa{
    protected:
        string login;
        //MUDANCA: o atributo senha saiu, nao precisamos guardar a senha depois do login

    public:
        //construtor
        Atendente(string n = "", string c = "", string log = ""): Pessoa(n, c), login(log){}

        string getLogin() const { return login; }


        bool autenticar(string logInput, string senInput){
            ifstream arquivo("usuarios.txt");//lendo as inf do usuarios.txt

            //se o arquivo nao existe, criamos com os atendentes de teste
            if(!arquivo.is_open()){
                ofstream criarArquivo("usuarios.txt");
                if(criarArquivo.is_open()){
                    criarArquivo << "atendente1 senha1\n";
                    criarArquivo << "atendente2 senha2\n";
                    criarArquivo << "atendente3 senha3\n";
                    criarArquivo << "atendente4 senha4\n";
                    criarArquivo.close();
                }
                arquivo.open("usuarios.txt");//abrindo o arquivo criado para ler
                if(!arquivo.is_open()) return false;//se falhar em abrir, retorna false e para
            }

            //le usuario e senha de cada linha e compara com o que foi digitado
            string usuarioSalvo, senhaSalva;
            while(arquivo >> usuarioSalvo >> senhaSalva){
                if(usuarioSalvo == logInput && senhaSalva == senInput){
                    arquivo.close();
                    this->login = logInput;
                    if(nome.empty()) this->nome = logInput;//o arquivo nao tem nome, entao usamos o login
                    return true;
                }
            }
            arquivo.close();
            return false;//se chegou aqui, login ou senha errados
        }
};

//class cliente
class Cliente : public Pessoa{
    public:
        //construtor
        Cliente(string n = "", string c = ""): Pessoa(n, c){}
};

#endif
