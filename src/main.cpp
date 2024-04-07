#include "includes/system.h"

int main() {
    List<Astronaut> astronauts;
    List<Expedition> expeditions;

    Astronaut* a = new Astronaut("Aalbert", "222.222.222-22", MALE);
    astronauts.add(a);
    a->kill();
    astronauts.add(new Astronaut("Luiza", "111.111.111-11", FEMALE));
    astronauts.add(new Astronaut("Marta", "111.111.111-11", FEMALE));
    astronauts.add(new Astronaut("Sonia", "111.111.111-11", FEMALE));
    Astronaut* b = new Astronaut("Alice", "222.222.222-22", FEMALE);
    astronauts.add(b);
    b->available = false;
    astronauts.add(new Astronaut("Carla", "111.111.111-11", FEMALE));
    astronauts.add(new Astronaut("Genia", "111.111.111-11", FEMALE));
    Astronaut* k = new Astronaut("Aalbert", "222.222.222-22", MALE);
    astronauts.add(k);
    k->available = false;
    Astronaut* c = new Astronaut("Arm", "222.222.222-22", OTHER);
    astronauts.add(c);
    c->kill();
    Astronaut* d = new Astronaut("Berna", "222.222.222-22", FEMALE);
    astronauts.add(d);
    d->kill();
    astronauts.sort(Astronaut::compare);

    System sys(&astronauts, &expeditions);
    sys.menu();

    return 0;
};