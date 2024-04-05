#include "includes/utils.h"

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

string lower(string text) {
    for(unsigned int i = 0; i < text.length(); i++) {
        text[i] = tolower(text[i]);
    };

    return text;
};

string capitalize(string text) {
    for(unsigned int i = 0; i < text.length(); i++) {
        if(i == 0 || iswspace(text[i-1])) text[i] = toupper(text[i]);
        else text[i] = tolower(text[i]); 
    };

    return text;
};

string toCpf(string text) {
    return text.substr(0,3) + "." + text.substr(3,3) + "." + text.substr(6,3) + "-" + text.substr(9,2);
};

bool isCpf(string text) {
    regex rx("([0-9]{3}).([0-9]{3}).([0-9]{3})-([0-9]{2})");
    return regex_match(text.begin(), text.end(), rx) && text.length() == 14;
};

void clear() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
};

char input(string text) {
    cout << text;
    while(true) {
        if(kbhit()) return getch();
    };
};