#pragma once
#ifndef Code03_Coffee_HPP
#define Code03_Coffee_HPP
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include "utility_func.hpp"
using namespace std;


namespace Code03_Coffee {
// ��Ŀ
// ����arr����ÿһ�����Ȼ���һ�����ȵ�ʱ�䣬
// ÿ�����Ȼ�ֻ�ܴ��е����쿧�ȡ�
// ������n������Ҫ�ȿ��ȣ�ֻ���ÿ��Ȼ������쿧�ȡ�
// ��Ϊÿ���˺ȿ��ȵ�ʱ��ǳ��̣���õ�ʱ�伴�Ǻ����ʱ�䡣
// ÿ���˺���֮�󿧷ȱ�����ѡ��ϴ������Ȼ�ӷ��ɾ���
//	ֻ��һ̨ϴ���ȱ��Ļ�����ֻ�ܴ��е�ϴ���ȱ���
// ϴ���ӵĻ���ϴ��һ������ʱ��Ϊa��
//	�κ�һ��������Ȼ�ӷ��ɾ���ʱ��Ϊb��
// �ĸ�������arr, n, a, b
// ����ʱ����0��ʼ�����������˺��꿧��
// ��ϴ�꿧�ȱ���ȫ�����̽�������������ʲôʱ��㡣




	class Solution
	{
	public:
		// ��֤�ķ���
		// ���׵ı���
		// �������Ǿ�����ȷ
		int right(vector<int> & arr, int n, int a, int b) {
			vector<int> times(arr.size(), 0);
			vector<int> drinks(n, 0);
			return forceMake(arr, drinks, times, 0, a, b);
		}
		// ����������
		// �� index �˺ȿ���(�� index ������ ��ʱ��)
		// ��Ҫ���drinks����(����ʲôʱ����꿧����)
		// ��Ҫ��� times ���� (���Ȼ�ɶʱ�����)
		int forceMake(vector<int> & arr, vector<int> & drinks,
			vector<int> & times, 
			int index, int a, int b) 
		{
			if (index == drinks.size())
			{
				auto sorteddrinks = drinks;
				std::sort(sorteddrinks.begin(), sorteddrinks.end());
				return forceWash(sorteddrinks, 0, 0, a, b);
			}
			// �� index ����(����) �� �� i �ſ��Ȼ�ĥ����
			int min_time = INT_MAX;
			for (int i = 0; i < arr.size(); i++)
			{
				int addtime = arr[i];
				int pre = times[i];
				times[i] = times[i] + addtime;
				drinks[index] = times[i];
				int tmp_mintime = forceMake(arr, drinks,
					times, index+1, a, b);
				min_time = std::min(min_time, tmp_mintime);
				drinks[index] = 0;
				times[i] = pre;
			}
			return min_time;
			
		}

		// ���ӵĿ���ʱ�� drinks
		// a ϴһ�����ӵ�ʱ��
		// b ��Ȼ���ﱭ�ӵ�ʱ��
		// ��index ����ʼ
		int forceWash(vector<int> & drinks, int index,
			int washavailable, int a, int b)
		{
			if(index == drinks.size())
			{
				return 0;
			}
			int min_time = INT_MAX;
			// �� index ������ ������Ǿ���ϴһ��
			// ���� washtime ʱ��
			int washovertime = std::max(washavailable, 
				drinks[index]) + a;
			// ʣ�µı�����Ҫ������ô��ʱ��
			int restime1 = forceWash(drinks, index+1, 
				washovertime,a,b);
			// ����ʱ��ȡ max����ϴ��index�����ӵ������
			// �õ����ʱ��
			int p1 = std::max(washovertime, restime1);

			// ��index�����ӣ�������Ȼ���
			int drytime = drinks[index] + b;
			int restime2 = forceWash(drinks, index + 1,
				washavailable, a, b);
			int p2 = std::max(drytime, restime2);

			return std::min(p1, p2);
		}

		struct Machine
		{
			int makecoffeetime = 0;
			int cur = 0;
		};

		

		int minTime1(vector<int> & arr, int n, int a, int b)
		{
			auto compare_machine = []
			(const Machine & A, const Machine & B)->bool {
				return (A.makecoffeetime + A.cur) >
					(B.makecoffeetime + B.cur);
			};

			priority_queue<Machine, vector<Machine>,
				decltype(compare_machine)> pq(compare_machine);

			vector<int> drinks(n, 0);
			for (auto & makecoffeetime : arr)
			{
				Machine m;
				m.cur = 0;
				m.makecoffeetime = makecoffeetime;
				pq.push(m);
			}

			for (int i = 0; i < n; i++)
			{
				Machine m = pq.top();
				pq.pop();
				m.cur += m.makecoffeetime;
				drinks[i] = m.cur;
				pq.push(m);
			}
			return bestTime(drinks, 0 ,0 ,a,b);
		}

		int bestTime(vector<int> & drinks, int index,
			int washavailable, int a, int b)
		{
			if (index == drinks.size())
			{
				return 0;
			}
			int min_time = INT_MAX;
			// �� index ������ ������Ǿ���ϴһ��
			// ���� washtime ʱ��
			int washovertime = std::max(washavailable,
				drinks[index]) + a;
			// ʣ�µı�����Ҫ������ô��ʱ��
			int restime1 = bestTime(drinks, index + 1,
				washovertime, a, b);
			// ����ʱ��ȡ max����ϴ��index�����ӵ������
			// �õ����ʱ��
			int p1 = std::max(washovertime, restime1);
			// ��index�����ӣ�������Ȼ���
			int drytime = drinks[index] + b;
			int restime2 = bestTime(drinks, index + 1,
				washavailable, a, b);
			int p2 = std::max(drytime, restime2);
			return std::min(p1, p2);
		}

		int bestTimedp(vector<int> & drinks,int a, int b)
		{
			int maxAvailable = 0;
			int N = drinks.size();
			for (int i = 0; i < N; i++)
			{
				maxAvailable = std::max(maxAvailable, drinks[i]) 
					+ a;
			}
			vector<vector<int>> dp
			(N+1, vector<int>(maxAvailable +1, 0));
			
			for (int index = N - 1; index >= 0; index--)
			{
				for (int washavailable = maxAvailable; 
					washavailable >= 0; 
					washavailable--)
				{
					int min_time = INT_MAX;
					// �� index ������ ������Ǿ���ϴһ��
					// ���� washtime ʱ��
					int washovertime = std::max(washavailable,
						drinks[index]) + a;
					// ʣ�µı�����Ҫ������ô��ʱ��
					int restime1 = 0;
					if (washovertime <= maxAvailable)
					{
						restime1 = dp[index + 1][washovertime];
					}
					// ����ʱ��ȡ max����ϴ��index�����ӵ������
					// �õ����ʱ��
					int p1 = std::max(washovertime, restime1);
					// ��index�����ӣ�������Ȼ���
					int drytime = drinks[index] + b;
					int restime2 = dp[index + 1][washavailable];
					int p2 = std::max(drytime, restime2);
					dp[index][washavailable] = std::min(p1, p2);
				}
			}
			return dp[0][0];
		}


		int minTime2(vector<int> & arr, int n, int a, int b)
		{
			auto compare_machine = []
			(const Machine & A, const Machine & B)->bool {
				return (A.makecoffeetime + A.cur) >
					(B.makecoffeetime + B.cur);
			};

			priority_queue<Machine, vector<Machine>,
				decltype(compare_machine)> pq(compare_machine);

			vector<int> drinks(n, 0);
			for (auto & makecoffeetime : arr)
			{
				Machine m;
				m.cur = 0;
				m.makecoffeetime = makecoffeetime;
				pq.push(m);
			}

			for (int i = 0; i < n; i++)
			{
				Machine m = pq.top();
				pq.pop();
				m.cur += m.makecoffeetime;
				drinks[i] = m.cur;
				pq.push(m);
			}
			return bestTimedp(drinks, a, b);
		}
	};

}

void test_Code03_Coffee() {
	int len = 10;
	int max = 10;
	int testTime = 10;
	cout << "���Կ�ʼ" << endl;
	Code03_Coffee::Solution sln;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dist(0.0, 1.0);

	for (int i = 0; i < testTime; i++)
	{
		vector<int> arr = generateRandomArray(len, max, 1);
		//vector<int> arr = { 6,2,7,7,7 };
		int n = (int)(dist(gen) * 7) + 1;
		int a = (int)(dist(gen) * 7) + 1;
		int b = (int)(dist(gen) * 10) + 1;
		/*int n = 3;
		int a = 3;
		int b = 4;*/
		int ans1 = sln.right(arr, n, a, b);
		int ans2 = sln.minTime1(arr, n, a, b);
		int ans3 = sln.minTime2(arr, n, a, b);
		if (ans1 != ans2 || ans2 != ans3) {
			print(arr);
			cout << "n : " << n << endl;
			cout << "a : " << a << endl;
			cout << "b : " << b << endl;
			cout << ans1 << " , " << ans2 << " , " << ans3 << endl;
			cout << "===============" << endl;
			break;
		}
	}
	cout << "���Խ���" << endl;
}




#endif 