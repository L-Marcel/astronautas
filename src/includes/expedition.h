#pragma once
#include "astronaut.h"

enum ExpeditionState {
    PLANNING,
    HAPPENING,
    SUCCESS,
    FAILURE
};

class Expedition {
    private:
        ExpeditionState state;
        List<Astronaut> astronauts;
        string name;
        
        /// @brief Add an astronaut to expedition
        /// @param astronaut the astronaut to add
        void addAstronaut(Astronaut* astronaut);
    public:
        Expedition();

        /// @brief Initializes a form to create an expedition
        /// @param database Expedition database
        /// @return Expedition's pointer
        static Expedition* form(List<Expedition>* database);

        /// @brief Print expedition's data
        /// @param database list of expeditions to calculate the columns max width
        /// @param true If you want to print all data, default is false
        void print(List<Expedition>* database, bool full = false);
};