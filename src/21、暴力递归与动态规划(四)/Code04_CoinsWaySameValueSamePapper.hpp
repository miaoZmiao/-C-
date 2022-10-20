#pragma once
#ifndef Code04_CoinsWaySameValueSamePapper_HPP
#define Code04_CoinsWaySameValueSamePapper_HPP
#include <vector>
#include <string>
#include <iostream>
#include <map>
using namespace  std;;
//	��Ŀ��
//	arr�ǻ������飬���е�ֵ�����������ٸ���һ������aim��
//	ÿ��ֵ����Ϊ��һ�Ż��ң�
//	��Ϊֵ��ͬ�Ļ���û���κβ�ͬ��
//	�������aim�ķ�����
//	���磺arr = { 1,2,1,1,2,1,2 }��aim = 4
//	������1 + 1 + 1 + 1��1 + 1 + 2��2 + 2
//	һ����3�ַ��������Է���3

namespace Code04_CoinsWaySameValueSamePapper {

	class Solution
	{
	public:
		 // ��ҪԤ����
		int coinWays(vector<int> & arr, int aim) {
			// Ԥ����
			std::map<int, int> mp;
			for (auto & i : arr)
			{
				if (mp.find(i) != mp.end())
				{
					mp[i]++;
				}
				else
				{
					mp[i] = 1;
				}
			}
			vector<int> coins;
			vector<int> zhangs;
			for (auto& m : mp)
			{
				coins.push_back(m.first);
				zhangs.push_back(m.second);
			}
			return process1(coins, zhangs, 0, aim);
		}
		int process1(vector<int> & coins, vector<int> & zhangs,
			int index, int aim) 
		{
			if (index == coins.size())
			{
				return aim == 0 ? 1 : 0;
			}
			int ways = 0;
			int value = coins[index];
			for (int zhang = 0; zhang <=zhangs[index]; zhang++)
			{
				if (aim - zhang * value < 0)
				{
					break;
				}
				ways += process1(coins, zhangs, 
					index+1, aim- zhang * value);
			}
			return ways;
		}

		// ��ҪԤ����
		int coinWaysDP(vector<int> & arr, int aim) {
			// Ԥ����
			std::map<int, int> mp;
			for (auto & i : arr)
			{
				if (mp.find(i) != mp.end())
				{
					mp[i]++;
				}
				else
				{
					mp[i] = 1;
				}
			}
			vector<int> coins;
			vector<int> zhangs;
			for (auto& m : mp)
			{
				coins.push_back(m.first);
				zhangs.push_back(m.second);
			}
			return dpways(coins, zhangs, aim);
		}
		// ��̬�滮
		// ���Ż�
		int dpways(vector<int> & coins, vector<int> & zhangs, int target)
		{
			int N = coins.size();
			
			vector<vector<int>> dp(N + 1, vector<int>(target + 1, 0));
			dp[N][0] = 1;

			for (int index = N - 1; index >= 0; index--)
			{
				for (int aim = 0; aim <= target;aim++)
				{
					int ways = 0;
					int value = coins[index];
					for (int zhang = 0; zhang <= zhangs[index]; zhang++)
					{
						if (aim - zhang * value < 0)
						{
							break;
						}
						ways += dp[index + 1][aim - zhang * value];
					}
					dp[index][aim] = ways;
				}
			}
			return dp[0][target];
		}

		// ��̬�滮��ö����Ϊ���Ա��Ż���
		// dpwaysEO = dpwaysEnumOptimization
		int dpwaysEO(vector<int> & coins, vector<int> & zhangs,
			int target) 
		{
			int N = coins.size();
			vector<vector<int>> dp(N + 1, vector<int>(target + 1, 0));
			dp[N][0] = 1;

			for (int index = N - 1; index >= 0; index--)
			{
				for (int aim = 0; aim <= target; aim++)
				{
					int value = coins[index];
					dp[index][aim] = dp[index + 1][aim];
					int zhang = zhangs[index];
					if (aim - value >= 0)
					{
						dp[index][aim] += dp[index][aim - value];
						if (aim - (zhang + 1)*value >= 0)
						{
							dp[index][aim] -= dp[index + 1][aim - (zhang + 1)*value];
						}
					}
					
				}
			}
			return dp[0][target];
		}

		// ��ҪԤ����
		int coinWaysDPEnum(vector<int> & arr, int aim) {
			// Ԥ����
			std::map<int, int> mp;
			for (auto & i : arr)
			{
				if (mp.find(i) != mp.end())
				{
					mp[i]++;
				}
				else
				{
					mp[i] = 1;
				}
			}
			vector<int> coins;
			vector<int> zhangs;
			for (auto& m : mp)
			{
				coins.push_back(m.first);
				zhangs.push_back(m.second);
			}
			return dpwaysEO(coins, zhangs, aim);
		}
	};
}

void test_Code04_CoinsWaySameValueSamePapper() {

	int maxvalue = 10;
	int minvalue = 1;
	int test_loop = 10;
	int N = 20;
	int aim = 22;
	cout << "���Կ�ʼ" << endl;
	stop_watch st;
	double elapse_force = 0;
	double elapse_dp = 0.0;
	double elapse_dp_enum = 0.0;
	Code04_CoinsWaySameValueSamePapper::Solution sln;
	for (int i = 0; i < test_loop; i++) 
	{
		vector<int> arr = generateRandomArray(N, maxvalue, minvalue);
		st.start();
		int ans1 = sln.coinWays(arr, aim);
		st.stop();
		elapse_force += st.elapsed_ms();
		st.start();
		int ans2 = sln.coinWaysDP(arr, aim);
		st.stop();
		elapse_dp += st.elapsed_ms();
		st.start();
		int ans3 = sln.coinWaysDPEnum(arr, aim);
		st.stop();
		elapse_dp_enum += st.elapsed_ms();
		if (ans1 != ans2 || ans2 != ans3)
		{
			print(arr);
			cout << ans1 << "," << ans2 << "," << ans3 << endl;
			break;
		}
	}
	cout << "���Խ���" << endl;
	cout << "average elapse(ms)" << endl;
	cout << "force:" << elapse_force / test_loop << endl;
	cout << "dp:" << elapse_dp / test_loop << endl;
	cout << "dpEnumOptimization:" << elapse_dp_enum / test_loop << endl;


	//	���Կ�ʼ
	//	���Խ���
	//	average elapse(ms)
	//	force:0.0831
	//	dp : 0.0241
	//	dpEnumOptimization : 0.0217


}

#endif