#pragma once
#include "utils.h"

template <typename T> class List {
    private:
        unsigned int qtd;
        T** items;
    public:
        List();
        
        /// @brief Add an item in the current list
        /// @param item item's pointer
        void add(T* item);

        /// @brief Gets an item by index
        /// @param index item's index
        /// @return item's pointer
        T* get(unsigned int index);

        /// @brief Remove an item in the current list
        /// @param index item's index
        void remove(unsigned int index);

        /// @return Amount of items in list
        unsigned int getAmount();
};