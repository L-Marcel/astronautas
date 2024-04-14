#include "includes/system.h"

int main() {
    List<Astronaut> astronauts;
    List<Expedition> expeditions;

    Astronaut* a = new Astronaut("Aalbert", "222.222.222-22", MALE, 18);
    astronauts.add(a);
    a->kill();
    astronauts.add(new Astronaut("Luiza", "111.111.111-11", FEMALE, 18));
    astronauts.add(new Astronaut("Marta", "111.111.111-11", FEMALE, 18));
    astronauts.add(new Astronaut("Sonia", "111.111.111-11", FEMALE, 24));
    Astronaut* b = new Astronaut("Alice", "222.222.222-22", FEMALE, 23);
    astronauts.add(b);
    b->available = false;
    astronauts.add(new Astronaut("Carla", "111.111.111-11", FEMALE, 18));
    astronauts.add(new Astronaut("Genia", "111.111.111-11", FEMALE, 16));
    Astronaut* k = new Astronaut("Aalbert", "222.222.222-22", MALE, 18);
    astronauts.add(k);
    k->available = false;
    Astronaut* c = new Astronaut("Arm", "222.222.222-22", OTHER, 18);
    astronauts.add(c);
    c->kill();
    Astronaut* d = new Astronaut("Berna", "222.222.222-22", FEMALE, 17);
    astronauts.add(d);
    d->kill();
    astronauts.sort(Astronaut::compare);

    System sys(&astronauts, &expeditions);
    sys.menu();

    // // 27
    // do {
    //     int key = input("aperte: ");
    //     cout << key << endl;

    //     if(key == SPECIAL_KEY) {
    //         int specialKey = getch();
    //         if(specialKey == LEFT) cout << "left" << endl;
    //         cout << specialKey << endl;
    //         break;
    //     };
    // } while(true);

    return 0;
};