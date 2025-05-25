using namespace std;

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#undef min // отменяет определение макроса (для нормальной работы max и windows,h)
#undef max

//static void output(vector <plane> sizif2, int i2)
//{
//    cout << "Номер: " << sizif2[i2].number << endl <<
//        "Пункт назначения: " << sizif2[i2].destination << endl <<
//        "Фамилия: " << sizif2[i2].surname << endl <<
//        "Дата: " << sizif2[i2].date << endl;
//}

void ignore() { cin.ignore(numeric_limits<streamsize>::max(), '\n'); }

int check(int number) //проверка переменных на буквы и другие некорректные символы
{
    setlocale(LC_ALL, "rus");
    bool inputValid = false;

    while (!inputValid)
    {
        if (cin >> number) {
            inputValid = true;
            return number;
        }
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Такой операции нет" << endl;
        }
    }
}

struct plane //структура с данными заявки 
{
    string destination; 
    string number;   
    string surname;     
    string date;    
};

bool check_num(string strok) // проверка строки на цифры
{
    bool flag = true;
    for (int i = 0; i < strok.size(); i++) {
        int u = (int)strok[i];
        if (i == 0) {
            if (u >= 48 && u <= 57 || u == (int)'-') {}
            else { flag = false; }
        }
        else {
            if (u >= 48 && u <= 57) {}
            else { flag = false; }
        }
    }
    return flag;
}

plane addnewapp() //добавить новую заявку
{
    cout << "Введите даннные заявки " << endl;;
    plane bilet2, err;
    cout << "Введите номер: ";
    cin >> bilet2.number;
    ignore();
    cout << "Введите пункт назначения: ";
    cin >> bilet2.destination;
    ignore();
    cout << "Введите фамилию: ";
    cin >> bilet2.surname;
    ignore();
    cout << "Введите дату: ";
    cin >> bilet2.date;
    ignore();
    //if (check_num(bilet2.number) == false)
    //{
    //    cout << "Номер введён некорректно " << endl;
    //    err.number = 2;
    //    return err;
    //}
    //cout << endl <<  bilet2.destination << " " << bilet2.number << " " <<  bilet2.surname << " " << bilet2.date;

    return bilet2;

}

void highlight() //просто выделение 
{
    string hl = "-";
    for (int i = 0; i < 40; i++)
    {
        cout << hl;
    }
    cout << endl;
}

void sealprinzipi(vector <plane> sizeb) //вывести всё
{
    if (sizeb.size() == 0) 
    { 
        highlight();
        cout << "Заявок нет" << endl; 
        highlight();
    }
    else {
        for (int i = 0; i < sizeb.size(); i++)
        {
            highlight();
            cout << "Номер: " << sizeb[i].number << endl <<
                "Пункт назначения: " << sizeb[i].destination << endl <<
                "Фамилия: " << sizeb[i].surname << endl <<
                "Дата: " << sizeb[i].date << endl;
        }
        highlight();
    }
}

void senumbnamdade(vector <plane> sizif, plane s) //найти по номеру и дате заявки
{
    bool flag2 = 0;
    for (int i = 0; i < sizif.size(); i++)
    {
        if (s.date == sizif[i].date && s.number == sizif[i].number)
        {
            highlight();

            cout << "Номер: " << sizif[i].number << endl <<
                "Пункт назначения: " << sizif[i].destination << endl <<
                "Фамилия: " << sizif[i].surname << endl << 
                "Дата: " << sizif[i].date << endl;
            flag2 = 1;
        }
    }
    if (flag2 == 0) 
    {
        highlight();
        cout << "совпадений нет" << endl; 
    }
    highlight();
}


int main()
{
    //system("chcp 1251");
    //setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string opa = "-1";
    int op = stoi(opa);
    cout << "Выберите операцию " << endl <<
        "1 - добавить заявку" << endl <<
        "2 - вывести все заявки" << endl <<
        "3 - вывести все заявки по указанному рейсу" << endl <<
        "4 - удалить заявку" << endl << 
        "5 - завершение программы" << endl;
    vector <plane> bilet;
    do
    {
        //cout << "Операция: ";
        switch (op)
        {
        case -1: {
        cout << "Операция: ";
        //cin >> op;
        op = check(op);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        //if (check_num(opa)) { op = stoi(opa);}
        }break;
        case 1:
        {
            bool fl = false;
            int n = bilet.size();
            bilet.push_back(addnewapp());
            if (check_num(bilet[n].number) == false)
            {
                cout << "Номер введён некорректно" << endl;
                bilet.pop_back();
            }
            else if (check_num(bilet[n].date) == false)
            {
                cout << "Дата введена некорректно" << endl;
                bilet.pop_back();
            }

            for (int i = 0; i < n; i++)
            {
                if ((bilet.back().number == bilet[i].number) && (bilet.back().surname == bilet[i].surname)  && (bilet.back().date == bilet[i].date))
                {
                    fl = true;
                    bilet.pop_back();
                }
            }
            if (fl) { cout << "Такой заявки быть не может" << endl; }
            op = -1;

        }break;
        case 2:
        {
            sealprinzipi(bilet);
            op = -1;
        }break;
        case 3:
        {
            plane numb3;
            cout << "Введите номер: ";
            cin >> numb3.number;
            ignore();
            cout << "Введите дату: ";
            cin >> numb3.date;
            ignore();
            senumbnamdade(bilet, numb3);
            op = -1;
        }break;
        case 4:
        {
            plane base6;
            cout << "Введите данные заявки" << endl;
            cout << "Введите номер: ";
            cin >> base6.number;
            ignore();
            cout << "Введите пункт назначения: ";
            cin >> base6.destination;
            ignore();
            cout << "Введите фамилию: ";
            cin >> base6.surname;
            ignore();
            cout << "Введите дату: ";
            cin >> base6.date;
            ignore();

            bool flag = 1;
            for (int i = 0; i < bilet.size(); i++)
            {
                if (base6.number == bilet[i].number && base6.destination == bilet[i].destination && base6.date == bilet[i].date && base6.surname == bilet[i].surname)
                {
                    bilet.erase(bilet.begin() + i);

                    flag = 0;
                }
            }
            if (flag == 1) { cout << "Такой заявки нет" << endl; }

            op = -1;
        }break;

        default:
            cout << "Такой операции нет" << endl;
            op = -1;
            break;
        }
    }while (op != 5);

}
