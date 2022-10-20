#pragma once
#ifndef Code03_DeleteAdjacentSameCharacter_HPP
#define Code03_DeleteAdjacentSameCharacter_HPP
#include "utility_func.hpp"
#include <iostream>
#include <algorithm>
#include <string>
// ���һ���ַ����ڵ�λ��û����ͬ�ַ�����ô���λ�õ��ַ����ֲ��ܱ�����
// ����:"ab"������a��b�����ܱ�����
// ���һ���ַ����ڵ�λ������ͬ�ַ����Ϳ���һ������
// ����:"abbbc"���м�һ����b�ǿ��Ա������ģ�����֮��ʣ��"ac"
// ĳЩ�ַ���������ˣ�ʣ�µ��ַ���Ϊ���¿���һ��
// ����һ���ַ���������Ծ���ÿһ��������˳��Ŀ�����뾡���ܶ�������ַ����������ٵ�ʣ���ַ�����
// ���磺"aacca", ���������������"aa"����ô��ʣ��"cca"��Ȼ���"cc"������ʣ�µ�"a"���޷�������������1
// ��������������м��"cc"����ô��ʣ��"aaa"�����������һ���ַ�Ҳ��ʣ�ˣ�����0����������Ž⡣
// �ٱ��磺"baaccabb"��
// �������������������a��ʣ��"bccabb"��
// �������������������c��ʣ��"babb"��
// ����������Ҳ������b��ʣ��"ba"�޷�������������2
// �����Ų����ǣ�
// ����������м������c��ʣ��"baaabb"��
// ����������м������a��ʣ��"bbb"��
// �����������b���������κ��ַ�������0����������Ž�

namespace Code03_DeleteAdjacentSameCharacter {

	class Solution {
	public:
		// ������
		 int restMin1(string s) {

			if (s.size() < 2) {
				return s.size();
			}
			int minLen = s.size();
			for (int L = 0; L < s.size(); L++) {
				for (int R = L + 1; R < s.size(); R++) {
					if (canDelete(s.substr(L, R-L+ 1))) {
						minLen = std::min(minLen, restMin1(s.substr(0, L) + s.substr(R + 1)));
					}
				}
			}
			return minLen;
		}

		 bool canDelete(string s) {
			 for (int i = 1; i < s.size(); i++) {
				 if (s[i - 1] != s[i]) {
					 return false;
				 }
			 }
			 return true;
		 }

		 // �������Եı����ݹ�汾
		 int restMin2(string str) {
			 if (str.size() < 2) {
				 return str.size();
			 }
			 return process(str, 0, str.size()-1, false);
		 }



		 int process(string str, int L, int R, bool has) {
			 if (L > R) {
				 return 0;
			 }
			 if (L == R) {
				 return has ? 0 : 1;
			 }
			 int index = L;
			 int K = has ? 1 : 0;
			 while (index <= R && str[index] == str[L]) {
				 K++;
				 index++;
			 }
			 // index��ʾ����һ������[L]�ַ���λ��
			 int way1 = (K > 1 ? 0 : 1) + process(str, index, R, false);
			 int way2 = INT_MAX;
			 for (int split = index; split <= R; split++) {
				 if (str[split] == str[L] && str[split] != str[split - 1]) {
					 if (process(str, index, split - 1, false) == 0) {
						 way2 = std::min(way2, process(str, split, R, K != 0));
					 }
				 }
			 }
			 return std::min(way1, way2);
		 }

		 // �������ԵĶ�̬�滮�汾
		 int restMin3(string str) {

			 if (str.length() < 2) {
				 return str.length();
			 }
			 int N = str.size();
			 vector<vector<vector<int>>> dp(N, vector<vector<int>>(N, vector<int>(2, -1)));
			 return dpProcess(str, 0, N - 1, false, dp);
		 }

		 int dpProcess(string str, int L, int R, bool has, vector<vector<vector<int>>>& dp) {
			 if (L > R) {
				 return 0;
			 }
			 int K = has ? 1 : 0;
			 if (dp[L][R][K] != -1) {
				 return dp[L][R][K];
			 }
			 int ans = 0;
			 if (L == R) {
				 ans = (K == 0 ? 1 : 0);
			 }
			 else {
				 int index = L;
				 int all = K;
				 while (index <= R && str[index] == str[L]) {
					 all++;
					 index++;
				 }
				 int way1 = (all > 1 ? 0 : 1) + dpProcess(str, index, R, false, dp);
				 int way2 = INT_MAX;
				 for (int split = index; split <= R; split++) {
					 if (str[split] == str[L] && str[split] != str[split - 1]) {
						 if (dpProcess(str, index, split - 1, false, dp) == 0) {
							 way2 = std::min(way2, dpProcess(str, split, R, all > 0, dp));
						 }
					 }
				 }
				 ans = std::min(way1, way2);
			 }
			 dp[L][R][K] = ans;
			 return ans;
		 }
	};

}


void test_Code03_DeleteAdjacentSameCharacter() {
	int maxLen = 16;
	int variety = 3;
	int testTime = 1000;

	cout << "test_Code03_DeleteAdjacentSameCharacter begin" << endl;
	Code03_DeleteAdjacentSameCharacter::Solution sln;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<> dist(1, maxLen);
	for (int i = 0; i < testTime; i++) {
		int len = dist(mt);
		string str = generatestr(len, 'a','h');
		int ans1 = sln.restMin1(str);
		int ans2 = sln.restMin2(str);
		int ans3 = sln.restMin3(str);
		if (ans1 != ans2 || ans1 != ans3) {
			cout << ans1 << "," << ans2 << "," << ans3 << endl;
			cout << "�����ˣ�" << endl;
			break;
		}
	}
	cout << "test_Code03_DeleteAdjacentSameCharacter end" << endl;
}


#endif