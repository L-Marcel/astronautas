#include "includes/entities.h"
#include <format>

Astronaut::Astronaut() {};
Astronaut::Astronaut(string name, string cpf) {
    this->name = name;
    this->cpf = cpf;
};

string Astronaut::getName() {
    return this->name;
};

void Astronaut::kill() {
    this->alive = false;
};

void Astronaut::print(long long unsigned int maxNameWidth, bool full) {
    string availability = "[";
    availability.append(
        this->available? "Disponivel]":
            (this->alive? "Indisponível]":"Morto]")
    );

    if(!full) cout << setw(maxNameWidth + 2) << left << name << setw(15) << availability << endl;
    else cout << setw(maxNameWidth + 2) << left << name << setw(16) << cpf << setw(15) << availability << endl;
};

long long unsigned int Astronaut::getMaxNameWidth(List<Astronaut>* database) {
    long long unsigned int maxNameWidth = 0;

    if(database != NULL) {
        for(unsigned int i = 0; i < database->getAmount(); i++) {
            long long unsigned int nameWidth = database->get(i)->getName().length();
            if(nameWidth > maxNameWidth) maxNameWidth = nameWidth;
        };
    };

    return maxNameWidth;
};

Astronaut* Astronaut::form(List<Astronaut>* database) {
    string name;
    string cpf;

    do {
        clear();
        cout << "CRIANDO NOVO ASTRONAUTA" << endl << endl;
        cout << "Qual o nome do astronauta? ";
        getline(cin, name);
        name = capitalize(trim(name));
    } while(name == "");
    
    while(true) {
        clear();
        cout << "CRIANDO NOVO ASTRONAUTA" << endl << endl;
        cout << "Qual o nome do astronauta? " << name << endl;
        cout << "Qual o cpf do astronauta? ";

        getline(cin, cpf);
        cpf = trim(cpf);

        bool unformattedCpf = cpf.length() == 11 && !isCpf(cpf);
        bool formattedCpf = isCpf(cpf);

        if(unformattedCpf || formattedCpf) {
            if(unformattedCpf) {
                cpf = toCpf(cpf);
            };

            if(database->exists([&cpf](Astronaut* astronaut){
                return astronaut->cpf == cpf;
            })) {
                while(true) {
                    clear();
                    cout << "Existe um astronauta cadastrado com esse CPF!" << endl;
                    char key = input("Pressione ENTER para tentar novamente\nOu BACKSPACE para cancelar...");
                    if(ENTER == key) break;
                    else if('\b' == key) return NULL;
                };
                
                cpf = "";
            } else if(isCpf(cpf)) {
                break;
            } else {
                while(true) {
                    clear();
                    cout << "Informe um CPF valido!" << endl;
                    char key = input("Pressione ENTER para tentar novamente\nOu BACKSPACE para cancelar...");
                    if(ENTER == key) break;
                    else if('\b' == key) return NULL;
                };

                cpf = "";
            };
        };
    };

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

    Astronaut* createdAstronaut = new Astronaut(name, cpf);
    database->add(createdAstronaut);

    return createdAstronaut;
}

void Astronaut::list(List<Astronaut>* database) {
    long long unsigned int maxNameWidth = Astronaut::getMaxNameWidth(database);
    unsigned int page = 0;
    unsigned int perPage = 8
;
    unsigned int maxPage = database->getAmount() / perPage;
    if(database->getAmount() % perPage == 0 && maxPage > 0) maxPage--;

    do {
        clear();
        cout << "LISTA DE ASTRONAUTAS DA EMPRESA [" << page + 1 << "/" << maxPage + 1 << "]" << endl << endl;
        
        unsigned int end = min(database->getAmount(), (page + 1) * perPage);
        unsigned int start = page * perPage;

        for(unsigned int i = start; i < end; i++) {
            cout << "[" << i - (page * perPage) << "] ";
            database->get(i)->print(maxNameWidth); 
        };

        cout << endl;
        if(page < maxPage) cout << "[->] Proxima pagina" << endl;
        if(page > 0) cout << "[<-] Pagina anterior" << endl;
        cout << "[BACKSPACE] Voltar para o menu principal" << endl << endl;

        char key = input("");

        if(key == BACKSPACE) break;
        else if(key >= '0' && key < '0' + int(end - start)) {
            while(true) {
                clear();
                database->get((key - '0') + (page * perPage))->print(maxNameWidth, true);
                char option = input("Pressione ENTER para voltar...");
                if(option == ENTER) break;
            };
        } else if(key == SPECIAL_KEY) {
            int specialKey = getch();
            if(specialKey == LEFT && page > 0) page--;
            else if(specialKey == RIGHT && page < maxPage) page++;
        };
    } while(true);
};

Expedition::Expedition() {};