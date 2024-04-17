#pragma once
#include "utils.h"
#include <functional>

template <typename T>
class List
{
private:
    unsigned int qtd;
    T **items;

public:
    List();

    /// @brief Add an item in the current list
    /// @param item Item's pointer
    void add(T *item);

    /// @brief Orderer the list
    /// @param compare The function used to compare the items
    void sort(function<bool(T *, T *)> compare);

    /// @brief Filter the list
    /// @param condition The filter condition function
    /// @return A new list, but filtered
    List<T> filter(function<bool(T *)> condition);

    /// @brief Gets an item by index
    /// @param index Item's index
    /// @return Item's pointer
    T *get(unsigned int index);

    /// @brief Gets an item's index
    /// @param item Item's pointer
    /// @return The index, if the item exists, throw an error otherwise
    unsigned int getIndex(T *item);

    /// @brief Find an item if exists
    /// @param search Function to search
    /// @return Item's pointer if exists, NULL otherwise
    T *find(function<bool(T *)> search);

    /// @brief Check if an item exists
    /// @param compare Funciton to compare
    /// @return True if exists, false otherwise
    bool exists(function<bool(T *)> compare);

    /// @brief Check if an item exists
    /// @param check Funciton to check
    /// @return True if all pass in check, false otherwise
    bool all(function<bool(T *)> compare);

    /// @brief Remove an item in the current list
    /// @param index Item's index
    void remove(unsigned int index);

    /// @return Amount of items in list
    unsigned int getAmount();
};