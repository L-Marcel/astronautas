#include "includes/entities.h"

int main() {
    List<Astronaut> astronauts;
    List<Expedition> expeditions;

    char option = ' ';
    do {
        clear();
        cout << "ASTRONAUTAS / SISTEMA DE VOO" << endl << endl;
        cout << "[0] Cadastrar astronauta" << endl;
        cout << "[1] Iniciar planejamento de voo" << endl;
        cout << "[2] Acessar painel de controle de voo" << endl;
        cout << "[3] Listar astronautas da empresa" << endl;
        cout << "[4] Listar astronautas falecidos (memorial)" << endl;
        cout << "[BACKSPACE] Sair do sistema de voo" << endl << endl;
        
        option = input("");

        switch(option) {
            case '0':
                Astronaut::form(&astronauts);
                break;
            case '3':
                Astronaut::list(&astronauts);
                break;
            case BACKSPACE:
                char confirm = ' ';
                do {
                    clear();
                    cout << "Tem certeza que deseja sair [Y/n]? ";
                    confirm = tolower(getchar());
                } while(confirm != 'y' && confirm != 'n');

                if(confirm == 'n') option = ' ';
                break;
        };
    } while(option != BACKSPACE);
    
    return 0;
};