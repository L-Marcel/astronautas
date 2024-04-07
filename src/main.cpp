#include "includes/system.h"

int main() {
    List<Astronaut> astronauts;
    List<Expedition> expeditions;

    astronauts.add(new Astronaut("Luiza", "111.111.111-11", FEMALE));
    astronauts.add(new Astronaut("Marta", "111.111.111-11", FEMALE));
    astronauts.add(new Astronaut("Sonia", "111.111.111-11", FEMALE));
    astronauts.add(new Astronaut("Carla", "111.111.111-11", FEMALE));
    astronauts.add(new Astronaut("Genia", "111.111.111-11", FEMALE));

    Astronaut* k = new Astronaut("Aalbert", "222.222.222-22", MALE);
    astronauts.add(k);

    k->available = false;


    Astronaut* b = new Astronaut("Alice", "222.222.222-22", FEMALE);
    astronauts.add(b);

    b->available = false;

    Astronaut* c = new Astronaut("Arm", "222.222.222-22", OTHER);
    astronauts.add(c);

    c->kill();

    Astronaut* d = new Astronaut("Berna", "222.222.222-22", FEMALE);
    astronauts.add(d);

    d->kill();


    Astronaut* a = new Astronaut("Aalbert", "222.222.222-22", MALE);
    astronauts.add(a);

    a->kill();

    astronauts.sort(Astronaut::compare);

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
            case '1':
                //Expedition::form(&astronauts, &expeditions);
                break;
            case '3':
                Astronaut::list(
                    &astronauts, 
                    "ASTRONAUTAS CADASTRADOS NO SISTEMA", 
                    true, false
                );
                break;
            case '4':
                Astronaut::list(
                    &astronauts, 
                    "MEMORIAL DOS ASTRONAUTAS", 
                    false, false
                );
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