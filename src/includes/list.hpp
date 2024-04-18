#include "utils.hpp"
#include <functional>

template <typename T>
class List {
    private:
        unsigned int qtd = 0;
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

        /// @brief Free all allocated memories
        void free();

        /// @brief Free the list allocation
        void clear();
};

template <typename T> List<T>::List() {
    this->qtd = 0;
    this->items = new T*[0];
};

template <typename T> void List<T>::add(T* item) {
    this->qtd++;
    T** items = new T*[qtd];
    for(unsigned i = 0; i < qtd - 1; i++) {
        items[i] = this->items[i];
    };

    delete[] this->items;
    items[this->qtd - 1] = item;

    this->items = items;
};

template <typename T> void List<T>::sort(function<bool(T*, T*)> compare) {
    std::sort(this->items, this->items + this->qtd, compare);
};

template <typename T> List<T> List<T>::filter(function<bool(T*)> condition) {
    List<T> filteredList;

    for(unsigned int i = 0; i < this->qtd; i++) {
        T* item = this->items[i];

        if(condition(item)) filteredList.add(item);
    };

    return filteredList;
};

template <typename T> unsigned int List<T>::getIndex(T* item) {
    for(unsigned int i = 0; i < this->qtd; i++) {
        if(this->items[i] == item) return i;
    }; 

    throw (-1);
};

template <typename T> T* List<T>::get(unsigned int index) {
    if(index > this->qtd - 1) return nullptr;
    return this->items[index];
};

template <typename T> void List<T>::remove(unsigned int index) {
    if(index > this->qtd - 1) return;
    
    this->qtd--;
    T** items = new T*[this->qtd];
    
    if(this->qtd > 0) {
        int gap = 0;
        for(unsigned int i = 0; i < this->qtd; i++) {
            if(i == index) gap++;
            items[i] = this->items[i + gap];
        };
    };

    delete[] this->items;
    this->items = items;
};

template <typename T> unsigned int List<T>::getAmount() {
    return this->qtd;
};

template <typename T> T* List<T>::find(function<bool(T*)> search) {
    for(unsigned int i = 0; i < this->qtd; i++) {
        if(search(this->items[i])) {
            return this->items[i];
        };
    };

    return nullptr;
};

template <typename T> bool List<T>::exists(function<bool(T*)> compare) {
    for(unsigned int i = 0; i < this->qtd; i++) {
        if(compare(this->items[i])) {
            return true;
        };
    };

    return false;
};

template <typename T> bool List<T>::all(function<bool(T*)> check) {
    for(unsigned int i = 0; i < this->qtd; i++) {
        if(!check(this->items[i])) {
            return false;
        };
    };

    return true;
};

template <typename T> void List<T>::clear() {
    this->qtd = 0;
    if(this->items != nullptr) {
        delete[] this->items;
        this->items = nullptr;
    };
};

template <typename T> void List<T>::free() {
    for(unsigned int i = 0; i < this->qtd; i++) {
        if(this->items[i] != nullptr) {
            delete this->items[i];
            this->items[i] = nullptr;
        };
    };

    this->clear();
};