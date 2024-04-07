#pragma once
#include "list.h"

enum Gener {
    MALE,
    FEMALE,
    OTHER
};

/// @brief Convert a gener to string
/// @param gener the gener
/// @return gener string
string generToString(Gener gener);

class Astronaut {
    private:
        
        bool alive = true;
        string name;
        string cpf;
        Gener gener;

        /// @brief Get the max lenght of an astronaut's name
        /// @param database Astronaut database
        /// @return Max lenght of an astronaut's name
        static long long unsigned int getMaxNameWidth(List<Astronaut>* database);
    public:
        /// [LEMBRETE] Se lembrar de mover para privado depois
        bool available = true;

        Astronaut();
        Astronaut(string name, string cpf, Gener gener);

        /// @brief Compare two astronauts
        /// @param a First astronaut
        /// @param b Second astronaut
        static bool compare(Astronaut* a, Astronaut* b);

        /// @brief Initializes a form to create an astronaut
        /// @param database Astronaut database
        /// @return Astronaut's pointer or NULL
        static Astronaut* form(List<Astronaut>* database);

        /// @brief Count the number of dead astronauts
        /// @param database Astronaut database
        /// @return The number of deadths
        static unsigned int countDeaths(List<Astronaut>* database);

        /// @brief Show the list of astronauts
        /// @param database Astronaut database
        /// @param title List's title
        /// @param onlyAlive True if you want to show only alive astronauts, false otherwise
        /// @param catchAstronaut True if you want to return the selected astronaut
        /// @return Astronaut's pointer or NULL
        static Astronaut* list(List<Astronaut>* database, string title, bool onlyAlive, bool catchAstronaut);

        /// @return Astronaut's name
        string getName();

        /// @brief Kill the astronaut
        void kill();

        /// @brief Print astronaut's data
        /// @param maxNameWidth Max lenght of an astronaut's name
        /// @param true If you want to print all data, default is false
        void print(long long unsigned int maxNameWidth, bool full = false);
};