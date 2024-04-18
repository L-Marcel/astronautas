#include "includes/system.hpp"

int main(int argc, char *argv[]) {
    List<Astronaut> astronauts;
    List<Expedition> expeditions;

    System sys(&astronauts, &expeditions);

    if(argc > 1 && argv[1] == string("seeded")) {
        sys.seed();
    };

    sys.menu();
    sys.free();

    return 0;
};