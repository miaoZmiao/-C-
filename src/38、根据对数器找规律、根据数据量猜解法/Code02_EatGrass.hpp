#pragma once
#ifndef Code02_EatGrass_HPP
#define Code02_EatGrass_HPP
#include <vector>
#include "utility_func.hpp"
#include <string>
#include <iostream>

namespace Code02_EatGrass {

	std::string whoWin(int N)
	{
		if (N < 5)
		{
			return (N == 0 || N == 2) ? "����" : "����";
		}

		int want = 1;
		while (want <= N)
		{
			if (whoWin(N - want) == "����")
			{
				return "����";
			}
			if (want <= N / 4)
			{
				want = want * 4;
			}
			else
			{
				break;
			}
		}

		return "����";
	}

	string smartWhoWin(int n)
	{
		if (n < 5)
		{
			return (n == 0 || n == 2) ? "����" : "����";
		}
		int rem = (n - 4) % 5;
		if (rem == 1 || rem == 3)
		{
			return "����";
		}
		return "����";
	}

}



void test_Code02_EatGrass() {
	cout << "test_Code02_EatGrass begin" << endl;
	for (int i = 1; i < 50; i++)
	{
		cout << i << ",	" << Code02_EatGrass::whoWin(i)<<",	"<< Code02_EatGrass::smartWhoWin(i)<< endl;
	}
	cout << "test_Code02_EatGrass end" << endl;
}

#endif