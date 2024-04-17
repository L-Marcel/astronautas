#include "includes/expedition.h"

Expedition::Expedition() {};
Expedition::Expedition(
    ExpeditionState state, int code
) {
    this->state = state;
    this->code = code;
};

void Expedition::addAstronaut(Astronaut* astronaut) {
    this->astronauts.add(astronaut);
    this->astronauts.sort(Astronaut::compare);
};

void Expedition::removeAstronaut(Astronaut* astronaut) {
    try {
        unsigned int index = this->astronauts.getIndex(astronaut);
        this->astronauts.remove(index);
    } catch(int err) {};
};

long long unsigned int Expedition::getMaxCodeWidth(List<Expedition>* database) {
    long long unsigned int maxCodeWidth = 6;

    if(database != NULL) {
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
    ExpeditionState state = PLANNING;
    unsigned int amount = database->getAmount();

    int lastCode = 0;

    for(unsigned int i = 0; i < amount; i++) {
        int code = database->get(i)->getCode();
        if(code > lastCode) lastCode = code;
    };

    int code = lastCode + 1;
    
    Expedition* expedition = new Expedition(state, code);
    Astronaut* astronaut = NULL;
    List<Astronaut> astronautCanBeAdded;
    char option;
    bool planning = true;
    while(planning) {
        clearTerminal();
        cout << "INICIANDO PLANEJAMENTO DO VOO " << codeToString(code) << endl << endl;
        cout << "[0] Adicionar astronauta ao voo" << endl;
        cout << "[1] Listar astronautas do voo (total: " << expedition->astronauts.getAmount() << ")" << endl;
        cout << "[2] Remover astronauta do voo" << endl << endl;
        cout << "[ENTER] Confirmar planejamento do voo" << endl;
        cout << "[BACKSPACE] Cancelar planejamento do voo" << endl << endl;

        option = input("");

        switch(option) {
            case '0':
                astronautCanBeAdded = astronauts->filter(
                    [&expedition](Astronaut* astronaut){
                        return !(expedition->getAstronauts()->exists([&astronaut](Astronaut* another){
                            return astronaut == another;
                        }));
                    }
                );

                astronaut = Astronaut::list(&astronautCanBeAdded, "ADICIONANDO ASTRONAUTA AO VOO " + codeToString(code), ALIVE, true);
                if(astronaut != NULL) expedition->addAstronaut(astronaut);
                astronaut = NULL;
                break;
            case '1':
                Astronaut::list(&expedition->astronauts, "ASTRONAUTAS DO VOO " + codeToString(code), ALL, false);
                break;
            case '2':
                astronaut = Astronaut::list(&expedition->astronauts, "REMOVENDO ASTRONAUTA DO VOO " + codeToString(code), ALL, true);
                if(astronaut != NULL) expedition->removeAstronaut(astronaut);
                astronaut = NULL;
                break;
            case ENTER:
                char confirm;
                do {
                    clearTerminal();
                    
                    cout << "Uma vez planejado, o voo " + codeToString(code) + " deve acontecer!" << endl;
                    cout << "Deseja mesmo planejar esse voo [Y/n]? ";
            
                    confirm = tolower(getChar());
                } while(confirm != 'y' && confirm != 'n');

                if(confirm == 'y') {
                    database->add(expedition);
                    database->sort(Expedition::compare);
                    return expedition;
                };
                break;
            case BACKSPACE:
                char confirmCancel;
                do {
                    clearTerminal();
                    
                    cout << "Uma vez cancelado o planejado todos os dados dele vao se perder!" << endl;
                    cout << "Deseja mesmo cancelar esse planejamento [Y/n]? ";
            
                    confirmCancel = tolower(getChar());
                } while(confirmCancel != 'y' && confirmCancel != 'n');

                if(confirmCancel == 'y') {
                    delete expedition;
                    return NULL;
                };
                break;
            default:
                break;
        };
    };

    return NULL;
};

Expedition* Expedition::list(List<Expedition>* database) {
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
            cout << "VOOS CADASTRADOS" << " [" << page + 1 << "/" << maxPage + 1 << "]" << endl << endl;

            cout << "[#]  " << setw(maxCodeWitdth + 2) << left << "CODIGO" 
            << setw(13) << "TRIPULANTES" 
            << setw(16) << "STATUS" << endl;
            for(unsigned int i = start; i < end; i++) {
                cout << "[" << i - (page * perPage) << "]  ";
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

        char key = input("");

        if(key == BACKSPACE) return NULL;
        else if(key >= '0' && key < '0' + int(end - start)) {
            unsigned int index = (key - '0') + (page * perPage);
            return database->get(index);
        } else if(key == SPECIAL_KEY) {
            #ifdef _WIN32
                int specialKey = getch();
            #else
                int specialKey = input("");
            #endif
            if(specialKey == LEFT && page > 0) page--;
            else if(specialKey == RIGHT && page < maxPage) page++;
        };
    } while(true);

    return NULL;
};

void Expedition::edit( 
    List<Expedition>* database, 
    List<Astronaut>* astronauts
) {
    char option;
    Astronaut* astronaut = NULL;
    List<Astronaut> astronautCanBeAdded;

    switch (this->getState()) {
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

                option = input("");

                switch(option) {
                    case '0':
                        astronautCanBeAdded = astronauts->filter(
                            [this](Astronaut* astronaut){
                                return !(this->getAstronauts()->exists([&astronaut](Astronaut* another){
                                    return astronaut == another;
                                }));
                            }
                        );

                        astronaut = Astronaut::list(&astronautCanBeAdded, "ADICIONANDO ASTRONAUTA AO VOO " + codeToString(this->code), ALIVE, true);
                        if(astronaut != NULL) this->addAstronaut(astronaut);
                        astronaut = NULL;
                        break;
                    case '1':
                        Astronaut::list(&this->astronauts, "ASTRONAUTAS DO VOO " + codeToString(code), ALL, false);
                        break;
                    case '2':
                        astronaut = Astronaut::list(&this->astronauts, "REMOVENDO ASTRONAUTA DO VOO " + codeToString(code), ALL, true);
                        if(astronaut != NULL) this->removeAstronaut(astronaut);
                        astronaut = NULL;
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
                                
                                for(unsigned int i = 0; i < this->astronauts.getAmount(); i++) {
                                    this->astronauts.get(i)->sendToExpedition();
                                };

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
                cout << "VOO " << codeToString(this->code) << "[LANÇADO]" << endl << endl;
                cout << "[0] Listar astronautas no voo (total: " << this->astronauts.getAmount() << ")" << endl;
                cout << "[1] Finalizar voo" << endl;
                cout << "[2] Explodir voo" << endl << endl;
                cout << "[BACKSPACE] Voltar para menu" << endl << endl;

                option = input("");

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
                            
                            for(unsigned int i = 0; i < this->astronauts.getAmount(); i++) {
                                this->astronauts.get(i)->returnFromExpedition();
                            };

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
                            
                            for(unsigned int i = 0; i < this->astronauts.getAmount(); i++) {
                                this->astronauts.get(i)->kill();
                            };

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
                cout << "VOO " << codeToString(this->code) << "[FINALIZADO COM SUCESSO]" << endl << endl;
                cout << "[0] Listar astronautas no voo (total: " << this->astronauts.getAmount() << ")" << endl << endl;
                cout << "[BACKSPACE] Voltar para menu" << endl << endl;

                option = input("");

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
                cout << "VOO " << codeToString(this->code) << "[FRACASSO TOTAL]" << endl << endl;
                cout << "[0] Listar astronautas no voo (total: " << this->astronauts.getAmount() << ")" << endl << endl;
                cout << "[BACKSPACE] Voltar para menu" << endl << endl;

                option = input("");

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