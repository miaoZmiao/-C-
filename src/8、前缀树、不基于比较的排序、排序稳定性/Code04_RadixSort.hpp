#pragma once

#include "utility_func.hpp"
#include <algorithm>
#include <cmath>
namespace Code04_RadixSort {

	int maxbits(const vector<int> & arr) {
		int max = INT_MIN;
		for (int i = 0; i < arr.size(); i++) {
			max = std::max(max, arr[i]);
		}
		int res = 0;
		while (max != 0) {
			res++;
			max /= 10;
		}
		return res;
	}


	int getDigit(int x, int d) {
		return ((x / ((int)std::pow(10, d - 1))) % 10);
	}


	void radixSort(vector<int> & arr, int L, int R, int digit) {
		const int radix = 10;
		int i = 0, j = 0;
		// �ж��ٸ���׼�����ٸ������ռ�
		vector<int> help(R - L + 1, 0);
		for (int d = 1; d <= digit; d++) { // �ж���λ�ͽ�������
			// 10���ռ�
			// count[0] ��ǰλ(dλ)��0�������ж��ٸ�
			// count[1] ��ǰλ(dλ)��(0��1)�������ж��ٸ�
			// count[2] ��ǰλ(dλ)��(0��1��2)�������ж��ٸ�
			// count[i] ��ǰλ(dλ)��(0~i)�������ж��ٸ�
			vector<int> count(radix, 0); // count[0..9]
			for (i = L; i <= R; i++) {
				// 103  1   3
				// 209  1   9
				j = getDigit(arr[i], d);
				count[j]++;
			}
			for (i = 1; i < radix; i++) {
				count[i] = count[i] + count[i - 1];
			}
			for (i = R; i >= L; i--) {
				j = getDigit(arr[i], d);
				help[count[j] - 1] = arr[i];
				count[j]--;
			}
			for (i = L, j = 0; i <= R; i++, j++) {
				arr[i] = help[j];
			}
		}
	}

	// only for no-negative value
	void radixSort(vector<int> & arr) {
		if (arr.size() < 2) {
			return;
		}
		radixSort(arr, 0, arr.size() - 1, maxbits(arr));
	}

	void test_main() {
		
		int testTime = 5000;
		int maxSize = 100;
		int maxValue = 1000;
		bool succeed = true;
		for (int i = 0; i < testTime; i++) {
			vector<int> arr1 = generateRandomArray(maxSize, maxValue);
			vector<int> arr2 = arr1;
			radixSort(arr1);
			std::sort(arr2.begin(), arr2.end());
			if (!vector_equal(arr1, arr2)) {
				succeed = false;
				print(arr1);
				print(arr2);
				break;
			}
		}
		cout << (succeed ? "Nice!" : "Fucking fucked!") << endl;

	}


}




void test_Code04_RadixSort() {

	cout << "test_Code04_RadixSort begin" << endl;
	Code04_RadixSort::test_main();
	cout << "test_Code04_RadixSort end" << endl;
}