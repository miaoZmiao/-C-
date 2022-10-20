#pragma once
#ifndef Code02_TSP_HPP
#define Code02_TSP_HPP
//TSP���� ��N�����У��κ���������֮��Ķ��о��룬�κ�һ�����е��Լ��ľ��붼Ϊ0����
//�е㵽��ľ� �붼����һ��N*N�Ķ�ά����matrix�Ҳ��������ͼ���ڽӾ����ʾ����Ҫ
//��һ�����̴�k���� �������뾭��ÿһ��������ֻ��һ�����ж���һ�Σ����ص�������k
//�ǣ������ܾ�����̵�·�� ���롣��������һ��matrix������k��

#include "utility_func.hpp"


namespace Code02_TSP {

	class Solution {
	public:

		int t1(vector<vector<int>> & matrix) {
			int N = matrix.size();

			vector<int> arr(N, 1);
			// arr[0] = -1;
			return func1(matrix, arr, 0);
		}

		int func1(vector<vector<int>> & matrix, 
			vector<int> & leftcities, 
			int start)
		{
			int cityNum = 0;
			for (int i = 0; i < leftcities.size(); i++)
			{
				if (leftcities[i] == 1)
				{
					cityNum++;
				}
			}
			if (cityNum == 1)
			{
				return matrix[start][0];
			}
			int ans = INT_MAX;
			leftcities[start] = -1;
			for (int i = 0; i < leftcities.size(); i++)
			{
				if (leftcities[i] == -1)
				{
					continue;
				}
				leftcities[i] = -1;
				int next = func1(matrix, leftcities, i);
				ans = std::min(ans, next + matrix[start][i]);
				leftcities[i] = 1;
			}
			leftcities[start] = 1;
			return ans;
		}
		// t2 ����״̬ѹ��
		int t2(vector<vector<int>> & matrix)
		{
			int N = matrix.size();
			int cityStatus = (1 << N) - 1;
			//cityStatus = cityStatus & (~1);
			return f2(matrix, cityStatus, 0);
		}
		int f2(vector<vector<int>> & matrix, int cityStatus, int start)
		{
			if (cityStatus == (cityStatus&(~cityStatus + 1)))
			{
				return matrix[start][0];
			}
			int ans = INT_MAX;
			int N = matrix.size(); 
			cityStatus = (~(1 << start)) & cityStatus;
			for (int i = 0; i < N; i++)
			{
				if ((cityStatus &(1 << i)) == 0)
				{
					continue;
				}
				int nextcityStatus = (1 << i);
				nextcityStatus = ~nextcityStatus;
				nextcityStatus = cityStatus & nextcityStatus;
				int next = f2(matrix, nextcityStatus, i);
				ans = std::min(ans, next + matrix[start][i]);
			}
			cityStatus = (1 << start) | cityStatus;
			return ans;
		}

		// t2 ����״̬ѹ��
		// t3 ��ɵ����
		int t3(vector<vector<int>> & matrix) {
			
			int N = matrix.size();
			int cityStatus = (1 << N) - 1;
			std::map<int, int> dp;
			return f3(matrix, cityStatus, 0, dp);
		}

		int f3(vector<vector<int>> & matrix, int cityStatus, int start, 
			std::map<int, int> & dp)
		{
			auto iter = dp.find(cityStatus);
			if (iter != dp.end())
			{
				return iter->second;
			}
			if (cityStatus == (cityStatus&(~cityStatus + 1)))
			{
				dp[cityStatus] = matrix[start][0];
				return matrix[start][0];
			}
			int ans = INT_MAX;
			int N = matrix.size();
			cityStatus = (~(1 << start)) & cityStatus;
			for (int i = 0; i < N; i++)
			{
				if ((cityStatus &(1 << i)) == 0)
				{
					continue;
				}
				int nextcityStatus = (1 << i);
				nextcityStatus = ~nextcityStatus;
				nextcityStatus = cityStatus & nextcityStatus;
				int next = f2(matrix, nextcityStatus, i);
				ans = std::min(ans, next + matrix[start][i]);
			}
			cityStatus = (1 << start) | cityStatus;
			dp[cityStatus] = ans;
			return ans;
		}

		int t4(vector<vector<int>> & matrix) {
			int N = matrix.size();
			int statusNum = (1 << N);
			vector<vector<int>> dp(statusNum, vector<int>(N, 0));

			for (int cityStatus = 0; cityStatus < statusNum; cityStatus++)
			{
				for (int start = 0; start < N; start++)
				{
					if (cityStatus == (cityStatus&(~cityStatus + 1)))
					{
						dp[cityStatus][start]= matrix[start][0];
					}
					else
					{
						int ans = INT_MAX;
						int preStatus = (~(1 << start)) & cityStatus;
						for (int i = 0; i < N; i++)
						{
							if ((preStatus &(1 << i)) == 0)
							{
								continue;
							}
							int nextcityStatus = (1 << i);
							nextcityStatus = ~nextcityStatus;
							nextcityStatus = preStatus & nextcityStatus;
							int next = f2(matrix, nextcityStatus, i);
							ans = std::min(ans, next + matrix[start][i]);
						}
						dp[cityStatus][start] = ans;
					}
				}
			}
			return dp[statusNum-1][0];
		}


	};


}


void test_Code02_TSP() {

	Code02_TSP::Solution sln;
	int N = 8;
	int M = 8;
	int testTime = 100;
	cout << "test_Code02_TSP begin" << endl;
	for (int i = 0; i < testTime; i++)
	{
		vector<vector<int>> matrix = generate_M_N_matrix(M, N, 1, 10);

		//int ans1 = sln.t1(matrix);
		int ans2 = sln.t2(matrix);
		int ans3 = sln.t3(matrix);
		int ans4 = sln.t4(matrix);
		if (/*ans1 != ans2 || */ans2 != ans3 || ans3 != ans4)
		{
			printMatrix(matrix);
			cout /*<< ans1 << "," */<< ans2 << ","<<ans3<<","<<ans4<<endl;
			break;
		}
	}
	cout << "test_Code02_TSP end" << endl;



}


#endif