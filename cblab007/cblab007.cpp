using namespace std;

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

struct lapdata			//модель, габаритные размеры (диагональ, толщина), вес, цена
{
	string model;
	string dia;
	string diap;
	string mass;
	string massp;
	string wig;
	string wigp;
	string prize;
	string prizep;
	
};

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
			"Диагональ: " << laptops[fp].dia << " " << laptops[fp].diap << endl <<
			"Толщина: " << laptops[fp].wig << " " << laptops[fp].wigp << endl <<
			"Вес: " << laptops[fp].mass  << " " << laptops[fp].massp << endl <<
			"Цена: " << laptops[fp].prize << " " <<  laptops[fp].prizep << endl;
	}
	hl();
}

void seel2(vector <string> laptops, int fp, int sp)
{
	for (int i = 0; i <  laptops.size(); i++)
	{
		cout << laptops[i] << " ";
		if ((i + 1) % 9 == 0)
		{
			cout << endl;
		}
	}
	//hl();
}
//bool findonpr(vector <lapdata> laptops, string model2, int i)
//{
//	bool fl = false;
//	//cout << "Введите название производителя: ";
//	string model3;
//	//cin >> model2;
//	//cin.ignore(numeric_limits<streamsize>::max(), '\n');
//	char sd = '_';
//	//for (int i = 0; i < laptops.size(); i++)
//	//{
//	size_t pos = laptops[i].model.find(sd);
//	if (pos != string::npos)
//	{
//		model3 = laptops[i].model.substr(0, pos);
//	}
//	if (model3 == model2)
//	{
//		seel(laptops, i, i + 1);
//		fl = true;
//	}
//	//}
//	if (fl == false) { return fl; }
//}


void findothers(vector <lapdata> laptops, int parop)
{
	bool fl2 = false;
	cout << "Значеие: ";
	string param;
	cin >> param;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int i = 0; i < laptops.size(); i++)
	{
		switch (parop)
		{
		case(1):
		{
			string model3;
			char sd = '_';
			size_t pos = laptops[i].model.find(sd);
			if (pos != string::npos)
			{
				model3 = laptops[i].model.substr(0, pos);
			}
			if (model3 == param)
			{
				seel(laptops, i, i + 1);
				fl2 = true;
			}
		}break;
		case(2):
		{
			if (param == laptops[i].dia)
			{
				seel(laptops, i, i + 1);
				fl2 = true;
			}
		}break;
		case(3):		
		{
			if (param == laptops[i].wig)
			{
				seel(laptops, i, i + 1);
				fl2 = true;
			}
		}break;

		case(4):
		{
			if (param == laptops[i].mass)
			{
				seel(laptops, i, i + 1);
				fl2 = true;
			}
		}break;
		case(5):
		{
			if (param == laptops[i].prize)
			{
				seel(laptops, i, i + 1);
				fl2 = true;
			}
		}break;
		default:
			cout << "такой операции нет" << endl;
			break;
		}
	}
	if (fl2 == false) { cout << "такой модели нет" << endl; }
}

//void findonpr(vector <lapdata> laptops)
//{
//	bool fl = false;
//	cout << "Введите название производителя: ";
//	string model2, model3;
//	cin >> model2;
//	cin.ignore(numeric_limits<streamsize>::max(), '\n');
//	char sd = '_';
//	for (int i = 0; i < laptops.size(); i++)
//	{
//		size_t pos = laptops[i].model.find(sd);
//		if (pos != string::npos)
//		{
//			 model3 = laptops[i].model.substr(0, pos);
//		}
//		if (model3 == model2)
//		{
//			seel(laptops, i, i+1);
//			fl = true;
//		}
//	}
//	if (fl == false) { cout << "Такой модели нет" << endl; }
//}

int main()
{
	setlocale(LC_ALL, "rus");
	int op = 0;
	cout << "Введите номер задания (1, 2): ";
	op = check(op);
	switch (op)
	{
	case(1):
	{
		setlocale(LC_ALL, "rus");
		string line = "Laptopdata.txt";
		vector <lapdata> laptops;

		ifstream ind(line);
		if (!ind.is_open()) {
			cout << "Ошибка открытия файла!" << endl;
			return 1;
		}

		string a1, a2, a3, a4, a5, a6, a7, a8, a9;

		while (ind >> a1 >> a2 >> a3 >> a4 >> a5 >> a6 >> a7 >> a8 >> a9)
		{
			lapdata line2 = { a1, a2, a3, a4, a5, a6, a7, a8, a9};
			laptops.push_back(line2);
		}

		int op = 0;

		cout << "Введите операцию: " << endl <<
			"1 - вывести все модели" << endl <<
			"2 - поиск ноутбука по модели" << endl <<
			"3 - завершение программы" << endl;
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
				int op2 = 0;
				cout << "Введите параметр поиска" << endl
					<< "По производителю - 1" << endl
					<< "По диагонали - 2" << endl
					<< "По толщине - 3" << endl
					<< "По весу - 4" << endl
					<< "По цене - 5" << endl;
				cout << "Тип параметра: ";
				op2 = check(op2);
				findothers(laptops, op2);
			}break;
			default:
				if (op != 3) { cout << "такой операции нет " << endl; }
				break;
			}
		} while (op != 3);
	}break;
	case(2):
	{
		vector <string> laprevers;
		ifstream ind("Laptopdata.txt");
		if (!ind.is_open()) {
			cout << "Ошибка открытия файла!" << endl;
			return 1;
		}

		string word;

		while (ind >> word)
		{
			laprevers.push_back(word);
		}
		ind.close();
		seel2(laprevers, 0, laprevers.size());
		
		cout << "\n\n\n";

		vector <string> laprev2 (laprevers.rbegin(), laprevers.rend());
		seel2(laprev2, 0, laprevers.size());

		ofstream ind2("Laptopdatareverse");
		if (!ind2.is_open()) {
			cout << "Ошибка открытия файла!" << endl;
			return 1;
		}
		int i2 = 0;
		for (string i : laprev2)
		{
			ind2 << i << " ";
			i2++;
			if (i2 % 9 == 0) { ind2 << endl; }
			
		}
		ind2.close();
	}
	default:
		break;
	}

	

}

