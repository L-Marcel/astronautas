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

string codeToString(int code) {
    string result = "";
    
    int steps = 0;
    int rest = 0;
    do {
        steps++;
        rest = code % 10;
        result = to_string(rest) + result;
        code -= rest;
        code /= 10;
    } while(code > 0);

    while(steps < 3) {
        steps++;
        result = "0" + result;
    };

    return result;
};

string toCpf(string text) {
    string result = "";

    long long unsigned int gap = 0;
    short int points = 2;
    bool skip = false;
    for(long long unsigned int i = 0; i < text.length(); i++) {
        if(result.length() == 14) break;

        char divisor = points > 0? '.':'-';

        if(i % 3 == gap && i > 0 && !skip) {
            if(text[i] != divisor) {
                points--;
                result += divisor;
                i--;
                skip = true;
                continue;
            } else {
                points--;
                skip = true;
                gap++;
                result += text[i];
                continue;
            };
        };
       
        skip = false;

        if(text[i] < '0' || text[i] > '9') break;

        result += text[i];
    };

    return result;
};

bool isCpf(string text) {
    regex rx("([0-9]{3}).([0-9]{3}).([0-9]{3})-([0-9]{2})");
    return regex_match(text.begin(), text.end(), rx) && text.length() == 14;
};

void clearTerminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
};

#ifndef _WIN32
int linux_getch(){
  struct termios oldattr, newattr;
  unsigned char ch;
  int retcode;
  tcgetattr(STDIN_FILENO, &oldattr);
  newattr=oldattr;
  newattr.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
  retcode=read(STDIN_FILENO, &ch, 1);
  tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
  return retcode<=0? EOF: (int)ch;
};
#endif

char input(string text) {
    cout << text;

    #ifdef _WIN32
        while(true) {
            if(kbhit()) return getch();
        };
    #else
        while(true) {
            int ch = linux_getch();
            if(ch != EOF) {
                return ch;
            };
        };
    #endif
};

char getChar() {
    char result;

    do {
        result = getchar();
    } while(result == '\n');

    return result;
};

string getLine() {
    string result;

    while(getline(cin, result)) {
        if(result != "") break;
    };

    return result;
};