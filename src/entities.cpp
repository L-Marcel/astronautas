#include "includes/entities.h"

Astronaut::Astronaut() {};
Astronaut::Astronaut(string name, string cpf) {
    this->name = name;
    this->cpf = cpf;
};

string Astronaut::getName() {
    return this->name;
};

Astronaut* Astronaut::form() {
    string name;
    string cpf;

    do {
        clear();
        cout << "CRIANDO NOVO ASTRONAUTA" << endl << endl;
        cout << "Qual o nome do astronauta? ";
        getline(cin, name);
        name = trim(name);
    } while(name == "");
    
    do {
        clear();
        cout << "CRIANDO NOVO ASTRONAUTA" << endl << endl;
        cout << "Qual o nome do astronauta? " << name << endl;
        cout << "Qual o cpf do astronauta? ";

        getline(cin, cpf);
        cpf = trim(cpf);
    } while(cpf == "" || cpf.length() != 11);

    char confirm;
    do {
        clear();
        cout << "CADASTRANDO NOVO ASTRONAUTA" << endl << endl;
        cout << "Qual o nome do astronauta? " << name << endl;
        cout << "Qual o cpf do astronauta? " << cpf << endl << endl;
        cout << "Confirmar cadastro [Y/n]? ";
        confirm = tolower(getchar());
    } while(confirm != 'y' && confirm != 'n');

    if(confirm == 'n') return NULL;

    return new Astronaut(name, cpf);
}

Expedition::Expedition() {};