#include <iostream>
#include <cstring>
#include <clocale>
#include <Windows.h>
#include <vector>
#include <sstream>
#include <string>

#undef min
#undef max

using namespace std;

int check(int number)		//проверка переменных на буквы и другие некорректные символы
{
    setlocale(LC_ALL, "rus");
    bool inputValid = false;

    do
    {
        if (cin >> number) {
            inputValid = true;
            return number;
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Такой операции нет" << endl;
        }
    } while (!inputValid);
}


void init_console() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

// проверка содержит ли слово все символы подстроки
bool contains_all_chars(const char* word, const char* substr) {
    for (size_t i = 0; substr[i] != '\0'; ++i) {
        bool found = false;
        for (size_t j = 0; word[j] != '\0'; ++j) {
            if (substr[i] == word[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

// Проверка содержит ли слово подстроку
bool contains_substring(const char* word, const char* substr) {
    return strstr(word, substr) != nullptr;
}

// Возврат новой строки с подходящ словами по условию 
char* filter_words(const char* text, const char* substr) {
    const size_t MAX_WORDS = 100;
    const size_t MAX_WORD_LEN = 100;

    char words[MAX_WORDS][MAX_WORD_LEN];
    size_t word_count = 0;

    // Разбиваем строку на слова
    char* text_copy = new char[strlen(text) + 1];
    strcpy_s(text_copy, strlen(text) + 1, text);

    char* next_token = nullptr;
    char* token = strtok_s(text_copy, " ", &next_token);
    while (token != nullptr && word_count < MAX_WORDS) {
        if (contains_all_chars(token, substr)) {
            strcpy_s(words[word_count], MAX_WORD_LEN, token);
            word_count++;
        }
        token = strtok_s(nullptr, " ", &next_token);
    }
    delete[] text_copy;

    // Собираем результат
    if (word_count == 0) {
        return nullptr;
    }

    size_t total_len = 0;
    for (size_t i = 0; i < word_count; ++i) {
        total_len += strlen(words[i]) + 1; // +1  для пробела
    }

    char* result = new char[total_len];
    result[0] = '\0';

    for (size_t i = 0; i < word_count; ++i) {
        strcat_s(result, total_len, words[i]);
        if (i != word_count - 1) {
            strcat_s(result, total_len, " ");
        }
    }

    return result;
}

// перемещение первого слова с подстрокой в начало
void move_substring_word_to_front(char* text, const char* substr) {
    const size_t MAX_WORDS = 100;
    const size_t MAX_WORD_LEN = 100;
    const size_t MAX_TEXT_LEN = 1000;

    char words[MAX_WORDS][MAX_WORD_LEN];
    size_t word_count = 0;
    size_t match_index = MAX_WORDS;

    //  строку на слова
    char* text_copy = new char[strlen(text) + 1];
    strcpy_s(text_copy, strlen(text) + 1, text);

    char* next_token = nullptr;
    char* token = strtok_s(text_copy, " ", &next_token);
    while (token != nullptr && word_count < MAX_WORDS) {
        if (match_index == MAX_WORDS && contains_substring(token, substr)) {
            match_index = word_count;
        }
        strcpy_s(words[word_count], MAX_WORD_LEN, token);
        word_count++;
        token = strtok_s(nullptr, " ", &next_token);
    }
    delete[] text_copy;

    if (match_index == MAX_WORDS) {
        return; // Если не нашли подходящего слова
    }

    // Сбор всех результатов
    strcpy_s(text, MAX_TEXT_LEN, words[match_index]);
    strcat_s(text, MAX_TEXT_LEN, " ");

    for (size_t i = 0; i < word_count; ++i) {
        if (i != match_index) {
            strcat_s(text, MAX_TEXT_LEN, words[i]);
            strcat_s(text, MAX_TEXT_LEN, " ");
        }
    }

    // Удаление последнегопробела
    text[strlen(text) - 1] = '\0';
}

// Функция для вывода массива слов
void printWords(const vector<string>& words) {
    cout << "Количество слов: " << words.size() << endl;
    cout << "Слова:" << endl;
    for (size_t i = 0; i < words.size(); i++) {
        cout << i + 1 << ". \"" << words[i] << "\"" << endl;
    }
}


// Функция для разбиения строки вручную (без использования stringstream)
vector<string> splitStringManual(const string& str) {
    vector<string> words;
    string currentWord = "";

    for (size_t i = 0; i < str.length(); i++) {
        // Если символ не пробел, добавляем к текущему слову
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n') {
            currentWord += str[i];
        }
        // Если встретили разделитель и слово не пустое
        else if (!currentWord.empty()) {
            words.push_back(currentWord);
            currentWord = "";
        }
    }

    // Добавляем последнее слово, если оно не пустое
    if (!currentWord.empty()) {
        words.push_back(currentWord);
    }

    return words;
}

int main() {
    init_console();
    int op = 0;
    cout << "Введите задание (1 или 2): ";
    op = check(op);
    switch (op)
    {
    case(1):
    {
        const size_t MAX_INPUT = 1000;
        char text[MAX_INPUT];
        char substr[MAX_INPUT];

        cout << "Введите строку: ";
        cin.getline(text, MAX_INPUT);

        cout << "Введите подстроку: ";
        cin.getline(substr, MAX_INPUT);

        // Фильтр слов
        char* filtered = filter_words(text, substr);
        if (filtered != nullptr) {
            cout << "Слова, содержащие все символы подстроки: " << filtered << endl;
            delete[] filtered;
        }
        else {
            cout << "Нет подходящих слов." << endl;
        }

        // Смещение первого подходящего вначало
        move_substring_word_to_front(text, substr);
        cout << "Результат после перемещения: " << text << endl;

        return 0;
    }break;
    case(2):
    {
        setlocale(LC_ALL, "rus");
        string inputString;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Введите строку для разбиения на слова: ";
        getline(cin, inputString);


        cout << "\nразбиение: " << endl;
        vector<string> words3 = splitStringManual(inputString);
        printWords(words3);

        return 0;
    }break;
    default:
        break;
    }
 
}