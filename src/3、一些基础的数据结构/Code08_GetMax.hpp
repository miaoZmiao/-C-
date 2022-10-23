#pragma once
#include "utility_func.hpp"

namespace Code08_GetMax {

	// arr[L..R]��Χ�������ֵ  L ... R   N
	int process(vector<int> & arr, int L, int R) {
		// arr[L..R]��Χ��ֻ��һ������ֱ�ӷ��أ�base case
		if (L == R) {
			return arr[L];
		}
		// L...R ��ֻһ����
		// mid = (L + R) / 2
		int mid = L + ((R - L) >> 1); // �е�   	1
		int leftMax = process(arr, L, mid);
		int rightMax = process(arr, mid + 1, R);
		return std::max(leftMax, rightMax);
	}


	// ��arr�е����ֵ
	int getMax(vector<int> & arr) {
		return process(arr, 0, arr.size() - 1);
	}

	
}