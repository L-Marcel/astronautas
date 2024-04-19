#include "includes/expedition.hpp"

Expedition::Expedition() {};
Expedition::Expedition(
    ExpeditionState state, int code
) {
    this->state = state;
    this->code = code;
};

Expedition::~Expedition() {
   this->astronauts.clear();
};

void Expedition::addAstronaut(Astronaut* astronaut) {
    this->astronauts.add(astronaut);
    this->astronauts.sort(Astronaut::compare);
};

void Expedition::removeAstronaut(Astronaut* astronaut) {
    try {
        unsigned int index = this->astronauts.getIndex(astronaut);
        this->astronauts.remove(index);
    } catch(string err) {
        cout << err << endl << endl;
        cout << "Aperte ENTER para continuar..." << endl << endl;
    };
};

long long unsigned int Expedition::getMaxCodeWidth(List<Expedition>* database) {
    long long unsigned int maxCodeWidth = 6;

    if(database != nullptr) {
        for(unsigned int i = 0; i < database->getAmount(); i++) {
            long long unsigned int codeWidth = codeToString(database->get(i)->getCode()).length();
            if(codeWidth > maxCodeWidth) maxCodeWidth = codeWidth;
        };
    };

    return maxCodeWidth;
};

bool Expedition::compare(Expedition* a, Expedition* b) {
    if(a->state != b->state) return a->state > b->state;
    return a->code >= b->code;
};

Expedition* Expedition::form(List<Expedition>* database, List<Astronaut>* astronauts) {
    int code = 0;
    do {
        clearTerminal();
        cout << "PLANEJANDO NOVO VOO" << endl << endl;
        cout << "Qual o código do voo? ";

        try {
            code = getNumber();
        } catch(string err) {
            cout << err << endl;
            char key = askToContinue();
            if(ENTER == key) continue;
            else if(BACKSPACE == key) return nullptr;
        };

        if(code < 0) {
            while(true) {
                clearTerminal();
                cout << "O código de voo não pode ser negativo!" << endl;
                char key = askToContinue();
                if(ENTER == key) break;
                else if(BACKSPACE == key) return nullptr;
            };
        } else if(database->exists([&code](Expedition* expedition) {
            return code == expedition->getCode();
        })) {
            while(true) {
                clearTerminal();
                cout << "O código de voo " + codeToString(code) + " já está em uso!" << endl;
                code = -1;
                char key = askToContinue();
                if(ENTER == key) break;
                else if(BACKSPACE == key) return nullptr;
            };
        };
    } while(code < 0);

    char confirm;
    do {
        clearTerminal();
        cout << "PLANEJANDO NOVO VOO" << endl << endl;
        cout << "Qual o código do voo? " << codeToString(code) << endl;
        cout << "Deseja mesmo planejar esse voo [Y/n]? ";
        confirm = tolower(getChar());
    } while(confirm != 'y' && confirm != 'n');

    if(confirm == 'n') return nullptr;

    Expedition* createdExpedition = new Expedition(PLANNING, code);
    database->add(createdExpedition);
    database->sort(Expedition::compare);

    return createdExpedition;
};

Expedition* Expedition::list(List<Expedition>* database, string title, bool catchExpediton) {
    long long unsigned int maxCodeWitdth = Expedition::getMaxCodeWidth(database);
    unsigned int page = 0;
    unsigned int perPage = 8;
    unsigned int amount =  database->getAmount();
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
            
            if(catchExpediton) cout << "[#]  ";
            else cout << "> ";

            cout << setw(maxCodeWitdth + 2) << left << "CODIGO" 
            << setw(13) << "TRIPULANTES" 
            << setw(16) << "STATUS" << endl;
            for(unsigned int i = start; i < end; i++) {
                if(catchExpediton) cout << "[" << i - (page * perPage) << "]  ";
                else cout << "∘ ";
                database->get(i)->print(maxCodeWitdth);
            };

            cout << endl;

            bool nextPage = page < maxPage;
            bool previousPage = page > 0;

            if(nextPage) cout << "[->] Proxima pagina" << endl;
            if(previousPage) cout << "[<-] Pagina anterior" << endl;

            if(nextPage || previousPage) cout << endl;
        } else {
            cout << "NENHUM VOO ENCONTRADO" << endl << endl;
        };
        
        cout << "[BACKSPACE] Voltar para o menu" << endl << endl;

        char key = input();

        if(key == BACKSPACE) return nullptr;
        else if(key >= '0' && key < '0' + int(end - start) && catchExpediton) {
            unsigned int index = (key - '0') + (page * perPage);
            return database->get(index);
        } else if(key == SPECIAL_KEY) {
            #ifdef _WIN32
                int specialKey = getch();
            #else
                int specialKey = input();
            #endif
            if(specialKey == LEFT && page > 0) page--;
            else if(specialKey == RIGHT && page < maxPage) page++;
        };
    } while(true);

    return nullptr;
};

void Expedition::edit( 
    List<Expedition>* database, 
    List<Astronaut>* astronauts
) {
    char option;
    Astronaut* astronaut = nullptr;
    
    this->astronauts.sort(Astronaut::compare);
    List<Astronaut>* astronautCanBeAdded;

    switch(this->getState()) {
        case PLANNING:
            while(true) {
                bool canLaunch = 
                    this->astronauts.getAmount() > 0
                    && this->astronauts.all([](Astronaut* astronaut){
                        return astronaut->getAvailable();
                    });

                clearTerminal();
                cout << "PLANEJAMENTO DO VOO " << codeToString(this->code) << endl << endl;
                cout << "[0] Adicionar astronauta ao voo" << endl;
                cout << "[1] Listar astronautas do voo (total: " << this->astronauts.getAmount() << ")" << endl;
                cout << "[2] Remover astronauta do voo" << endl;
                if(canLaunch) cout << "[3] Lançar voo" << endl;
                cout << endl << "[BACKSPACE] Voltar para menu" << endl << endl;

                option = input();

                switch(option) {
                    case '0':
                        astronautCanBeAdded = astronauts->filter(
                            [this](Astronaut* astronaut){
                                return !(this->getAstronauts()->exists([&astronaut](Astronaut* another){
                                    return astronaut == another;
                                }));
                            }
                        );

                        astronaut = Astronaut::list(astronautCanBeAdded, "ADICIONANDO ASTRONAUTA AO VOO " + codeToString(this->code), ALIVE, true);
                        if(astronaut != nullptr) this->addAstronaut(astronaut);
                        astronaut = nullptr;
                        List<Astronaut>::destroy(astronautCanBeAdded);
                        break;
                    case '1':
                        Astronaut::list(&this->astronauts, "ASTRONAUTAS DO VOO " + codeToString(code), ALL, false);
                        break;
                    case '2':
                        astronaut = Astronaut::list(&this->astronauts, "REMOVENDO ASTRONAUTA DO VOO " + codeToString(code), ALL, true);
                        if(astronaut != nullptr) this->removeAstronaut(astronaut);
                        astronaut = nullptr;
                        break;
                    case '3':
                        if(canLaunch) {
                            char confirm;
                            do {
                                clearTerminal();
                                
                                cout << "Deseja mesmo lançar o voo " << codeToString(code) << " [Y/n]? ";
                        
                                confirm = tolower(getChar());
                            } while(confirm != 'y' && confirm != 'n');

                            if(confirm == 'y') {
                                this->state = HAPPENING;
                                
                                Astronaut* currentAstronaut = nullptr;
                                for(unsigned int i = 0; i < this->astronauts.getAmount(); i++) {
                                    currentAstronaut = this->astronauts.get(i);
                                    if(currentAstronaut != nullptr) currentAstronaut->sendToExpedition();
                                };

                                astronauts->sort(Astronaut::compare);
                                database->sort(Expedition::compare);
                        
                                return;
                            };
                        };
                        break;
                    case BACKSPACE:
                        return;
                    default:
                        break;
                };
            };
            break;
        case HAPPENING:
            while(true) {
                clearTerminal();
                cout << "VOO " << codeToString(this->code) << " [LANÇADO]" << endl << endl;
                cout << "[0] Listar astronautas no voo (total: " << this->astronauts.getAmount() << ")" << endl;
                cout << "[1] Finalizar voo" << endl;
                cout << "[2] Explodir voo" << endl << endl;
                cout << "[BACKSPACE] Voltar para menu" << endl << endl;

                option = input();

                switch(option) {
                    case '0':
                        Astronaut::list(&this->astronauts, "ASTRONAUTAS DO VOO " + codeToString(code), ALL, false);
                        break;
                    case '1':
                        char confirmEnd;
                        do {
                            clearTerminal();
                            
                            cout << "Deseja mesmo finalizar o voo " << codeToString(code) << " [Y/n]? ";
                    
                            confirmEnd = tolower(getChar());
                        } while(confirmEnd != 'y' && confirmEnd != 'n');

                        if(confirmEnd == 'y') {
                            this->state = SUCCESS;
                            
                            Astronaut* currentAstronaut = nullptr;
                            for(unsigned int i = 0; i < this->astronauts.getAmount(); i++) {
                                currentAstronaut = this->astronauts.get(i);
                                if(currentAstronaut != nullptr) currentAstronaut->returnFromExpedition();
                            };

                            astronauts->sort(Astronaut::compare);
                            database->sort(Expedition::compare);
                            return;
                        };
                        break;
                    case '2':
                        char confirmExplosion;
                        do {
                            clearTerminal();
                            
                            cout << "Deseja mesmo registrar que o voo " << codeToString(code) << " explodiu [Y/n]? ";
                    
                            confirmExplosion = tolower(getChar());
                        } while(confirmExplosion != 'y' && confirmExplosion != 'n');

                        if(confirmExplosion == 'y') {
                            this->state = FAILURE;
                            
                            Astronaut* currentAstronaut = nullptr;
                            for(unsigned int i = 0; i < this->astronauts.getAmount(); i++) {
                                currentAstronaut = this->astronauts.get(i);
                                if(currentAstronaut != nullptr) currentAstronaut->kill();
                            };

                            astronauts->sort(Astronaut::compare);
                            database->sort(Expedition::compare);
                            return;
                        };
                        break;
                    case BACKSPACE:
                        return;
                    default:
                        break;
                };
            };
        case SUCCESS:
            while(true) {
                clearTerminal();
                cout << "VOO " << codeToString(this->code) << " [FINALIZADO COM SUCESSO]" << endl << endl;
                cout << "[0] Listar astronautas no voo (total: " << this->astronauts.getAmount() << ")" << endl << endl;
                cout << "[BACKSPACE] Voltar para menu" << endl << endl;

                option = input();

                switch(option) {
                    case '0':
                        Astronaut::list(&this->astronauts, "ASTRONAUTAS DO VOO " + codeToString(code), ALL, false);
                        break;
                    case BACKSPACE:
                        return;
                    default:
                        break;
                };
            };
        case FAILURE:
            while(true) {
                clearTerminal();
                cout << "VOO " << codeToString(this->code) << " [FRACASSO TOTAL]" << endl << endl;
                cout << "[0] Listar astronautas no voo (total: " << this->astronauts.getAmount() << ")" << endl << endl;
                cout << "[BACKSPACE] Voltar para menu" << endl << endl;

                option = input();

                switch(option) {
                    case '0':
                        Astronaut::list(&this->astronauts, "ASTRONAUTAS DO VOO " + codeToString(code), ALL, false);
                        break;
                    case BACKSPACE:
                        return;
                    default:
                        break;
                };
            };
        default:
            break;
    }
    
};

int Expedition::getCode() {
    return this->code;
};

ExpeditionState Expedition::getState() {
    return this->state;
};

string Expedition::getStateAsString() {
    switch (this->state) {
        case PLANNING: return "Planejamento";
        case HAPPENING: return "Lançado";
        case SUCCESS: return "Finalizado";
        case FAILURE: return "Fracassado";
        default: return "Desconhecido";
    };
};

List<Astronaut>* Expedition::getAstronauts() {
    return &this->astronauts;
};

void Expedition::print(long long unsigned int maxCodeWidth) {
    cout << setw(maxCodeWidth + 2) << left << codeToString(this->code) << setw(13) << this->astronauts.getAmount() << setw(16) << "[" + this->getStateAsString() + "]" << endl;
}; 