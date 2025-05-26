using namespace std;

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

struct lapdata			//модель, габаритные размеры (диагональ, толщина), вес, цена
{
	string model;
	float dia;
	float wig;
	float mass;
	float prize;
	
};

int check(int number) //проверка переменных на буквы и другие некорректные символы
{
	setlocale(LC_ALL, "rus");
	bool inputValid = false;

	do
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
	} while (!inputValid);
}

void hl()
{
	for (int i = 0; i < 25; i++)
	{
		cout << "-";
	}
	cout << endl;
}

void seel(vector <lapdata> laptops, int fp, int sp)
{
	for (fp; fp < sp; fp++)
	{
		hl();
		cout << laptops[fp].model << endl <<
				laptops[fp].dia << "''" << endl <<
				laptops[fp].wig << " см." << endl <<
				laptops[fp].mass << " кг." << endl <<
				laptops[fp].prize << " р." << endl;
	}
	hl();
}

void findonpr(vector <lapdata> laptops)
{
	bool fl = false;
	cout << "Введите название производителя: ";
	string model2, model3;
	cin >> model2;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	char sd = '_';
	for (int i = 0; i < laptops.size(); i++)
	{
		size_t pos = laptops[i].model.find(sd);
		if (pos != string::npos)
		{
			 model3 = laptops[i].model.substr(0, pos);
		}
		if (model3 == model2)
		{
			seel(laptops, i, i+1);
			fl = true;
		}
	}
	if (fl == false) { cout << "Такой модели нет" << endl; }
	
}

int main()
{
	setlocale(LC_ALL, "rus");
	string line = "Laptopdata.txt";
	vector <lapdata> laptops;
	
	ifstream ind(line);
	if (!ind.is_open()) {
		cout << "Ошибка открытия файла!" << endl;
		return 1;
	}

	string a1, a2, a3, a4, a5;

	while (ind >> a1 >> a2 >> a3 >> a4 >> a5)
	{
		lapdata line2 = { a1, stof(a2), stof(a3), stof(a4), stof(a5) };
		laptops.push_back(line2);
	}

	int op = 0;

	cout << "Введите операцию: " << endl <<
		"1 - вывести все модели" << endl <<
		"2 - поиск ноутбука по модели" << endl;
	do
	{
		cout << "Операция: ";
		op = check(op);
		switch (op)
		{
		case(1):
		{
			seel(laptops, 0, laptops.size());
			break;
		}
		case(2):
		{
			findonpr(laptops);
			break;
		}
		default:
			if(op != 4){cout << "такой операции нет " << endl;}
			break;
		}
	}while (op != 4);
	

}

