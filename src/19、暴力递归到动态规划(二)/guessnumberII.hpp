#pragma once
#ifndef GUESS_NUMBER_II
#define GUESS_NUMBER_II

//375. �����ִ�С II
//����������һ��������Ϸ����Ϸ�������£�
//
//�Ҵ� 1 �� n ֮��ѡ��һ�����֡�
//��������ѡ���ĸ����֡�
//�����µ���ȷ�����֣��ͻ� Ӯ����Ϸ ��
//�����´��ˣ���ô�һ�����㣬��ѡ�����ֱ���� ������߸�С ����������Ҫ����������
//ÿ����������� x ���Ҳ´��˵�ʱ������Ҫ֧�����Ϊ x ���ֽ�����㻨����Ǯ���ͻ� �����Ϸ ��
//����һ���ض������� n �������ܹ� ȷ�����ʤ ����С�ֽ�����������ѡ���Ǹ����� ��

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

namespace GUESS_NUMBER_II
{
	class Solution {
	public:
		int getMoneyAmount(int n) {
			return  process(1, n);
		}

		int minGold(int n)
		{
			return dpways(n);
		}

		//
		// 1,2,3,4,5,6
		//	 2	 4 5
		// 1,2,3,4,5,6,7,8
		//         5
		//        
		int process(int L, int R)
		{
			if (L >= R)
			{
				return 0;
			}
			if (L + 1 == R)
			{
				return L;
			}
			int p1 = L + process(L+1, R);
			int p2 = R + process(L, R - 1);
			int mincost = std::min(p1, p2);
			for (int i = L + 1; i < R; i++)
			{
				int c1 = process(L, i-1);
				int c2 = process(i + 1, R);
				int cur = i + std::max(c1, c2);
				mincost = std::min(mincost, cur);
			}
			return mincost;
		}

		int dpways(int N)
		{
			vector<vector<int>> dp(N+1, vector<int>(N+1, 0));
			for (int i = 0; i < N; i++)
			{
				dp[i][i + 1] = i;
			}

			for (int col = 2; col < N + 1; col++)
			{
				int L = 1;
				int R = col;
				while (L <= N && R <= N)
				{
					int p1 = L + dp[L + 1][R];
					int p2 = R + dp[L][R - 1];
					int mincost = std::min(p1, p2);
					for (int i = L + 1; i < R; i++)
					{
						int c1 = dp[L][i - 1];
						int c2 = dp[i + 1][R];
						int cur = i + std::max(c1, c2);
						mincost = std::min(mincost, cur);
					}
					dp[L][R] = mincost;
					L++;
					R++;
				}
			}
			return dp[1][N];
		}



	};

}

void test_guess_number_ii()
{
	int N = 10;
	GUESS_NUMBER_II::Solution sln;
	int input = 1;
	while (input <= N)
	{
		int ret = sln.getMoneyAmount(input);
		int ret_dp = sln.minGold(input);
		if (ret != ret_dp)
		{
			cout << "input:"<< input << endl;
			cout << "ret_dp:" << ret_dp << endl;
		}
		else
		{
			cout << "test_OK for input:" << input << endl;
		}
		input++;
	}
	
}


#endif

