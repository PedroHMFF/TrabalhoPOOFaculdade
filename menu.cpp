#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <iomanip>

using namespace std;

string cidades[3] = {"Jericoacoara", "Canoa Quebrada", "Cumbuco"};
string tipos[5] = {"Solteiro", "Duplo", "Casal", "Triplo", "Quadruplo"};
double precos[5] = {200, 300, 350, 450, 550};

int dataParaDias(string data){
    if (data.size() != 10 || data[2] != '/' || data[5] != '/') return 0;

    int dia = atoi(data.substr(0,2).c_str());
    int mes = atoi(data.substr(3,2).c_str());
    int ano = atoi(data.substr(6,4).c_str());

    int diasMes[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (ano % 4 == 0) diasMes[1] = 29;

    if (ano < 2000 || mes < 1 || mes > 12 || dia < 1 || dia > diasMes[mes-1]) return 0;

    int total = 0;
    for (int a = 2000; a < ano; a++){
        total += 365;
        if (a % 4 == 0) total++;
    }
    for (int m = 0; m < mes-1; m++){
        total += diasMes[m];
    }
    return total + dia;
}

class Atendente{
    private:
        string nome;
        string login;

    public:
        Atendente(string nome =  "",string login = ""):nome(nome),login(login){}
        string getNome(){
            return nome;
        }
        string getLogin(){
            return login;
        }

    bool autenticar(const string& loginImput, const string& senhaImput){
        ifstream arquivo("usuarios.txt");

        if(!arquivo.is_open()){
            cout << "[Aviso] Arquivo usuarios.txt nao encontrado. Criando arquivo...\n";
            ofstream criarArquivo("usuarios.txt");
        if (criarArquivo.is_open()) {
            criarArquivo << "atendente1 senha1\n";
            criarArquivo << "atendente2 senha2\n";
            criarArquivo << "atendente3 senha3\n";
            criarArquivo << "atendente4 senha4\n";
            criarArquivo.close();
            }
        arquivo.open("usuarios.txt");//abrindo o arquivo criado de modopra ler
        if(!arquivo.is_open()) return false;//se o sistema falhar em abrio arquivo, o metodo interrompe e termina
    }

    string usuarioSalvo, senhaSalva;
    while (arquivo >> usuarioSalvo >> senhaSalva){
        if (usuarioSalvo == loginImput && senhaSalva == senhaImput){
            arquivo.close();
            this->login = loginImput;
            this->nome = loginImput;
            return true;
        }
    }
    arquivo.close();
    return false;
}

};


class Desconto{
    public:
        virtual ~Desconto(){}
        virtual double calcular(double valor) = 0;
        virtual string nome() = 0;
};

class SemDesconto : public Desconto{
    public:
        double calcular(double valor){ return 0; }
        string nome(){ return "Sem desconto"; }
};

class DescontoVIP : public Desconto{
    public:
        double calcular(double valor){ return valor * 0.10; }
        string nome(){ return "Cliente VIP (10%)"; }
};

class DescontoBaixaTemporada : public Desconto{
    public:
        double calcular(double valor){ return valor * 0.20; }
        string nome(){ return "Baixa temporada (20%)"; }
};

class DescontoFeriado : public Desconto{
    public:
        double calcular(double valor){ return valor * 0.15; }
        string nome(){ return "Promocao de feriados (15%)"; }
};


struct Reserva{
    int id;
    string atendente;
    string cliente;
    string cpf;
    string cidade;
    int tipo;
    string data;
    int dias;
    int diarias;
    string desconto;
    double total;
    double entrada;
    bool confirmada;
};

void imprimirReserva(ostream& saida, Reserva r){
    saida << "Reserva " << r.id << endl;
    saida << "Atendente: " << r.atendente << endl;
    saida << "Cliente: " << r.cliente << " | CPF: " << r.cpf << endl;
    saida << "Localidade: " << r.cidade << endl;
    saida << "Tipo de quarto: " << tipos[r.tipo] << endl;
    saida << "Data de check-in: " << r.data << endl;
    saida << "Numero de diarias: " << r.diarias << endl;
    saida << "Desconto: " << r.desconto << endl;
    saida << "Valor total: R$ " << r.total << endl;
    saida << "Valor da entrada (1/3): R$ " << r.entrada << endl;
    if (r.confirmada) saida << "Status: Confirmada" << endl;
    else saida << "Status: Pendente de confirmacao" << endl;
    saida << endl;
}


class ControladorReservas{
    private:
        vector<Reserva> lista;
        int proximoId;

        ControladorReservas(){
            proximoId = 1;
        }

    public:
        static ControladorReservas& getInstancia(){
            static ControladorReservas instancia;
            return instancia;
        }

        bool cruza(Reserva a, string cidade, int tipo, int dias, int diarias){
            return a.cidade == cidade && a.tipo == tipo &&
                   dias < a.dias + a.diarias && a.dias < dias + diarias;
        }

        bool disponivel(string cidade, int tipo, int dias, int diarias){
            for (int i = 0; i < lista.size(); i++){
                if (lista[i].confirmada && cruza(lista[i], cidade, tipo, dias, diarias)){
                    return false;
                }
            }
            return true;
        }

        void adicionar(Reserva nova){
            nova.id = proximoId;
            proximoId++;

            if (nova.confirmada){
                int i = 0;
                while (i < lista.size()){
                    if (!lista[i].confirmada && cruza(lista[i], nova.cidade, nova.tipo, nova.dias, nova.diarias)){
                        cout << "\n[AVISO] A reserva " << lista[i].id << " de " << lista[i].cliente
                             << " foi cancelada, pois outra pessoa reservou e pagou o mesmo quarto." << endl;
                        lista.erase(lista.begin() + i);
                    } else {
                        i++;
                    }
                }
            }

            lista.push_back(nova);
            cout << endl;
            imprimirReserva(cout, nova);
        }

        void salvar(){
            for (int i = 0; i < lista.size(); i++){
                for (int j = 0; j < lista.size() - 1; j++){
                    if (lista[j].dias > lista[j+1].dias){
                        Reserva aux = lista[j];
                        lista[j] = lista[j+1];
                        lista[j+1] = aux;
                    }
                }
            }

            ofstream arq("reservas.txt");
            arq << fixed << setprecision(2);
            for (int i = 0; i < lista.size(); i++){
                imprimirReserva(arq, lista[i]);
            }
            arq.close();
            cout << "Arquivo reservas.txt gerado!" << endl;
        }
};


void consultar(){
    int cidade, diarias;
    string data;

    cout << "Localidade (1-Jericoacoara 2-Canoa Quebrada 3-Cumbuco): ";
    cin >> cidade;
    cout << "Data de check-in (DD/MM/AAAA): ";
    cin >> data;
    cout << "Numero de diarias: ";
    cin >> diarias;

    int dias = dataParaDias(data);
    if (cidade < 1 || cidade > 3 || dias == 0 || diarias < 1){
        cout << "Dados invalidos!" << endl;
        return;
    }

    for (int i = 0; i < 5; i++){
        cout << tipos[i] << ": ";
        if (ControladorReservas::getInstancia().disponivel(cidades[cidade-1], i, dias, diarias))
            cout << "Disponivel" << endl;
        else
            cout << "Indisponivel" << endl;
    }
}

void reservar(Atendente& atend){
    Reserva r;
    int cidade, opDesc;
    char pagou;

    cout << "Localidade (1-Jericoacoara 2-Canoa Quebrada 3-Cumbuco): ";
    cin >> cidade;
    cout << "Data de check-in (DD/MM/AAAA): ";
    cin >> r.data;
    cout << "Numero de diarias: ";
    cin >> r.diarias;
    cout << "Tipo de quarto (1-Solteiro 2-Duplo 3-Casal 4-Triplo 5-Quadruplo): ";
    cin >> r.tipo;

    r.dias = dataParaDias(r.data);
    r.tipo--;
    if (cidade < 1 || cidade > 3 || r.dias == 0 || r.diarias < 1 || r.tipo < 0 || r.tipo > 4){
        cout << "Dados invalidos!" << endl;
        return;
    }
    r.cidade = cidades[cidade-1];

    if (!ControladorReservas::getInstancia().disponivel(r.cidade, r.tipo, r.dias, r.diarias)){
        cout << "Quarto indisponivel nesse periodo!" << endl;
        return;
    }

    cin.ignore();
    cout << "Nome completo do cliente: ";
    getline(cin, r.cliente);
    cout << "CPF do cliente: ";
    getline(cin, r.cpf);

    cout << "Desconto (1-Nenhum 2-VIP 3-Baixa temporada 4-Feriado): ";
    cin >> opDesc;

    Desconto* d;
    if (opDesc == 2) d = new DescontoVIP();
    else if (opDesc == 3) d = new DescontoBaixaTemporada();
    else if (opDesc == 4) d = new DescontoFeriado();
    else d = new SemDesconto();

    double bruto = precos[r.tipo] * r.diarias;
    r.total = bruto - d->calcular(bruto);
    r.entrada = r.total / 3;
    r.desconto = d->nome();
    delete d;

    cout << "Valor total: R$ " << r.total << " | Entrada: R$ " << r.entrada << endl;
    cout << "A entrada foi paga? (s/n): ";
    cin >> pagou;
    r.confirmada = (pagou == 's' || pagou == 'S');
    r.atendente = atend.getNome();

    ControladorReservas::getInstancia().adicionar(r);
}


int main (){
    cout << fixed << setprecision(2);
    Atendente atend;
    string loginDigitado,senhaDigitada;
    int opcc;

    cout << "---- TELA DE LOGIN ----\n";
    cout << "Usuario: ";
    cin >> loginDigitado;
    cout << "Senha: ";
    cin >> senhaDigitada;
    if (atend.autenticar(loginDigitado,senhaDigitada)){
        cout << "\nLogin efetuado com sucesso!!\n";
        cout << "Bem vindo(a), " << atend.getLogin() << "!\n";

        do{
            cout << "\nEscolha sua opção!!" << endl;
            cout << "1 - Deseja consultar disponibilidade de quartos(Jericoacoara, Canoa Quebrada ou Cumbuco)" << endl;
            cout << "2 - Realizar uma reserva" << endl;
            cout << "0 - sair do programa" << endl;
            cout << "--->:";
            cin >> opcc;
            switch (opcc){
                case 1:
                    consultar();
                    break;
                case 2:
                    reservar(atend);
                    break;
                case 0:
                    cout << "Saindo do programa..." << endl;
                    ControladorReservas::getInstancia().salvar();
                    break;
                default:
                    cout << "Opção invalida!!tente novamente!!";

                }
        } while (opcc != 0);

    }else{
        cout << "\n[ERRO] Usuario ou senha incorretos \n";
    }

    return 0;
}