#include "includes/astronaut.h"

string generToString(Gener gener) {
    switch (gener) {
        case MALE: return "Masculino";
        case FEMALE: return "Feminino";
        default: return "Outro";
    };
};

Astronaut::Astronaut() {};
Astronaut::Astronaut(string name, string cpf, Gener gener, int age) {
    this->name = name;
    this->cpf = cpf;
    this->gener = gener;
    this->age = age;
};

long long unsigned int Astronaut::getMaxNameWidth(List<Astronaut>* database) {
    long long unsigned int maxNameWidth = 4;

    if(database != NULL) {
        for(unsigned int i = 0; i < database->getAmount(); i++) {
            long long unsigned int nameWidth = database->get(i)->getName().length();
            if(nameWidth > maxNameWidth) maxNameWidth = nameWidth;
        };
    };

    return maxNameWidth;
};

bool Astronaut::compare(Astronaut* a, Astronaut* b) {
    if(a->alive != b->alive) return a->alive > b->alive;
    if(a->available != b->available) return a->available > b->available;
    
    bool name = false;

    string na = a->getName();
    string nb = b->getName();

    unsigned int size = min(na.length(), nb.length());
    for(unsigned int i = 0; i < size; i++) {
        if(na[i] < nb[i]) {
            name = true;
            break;
        } else if(na[i] > nb[i]) {
            name = false;
            break;
        } else if(i == size - 1) {
            name = na.length() > nb.length();
            break;
        };
    };

    return name;
};

Astronaut* Astronaut::form(List<Astronaut>* database) {
    string name;
    string cpf;
    Gener gener;
    int age;

    do {
        clearTerminal();
        cout << "CRIANDO NOVO ASTRONAUTA" << endl << endl;
        cout << "Qual o nome do astronauta? ";
        name = capitalize(trim(getLine()));
    } while(name == "");
    
    while(true) {
        clearTerminal();
        cout << "CRIANDO NOVO ASTRONAUTA" << endl << endl;
        cout << "Qual o nome do astronauta? " << name << endl;
        cout << "Qual o cpf do astronauta? ";

        cpf = toCpf(trim(getLine()));

        bool validCpf = isCpf(cpf);

        if(validCpf) {
            if(database->exists([&cpf](Astronaut* astronaut){
                return astronaut->cpf == cpf;
            })) {
                while(true) {
                    clearTerminal();
                    cout << "Existe um astronauta cadastrado com esse CPF!" << endl;
                    char key = input("Pressione ENTER para tentar novamente\nOu BACKSPACE para cancelar...");
                    if(ENTER == key) break;
                    else if('\b' == key) return NULL;
                };
                
                cpf = "";
            } else break;
        };
    };

    char generChar;
    do {
        clearTerminal();
        cout << "CADASTRANDO NOVO ASTRONAUTA" << endl << endl;
        cout << "Qual o nome do astronauta? " << name << endl;
        cout << "Qual o cpf do astronauta? " << cpf << endl;
        cout << "Com qual genero o astronauta se identifica? " << endl << endl;
        
        cout << "[M] Masculino" << endl;
        cout << "[F] Feminino" << endl;
        cout << "[O] Outro" << endl << endl;

        cout << "Resposta: ";

        generChar = tolower(getChar());
    } while(generChar != 'm' && generChar != 'f' && generChar != 'o');

    switch (generChar) {
        case 'm':
            gener = MALE;
            break;
        case 'f':
            gener = FEMALE;
            break;
        default:
            gener = OTHER;
            break;
    };

    string generRef = generToString(gener);
    do {
        clearTerminal();
        cout << "CADASTRANDO NOVO ASTRONAUTA" << endl << endl;
        cout << "Qual o nome do astronauta? " << name << endl;
        cout << "Qual o cpf do astronauta? " << cpf << endl;
        cout << "Com qual genero o astronauta se identifica? " << generRef << endl;
        cout << "Qual a idade do astronauta? ";

        age = stoi(getLine());
        if(age > 200) {
            while(true) {
                clearTerminal();
                cout << "A idade limite aceitavel e 200!" << endl;
                char key = input("Pressione ENTER para tentar novamente\nOu BACKSPACE para cancelar...");
                if(ENTER == key) break;
                else if('\b' == key) return NULL;
            };
        } else if(age < 18) {
            while(true) {
                clearTerminal();
                cout << "O astronauta precisa ser maior de idade!" << endl;
                char key = input("Pressione ENTER para tentar novamente\nOu BACKSPACE para cancelar...");
                if(ENTER == key) break;
                else if('\b' == key) return NULL;
            };
        };
    } while(age == EOF || age > 200 || age < 18);

    char confirm;
    do {
        clearTerminal();
        cout << "CADASTRANDO NOVO ASTRONAUTA" << endl << endl;
        cout << "Qual o nome do astronauta? " << name << endl;
        cout << "Qual o cpf do astronauta? " << cpf << endl;
        cout << "Com qual genero o astronauta se identifica? " << generRef << endl;
        cout << "Qual a idade do astronauta? " << age << endl;
        cout << "Confirmar cadastro [Y/n]? ";
        
        confirm = tolower(getChar());
    } while(confirm != 'y' && confirm != 'n');

    if(confirm == 'n') return NULL;

    Astronaut* createdAstronaut = new Astronaut(name, cpf, gener, age);
    database->add(createdAstronaut);
    database->sort(Astronaut::compare);

    return createdAstronaut;
}

unsigned int Astronaut::countDeaths(List<Astronaut>* database) {
    unsigned int deaths = 0;

    if(database->getAmount() == 0) return 0;

    for(unsigned int i = database->getAmount() - 1; i >= 0; i--) {
        if(database->get(i)->alive) break;
        deaths++;
    };

    return deaths;
};

unsigned int Astronaut::countAlives(List<Astronaut>* database) {
    unsigned int alives = 0;

    for(unsigned int i = 0; i < database->getAmount(); i++) {
        if(!database->get(i)->alive) break;
        alives++;
    };

    return alives;
};

Astronaut* Astronaut::search(
    List<Astronaut>* database, string title, 
    AstronautFilter filter, AstronautSearch search,
    string searchParam, bool catchAstronaut,
    List<Astronaut>* baseDatabase
) {
    long long unsigned int maxNameWidth = Astronaut::getMaxNameWidth(database);
    unsigned int page = 0;
    unsigned int perPage = 8;
    unsigned int alivesGap = (filter == DEAD? Astronaut::countAlives(database):0);
    unsigned int deathsGap = (filter == ALIVE? Astronaut::countDeaths(database):0);
    unsigned int amount =  database->getAmount() - deathsGap - alivesGap;
    unsigned int maxPage = amount / perPage;
    if((amount % perPage == 0) && maxPage > 0) maxPage--;

    unsigned int end = 0;
    unsigned int start = 0;

    do {
        end = min(amount, ((page + 1) * perPage));
        start = (page * perPage);

        clearTerminal();

        if(amount > 0) {
            cout << title << " [" << page + 1 << "/" << maxPage + 1 << "]" << endl << endl;

            if(search == NAME) {
                cout << "Buscando por NOME: " + searchParam << endl << endl;
            } else if(search == CPF) {
                cout << "Buscando por CPF: " + searchParam << endl << endl;
            };

            cout << "[#]  " << setw(maxNameWidth + 2) << left << "NOME" << setw(16) << "CPF" << setw(7) << "IDADE" << setw(6) << "VOOS" << setw(15) << "STATUS" << endl;
            for(unsigned int i = start; i < end; i++) {
                cout << "[" << i - (page * perPage) << "]  ";
                database->get(i + alivesGap)->print(maxNameWidth);
            };

            cout << endl;

            bool nextPage = page < maxPage;
            bool previousPage = page > 0;

            if(nextPage) cout << "[->] Proxima pagina" << endl;
            if(previousPage) cout << "[<-] Pagina anterior" << endl;

            if(nextPage || previousPage) cout << endl;
        } else {
            if(search == NAME) {
                cout << "NENHUM ASTRONAUTA ENCONTRADO COM\nNOME: " + searchParam << endl << endl;
            } else if(search == CPF) {
                cout << "NENHUM ASTRONAUTA ENCONTRADO COM\nCPF: " + searchParam << endl << endl;
            } else {
                cout << "NENHUM ASTRONAUTA ENCONTRADO" << endl << endl;
            };
        };

        if(search == NONE) {
            cout << "[n] Buscar astronauta por NOME" << endl;
            cout << "[c] Buscar astronauta por CPF" << endl;
            cout << "[BACKSPACE] Voltar para o menu" << endl << endl;
        } else {
            cout << "[ENTER] Limpar parametro de busca" << endl;;
            cout << "[BACKSPACE] Voltar para o menu" << endl << endl;
        };

        char key = input("");

        if(key == BACKSPACE) return NULL;
        else if(key >= '0' && key < '0' + int(end - start) && catchAstronaut) {
            unsigned int index = (key - '0') + (page * perPage) + alivesGap;
            return database->get(index);
        } else if(key == SPECIAL_KEY) {
            #ifdef _WIN32
                int specialKey = getch();
            #else
                int specialKey = input("");
            #endif
            if(specialKey == LEFT && page > 0) page--;
            else if(specialKey == RIGHT && page < maxPage) page++;
        } else if(key == 'n' && search == NONE) {
            string nameToSearch = "";

            do {
                clearTerminal();
                cout << title << endl << endl;
                cout << "Qual o NOME do astronauta que voce este procurando? ";

                nameToSearch = trim(getLine());
            } while(nameToSearch == "");

            string lowerNameToSearch = lower(nameToSearch);
            List<Astronaut> filteredAstronaut = database->filter([&lowerNameToSearch](Astronaut* astronaut){
                return lower(astronaut->getName()).find(lowerNameToSearch) != string::npos;
            });

            return Astronaut::search(&filteredAstronaut, title, filter, NAME, nameToSearch, catchAstronaut, baseDatabase);
        } else if(key == 'c' && search == NONE) {
            string cpfToSearch = "";

            do {
                clearTerminal();
                cout << title << endl << endl;
                cout << "Qual o CPF do astronauta que voce este procurando? ";

                cpfToSearch = toCpf(getLine());
            } while(cpfToSearch == "");

            List<Astronaut> filteredAstronaut = database->filter([&cpfToSearch](Astronaut* astronaut){
                return astronaut->getCpf().find(cpfToSearch) != string::npos;
            });

            return Astronaut::search(&filteredAstronaut, title, filter, CPF, cpfToSearch, catchAstronaut, baseDatabase);
        } else if(key == ENTER && search != NONE && baseDatabase != NULL) {
            return Astronaut::search(baseDatabase, title, filter, NONE, "", catchAstronaut, baseDatabase);
        };
    } while(true);

    return NULL;
};

Astronaut* Astronaut::list(
    List<Astronaut>* database, string title, 
    AstronautFilter filter,
    bool catchAstronaut
) {
    return Astronaut::search(database, title, filter, NONE, "", catchAstronaut, database);
};

string Astronaut::getName() {
    return this->name;
};

string Astronaut::getCpf() {
    return this->cpf;
};

void Astronaut::kill() {
    this->alive = false;
};

void Astronaut::print(long long unsigned int maxNameWidth) {
    string availability = "[";
    availability.append(
        this->alive? 
            (this->available? "Disponivel]":"Indisponivel]"):
            (this->gener == MALE? "Morto]": (
                this->gener == FEMALE? "Morta]":
                "Mortx]"
            ))
    );

    cout << setw(maxNameWidth + 2) << left << name << setw(16) << cpf << setw(7) << age << setw(6) << expeditions << setw(15) << availability << endl;
}; 