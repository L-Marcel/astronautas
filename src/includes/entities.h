#pragma once
#include "list.h"

class Astronaut {
    private:
        bool available = true;
        bool alive = true;
        string name;
        string cpf;

        /// @brief Get the max lenght of an astronaut's name
        /// @param database Astronaut database
        /// @return Max lenght of an astronaut's name
        static long long unsigned int getMaxNameWidth(List<Astronaut>* database);
    public:
        Astronaut();
        Astronaut(string name, string cpf);

        /// @brief Initializes a form to create an astronaut
        /// @param database Astronaut database
        /// @return Astronaut's pointer
        static Astronaut* form(List<Astronaut>* database);

        /// @brief Show the list of astronauts (only if alive)
        /// @param database 
        static void list(List<Astronaut>* database);

        /// @return Astronaut's name
        string getName();

        /// @brief Kill the astronaut
        void kill();

        /// @brief Print astronaut's data
        /// @param maxNameWidth Max lenght of an astronaut's name
        /// @param true If you want to print all data, default is false
        void print(long long unsigned int maxNameWidth, bool full = false);
};

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
    public:
        Expedition();

        /// @brief Initializes a form to create an expedition
        /// @param database Expedition database
        /// @return Expedition's pointer
        static Expedition* form(List<Expedition>* database);

        void addAstronaut(Astronaut* astronaut);

        /// @brief Print expedition's data
        /// @param database list of expeditions to calculate the columns max width
        /// @param true If you want to print all data, default is false
        void print(List<Expedition>* database, bool full = false);
};