#include "includes/list.h"

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
    if(index > this->qtd - 1) return NULL;
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

    return NULL;
};

template <typename T> bool List<T>::exists(function<bool(T*)> compare) {
    for(unsigned int i = 0; i < this->qtd; i++) {
        if(compare(this->items[i])) {
            return true;
        };
    };

    return false;
};


class Astronaut;
class Expedition;

template class List<Astronaut>;
template class List<Expedition>;