#pragma once
#ifndef Code04_MoneyProblem_HPP
#define Code04_MoneyProblem_HPP
#include <algorithm>
#include "utility_func.hpp"
namespace Code04_MoneyProblem {

// int[] d d[i]��i�Ź��޵�����
// int[] p p[i]��i�Ź���Ҫ���Ǯ
// ability ��ǰ�������е�����
// index �����˵�index�����޵���ǰ

// Ŀǰ�����������ability����������index�Ź��޵���ǰ�����Ҫͨ���������еĹ��ޣ�
// �뷵����Ҫ��������Ǯ��
	long process1(vector<int> &d, vector<int>& p, int index, int ability)
	{
		if (index == d.size())
		{
			return 0;
		}
		if (ability < d[index])
		{
			return p[index] + process1(d, p, index + 1, ability + d[index]);
		}
		// ability >= d[index]
		long huilu = p[index] + process1(d, p, index + 1, ability + d[index]);
		long buhuilu = process1(d, p, index + 1, ability);
		return std::min(
			huilu,
			buhuilu
		);

	}

	long func1(vector<int> &d, vector<int>& p)
	{
		return process1(d, p, 0, 0);
	}

	// ���û���money ���ܻ�õ��������
	long process2(vector<int> &d, vector<int>& p, int index, int money)
	{
		if (index == -1) { // һ������Ҳû������
			return money == 0 ? 0 : -1;
		}
		// index >= 0
		// 1) ����¸��ǰindex�Ź���
		long preMaxAbility = process2(d, p, index - 1, money);
		long p1 = -1;
		if (preMaxAbility != -1 && preMaxAbility >= d[index]) {
			p1 = preMaxAbility;
		}
		// 2) ��¸��ǰ�Ĺ��� ��ǰ��Ǯ p[index]
		long preMaxAbility2 = process2(d, p, index - 1, money - p[index]);
		long p2 = -1;
		if (preMaxAbility2 != -1) {
			p2 = d[index] + preMaxAbility2;
		}
		return std::max(p1, p2);
	}

	long func2(vector<int> & d, vector<int> & p) {
		long allMoney = 0;
		for (int i = 0; i < p.size(); i++) {
			allMoney += p[i];
		}
		int N = d.size();
		for (long money = 0; money < allMoney; money++) {
			if (process2(d, p, N - 1, money) != -1) {
				return money;
			}
		}
		return allMoney;
	}


	long dp1(vector<int> & d, vector<int> & p)
	{
		int N = d.size();
		long abilitysum = 0;
		for (int i = 0; i < N; i++)
		{
			abilitysum += d[i];
		}

		vector<vector<long>> dp(N + 1, vector<long>(abilitysum + 1, 0));

		for (int index = N - 1; index >= 0; index--)
		{
			for (long ability = 0; ability <= abilitysum; ability++)
			{
				if (ability + d[index] > abilitysum)
				{
					continue;
				}
				if (ability < d[index])
				{
					dp[index][ability] = p[index] + dp[index + 1] [ability + d[index]];
				}
				else
				{
					long huilu = p[index] + dp[index + 1] [ability + d[index]];
					long buhuilu = dp[index + 1][ ability];
					dp[index][ability] = std::min(huilu, buhuilu);
				}
			}
		}
		return dp[0][0];
	}	

	long dp2(vector<int> & d, vector<int> & p) {
	
		long allMoney = 0;
		for (int i = 0; i < p.size(); i++) {
			allMoney += p[i];
		}
		int N = d.size();

		vector<vector<long>> dp(N + 1, vector<long>(allMoney + 1, -1));
		for (int i = 0; i <= allMoney; i++)
		{
			if (p[0] == i)
			{
				dp[0][i] = d[0];
				break;
			}
		}

		for (int index = 1; index < N; index++)
		{
			for (long money = 0; money <= allMoney; money++)
			{				
				long preMaxAbility = dp[index - 1][money];
				long p1 = -1;
				if (preMaxAbility != -1 && preMaxAbility >= d[index]) 
				{
					p1 = preMaxAbility;
				}
				long preMaxAbility2 = -1;
				if (money - p[index] >= 0)
				{
					 preMaxAbility2 = dp[index - 1][money - p[index]];
				}
				long p2 = -1;
				if (preMaxAbility2 != -1) {
					p2 = d[index] + preMaxAbility2;
				}
				dp[index][money] = std::max(p1, p2);
			}
		}

		for (long money = 0; money <= allMoney; money++)
		{
			if (dp[N - 1][money] != -1)
			{
				return money;
			}
		}
		return allMoney;
	}
}

void test_Code04_MoneyProblem() {
	int len = 10;
	int max_power = 20;
	int max_price = 10;
	int testTimes = 50;
	cout << "test_Code04_MoneyProblem begin" << endl;
	for (int i = 0; i < testTimes; i++)
	{
		vector<int> d = generateRandomArray(len, max_power, 1);
		vector<int> p = generateRandomArray(len, max_price, 1);
		long ans1 = Code04_MoneyProblem::func1(d, p);
		long ans2= Code04_MoneyProblem::func2(d, p);
		long ans3 = Code04_MoneyProblem::dp1(d, p);
		long ans4 = Code04_MoneyProblem::dp2(d, p);
		if (ans1 != ans2 || ans2 != ans3 || ans3 != ans4)
		{
			cout << "d:" << endl;
			print(d);
			cout << "p:" << endl;
			print(p);
			cout << ans1 << "," << ans2 << "," << ans3 << "," << ans4 << endl;
			break;
		}
	}
	cout << "test_Code04_MoneyProblem end" << endl;

}

#endif