#pragma once
#ifndef Code02_BestSplitForEveryPosition_HPP
#define Code02_BestSplitForEveryPosition_HPP
#include <algorithm>
#include "utility_func.hpp"
//����Ŀһ���ᵽ�ģ�//min{ �󲿷��ۼӺͣ��Ҳ����ۼӺ� }������ΪS(N - 1)��Ҳ����˵��//S(N - 1)����arr[0��N - 1]��Χ�ϣ������Ż������õ���min{ �󲿷��ۼӺͣ��Ҳ����ۼӺ� }�����ֵ//����Ҫ�󷵻�һ������ΪN��s���飬//s[i] = ��arr[0��i]��Χ�ϣ������Ż������õ���min{ �󲿷��ۼӺͣ��Ҳ����ۼӺ� }�����ֵ//�õ�����s����Ĺ��̣�����ʱ�临�Ӷ�O(N)
namespace Code02_BestSplitForEveryPosition {

	vector<int> bestSplit1(vector<int>& arr)
	{
		if (arr.size()<2)
		{
			return { 0 };
		}
		int N = arr.size();
		vector<int> ans(N, 0);
		ans[0] = 0;
		for (int i = 1; i < N; i++)
		{
			for (int s = 0; s < i; s++)
			{
				int sumL = 0;
				for (int L = 0; L <= s; L++)
				{
					sumL += arr[L];
				}
				int sumR = 0;
				for (int R = s + 1; R <= i; R++)
				{
					sumR += arr[R];
				}
				ans[i] = std::max(ans[i], std::min(sumL, sumR));
			}
		}
		return ans;
	}

	int getsum(vector<int>& sum, int L, int R)
	{
		return sum[R + 1] - sum[L];
	}


	vector<int> bestSplit2(vector<int>& arr)
	{
		if (arr.size() < 2)
		{
			return { 0 };
		}
		int N = arr.size();
		vector<int> ans(N, 0);
		vector<int> sum(N + 1, 0);
		for (int i = 1; i < N + 1; i++)
		{
			sum[i] = sum[i - 1] + arr[i - 1];
		}

		for (int range = 1; range < N; range++)
		{
			for (int s = 0; s < range; s++)
			{
				int sumL = getsum(sum, 0, s);
				int sumR = getsum(sum, s + 1, range);
				ans[range] = std::max(ans[range], std::min(sumL, sumR));
			}
		}
		return ans;
	}

	vector<int> bestSplit3(vector<int>& arr) {
		if (arr.size() < 2)
		{
			return { 0 };
		}
		int N = arr.size();
		vector<int> ans(N, 0);
		vector<int> sum(N + 1, 0);
		for (int i = 1; i < N + 1; i++)
		{
			sum[i] = sum[i - 1] + arr[i - 1];
		}
		int best = 0;
		for (int range = 1; range < N; range++)
		{
			while (best + 1 < range) {
				int before = std::min(getsum(sum, 0, best), getsum(sum, best + 1, range));
				int after = std::min(getsum(sum, 0, best + 1), getsum(sum, best + 2, range));
				// ע�⣬һ��Ҫ��>=��ֻ��>�����
				// ���ϻὲ��
				if (after >= before) {
					best++;
				}
				else {
					break;
				}
			}
			ans[range] = std::min(getsum(sum, 0, best), getsum(sum, best + 1, range));
			
		
		}
		return ans;

	}

}

void test_Code02_BestSplitForEveryPosition() {
	int N = 20;
	int maxvalue = 30;
	int minvalue = 0;
	int testTime = 1000;
	cout << "test_Code02_BestSplitForEveryPosition begin" << endl;
	for (int i = 0; i < testTime; i++)
	{
		vector<int> arr = generateRandomArray(N, maxvalue, minvalue);
		vector<int> ans1 = Code02_BestSplitForEveryPosition::bestSplit1(arr);
		vector<int> ans2 = Code02_BestSplitForEveryPosition::bestSplit2(arr);
		vector<int> ans3 = Code02_BestSplitForEveryPosition::bestSplit3(arr);
		if (!vector_equal(ans1, ans2) || !vector_equal(ans2, ans3))
		{
			print(arr);
			print(ans1);
			print(ans2);
			print(ans3);
			break;
		}
	}
	cout << "test_Code02_BestSplitForEveryPosition end" << endl;
}


#endif