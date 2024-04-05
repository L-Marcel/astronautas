#include <iostream>

using namespace std;

string trim(string text) {
    long long unsigned int begin = 0;
    for(long long unsigned int i = 0; i < text.length(); i++) {
        if(!isspace(text[i])) break;
        begin++;
    };

    long long unsigned int end = text.length() - begin;
    for(long long unsigned int i = end - 1; i > begin; i--) {
        if(!isspace(text[i])) break;
        end++;
    };

    return text.substr(begin, end);
};

void clear() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
};