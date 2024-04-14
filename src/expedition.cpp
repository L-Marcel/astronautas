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

Expedition* Expedition::form(List<Expedition>* database, List<Astronaut>* astronauts) {
    ExpeditionState state = PLANNING;
    unsigned int amount = database->getAmount();
    int code = amount > 0? 
        (database->get(amount - 1)->getCode() + 1)
        :1;

    
    Expedition* expedition = new Expedition(state, code);
    Astronaut* astronaut = NULL;
    List<Astronaut> astronautCanBeAdded;
    char option;
    bool planning = true;
    while(planning) {
        bool canConfirm = expedition->astronauts.getAmount() > 0;

        clearTerminal();
        cout << "INICIANDO PLANEJAMENTO DO VOO " << codeToString(code) << endl << endl;
        cout << "[0] Adicionar astronauta ao voo" << endl;
        cout << "[1] Listar astronautas do voo (total: " << expedition->astronauts.getAmount() << ")" << endl;
        cout << "[2] Remover astronauta do voo" << endl << endl;
        if(canConfirm) cout << "[ENTER] Confirmar planejamento do voo" << endl;
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
                if(canConfirm) {
                    char confirm;
                    do {
                        clearTerminal();
                        
                        cout << "Uma vez planejado, o voo " + codeToString(code) + " deve acontecer!" << endl;
                        cout << "Deseja mesmo planejar esse voo [Y/n]? ";
                
                        confirm = tolower(getChar());
                    } while(confirm != 'y' && confirm != 'n');

                    if(confirm == 'y') {
                        database->add(expedition);
                        return expedition;
                    };
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

int Expedition::getCode() {
    return this->code;
};

List<Astronaut>* Expedition::getAstronauts() {
    return &this->astronauts;
};