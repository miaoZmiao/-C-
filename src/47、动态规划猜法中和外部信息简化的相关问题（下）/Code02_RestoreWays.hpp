#pragma once
#ifndef Code02_RestoreWays_HPP
#define Code02_RestoreWays_HPP
#include "utility_func.hpp"
#include "stop_watch.hpp"
#include <iomanip>
// ��������arr����Ϊn(3 <= n <= 10^4)�����ÿ��������<=200����������������������
// 1. 0λ�õ�Ҫ��arr[0]<=arr[1] 
// 2. n-1λ�õ�Ҫ��arr[n-1]<=arr[n-2]
// 3. �м�iλ�õ�Ҫ��arr[i]<=max(arr[i-1],arr[i+1]) 
// ������arr��Щ���ֶ�ʧ�ˣ�����kλ�õ�����֮ǰ����������ʧ֮��kλ�õ�����Ϊ0
// �������������������������ж����ֲ�ͬ��arr����������������
// ���� [6,0,9] ֻ�л�ԭ�� [6,9,9]����ȫ���������������Է���1�֣���[6,9,9]���
namespace Code02_RestoreWays {

	class Solution {
	public:
		int ways0(vector<int> & arr) {
			return process0(arr, 0);
		}
		int process0(vector<int> & arr, int index) {
			if (index == arr.size()) {
				return isValid(arr) ? 1 : 0;
			}
			else {
				if (arr[index] != 0) {
					return process0(arr, index + 1);
				}
				else {
					int ways = 0;
					for (int v = 1; v < 201; v++) {
						arr[index] = v;
						ways += process0(arr, index + 1);
					}
					arr[index] = 0;
					return ways;
				}
			}
		}

		bool isValid(vector<int> & arr) {
			if (arr[0] > arr[1]) {
				return false;
			}
			if (arr[arr.size() - 1] > arr[arr.size() - 2]) {
				return false;
			}
			for (int i = 1; i < arr.size() - 1; i++) {
				if (arr[i] > std::max(arr[i - 1], arr[i + 1])) {
					return false;
				}
			}
			return true;
		}

		int ways1(vector<int> & arr) {
			int N = arr.size();
			if (arr[N - 1] != 0) {
				return process1(arr, N - 1, arr[N - 1], 2);
			}
			else {
				int ways = 0;
				for (int v = 1; v < 201; v++) {
					ways += process1(arr, N - 1, v, 2);
				}
				return ways;
			}
		}
		// ���iλ�õ����ֱ����v,
		// ����arr[i]��arr[i+1]�Ĺ�ϵΪs��
		// s==0������arr[i] < arr[i+1] �Ҵ�
		// s==1������arr[i] == arr[i+1] ��=��ǰ
		// s==2������arr[i] > arr[i+1] ��С
		// ����0...i��Χ���ж�������Ч��ת����ʽ��
		int process1(vector<int> & arr, int i, int v, int s) {
			if (i == 0) { // 0...i ֻʣһ�����ˣ�0...0
				return ((s == 0 || s == 1) && (arr[0] == 0 || v == arr[0])) ? 1 : 0;
			}
			// i > 0
			if (arr[i] != 0 && v != arr[i]) {
				return 0;
			}
			// i>0 �����ң� iλ�õ�����Ŀ��Ա��V��
			int ways = 0;
			if (s == 0 || s == 1) { // [i] -> V <= [i+1]
				for (int pre = 1; pre < 201; pre++) {
					ways += process1(arr, i - 1, pre, pre < v ? 0 : (pre == v ? 1 : 2));
				}
			}
			else { // ? ��ǰ > �� ��ǰ <= max{����}
				for (int pre = v; pre < 201; pre++) {
					ways += process1(arr, i - 1, pre, pre == v ? 1 : 2);
				}
			}
			return ways;
		}

		int zuo(vector<int> & arr, int i, int v, int s) {
			if (i == 0) { // 0...i ֻʣһ�����ˣ�0...0
				return ((s == 0 || s == 1) && (arr[0] == 0 || v == arr[0])) ? 1 : 0;
			}
			// i > 0
			if (arr[i] != 0 && v != arr[i]) {
				return 0;
			}
			// i>0 �����ң� iλ�õ�����Ŀ��Ա��V��
			int ways = 0;
			if (s == 0 || s == 1) { // [i] -> V <= [i+1]
				for (int pre = 1; pre < v; pre++) {
					ways += zuo(arr, i - 1, pre, 0);
				}
			}
			ways += zuo(arr, i - 1, v, 1);
			for (int pre = v + 1; pre < 201; pre++) {
				ways += zuo(arr, i - 1, pre, 2);
			}
			return ways;
		}

		int ways2(vector<int> & arr) {
			int N = arr.size();
			vector<vector<vector<int>>> dp(N, vector<vector<int>>(201, vector<int>(3, 0)));
			if (arr[0] != 0) {
				dp[0][arr[0]][0] = 1;
				dp[0][arr[0]][1] = 1;
			}
			else {
				for (int v = 1; v < 201; v++) {
					dp[0][v][0] = 1;
					dp[0][v][1] = 1;
				}
			}
			for (int i = 1; i < N; i++) {
				for (int v = 1; v < 201; v++) {
					for (int s = 0; s < 3; s++) {
						if (arr[i] == 0 || v == arr[i]) {
							if (s == 0 || s == 1) {
								for (int pre = 1; pre < v; pre++) {
									dp[i][v][s] += dp[i - 1][pre][0];
								}
							}
							dp[i][v][s] += dp[i - 1][v][1];
							for (int pre = v + 1; pre < 201; pre++) {
								dp[i][v][s] += dp[i - 1][pre][2];
							}
						}
					}
				}
			}
			if (arr[N - 1] != 0) {
				return dp[N - 1][arr[N - 1]][2];
			}
			else {
				int ways = 0;
				for (int v = 1; v < 201; v++) {
					ways += dp[N - 1][v][2];
				}
				return ways;
			}
		}

		int ways3(vector<int> & arr) {
			int N = arr.size();
			vector<vector<vector<int>>> dp(N, vector<vector<int>>(201, vector<int>(3, 0)));
			if (arr[0] != 0) {
				dp[0][arr[0]][0] = 1;
				dp[0][arr[0]][1] = 1;
			}
			else {
				for (int v = 1; v < 201; v++) {
					dp[0][v][0] = 1;
					dp[0][v][1] = 1;
				}
			}
			vector<vector<int>> presum(201, vector<int>(3, 0));
			for (int v = 1; v < 201; v++) {
				for (int s = 0; s < 3; s++) {
					presum[v][s] = presum[v - 1][s] + dp[0][v][s];
				}
			}
			for (int i = 1; i < N; i++) {
				for (int v = 1; v < 201; v++) {
					for (int s = 0; s < 3; s++) {
						if (arr[i] == 0 || v == arr[i]) {
							if (s == 0 || s == 1) {
								dp[i][v][s] += sum(1, v - 1, 0, presum);
							}
							dp[i][v][s] += dp[i - 1][v][1];
							dp[i][v][s] += sum(v + 1, 200, 2, presum);
						}
					}
				}
				for (int v = 1; v < 201; v++) {
					for (int s = 0; s < 3; s++) {
						presum[v][s] = presum[v - 1][s] + dp[i][v][s];
					}
				}
			}
			if (arr[N - 1] != 0) {
				return dp[N - 1][arr[N - 1]][2];
			}
			else {
				return sum(1, 200, 2, presum);
			}
		}

		int sum(int begin, int end, int relation, vector<vector<int>>& presum) {
			return presum[end][relation] - presum[begin - 1][relation];
		}

		vector<int> generateRandomArray(int len) {

			vector<int> ans(len, 0);
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_real_distribution<> dist(0.0, 1.0);
			for (int i = 0; i < ans.size(); i++) {
				if (dist(mt)< 0.5) {
					ans[i] = 0;
				}
				else {
					ans[i] = (int)(dist(mt) * 200) + 1;
				}
			}
			return ans;
		}


	};
}

void test_Code02_RestoreWays() {
	int len = 5;
	int testTime = 15;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<> dist(2, len);
	cout << "test_Code02_RestoreWays begin" << endl;
	Code02_RestoreWays::Solution sln;
	stop_watch st;
	double elapse0 = 0.0, elapse1 = 0.0, elapse2 = 0.0, elapse3 = 0.0;
	for (int i = 0; i < testTime; i++)
	{
		int N = dist(mt);
		vector<int> arr = sln.generateRandomArray(N);
		st.start();
		int ans0 = sln.ways0(arr);
		st.stop();
		elapse0 += st.elapsed_ms();
		st.start();
		int ans1 = sln.ways1(arr);
		st.stop();
		elapse1 += st.elapsed_ms();
		st.start();
		int ans2 = sln.ways2(arr);
		st.stop();
		elapse2 += st.elapsed_ms();
		st.start();
		int ans3 = sln.ways3(arr);
		st.stop();
		elapse3 += st.elapsed_ms();
		if (ans0 != ans1 || ans2 != ans3 || ans0 != ans2) {
			cout << "Oops" << endl;
		}

	}
	cout << "average elapse ms" << endl;
	cout << std::setprecision(3) << endl;
	cout << "way0:" << elapse0/ testTime << endl;
	cout << "way1:" << elapse1/ testTime << endl;
	cout << "way2:" << elapse2 / testTime << endl;
	cout << "way3:" << elapse3 / testTime << endl;
	cout << "test_Code02_RestoreWays end" << endl;
}

#endif