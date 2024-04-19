#include "includes/system.hpp"

System::System(List<Astronaut>* astronauts, List<Expedition>* expeditions) {
    this->astronauts = astronauts;
    this->expeditions = expeditions;
};

void System::menu() {
    char option = ' ';

    Expedition* expedition = nullptr;
    Astronaut* astronaut = nullptr;
    do {
        clearTerminal();
        cout << "ASTRONAUTAS / SISTEMA DE VOO" << endl << endl;
        cout << "[0] Cadastrar astronauta" << endl;
        cout << "[1] Iniciar planejamento de voo" << endl;
        cout << "[2] Lista de voos" << endl;
        cout << "[3] Listar astronautas da empresa" << endl;
        cout << "[4] Listar astronautas falecidos (memorial)" << endl << endl;
        cout << "[BACKSPACE] Sair do sistema de voo" << endl << endl;
        
        option = input();

        switch(option) {
            case '0':
                Astronaut::form(this->astronauts);
                break;
            case '1':
                Expedition::form(this->expeditions, this->astronauts);
                break;
            case '2':
                expedition = Expedition::list(this->expeditions, "VOOS CADASTRADOS NO SISTEMA");
                if(expedition != nullptr) expedition->edit(this->expeditions, this->astronauts);
                expedition = nullptr;
                break;
            case '3':
                astronaut = Astronaut::list(
                    this->astronauts, 
                    "ASTRONAUTAS CADASTRADOS NO SISTEMA", 
                    ALIVE, true
                );
                if(astronaut != nullptr) astronautPage(astronaut, this->expeditions);
                astronaut = nullptr;
                break;
            case '4':
                astronaut = Astronaut::list(
                    this->astronauts, 
                    "MEMORIAL DOS ASTRONAUTAS", 
                    DEAD, true
                );
                if(astronaut != nullptr) astronautPage(astronaut, this->expeditions);
                astronaut = nullptr;
                break;
            case BACKSPACE:
                char confirm;

                do {
                    clearTerminal();
                    cout << "Tem certeza que deseja sair [Y/n]? ";
                    confirm = tolower(getChar());
                } while(confirm != 'y' && confirm != 'n');

                if(confirm == 'n') option = ' ';
                break;
        };
    } while(option != BACKSPACE);
};

void System::free() {
    this->astronauts->free();
    this->expeditions->free();
};

void System::astronautPage(Astronaut* astronaut, List<Expedition>* expeditions) {
    List<Expedition>* astronautExpeditions = expeditions->filter([astronaut](Expedition* expedition) {
        return expedition->getAstronauts()->exists([astronaut](Astronaut* another) {
            return another->getCpf() == astronaut->getCpf();
        });
    });

    List<Expedition>* finishedExpeditions = astronautExpeditions->filter([](Expedition* expedition) {
        return expedition->getState() == SUCCESS || expedition->getState() == FAILURE;
    });

    List<Expedition>* futureExpeditions = astronautExpeditions->filter([](Expedition* expedition) {
        return expedition->getState() == PLANNING;
    });

    Expedition* inExpedition = astronautExpeditions->find([](Expedition* expedition) {
        return expedition->getState() == HAPPENING;
    });

    char option;
    string strongName = upper(astronaut->getName());

    while(true) {
        clearTerminal();
        cout << "ASTRONAUTA " << strongName << endl << endl;
        cout << "Cpf: " << astronaut->getCpf() << endl;
        cout << "Idade: " << astronaut->getAge() << endl;
        cout << "Genero: " << generToString(astronaut->getGener()) << endl;
        cout << "Status: " << astronaut->getStateAsString() << endl << endl;
        if(inExpedition != nullptr) {
            cout << "Participando do " << finishedExpeditions->getAmount() + 1 << "° voo (" << codeToString(inExpedition->getCode()) << ")";
            unsigned int friends = inExpedition->getAstronauts()->getAmount() - 1;

            if(friends > 1) cout << " com \noutros " << friends << " astronautas" << endl << endl;
            else if(friends == 1) cout << " com \noutro atronauta" << endl << endl;
            else cout << " e sozinh" << (
                astronaut->getGener() == MALE? "o": 
                (astronaut->getGener() == FEMALE? "a":"x")
            ) << endl << endl;
        };

        cout << "[0] Listar voos finalizadas (total: " << finishedExpeditions->getAmount() << ")" << endl;
        cout << "[1] Listar voos em planejamento (total: " << futureExpeditions->getAmount() << ")" << endl;
        
        cout << endl << "[BACKSPACE] Voltar para menu" << endl << endl;
        option = input();

        switch(option) {
            case '0':
                Expedition::list(finishedExpeditions, "VOOS FINALIZADOS DE " + strongName, false);
                break;
            case '1':
                Expedition::list(futureExpeditions, "VOOS PLANEJADOS DE " + strongName, false);
                break;
            case BACKSPACE: 
                List<Expedition>::destroy(finishedExpeditions);
                List<Expedition>::destroy(futureExpeditions);
                List<Expedition>::destroy(astronautExpeditions);
                return;
            default: 
                break;
        };
    };
};

void System::seed() {
    /// Warning: part of this function is AI-generated content!

    this->astronauts->add(new Astronaut("Neil Armstrong", "123.456.789-00", MALE, 20));
    this->astronauts->add(new Astronaut("Buzz Aldrin", "123.456.789-01", OTHER, 21));
    this->astronauts->add(new Astronaut("Michael Collins", "156.456.789-00", MALE, 35));
    this->astronauts->add(new Astronaut("Louis Gagarin", "987.456.789-02", FEMALE, 24));
    this->astronauts->add(new Astronaut("Fake Marcel", "897.456.635-04", MALE, 21));
    this->astronauts->add(new Astronaut("Another Marcel", "416.456.635-04", MALE, 21));
    this->astronauts->add(new Astronaut("Marcelo Francis", "741.456.635-04", OTHER, 18));
    this->astronauts->add(new Astronaut("Marcela Francis", "289.456.635-04", FEMALE, 18));
    this->astronauts->add(new Astronaut("Everything", "000.000.000-00", OTHER, 80));
    this->astronauts->add(new Astronaut("Nothing", "000.000.000-01", OTHER, 18));
};