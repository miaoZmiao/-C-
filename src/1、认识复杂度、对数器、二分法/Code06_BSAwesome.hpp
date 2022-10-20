#pragma once

#include "utility_func.hpp"



namespace Code06_BSAwesome {

	// �ֲ���С
// �������飬�������ֱ�Ȼ����ͬ
// ��������������������Ѱ�Ҿֲ���С
// ��ʾ��
// ֻҪ�ܹ�����һ���������ܹ�һ�����ų�һ������ԣ�
// �����ö��ַ�

	int find_local_minimum(vector<int> & arr) {
		if (arr.size() == 0)
		{
			return -1;
		}
		if (arr.size() == 1)
		{
			return 0;
		}
		if (arr.size() == 2)
		{
			return arr[0] > arr[1] ? 1 : 0;
		}
		// arr.size() >= 3

		if (arr[0] < arr[1])
		{
			return 0;
		}
		if (arr[arr.size() - 1] < arr[arr.size() - 2])
		{
			return arr.size() - 1;
		}

		// 
		int left = 1;
		int right = arr.size() - 2;
		int mid = 0;
		while (left < right)
		{
			int mid = left + ((right - left) >> 1);
			if (arr[mid] > arr[mid + 1])
			{
				left = mid + 1;
			}
			else if (arr[mid] > arr[mid - 1])
			{
				right = mid - 1;
			}
			else
			{
				return mid;
			}
		}
		return left;
	}
	
}