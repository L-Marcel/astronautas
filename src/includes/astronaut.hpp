#pragma once
#include "list.hpp"

enum Gener {
    MALE,
    FEMALE,
    OTHER
};

/// @brief Convert a gener to string
/// @param gener the gener
/// @return gener string
string generToString(Gener gener);

enum AstronautFilter {
    ALIVE,
    DEAD,
    ALL
};

enum AstronautSearch {
    NONE,
    NAME,
    CPF,
    AGE
};

class Astronaut {
    private:
        bool alive = true;
        
        string name;
        string cpf;
        Gener gener;
        int age;

        unsigned int expeditions = 0;

        /// @brief Get the max lenght of an astronaut's name
        /// @param database Astronaut database
        /// @return Max lenght of an astronaut's name
        static long long unsigned int getMaxNameWidth(List<Astronaut>* database);

        /// @brief Show the list of astronauts
        /// @param database Astronaut database
        /// @param title List's title
        /// @param filter Filter applied
        /// @param search Search mode
        /// @param searchParam Param used to search (only to show)
        /// @param catchAstronaut True if you want to return the selected astronaut
        /// @param baseDatabase Astronaut database without filter
        /// @return Astronaut's pointer or NULL
        static Astronaut* search(
            List<Astronaut>* database, string title, 
            AstronautFilter filter, AstronautSearch search = NONE,
            string searchParam = "", bool catchAstronaut = true,
            List<Astronaut>* baseDatabase = nullptr
        );
    public:
        /// [LEMBRETE] Se lembrar de mover para privado depois
        bool available = true;

        Astronaut();
        Astronaut(string name, string cpf, Gener gener, int age);
        ~Astronaut();

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

        /// @brief Count the number of alive astronauts
        /// @param database Astronaut database
        /// @return The number of alives
        static unsigned int countAlives(List<Astronaut>* database);

        /// @brief Show the list of astronauts
        /// @param database Astronaut database
        /// @param title List's title
        /// @param filter Filter applied
        /// @param catchAstronaut True if you want to return the selected astronaut
        /// @return Astronaut's pointer or NULL
        static Astronaut* list(
            List<Astronaut>* database, string title, 
            AstronautFilter filter,
            bool catchAstronaut = true
        );

        /// @return Astronaut's name
        string getName();

        /// @return Astronaut's cpf
        string getCpf();

        /// @return Astronaut's age
        int getAge();

        /// @return Astronaut's gener
        Gener getGener();

        /// @return The astronaut's state: available, unavailable or dead
        string getStateAsString();

        /// @return True if astronaut is available, false otherwise
        bool getAvailable();

        /// @brief Kill the astronaut
        void kill();

        /// @brief Change astronaut state to unavailable
        void sendToExpedition();

        /// @brief Change astronaut state to available, if alive
        void returnFromExpedition();

        /// @brief Print astronaut's data
        /// @param maxNameWidth Max lenght of an astronaut's name
        void print(long long unsigned int maxNameWidth);

        /// @brief Show astronaut's page
        void page();
};