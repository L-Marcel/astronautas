#include <iostream>
#include <cstdlib>

using namespace std;

template <typename T> class List {
    private:
        unsigned int qtd = 0;
        T** items;
    public:
        List<T>() {
            this->items = new T[0];
        };
        add(T* item) {
            this->qtd++;
            T** items = new T[qtd];
            for(int i = 0; i < qtd - 1; i++) {
                items[i] = 
            };
        };
};

class Astronaut {
    private:
        Expedition** expeditions;
        bool available = true;
        string cpf;
        string name;

};

class Expedition {
    private:

        Astronaut** astronauts;
        string name;
    public:
        Expedition() {
            this->astronauts = new Astronaut[0];
        };


};

int main() {
    srand(time(NULL));

    cout << rand() << endl;
    return 0;
};