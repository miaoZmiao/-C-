#pragma once
#include "utility_func.hpp"
#include <iostream>
#include "scope_guard.h"
namespace Code04_MaxHappyA {

	struct Employee {
		int happy;
		vector<Employee*> nexts;

		Employee(int h) {
			happy = h;
		}
		~Employee() {
			for (auto & e : nexts)
			{
				if (e != nullptr)
				{
					delete e;
					e = nullptr;
				}
			}
		}
	};


	class MaxHappy {
	public:
		int maxHappy1(Employee * boss) {
			if (boss == nullptr) {
				return 0;
			}
			return process1(boss, false);
		}

		// ��ǰ�����Ľڵ��cur��
		// up��ʾcur���ϼ��Ƿ�����
		// �ú������壺
		// ���upΪtrue����ʾ��cur�ϼ��Ѿ�ȷ������������£�cur�������ܹ��ṩ���Ŀ���ֵ�Ƕ��٣�
		// ���upΪfalse����ʾ��cur�ϼ��Ѿ�ȷ��������������£�cur�������ܹ��ṩ���Ŀ���ֵ�Ƕ��٣�
		int process1(Employee * cur, bool up) {
			if (up) { // ���cur���ϼ����Ļ���curû��ѡ��ֻ�ܲ���
				int ans = 0;
				for (Employee * next : cur->nexts) {
					ans += process1(next, false);
				}
				return ans;
			}
			else { // ���cur���ϼ������Ļ���cur����ѡ��������Ҳ���Բ���
				int p1 = cur->happy;
				int p2 = 0;
				for (Employee * next : cur->nexts) {
					p1 += process1(next, true);
					p2 += process1(next, false);
				}
				return std::max(p1, p2);
			}
		}

		struct Info {
			int no;
			int yes;

			Info(int n, int y) {
				no = n;
				yes = y;
			}
		};

		int maxHappy2(Employee * head) {
			Info allInfo = process(head);
			return std::max(allInfo.no, allInfo.yes);
		}

		

		Info process(Employee * x) {
			if (x == nullptr) {
				return Info(0, 0);
			}
			int no = 0;
			int yes = x->happy;
			for (Employee * next : x->nexts) {
				Info nextInfo = process(next);
				no += std::max(nextInfo.no, nextInfo.yes);
				yes += nextInfo.no;

			}
			return Info(no, yes);
		}
	};


	void genarateNexts(Employee * e, int level, int maxLevel, int maxNexts, int maxHappy, std::function<double()> rg);
	// for test
	Employee * genarateBoss(int maxLevel, int maxNexts, int maxHappy) {

		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<> dist(0.0, 1.0);
		auto get_random = [&]()->double {
			return dist(mt);
		};
		if (get_random() < 0.02) {
			return nullptr;
		}
		Employee * boss = new Employee((int)(get_random() * (maxHappy + 1)));
		genarateNexts(boss, 1, maxLevel, maxNexts, maxHappy, get_random);
		return boss;
	}

	// for test
	void genarateNexts(Employee * e, int level, int maxLevel, int maxNexts, int maxHappy , std::function<double()> rg) {
		if (level > maxLevel) {
			return;
		}
		int nextsSize = (int)(rg() * (maxNexts + 1));
		for (int i = 0; i < nextsSize; i++) {
			Employee * next = new Employee((int)(rg() * (maxHappy + 1)));
			e->nexts.push_back(next);
			genarateNexts(next, level + 1, maxLevel, maxNexts, maxHappy, rg);
		}
	}

	void test_main() {
		int maxLevel = 4;
		int maxNexts = 7;
		int maxHappy = 100;
		int testTimes = 1000;
		MaxHappy mh;
		for (int i = 0; i < testTimes; i++) {
			Employee *  boss = genarateBoss(maxLevel, maxNexts, maxHappy);
			scope_guard sg([boss]() {
				if (boss != nullptr)
				{
					delete boss;
				}
			});
			if (mh.maxHappy1(boss) != mh.maxHappy2(boss)) {
				cout<<"Oops!"<<endl;
				break;
			}
		}
	
	}


}

void test_Code04_MaxHappy() {

	cout << "test_Code04_MaxHappy begin" << endl;
	Code04_MaxHappyA::test_main();
	cout << "test_Code04_MaxHappy end" << endl;
}