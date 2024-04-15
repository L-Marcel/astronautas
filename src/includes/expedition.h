#pragma once
#include "astronaut.h"

enum ExpeditionState {
    PLANNING = 2,
    HAPPENING = 3,
    SUCCESS = 1,
    FAILURE = 0
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

        /// @brief Get the max lenght of an expedition's code
        /// @param database Expedition database
        /// @return Max lenght of an expedition's code
        static long long unsigned int getMaxCodeWidth(List<Expedition>* database);
    public:
        Expedition();
        Expedition(ExpeditionState state, int code);

        /// @brief Initializes a form to create an expedition
        /// @param database Expedition database
        /// @param astronauts Astronaut database
        /// @return Expedition's pointer
        static Expedition* form(List<Expedition>* database, List<Astronaut>* atronauts);

        /// @brief Compare two expeditions
        /// @param a First expedition
        /// @param b Second expedition
        static bool compare(Expedition* a, Expedition* b);

        /// @return Expedition's code
        int getCode();

        /// @return Expedition's code
        ExpeditionState getState();

        /// @return Expedition's code
        string getStateAsString();

        /// @return Expedition's astronaut database
        List<Astronaut>* getAstronauts();

        /// @brief Show the list of expeditions
        /// @param database Expedition database
        /// @return Expedition's pointer or NULL
        static Expedition* list(List<Expedition>* database);

        /// @brief Print expedition's data
        /// @param maxCodeWidth Max lenght of an expedition's name
        void print(long long unsigned int maxCodeWidth);
};