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

void hl()
{
	for (int i = 0; i < 25; i++)
	{
		cout << "-";
	}
	cout << endl;
}

void seel(vector <lapdata> laptops)
{
	for (int i = 0; i < laptops.size(); i++)
	{
		hl();
		cout << laptops[i].model << endl <<
			laptops[i].dia << "''" << endl <<
			laptops[i].wig << " см." << endl <<
			laptops[i].mass << " кг." << endl <<
			laptops[i].prize << " р." << endl;
	}
	hl();
}

void findonpr(vector <lapdata> laptops)
{
	cout << "Введите название производителя: " << endl;
	string model2;
	cin >> model2;
	char sd = '_';
	for (int i = 0; i < laptops.size(); i++)
	{
		size_t pos = laptops[i].model.find(sd);
		if (pos != string::npos)
		{

		}
	}
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
		cin >> op;
		switch (op)
		{
		case(1):
		{
			seel(laptops);
			break;
		}
		case(2):
		{

		}
		default:
			cout << "такой операции нет " << endl;
			break;
		}
	}while (op != 4);
	

}

