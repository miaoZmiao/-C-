#pragma once
#include "utility_func.hpp"

namespace Code04_BSExist {

	bool  findNumber(vector<int> & arr, int target) {
		if (arr.size() == 0)
		{
			return false;
		}

		int left = 0;
		int right = arr.size() - 1;
		int mid = 0;
		// �γ��Ͻ��˵�����Ҫ < ����<= 
		// �����ڱ߽������Ŀ��ǣ��������߼������߼���
		// �㷨���˼��һ����ǰ���£�С�ı߽������������
		// ���û����·
		while (left < right)
		{
			mid = left + ((right - left) >> 1);
			if (arr[mid] == target)
			{
				return true;
			}
			else if (arr[mid] > target)
			{
				right = mid - 1;
			}
			else if (arr[mid] < target)
			{
				left = mid + 1;
			}
		}

		return target == arr[left];

	}

}