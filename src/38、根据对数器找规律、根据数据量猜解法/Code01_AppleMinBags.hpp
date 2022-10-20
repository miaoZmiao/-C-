#pragma once
#ifndef Code01_AppleMinBags_HPP
#define Code01_AppleMinBags_HPP
#include <iostream>
using namespace std;
namespace Code01_AppleMinBags {
	/*	��Ŀһ
		С��ȥ��ƻ�����̵�ֻ�ṩ�������͵����ϴ���ÿ�����Ͷ�������������
		1����װ��6��ƻ���Ĵ���
		2����װ��8��ƻ���Ĵ���
		С����������ʹ�����ִ�����װƻ��������С����ǿ��֢����Ҫ���Լ�ʹ�õĴ��������������٣���ʹ�õ�ÿ�����ӱ���װ����
		����һ��������N����������ʹ�ö��ٴ��ӡ����N�޷���ʹ�õ�ÿ�����ӱ���װ�������� - 1
	*/
	int minBags(int apple) {
		if (apple < 0) {
			return -1;
		}
		int bag8 = (apple >> 3);
		int rest = apple - (bag8 << 3);
		while (bag8 >= 0) {
			// rest ��
			if (rest % 6 == 0) {
				return bag8 + (rest / 6);
			}
			else {
				bag8--;
				rest += 8;
			}
		}
		return -1;
	}

	int minBagAwesome(int apple) {
		if ((apple & 1) != 0) { // ���������������-1
			return -1;
		}
		if (apple < 18) {
			return apple == 0 ? 0 : (apple == 6 || apple == 8) ? 1
				: (apple == 12 || apple == 14 || apple == 16) ? 2 : -1;
		}
		return (apple - 18) / 8 + 3;
	}

}

void test_Code01_AppleMinBags() {

	cout << "test Code01_AppleMinBags begin" << endl;
	for (int i = 0; i < 200; i++)
	{
		cout << i<<":" << Code01_AppleMinBags::minBags(i) << endl;
	}
	cout << "test Code01_AppleMinBags end" << endl;
}


#endif