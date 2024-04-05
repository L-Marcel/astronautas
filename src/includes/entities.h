#pragma once
#include "list.h"

class Astronaut {
    private:
        bool available = true;
        string name;
        string cpf;
    public:
        Astronaut();
        Astronaut(string name, string cpf);

        /// @brief Initializes a form to create an astronaut
        /// @return Astronaut's pointer
        static Astronaut* form();

        /// @return Astronaut's name
        string getName();
};

class Expedition {
    private:
        List<Astronaut> astronauts;
        string name;
    public:
        Expedition();
};