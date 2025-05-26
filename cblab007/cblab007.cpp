using namespace std;

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

struct lapdata			//модель, габаритные размеры (диагональ, толщина), вес, цена
{
	string model;
	struct dimensions
	{
		string wig;
		string dia;
	};
	string mass;
	string prize;
	
};

void seel(vector <lapdata> laptops)
{
	for (int i = 0; i < laptops.size(); i++)
	{
		cout << laptops[i].model;
	}
}

int main()
{
	string line = "Laptopdata.txt";
	vector <lapdata> laptops;

	ifstream ind(line);
	if(ind.is_open())
	{
		string k;
		int i = 0;
		while(ind >> k)
		{
			laptops[i].model = k;
			i++;
		}
		ind.close();

		
	}


	//if (ind.is_open())
	//{
	//	while (getline(ind, line))
	//	{
	//		laptops.push_back(ind);
	//		cout << line << endl;
	//	}
	//}
	//ind.close();
	//cout << laptops[0].model << endl;
}

