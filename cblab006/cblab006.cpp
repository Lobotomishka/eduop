using namespace std;

#include <iostream>
#include <vector>
#include <ctime>


void output(vector <int> base2)
{
	for (int i : base2)
	{
		cout << i << " ";
	}
	cout << endl;
}

vector <int> fillvec(vector <int> base, int size2)
{
	srand(time(0));
	for (int i = 0; i < size2; i++)
	{
		base.push_back((rand() % 3) - 2);
	}
	return base;
}

vector <int> average(vector <int> base3)
{
	int k = 0, k01 = 0;
	float k0 = 0;
	for (int i : base3) 
	{
		k0 += i;
	}
	k0 /= base3.size();
	k01 = round(k0);
	cout << "Среднее арифметическое: \n" << k0 << " ==> " << k01 << endl;
	cout << "Введите место для среднего арифметического: ";
	cin >> k;
	k--;
	if (k >= base3.size() || k < 0) { cout << "Такого места в векторе нет\n"; base3.clear(); return base3; }
	else{base3[k] = k01;return base3;}
	
}

vector <int> maxdelit(vector <int> base5)
{
	int h = base5[0];
	for (int i : base5)
	{
		if (h <= i)
		{
			h = i;
		}
	}	
	
	//cout << h << endl << endl;

	int i = 0;
	while (i < base5.size())
	{
		if (h == base5[i])
		{
			base5.erase(base5.begin() + i);
		}
		else
		{
			i++;
		}
	}
	return base5;
	//int fl = 0;
	//for (int i : base5)
	//{
	//	if (base5[0] == i) { fl++; }
	//}
	//if (fl == base5.size())
	//{
	//	base5.clear();
	//	return base5;
	//}
	//else
	//{
		//for (int i : base5)
		//{
		//	//cout << " (" << i << ") ";
		//	if (h == i) //&& i == 0)
		//	{
		//		for (int i2 = 0; i2 < base5.size(); i2++)
		//		{
		//			if (base5[i] == i) { base5.erase(base5.begin() + i2); break; }
		//		}
		//		
		//	}
		//	//else if (h == base5[i])
		//	//{
		//	//	base5.erase(base5.begin() + i);
		//	//}
		//}
		//return base5;
	//}
}

int main()
{
	setlocale(LC_ALL, "rus");
	int size;
	cout << "Введите размер вектора: ";
	cin >> size;
	vector <int> base;

	base = fillvec(base, size); // заполнение вектора
	output(base); // вывод
	base = average(base);
	if (base.size() == 0) { return 0; }
	output(base);
	base = maxdelit(base);
	output(base);


}