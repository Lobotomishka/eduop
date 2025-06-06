#include <iostream>
#include <string>
#include <cstring>
#include <Windows.h>
using namespace std;

const int maxlword = 100;
const int maxlen = 1000;

void init_console()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

int main() {
    init_console();

    char input[maxlen];
    
    string words[maxlword];
    
    int wordCount = 0;
    char* next;
    cout << "Введите строку со словами: ";
    
    cin.getline(input, maxlen);

    char* p = strtok_s(input, " ", &next);
    while (p != nullptr && wordCount < maxlword) {
        words[wordCount++] = string(p);
        p = strtok_s(nullptr, " ", &next);
    }

    cout << "Считанные слова:\n";
    for (int i = 0; i < wordCount; i++) {
        cout << words[i] << endl;
    }

    return 0;
}