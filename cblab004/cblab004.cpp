#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;


void init_console()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

int main() {
    init_console();
    cout << "Введите строку: ";
    string input;
    getline(cin, input); // Считываем всю строку

    //  Подсчет количества слов
    int wordCount = 0;
    bool inWord = false;
    for (char c : input) {
        if (c == ' ') {
            if (inWord) {
                inWord = false;
            }
        }
        else {
            if (!inWord) {
                wordCount++;
                inWord = true;
            }
        }
    }

    // Если слов нет, завершаем программу
    if (wordCount == 0) {
        cout << "Пустая строка" << endl;
        return 0;
    }

    //  Создаем динамический массив для хранения слов
    string* words = new string[wordCount];

    // Извлекаем слова и сохраняем в массив
    int index = 0;
    size_t start = 0;
    size_t end = 0;
    size_t len = input.length();

    while (start < len && index < wordCount) {
        // Пропускаем пробелы
        while (start < len && input[start] == ' ') {
            start++;
        }

        // Находим конец слова
        end = start;
        while (end < len && input[end] != ' ') {
            end++;
        }

        // Извлекаем слово и сохраняем
        words[index++] = input.substr(start, end - start);

        // Переходим к следующей позиции
        start = end + 1;
    }

    //  Выводим результат
    cout << "Слов в массиве: " << wordCount << endl;
    for (int i = 0; i < wordCount; i++) {
        cout << words[i] << endl;
    }
}