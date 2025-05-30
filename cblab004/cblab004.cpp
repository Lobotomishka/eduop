using namespace std;

#include <iostream>
#include <vector>



int main()
{
    setlocale(LC_ALL, "rus");
    const int maxin = 1000;                        // Максимальный размер ввода
    const int maxwc = 100;                               // Максимальное количество слов
    char* nt = nullptr;
    char input[maxin];                             // Буфер для ввода пользователя
    char* words[maxwc];                                 // Массив указателей на слова
    int wordCount = 0;                                  // Счётчик слов

    cout << "Введите слова через пробел: ";
    cin.getline(input, maxin);                     // Считываем всю строку


    char* tk = strtok_s(input, " ", &nt);               // Разбиваем строку на слова с помощью strtok

    while (tk != nullptr && wordCount < maxwc)
    {
        words[wordCount++] = tk;                        // Сохраняем указатель на слово
        tk = strtok_s(nullptr, " ", &nt);               // Продолжаем разбиение
    }
    cout << endl;

    cout << "Введённые слова: ";
    for (int i = 0; i < wordCount; ++i)
    {
        cout << words[i] << " ";
    }
    char pods;
    cout << "Введите подстроку: " << endl;
    cin >> pods;

    cout << "\n\n";
    return 0;

}

