#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

struct baggage
{
	wstring last_name;
	int race_number;
	wstring date;
	int count;
	float weight;
};

int main()
{
	std::locale consoleLoc("ru-RU.chcp1252");
	wcout.imbue(consoleLoc);
	std::locale fileLocale("ru-RU.UTF-8");

	// reading data

	vector<wstring> surnames;
	vector<float> weights_of_all;

	wifstream ifs;
	try
	{
		ifs.open("Input.txt");
		if (!ifs.is_open())
		{
			cerr << "Unable to open file\n";
			exit(1);
		}
		ifs.imbue(fileLocale);

		while (!ifs.eof())
		{
			baggage bag;
			wstring line;
			getline(ifs, line);
			wchar_t* context;
			wchar_t *pch = wcstok_s((wchar_t*)line.c_str(), L" ", &context);
			bag.last_name = pch;
			bag.race_number = _wtoi(wcstok_s(NULL, L" ", &context));
			bag.date = wcstok_s(NULL, L" ", &context);
			bag.count = _wtoi(wcstok_s(NULL, L" ", &context));
			bag.weight = _wtof(wcstok_s(NULL, L" ", &context));

			if (bag.count == 1 && bag.weight > 30)
				surnames.push_back(bag.last_name);

			weights_of_all.push_back(bag.weight);
		}
	}
	catch (exception)
	{
		ifs.close();
	}

	float avg_weight = accumulate(weights_of_all.begin(), weights_of_all.end(), 0.0) / weights_of_all.size();

	// print out results

	wofstream fout;
	try
	{
		fout.open("out.txt");
		fout.imbue(fileLocale);
		if (!fout.is_open())
		{
			cerr << "Unable to open file\n";
			exit(1);
		}
		else
		{
			fout << L"Passengers with a single bag with weight > 30:" << endl;
			for_each(surnames.begin(), surnames.end(), [&](wstring &surname) { fout << surname << endl; });
			fout << endl;
			fout << L"Average baggages weight is: " << avg_weight;
		}
	}
	catch(exception)
	{
		cerr << "Unable to open file\n";
		fout.close();
	}

	cout << "Success!";
}