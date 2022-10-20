#pragma once

#include "utility_func.hpp"

namespace Code03_KM {

	// 
	// һ�����ֳ���K�Σ�������������M�Σ�
	//  M>1, K < M,
	// Ҫ���ҵ�����K�ε����֣�Ҫ�����ռ临�Ӷ�O(1)��ʱ�临�Ӷ�O(N)

	// arr��ֻ��һ�ֳ�����K��,���������M��
	// 

	int onlyKtimes(vector<int>& arr, int M, int K)
	{
		vector<int> alphabet(32, 0);
		for (auto it : arr)
		{
			for (int i = 0; i <= 31; i++)
			{
				if ((it&(1 << i)) != 0)
				{
					alphabet[i]++;
				}
			}
		}
		int ans = 0;
		for (int i = 0; i < 32; i++)
		{
			if ((alphabet[i] % M) != 0)
			{
				ans = ans | (1 << i);
			}
		}
		return ans;
	}
}