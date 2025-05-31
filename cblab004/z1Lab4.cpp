
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
    cout << "������� �����, ���������� ���������: ";
    getline(cin, input);

    // ������������ ���������� ����
    istringstream counter(input);
    string word;
    int wordCount = 0;
    while (counter >> word) {
        wordCount++;
    }

    // ������ ������ ����� ������� �������
    string* words = new string[wordCount];

    // ��������� ������ �������
    istringstream stream(input);
    int index = 0;
    while (stream >> word && index < wordCount) {
        words[index] = word;
        index++;
    }

    // ������� ���������
    //cout << "���������� ����: " << wordCount << endl;
    cout << "����� � �������:" << endl;
    for (int i = 0; i < wordCount; i++)
    {
        cout << i + 1 << " " << words[i] << endl;
        //cout << words[i];
        //if (i != wordCount - 1) {
        //    cout << ", ";
        //}
    }
    cout << endl;

    // ����������� ������
    //delete[] words;

    return 0;
}