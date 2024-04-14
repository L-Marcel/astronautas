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
        int code;
        
        /// @brief Add an astronaut to expedition
        /// @param astronaut the astronaut to add
        void addAstronaut(Astronaut* astronaut);

        /// @brief Remove an astronaut to expedition
        /// @param astronaut the astronaut to remove
        void removeAstronaut(Astronaut* astronaut);
    public:
        Expedition();
        Expedition(ExpeditionState state, int code);

        /// @brief Initializes a form to create an expedition
        /// @param database Expedition database
        /// @param astronauts Astronaut database
        /// @return Expedition's pointer
        static Expedition* form(List<Expedition>* database, List<Astronaut>* atronauts);

        /// @return Expedition's code
        int getCode();

        /// @return Expedition's astronaut database
        List<Astronaut>* getAstronauts();

        /// @brief Print expedition's data
        /// @param database list of expeditions to calculate the columns max width
        /// @param true If you want to print all data, default is false
        void print(List<Expedition>* database, bool full = false);
};