
#include <iostream>
#include <string>
#include <sstream>
#include <Windows.h>

using namespace std;

void init_console()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

int main()
{
    init_console();
    string input;
    cout << "Введите слова, разделённые пробелами: ";
    getline(cin, input);

    // Подсчитываем количество слов
    istringstream counter(input);
    string word;
    int wordCount = 0;
    while (counter >> word) {
        wordCount++;
    }

    // Создаём массив строк нужного размера
    string* words = new string[wordCount];

    // Заполняем массив словами
    istringstream stream(input);
    int index = 0;
    while (stream >> word && index < wordCount) {
        words[index] = word;
        index++;
    }

    // Выводим результат
    //cout << "Количество слов: " << wordCount << endl;
    cout << "Слова в массиве:" << endl;
    for (int i = 0; i < wordCount; i++)
    {
        cout << i + 1 << " " << words[i] << endl;
        //cout << words[i];
        //if (i != wordCount - 1) {
        //    cout << ", ";
        //}
    }
    cout << endl;

    // Освобождаем память
    //delete[] words;

    return 0;
}