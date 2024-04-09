#include "includes/system.h"

System::System(List<Astronaut>* astronauts, List<Expedition>* expeditions) {
    this->astronauts = astronauts;
    this->expeditions = expeditions;
};

void System::restart() {
    system("make dev && make run");
};

void System::menu() {
    char option = ' ';

    do {
        clearTerminal();
        cout << "ASTRONAUTAS / SISTEMA DE VOO" << endl << endl;
        cout << "[0] Cadastrar astronauta" << endl;
        cout << "[1] Iniciar planejamento de voo" << endl;
        cout << "[2] Acessar painel de controle de voo" << endl;
        cout << "[3] Listar astronautas da empresa" << endl;
        cout << "[4] Listar astronautas falecidos (memorial)" << endl << endl;
        cout << "[BACKSPACE] Sair do sistema de voo" << endl << endl;
        
        option = input("");

        switch(option) {
            case '0':
                Astronaut::form(this->astronauts);
                break;
            case '1':
                //Expedition::form(&astronauts, &expeditions);
                break;
            case '3':
                Astronaut::list(
                    this->astronauts, 
                    "ASTRONAUTAS CADASTRADOS NO SISTEMA", 
                    ALIVE, false
                );
                break;
            case '4':
                Astronaut::list(
                    this->astronauts, 
                    "MEMORIAL DOS ASTRONAUTAS", 
                    DEAD, false
                );
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