#pragma once
#include "expedition.hpp"

class System {
    private:
        List<Astronaut>* astronauts;
        List<Expedition>* expeditions;
        
        /// @brief Restart and update the system
        static void restart();
    public:
        System(List<Astronaut>* astronauts, List<Expedition>* expeditions);

        /// @brief Start menu
        void menu();

        /// @brief Free allocated memories
        void free();

        /// @brief Show astronaut's page
        /// @param astronaut Astronaut's pointer
        /// @param expeditions Expedition's database
        static void astronautPage(Astronaut* astronaut, List<Expedition>* expeditions);

        /// @brief Seed the system with some data
        void seed();
};