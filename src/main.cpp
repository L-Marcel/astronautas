#include "includes/entities.h"

int main() {
    List<Astronaut> astronauts;
    List<Expedition> expeditions;
    
    Astronaut* astro = Astronaut::form();

    if(astro != NULL) {
        clear();
        cout << "Astronauta criado: " << astro->getName() << endl;
    };
    return 0;
};