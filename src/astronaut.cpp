#include "includes/expedition.hpp"

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
Astronaut::~Astronaut() {};

long long unsigned int Astronaut::getMaxNameWidth(List<Astronaut>* database) {
    long long unsigned int maxNameWidth = 4;

    if(database != nullptr) {
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
                    char key = askToContinue();
                    if(ENTER == key) break;
                    else if(BACKSPACE == key) return nullptr;
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

        try {
            age = getNumber();
        } catch(string err) {
            cout << err << endl;
            char key = askToContinue();
            if(ENTER == key) continue;
            else if(BACKSPACE == key) return nullptr;
        };

        if(age > 200) {
            while(true) {
                clearTerminal();
                cout << "A idade limite aceitavel e 200!" << endl;
                char key = askToContinue();
                if(ENTER == key) break;
                else if(BACKSPACE == key) return nullptr;
            };
        } else if(age < 18) {
            while(true) {
                clearTerminal();
                cout << "O astronauta precisa ser maior de idade!" << endl;
                char key = askToContinue();
                if(ENTER == key) break;
                else if(BACKSPACE == key) return nullptr;
            };
        };
    } while(age > 200 || age < 18);

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

    if(confirm == 'n') return nullptr;

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
        
        if(i == 0) break;
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
            } else if(search == AGE) {
                cout << "Bsucando por IDADE: " + searchParam << endl << endl;
            };

            if(catchAstronaut) cout << "[#]  ";
            else cout << "> ";

            cout << setw(maxNameWidth + 2) << left << "NOME" 
            << setw(16) << "CPF" 
            << setw(7) << "IDADE" 
            << setw(6) << "VOOS" 
            << setw(15) << "STATUS" << endl;
            for(unsigned int i = start; i < end; i++) {
                if(catchAstronaut) cout << "[" << i - (page * perPage) << "]  ";
                else cout << "∘ ";
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
            } else if(search == AGE) {
                cout << "NENHUM ASTRONAUTA ENCONTRADO COM\nIDADE: " + searchParam << endl << endl;
            } else {
                cout << "NENHUM ASTRONAUTA ENCONTRADO" << endl << endl;
            };
        };

        if(search == NONE) {
            cout << "[n] Buscar astronauta por NOME" << endl;
            cout << "[c] Buscar astronauta por CPF" << endl;
            cout << "[i] Buscar astronauta por IDADE" << endl;
            cout << "[BACKSPACE] Voltar para o menu" << endl << endl;
        } else {
            cout << "[ENTER] Limpar parametro de busca" << endl;;
            cout << "[BACKSPACE] Voltar para o menu" << endl << endl;
        };

        char key = input();

        if(key == BACKSPACE) {
            if(search != NONE) List<Astronaut>::destroy(database);
            return nullptr;
        } else if(key >= '0' && key < '0' + int(end - start) && catchAstronaut) {
            unsigned int index = (key - '0') + (page * perPage) + alivesGap;
            Astronaut* selected = database->get(index);
            if(search != NONE) List<Astronaut>::destroy(database);
            return selected;
        } else if(key == SPECIAL_KEY) {
            #ifdef _WIN32
                int specialKey = getch();
            #else
                int specialKey = input();
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
            List<Astronaut>* filteredAstronaut = database->filter([&lowerNameToSearch](Astronaut* astronaut){
                return lower(astronaut->getName()).find(lowerNameToSearch) != string::npos;
            });

            return Astronaut::search(filteredAstronaut, title, filter, NAME, nameToSearch, catchAstronaut, baseDatabase);
        } else if(key == 'c' && search == NONE) {
            string cpfToSearch = "";

            do {
                clearTerminal();
                cout << title << endl << endl;
                cout << "Qual o CPF do astronauta que voce este procurando? ";

                cpfToSearch = toCpf(getLine());
            } while(cpfToSearch == "");

            List<Astronaut>* filteredAstronaut = database->filter([&cpfToSearch](Astronaut* astronaut){
                return astronaut->getCpf().find(cpfToSearch) != string::npos;
            });

            return Astronaut::search(filteredAstronaut, title, filter, CPF, cpfToSearch, catchAstronaut, baseDatabase);
        } else if(key == 'i' && search == NONE) {
            char method;
            do {
                clearTerminal();
                cout << "Qual o metodo de busca?" << endl << endl;
                cout << "[0] Astronautas com idade maior que..." << endl;
                cout << "[1] Astronautas com idade menor que..." << endl;
                cout << "[2] Astronautas com idade igual a..." << endl;
                cout << "[3] Astronautas com idade diferente de.." << endl;
                cout << "[4] Astronautas com idade maior ou igual a..." << endl;
                cout << "[5] Astronautas com idade menor ou igual a..." << endl << endl;
                method = input();
            } while(method < '0' || method > '5');

            int ageToSearch;
            string ageText;
            while(true) {
                clearTerminal();

                try {
                    switch(method) {
                        case '0': 
                            cout << "Buscar astronautas com idade maior que? ";
                            ageToSearch = getNumber();
                            ageText = "maior que " + ageToSearch;
                            break;
                        case '1':
                            cout << "Buscar astronautas com idade menor que? ";
                            ageToSearch = getNumber();
                            ageText = "menor que " + ageToSearch;
                            break;
                        case '2':
                            cout << "Buscar astronautas com idade igual a? ";
                            ageToSearch = getNumber();
                            ageText = "igual a " + ageToSearch;
                            break;
                        case '3':
                            cout << "Buscar astronautas com idade diferente de? ";
                            ageToSearch = getNumber();
                            ageText = "diferente de " + to_string(ageToSearch);
                            break;
                        case '4':
                            cout << "Buscar astronautas maior ou igual a? ";
                            ageToSearch = getNumber();
                            ageText = "maior ou igual a " + to_string(ageToSearch);
                            break;
                        case '5':
                            cout << "Buscar astronautas menor ou igual a? ";
                            ageToSearch = getNumber();
                            ageText = "menor ou igual a " + to_string(ageToSearch);
                            break;
                        default:
                            break;
                    };
                } catch(string err) {
                    cout << err << endl;
                    char key = askToContinue();
                    if(ENTER == key) continue;
                    else if(BACKSPACE == key) return nullptr;
                    continue;
                };

                // Why a while? Because if there is an 
                // error in getNumber, the code will continue running
                break;
            };

            List<Astronaut>* filteredAstronaut = database->filter([&method, &ageToSearch](Astronaut* astronaut){
                switch(method) {
                    case '0': return astronaut->getAge() > ageToSearch;
                    case '1': return astronaut->getAge() < ageToSearch;
                    case '2': return astronaut->getAge() == ageToSearch;
                    case '3': return astronaut->getAge() != ageToSearch;
                    case '4': return astronaut->getAge() >= ageToSearch;
                    case '5': return astronaut->getAge() <= ageToSearch;
                    default: return true;
                };
            });

            return Astronaut::search(filteredAstronaut, title, filter, AGE, ageText, catchAstronaut, baseDatabase);
        } else if(key == ENTER && search != NONE && baseDatabase != nullptr) {
            List<Astronaut>::destroy(database);
            return Astronaut::search(baseDatabase, title, filter, NONE, "", catchAstronaut, baseDatabase);
        };
    } while(true);

    return nullptr;
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

int Astronaut::getAge() {
    return this->age;
};

Gener Astronaut::getGener() {
    return this->gener;
};

string Astronaut::getStateAsString() {
    return this->alive? 
        (this->available? "Disponivel":"Indisponivel"):
        (this->gener == MALE? "Morto": (
            this->gener == FEMALE? "Morta":
            "Mortx"
        ));
};

bool Astronaut::getAvailable() {
    return this->available && this->alive;
};

void Astronaut::sendToExpedition() {
    this->available = false;
};

void Astronaut::returnFromExpedition() {
    if(this->alive) this->available = true;
    this->expeditions++;
};

void Astronaut::kill() {
    this->alive = false;
    this->available = false;
    this->expeditions++;
};

void Astronaut::print(long long unsigned int maxNameWidth) {
    cout << setw(maxNameWidth + 2) << left << name 
    << setw(16) << this->cpf 
    << setw(7) << this->age 
    << setw(6) << this->expeditions
    << setw(15) << "[" + this->getStateAsString() + "]" << endl;
}; 