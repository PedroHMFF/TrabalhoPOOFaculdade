#ifndef PESSOA_H
#define PESSOA_H


#include <iostream>
#include <fstream>
#include <string>


using namespace std;

class Pessoa{
    protected:
        string nome;
        string cpf;
    public:
        //construtor com parametros
        Pessoa(string n,string cfp): nome(n), cpf(cfp){}
        //construtor padrão
        Pessoa() : nome(""),cpf(""){}

        //destrutor
        virtual ~Pessoa(){} // destrutor virtual porque outras classes vao herda-la
        //getters e setters
        void setNome(string nom){
            nome = nom;            
        }
        string getNome(){
            return nome;
        }
        void setCpf(string cfp){
            cpf = cfp;
        }
        string getCpf(){
            return cpf;
        }

        //metodo para receber o nome  e cpf
        void RecebendoNomeECpf(){
            cout << "Digite o nome do cliente: ";
            getline(cin >> ws,nome);// o ws limpa o buffer pra n da problema, e captura nomes compostos com espaços
            cout << "Digite o cpf do cliente: ";
            cin >> cpf;
        }



};

//criando a classe Atendente
class Atendente : public Pessoa{
    protected:
        string login;
        string senha;

    public:
        //construtor
        Atendente(string n,string c, string log, string sen):Pessoa(n,c),login(log),senha(sen){}        
        //construtor padrao
        Atendente(string n = "", string c = "", string log = "", string sen = ""): Pessoa(n, c), login(log), senha(sen) {}
        //fazendo so o get
        string getLogin(){
            return login;
        }
        //metodo de autentificaçao
        bool autentificar(string logImput,string senImput){
            ifstream arquivo("usuarios.txt");//lendo as inf do usuarios.txt
            //agora vamo verificar se tem algo escrito nele ou nao, se nao tiver, escrevemos o login e senha
            if(!arquivo.is_open()){
                cout << "[AVISO!!] Arquivo usuarios.txt não encontrado. Criando arquivo...\n";
                ofstream criarArquivo("usuarios.txt");
                if(criarArquivo.is_open()){
                    criarArquivo << "atendente1 senha1\n";
                    criarArquivo << "atendente2 senha2\n";
                    criarArquivo << "atendente3 senha3\n";
                    criarArquivo << "atendente4 senha4\n";
                    criarArquivo.close();
                }
                arquivo.open("usuarios.txt");//abrindo o arquivo criado de modopra ler
                if(!arquivo.is_open()) return false;//se o sistema falhar em abrir o arquivo, ele retorna false e para
            }
        //embaixo, dentro do while, ele vai ser o arquivo, e salvar nome do usuario no usuariosalvo e mesma coisa com a senha   
        string usuariosalvo,senhasalva;
        while (arquivo >> usuariosalvo >> senhasalva){
            //if pra verificar se a senha e usuario e valido
            if (usuariosalvo == logImput && senhasalva == senImput){
                arquivo.close();//se acha a senha ou login, fecha o arquivo e salva no login e senha
                this->login = logImput;
                this->senha = senImput;
                return true;//retorna true se der tudo certo
            }
            
        }
        arquivo.close();
        return false;//se no fim chega aqui, quer dizer que nao deu certo       
        }   
};
//class cliente
class Cliente: public Pessoa{
    public:
        //construtor
        Cliente(string n = "",string c = ""): Pessoa(n,c){}

};

#endif 