#pragma once


#include "utility_func.hpp"
#include <stack>
namespace Code02_EvenTimesOddTimes {

	int find_odd_number(vector<int> & arr)
	{
		int eor = 0;

		for (auto ele : arr)
		{
			eor = eor ^ ele;
		}
		cout << eor << endl;
		return eor;
	}

	// ���ɣ� ��int�����������Ҳ��1��ȡ���������ã�

	int right_most_1(int num)
	{
		int ret = 0;
		ret = num & (~num + 1);
		return ret;
	}

	void printbinary(int num)
	{
		unsigned int tmp = num;
		stack<short> tmpst;
		while (tmp != 0)
		{
			if (tmp % 2)
			{
				tmpst.push(1);
			}
			else
			{
				tmpst.push(0);
			}
			tmp = tmp >> 1;
		}

		// print
		cout << endl;
		cout << "\t";
		int pop_num = 0;
		while (!tmpst.empty())
		{
			auto ele = tmpst.top();
			cout << ele;
			tmpst.pop();
			pop_num++;
			if (pop_num == 4)
			{
				cout << " ";
				pop_num = 0;
			}

		}
		cout << endl;
	}

	// �������ֳ����������Σ�������������ż����
	// Ҫ��ռ�O(1), ʱ��O(N)

	int find_odd_a_b_number(vector<int>& arr)
	{
		int eor = 0;
		for (auto it : arr)
		{
			eor = eor ^ it;
		}

		int rightmost_1 = eor & (~eor + 1);

		int a_ = 0;

		for (auto it : arr)
		{
			if ((rightmost_1 & it) != 0)
			{
				a_ = a_ ^ it;
			}
		}

		cout << "a : " << a_ << endl;
		cout << "b : " << (a_ ^ eor) << endl;


		return 0;
	}

}

void test_Code02_EvenTimesOddTimes() {
	cout << "Code02_EvenTimesOddTimes begin" << endl;
	int a = 5;
	int b = 7;

	a = a ^ b;
	b = a ^ b;
	a = a ^ b;

	cout << (a) << endl;
	cout<<(b) << endl;

	vector<int> arr1 = { 3, 3, 2, 3, 1, 1, 1, 3, 1, 1, 1 };
	Code02_EvenTimesOddTimes::find_odd_number(arr1);

	vector<int> arr2 = { 4, 3, 4, 2, 2, 2, 4, 1, 1, 1, 3, 3, 1, 1, 1, 4, 2, 2 };
	Code02_EvenTimesOddTimes::find_odd_a_b_number(arr2);
	cout << "Code02_EvenTimesOddTimes end" << endl;

}
