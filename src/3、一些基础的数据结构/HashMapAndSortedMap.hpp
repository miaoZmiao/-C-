#pragma once
#include <unordered_map>
#include <map>
#include <set>
#include <unordered_set>
using namespace std;

namespace HashMapAndSortedMap {

	// C++ ���Ҫʹ��  �Զ�������T ��Ϊ unordered_map
	// ���� unordered_set ���͵�  KEY
	// ����Ҫ���� T ���͵� hash ����
	// ������ std �����ռ� ��������T��ƫ�ػ�ʵ��
	//
	//namespace std {
	//	
	//	template<>
	//	struct std::hash<T> {
	//		size_t operator()(const T & obj)
	//		{
	//			// write your own hash calculate
	//			result = 1023051;
	//			return size_t(result);
	//		}
	//	};
	//}
	// ʵ����һ�� ��T������ΪKey �� unordered_map ����
	//  unordered_map<T, int>  umap1;
	// ʵ����һ�� ��T������ΪKey �� unordered_set ����
	//  unordered_set<T>  uset1;
	// ���Ҫʹ���Զ���������Ϊ map set �� KEY
	//  ��Ҫ����  ����T �ıȽϲ�����������map set ��ʵ��������Ϊ���Ͳ�������
	// 
	//struct MyCompare{
	//	
	//	bool operator()(const T & left, const T & right) const {
	//		// write you own campare calculate
	//		
	//		return left.value < right.value;
	//	}
	//};
	// ʵ���� map ��ʱ���� MyCompare 
	// map<T, int, MyCompare> map1;
	// ʵ���� set ��ʱ���� MyCompare
	// set<T, MyCompare> set1;
}