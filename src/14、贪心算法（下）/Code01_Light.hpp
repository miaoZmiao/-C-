#pragma once
#include <vector>
#include <string>
#include "utility_func.hpp"
#include <unordered_set>
#include <algorithm>
namespace Code01_Light {

	class Light {
	public:
		int minLight1(string road) {
			if (road.size() == 0) {
				return 0;
			}
			set<int> lights;
			return process(road, 0, lights);
		}

		// str[index....]λ�ã�����ѡ��ŵƻ��ǲ��ŵ�
		// str[0..index-1]λ���أ��Ѿ���������ˣ���Щ���˵Ƶ�λ�ã�����lights��
		// Ҫ��ѡ������������.�ķ�������������Щ��Ч�ķ����У�����������Ҫ������
		int process(const string & str, int index, set<int> & lights) {
			if (index == str.size()) { // ������ʱ��
				for (int i = 0; i < str.size(); i++) {
					if (str[i] != 'X') { // ��ǰλ���ǵ�Ļ�
						if (!lights.count(i - 1) && !lights.count(i) && !lights.count(i + 1)) {
							return INT_MAX;
						}
					}
				}
				return lights.size();
			}
			else { // str��û����
			 // i X .
				int no = process(str, index + 1, lights);
				int yes = INT_MAX;
				if (str[index] == '.') {
					lights.insert(index);
					yes = process(str, index + 1, lights);
					lights.erase(index);
				}
				return std::min(no, yes);
			}
		}

		int minLight2(string road) {
			string  str = road;
			int i = 0;
			int light = 0;
			while (i < str.size()) {
				if (str[i] == 'X') {
					i++;
				}
				else {
					light++;
					if (i + 1 == str.size()) {
						break;
					}
					else { // ��iλ��  i+ 1   X  .
						if (str[i + 1] == 'X') {
							i = i + 2;
						}
						else {
							i = i + 3;
						}
					}
				}
			}
			return light;
		}
	};


	// for test
	string randomstring(int len) {
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<>  dist(0.0, 1.0);

		string res((int)(dist(mt) * len) + 1, '\0');
		for (int i = 0; i < res.size(); i++) {
			res[i] = dist(mt) < 0.5 ? 'X' : '.';
		}
		return res;
	}

	void test_main() {
		int len = 20;
		int testTime = 1000;
		Light lt;
		for (int i = 0; i < testTime; i++) {
			string test = randomstring(len);
			int ans1 = lt.minLight1(test);
			int ans2 = lt.minLight2(test);
			if (ans1 != ans2) {
				cout << "oops!" << endl;
				break;
			}
		}
	
	}

}

void test_Code01_Light() {
	
	cout << "test_Code01_Light begin" << endl;
	Code01_Light::test_main();
	cout << "test_Code01_Light end" << endl;

}