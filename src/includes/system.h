#pragma once
#include "expedition.h"

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

        /// @brief Astronaut's page
        void astronautPage();
};