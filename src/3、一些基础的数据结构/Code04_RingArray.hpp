#pragma once
#include "utility_func.hpp"
namespace Code04_RingArray {
	class MyQueue {
		vector<int> arr;
		int pushi;// end
		int polli;// begin
		int size;
		int limit;
	public:
		MyQueue(int limit) {
			pushi = 0;
			polli = 0;
			size = 0;
			limit = limit;
		}

		void push(int value) {
			if (size == limit) {
				throw  std::runtime_error("�������ˣ������ټ���");
			}
			size++;
			arr[pushi] = value;
			pushi = nextIndex(pushi);
		}

		int pop() {
			if (size == 0) {
				throw std::runtime_error("���п��ˣ�����������");
			}
			size--;
			int ans = arr[polli];
			polli = nextIndex(polli);
			return ans;
		}

		bool isEmpty() {
			return size == 0;
		}

		// ������ڵ��±���i��������һ��λ��
		int nextIndex(int i) {
			return i < limit - 1 ? i + 1 : 0;
		}

	};
	
}