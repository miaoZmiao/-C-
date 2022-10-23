#pragma once
#ifndef Code01_Knapsack_HPP
#define Code01_Knapsack_HPP
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

namespace Code01_Knapsack
{
	// ���еĻ��������ͼ�ֵ������w��v������
	// Ϊ�˷��㣬����û�и���
	// bag�������������ܳ����������
	// ���أ������ص�����£��ܹ��õ�������ֵ
	
	int process1(vector<int> & w, vector<int> v, 
		int index, int bag);

	int maxValue(vector<int> & w, vector<int> v, int bag) {
		if (w.size() == 0 || v.size() == 0|| w.size() != v.size()) 
		{
			return 0;
		}
		// ���Ժ�����
		return process1(w, v, 0, bag);
	}

	int process1(vector<int> & w, vector<int> v,
		int index, int bag) {
		if (bag < 0)
		{
			return -1;
		}
		if (index == w.size())
		{
			return 0;
		}
		// ��Ҫ indexλ�õ�value
		int p1 = process1(w, v, index+1, bag);
		// Ҫindexλ�õ�value
		int p2 = 0;
		int next = process1(w, v, index + 1, bag - w[index]);
		if (next != -1)
		{
			p2 = v[index] + next;
		}
		return std::max(p1, p2);
	}

	int dpway(vector<int> & w, vector<int> v, int bag)
	{
		size_t N = w.size();
		// index , bag
		vector<vector<int>> dp(N+1, vector<int>(bag+1, 0)
			);
		// dp[N][1.....bag] = 0;
		for (int row = N - 1; row >= 0; row--)
		{
			for (int rest = 0; rest < bag + 1; rest++)
			{
				// ��Ҫ indexλ�õ�value
				int p1 =  dp[row + 1][rest];
				// Ҫindexλ�õ�value
				int p2 = 0;
				if (rest - w[row] >= 0)
				{
					p2 =v[row] + dp[row+1][rest - w[row]];
				}
				dp[row][rest] = std::max(p1, p2);
			}
		}

		return dp[0][bag];
	}



}

void test_Code01_Knapsack()
{
	vector<int> weight{ 3, 2, 4, 7, 3, 1, 7 };
	vector<int> value{ 5, 6, 3, 19, 12, 4, 2 };
	int bag = 15;
	cout << "test_Code01_Knapsack begin" << endl;
	cout << "maxValue:" << Code01_Knapsack::maxValue(weight,
		value, bag) << endl;
	cout << "dpway:" << Code01_Knapsack::dpway(weight, value, bag) 
		<< endl;
	cout << "test_Code01_Knapsack end" << endl;
}



#endif