#include <iostream>
#include <string>
#define _MAX 1000

class Data {
private:
    int dia;
    int mes;
    int ano;
public:
    bool setDia(int dia);
    bool setMes(int mes);
    bool setAno(int ano);
    int getDia();
    int getMes();
    int getAno();
    void setData(int dia, int mes, int ano);
    bool dataValida();
    void leData();
    void escreveData();
};

bool Data::setDia(int dia) {
    bool sucesso = false;
    if (dia >= 1 && dia <= 31) {
        this->dia = dia;
        sucesso = true;
    }
    return sucesso;
} // fim de setDia

bool Data::setMes(int mes) {
    bool sucesso = false;
    if (mes >= 1 && mes <= 12) {
        this->mes = mes;
        sucesso = true;
    }
    return sucesso;
} // fim de setMes

bool Data::setAno(int ano) {
    bool sucesso = false;
    if (ano >= 1 && ano <= 2100) {
        this->ano = ano;
        sucesso = true;
    }
    return sucesso;
} // fim de setAno

int Data::getDia() {
    return this->dia;
} // fim de getDia

int Data::getMes() {
    return this->mes;
} // fim de getMes

int Data::getAno() {
    return this->ano;
} // fim de getAno

void Data::setData(int dia, int mes, int ano) {
    setDia(dia);
    setMes(mes);
    setAno(ano);
} // fim de setData

bool Data::dataValida() {
    bool valida = true;

    if (this->ano < 0) {
        valida = false;
    }
    else if (this->mes < 1 || this->mes > 12) {
        valida = false;
    }
    else {
        bool bissexto = (this->ano % 4 == 0 && this->ano % 100 != 0) || (this->ano % 400 == 0);

        if (this->mes == 2) {
            // Fevereiro
            if (bissexto) {
                if (this->dia < 1 || this->dia > 29) {
                    valida = false;
                }
            } else {
                if (this->dia < 1 || this->dia > 28) {
                    valida = false;
                }
            }
        } else if (this->mes == 4 || this->mes == 6 || this->mes == 9 || this->mes == 11) {
            // Abril, Junho, Setembro, Novembro têm 30 dias
            if (this->dia < 1 || this->dia > 30) {
                valida = false;
            }
        } else {
            // Janeiro, Março, Maio, Julho, Agosto, Outubro, Dezembro têm 31 dias
            if (this->dia < 1 || this->dia > 31) {
                valida = false;
            }
        }
    }

    return valida;
} // fim de dataValida

void Data::leData() {
    int dia, mes, ano;
    printf("dd/mm/aaaa: ");
  int result = scanf("%i/%i/%i", &dia, &mes, &ano);
  if (result != 3) {
      printf("Error: Invalid input format.\n");
      // Handle the error (e.g., ask for input again)
  }
    setData(dia, mes, ano);
} // fim de leData

void Data::escreveData() {
    printf("%02i/%02i/%04i", getDia(), getMes(), getAno());
} // fim de escreveData

class Pessoa {
private:
    std::string nome;
    Data dataNascimento;
    static int quantidade;
public:
    void setNome(std::string);
    std::string getNome();
    bool setNascimento(int dia, int mes, int ano);
    Data getNascimento();
    void leNome();
    void escreveNome();
    void lePessoa();
    void escrevePessoa();
};

int Pessoa::quantidade = 0;

void Pessoa::setNome(std::string nome) {
    this->nome = nome;
} // fim de setNome

std::string Pessoa::getNome() {
    return this->nome;
} // fim de getNome

bool Pessoa::setNascimento(int dia, int mes, int ano) {
    bool sucesso = false;
    this->dataNascimento.setData(dia, mes, ano);
    sucesso = true;
    return sucesso;
} // fim de setNascimento

Data Pessoa::getNascimento() {
    return this->dataNascimento;
} // fim de getNascimento

void Pessoa::leNome() {
    std::string nome;
    std::cout << "\nNome: ";
    std::cin.ignore();
    std::getline(std::cin, nome);
    setNome(nome);
} // fim de leNome

void Pessoa::escreveNome() {
    std::cout << "\nNome: " << getNome();
} // fim de escreveNome

void Pessoa::lePessoa() {
    leNome();
    std::cout << "\nData de nascimento: ";
    this->dataNascimento.leData();
} // fim de lePessoa

void Pessoa::escrevePessoa() {
    std::cout << "\nNome: " << getNome();
    std::cout << "\nData de Nascimento: ";
    dataNascimento.escreveData();
} // fim de escrevePessoa

// Função para cadastrar uma nova pessoa
void cadastrarPessoa(Pessoa* pessoas[], int& quantidade) {
    if (quantidade >= _MAX) {
        std::cout << "Cadastro não realizado. Número máximo de pessoas atingido.\n";
        return;
    }
    pessoas[quantidade] = new Pessoa();
    pessoas[quantidade]->lePessoa();
    quantidade++;
} // fim de cadastrarPessoa

// Função para listar todas as pessoas cadastradas
void listarPessoas(Pessoa* pessoas[], int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        std::cout << "\nPessoa " << (i + 1) << ":";
        pessoas[i]->escrevePessoa();
        std::cout << std::endl;
    }
} // fim de listarPessoas

// Função para listar os aniversariantes do mês
void listarAniversariantesDoMes(Pessoa* pessoas[], int quantidade, int mes) {
    for (int i = 0; i < quantidade; i++) {
        if (pessoas[i]->getNascimento().getMes() == mes) {
            pessoas[i]->escrevePessoa();
            std::cout << std::endl;
        }
    }
} // fim de listarAniversariantesDoMes

// Função para exibir o menu e retornar a opção escolhida pelo usuário
int menu() {
    int opcao;
    do {
        std::cout << "\nMenu de Opções:";
        std::cout << "\n0 - Sair";
        std::cout << "\n1 - Cadastrar uma pessoa";
        std::cout << "\n2 - Listar as pessoas cadastradas";
        std::cout << "\n3 - Listar os aniversariantes do mês";
        std::cout << "\nEscolha uma opção: ";
        std::cin >> opcao;
        if (opcao < 0 || opcao > 3) {
            std::cout << "Opção inválida. Tente novamente.\n";
        }
    } while (opcao < 0 || opcao > 3);
    return opcao;
} // fim de menu

int main() {
    Pessoa* pessoas[_MAX];
    int quantidade = 0;
    int opcao;

    do {
        opcao = menu();
        switch (opcao) {
        case 0:
            std::cout << "Saindo...\n";
            break;
        case 1:
            cadastrarPessoa(pessoas, quantidade);
            break;
        case 2:
            listarPessoas(pessoas, quantidade);
            break;
        case 3: {
            int mes;
            std::cout << "Digite o mês: ";
            std::cin >> mes;
            if (mes >= 1 && mes <= 12) {
                listarAniversariantesDoMes(pessoas, quantidade, mes);
            } else {
                std::cout << "Mês inválido. Tente novamente.\n";
            }
            break;
        }
        default:
            std::cout << "Opção inválida. Tente novamente.\n";
            break;
        }
    } while (opcao != 0);

    // Libera a memória alocada
    for (int i = 0; i < quantidade; i++) {
        delete pessoas[i];
    }

    return 0;
} // fim de main
