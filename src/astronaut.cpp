#include "includes/astronaut.h"

string generToString(Gener gener) {
    switch (gener) {
        case MALE: return "Masculino";
        case FEMALE: return "Feminino";
        default: return "Outro";
    };
};

Astronaut::Astronaut() {};
Astronaut::Astronaut(string name, string cpf, Gener gener) {
    this->name = name;
    this->cpf = cpf;
    this->gener = gener;
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

    char generChar;
    do {
        clear();
        cout << "CADASTRANDO NOVO ASTRONAUTA" << endl << endl;
        cout << "Qual o nome do astronauta? " << name << endl;
        cout << "Qual o cpf do astronauta? " << cpf << endl;
        cout << "Com qual genero o astronauta se identifica? " << endl << endl;
        
        cout << "[M] Masculino" << endl;
        cout << "[F] Feminino" << endl;
        cout << "[O] Outro" << endl << endl;

        cout << "Resposta: ";

        generChar = tolower(getchar());
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
    char confirm;
    do {
        clear();
        cout << "CADASTRANDO NOVO ASTRONAUTA" << endl << endl;
        cout << "Qual o nome do astronauta? " << name << endl;
        cout << "Qual o cpf do astronauta? " << cpf << endl;
        cout << "Com qual genero o astronauta se identifica? " << generRef << endl << endl;
        cout << "Confirmar cadastro [Y/n]? ";
        confirm = tolower(getchar());
    } while(confirm != 'y' && confirm != 'n');

    if(confirm == 'n') return NULL;

    Astronaut* createdAstronaut = new Astronaut(name, cpf, gener);
    database->add(createdAstronaut);
    database->sort(Astronaut::compare);

    return createdAstronaut;
}

unsigned int Astronaut::countDeaths(List<Astronaut>* database) {
    unsigned int deaths = 0;

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

Astronaut* Astronaut::list(
    List<Astronaut>* database, string title, 
    AstronautFilter filter, bool catchAstronaut
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

        clear();
        
        if(amount > 0) {
            cout << title << " [" << page + 1 << "/" << maxPage + 1 << "]" << endl << endl;

            cout << "[#]  " << setw(maxNameWidth + 2) << left << "NOME" << setw(6) << "VOOS" << setw(15) << "STATUS" << endl;
            for(unsigned int i = start; i < end; i++) {
                cout << "[" << i - (page * perPage) << "]  ";
                database->get(i + alivesGap)->print(maxNameWidth);

            };

            cout << endl;
            if(page < maxPage) cout << "[->] Proxima pagina" << endl;
            if(page > 0) cout << "[<-] Pagina anterior" << endl;
        } else {
            cout << "NENHUM ASTRONAUTA ENCONTRADO" << endl << endl;;
        };

        cout << "[BACKSPACE] Voltar para o menu principal" << endl << endl;

        char key = input("");

        if(key == BACKSPACE) return NULL;
        else if(key >= '0' && key < '0' + int(end - start) && catchAstronaut) {
            unsigned int index = (key - '0') + (page * perPage) + alivesGap;
            return database->get(index);
        } else if(key == SPECIAL_KEY) {
            int specialKey = getch();
            if(specialKey == LEFT && page > 0) page--;
            else if(specialKey == RIGHT && page < maxPage) page++;
        };
    } while(true);

    return NULL;
};

string Astronaut::getName() {
    return this->name;
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

    cout << setw(maxNameWidth + 2) << left << name << setw(6) << expeditions << setw(15) << availability << endl;
}; 