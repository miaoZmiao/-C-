#pragma once
#ifndef Code04_MinCoinsOnePaper_HPP
#define Code04_MinCoinsOnePaper_HPP
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <deque>
#include "utility_func.hpp"
#include "stop_watch.hpp"

// ��Ŀ��
// arr�ǻ�������,����ֵ������������һ������aim
// ÿ��ֵ����Ϊ��һ�Ż���
// �������aim�����ٻ�������
// 
namespace Code04_MinCoinsOnePaper {
	class Solution
	{
	public:
		int minCoins(vector<int> & arr, int aim) {
			return process1(arr, 0, aim);
		}
		int process1(vector<int> & arr, int index, int aim)
		{
			if (aim < 0)
			{
				return INT_MAX;
			}
			if (index == arr.size())
			{
				return aim == 0 ? 0 : INT_MAX;
			}
			// ������index ��ֵ
			int p1 = process1(arr, index + 1, aim );
			int p2 = INT_MAX;
			int next = process1(arr, index + 1, aim - arr[index]);
			if (next != INT_MAX)
			{
				p2 = next + 1;
			}
			return std::min(p1, p2);
		}

		int dp1(vector<int> & arr, int target) {
			int N = arr.size();
			
			vector<vector<int>> dp(N+1, vector<int>(target+1, 0));
			dp[N][0] = 0;
			for (int aim = 1; aim <= target; aim++)
			{
				dp[N][aim] = INT_MAX;
			}
			for (int index = N - 1; index >= 0; index--)
			{
				for (int aim = 0; aim <= target; aim++)
				{
					int p1 = dp[ index + 1][aim];
					int p2 = INT_MAX;
					int next = INT_MAX;
					if (aim - arr[index] >= 0)
					{
						next = dp[index + 1][aim - arr[index]];
					}
					if (next != INT_MAX)
					{
						p2 = next + 1;
					}
					dp[index][aim] = std::min(p1, p2);
				}
			}
			return dp[0][target];
		}

		struct Info
		{
			vector<int> coins;
			vector<int> zhangs;
		};

		Info getInfo(vector<int> & arr)
		{
			unordered_map<int, int> ump;
			for (auto a : arr)
			{
				ump[a]++;
			}
			Info ans;
			for (auto it : ump)
			{
				ans.coins.push_back(it.first);
				ans.zhangs.push_back(it.second);
			}
			return ans;
		}

		int dp2(vector<int> & arr, int target)
		{
			Info info = getInfo(arr);
			int N = info.coins.size();
			auto & coins = info.coins;
			auto & zhangs = info.zhangs;
			vector<vector<int>> dp(N+1, vector<int>(target +1, 0));
			dp[N][0] = 0;
			for (int i = 1; i <= target; i++)
			{
				dp[N][i] = INT_MAX;
			}
			for (int index = N - 1; index >= 0; index--)
			{
				int value = coins[index];
				for (int aim = 0; aim <= target; aim++)
				{
					dp[index][aim] = INT_MAX;
					for (int zhang = 0; zhang <= zhangs[index]; zhang++)
					{
						if (aim - zhang * value >= 0)
						{
							if (INT_MAX
								!= dp[index + 1]
								[aim - zhang * value])
							{
								dp[index][aim] = std::min(
									dp[index][aim],
									zhang + dp[index + 1][aim - zhang * value]
								);
							}

						}
						else
						{
							break;
						}
						
					}
				
				}
			}

			return dp[0][target];
		}

		int dp3(vector<int> & arr, int target)
		{
			Info info = getInfo(arr);
			int N = info.coins.size();
			auto & coins = info.coins;
			auto & zhangs = info.zhangs;
			vector<vector<int>> dp(N + 1, vector<int>(target + 1, 0));
			dp[N][0] = 0;
			for (int i = 1; i <= target; i++)
			{
				dp[N][i] = INT_MAX;
			}
			for (int index = N - 1; index >= 0; index--)
			{
				int value = coins[index];
				int zhang = zhangs[index];
				for (int mod = 0; mod < std::min(target+1, value); mod++)
				{
					std::deque<int> dq;
					for (int r = mod; r <= target; r += value)
					{
						while (!dq.empty() && (
							INT_MAX == dp[index + 1][dq.back()] ||
							dp[index + 1][dq.back()] >=
							dp[index + 1][r] -
							compensate(dq.back(), r, value)
							)
							) 
						{
							dq.pop_back();
						}
						dq.push_back(r);

						int overdue = r - (zhang + 1)*value;
						if (overdue == dq.front())
						{
							dq.pop_front();
						}

						dp[index][r] =
							dp[index + 1][dq.front()] == INT_MAX ? INT_MAX : compensate(dq.front(), r, value)+ dp[index + 1][dq.front()];
					}
				}
			}
			return dp[0][target];
		}

		int compensate(int pre , int cur, int value)
		{
			return (cur - pre) / value;
		}






	};
}

void test_Code04_MinCoinsOnePaper()
{
	cout << "test_Code04_MinCoinsOnePaper begin" << endl;
	int maxLen = 5;
	int maxValue = 10;
	int testTime = 10;
	std::random_device rd;
	std::mt19937 gen(rd());
	int aimexpect = maxLen * maxValue / 2;
	std::uniform_int_distribution<> dist(aimexpect - aimexpect /2, aimexpect + aimexpect /2);
	cout << "���ܲ��Կ�ʼ" << endl;
	Code04_MinCoinsOnePaper::Solution sln;
	for (int i = 0; i < testTime; i++)
	{
		int aim = dist(gen);
		vector<int> arr = generateRandomArray(maxLen, maxValue, 1);
		int ans1 = sln.minCoins(arr, aim);
		int ans2 = sln.dp1(arr, aim);
		int ans3 = sln.dp2(arr, aim);
		int ans4 = sln.dp3(arr,aim);
		if (ans1 != ans2 || ans2 != ans3 || ans3 != ans4)
		{
			print(arr);
			cout << "aim:" << aim << endl;
			cout << ans1 <<","<< ans2 << ","<<ans3 
				<<","<<ans4<<endl;
			break;
		}
	}
	cout << "���ܲ��Խ���" << endl;
	cout << "==========" << endl;
	cout << "���ܲ��Կ�ʼ" << endl;
	maxLen = 30000;
	maxValue = 20;
	int aim = 60000;
	stop_watch sw;
	vector<int> arr = generateRandomArray(maxLen, maxValue, 1);
	sw.start();
	int ans2 = sln.dp2(arr, aim);
	sw.stop();
	cout << "dp2��:" << ans2 <<",��ʱ:"<<
		sw.elapsed_ms()<<"ms"<< endl;
	sw.start();
	int ans3 = sln.dp3(arr, aim);
	sw.stop();
	cout << "dp3��:" << ans3 << ",��ʱ:" <<
		sw.elapsed_ms() << "ms" << endl;

	cout << "���Ҵ����ظ���������£�" << endl;
	cout << "������������dp3��ʼ" << endl;
	maxLen = 20000000;
	aim = 10000;
	maxValue = 10000;
	arr = generateRandomArray(maxLen, maxValue, 1);
	sw.start();
	ans3 = sln.dp3(arr, aim);
	sw.stop();
	cout<<"dp3����ʱ�� : " << sw.elapsed_ms() <<" ms"<<endl;
	cout << "�����������Խ���" << endl;
	cout << "===========" << endl;
	cout << "�����Һ��ٳ����ظ���dp2��dp3�г���ʱ������" << endl;
	cout << "�����Ҵ��������ظ���dp3ʱ�临�Ӷ���������dp2" << endl;
	cout << "dp3���Ż��õ��˴�������Сֵ�ĸ��½ṹ" << endl;
	cout << "test_Code04_MinCoinsOnePaper end" << endl;
	/*	���ܲ��Կ�ʼ
		���ܲ��Խ���
		==========
		���ܲ��Կ�ʼ
		dp2�� : 3082, ��ʱ : 54913.8ms
		dp3�� : 3082, ��ʱ : 452.878ms
		���Ҵ����ظ���������£�
		������������dp3��ʼ
		dp3����ʱ�� : 52176.1 ms
		�����������Խ���
		========== =
		�����Һ��ٳ����ظ���dp2��dp3�г���ʱ������
		�����Ҵ��������ظ���dp3ʱ�临�Ӷ���������dp2
		dp3���Ż��õ��˴�������Сֵ�ĸ��½ṹ*/


}
#endif