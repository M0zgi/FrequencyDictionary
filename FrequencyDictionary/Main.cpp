#include<iostream>
#include<fstream>
#include<exception>
#include<Windows.h>
#include<string>
#include<set>
#include<map>
#include<algorithm>
#include<iomanip>

using namespace std;

int main()
{

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string fName = "text.txt"; // имя файла для считывания исходного текста
	string fName2 = "formated_dictionary.txt"; // имя файла для сохранения форматированного текста
	string fName3 = "frequency_dictionary.txt"; // имя файла для сохранения форматированного текста + кол-ва его повторения

	string str;
	
	pair <string, int> p;

	fstream fs;
	fs.exceptions(fstream::badbit | fstream::failbit);

	multiset <string> mset;
	map<string, int> mp;
	
	int count = 0;

	const char symbols[] = { '\"','.', ';', ':', '!', ',', ')', '(',  '&', '?', '"', '«', '»', '\0'};	

	try
	{
		fs.open(fName, fstream::in | fstream::out | fstream::app);

		while (!fs.eof())
		{
			str = "";

			fs >> str;

			for (size_t i = 0; i < strlen(symbols); ++i)
			{
				str.erase(remove(str.begin(), str.end(), symbols[i]), str.end());
			}

			mset.emplace(str);

			++mp[str];
		}

		fs.close();
	}
	catch (const fstream::failure & ex)
	{
		cout << ex.code();
	}
	
	try
	{
		fs.open(fName3, fstream::in | fstream::out);

		cout << " +--------------------+--------+\n";

		cout << " |        Слово       | Кол-во |\n";

		cout << " +--------------------+--------+\n";

		for (auto& item : mp)
		{
			auto it = item.first.size();

			if (it > 2)
			{
				if (p.second < item.second)
				{
					p.first = item.first;
					p.second = item.second;
				}
			}

				fs << item.first << " " << item.second << "\n";

			cout << left << " |" << setw(20) << item.first << "| " << setw(5) << item.second << "  | " << endl;
			cout << " +--------------------+--------+\n";
		}

		fs.close();
	}

	catch (const fstream::failure& ex)
	{
		cout << ex.code();
	}
	
	cout << endl << endl;
	cout << "Наиболее часто встречающееся слово: " << p.first << " - " << p.second << " раз(а)." << endl;		

	try
	{		
		fs.open(fName2, fstream::in | fstream::out);

		for (auto& item : mset)
		{
			fs << item << "\n";
		}

		fs.close();
	}

	catch (const fstream::failure& ex)
	{
		cout << ex.code();
	}	

	cout << endl;
	system("pause");
}