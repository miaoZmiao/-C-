#pragma once
#include <iostream>
#include "utility_func.hpp"
#include <unordered_map>
namespace Code04_CopyListWithRandom {

	struct Node {
		int value;
		Node * next = nullptr;
		Node * random = nullptr;
		Node(int data) {
			value = data;
		}
	};

	Node * copyRandomList1(Node * head) {
		// key �Ͻڵ�
		// value �½ڵ�
		unordered_map<Node *, Node *> map;
		Node * cur = head;
		while (cur != nullptr) {
			map.insert({ cur, new Node(cur->value) });
			cur = cur->next;
		}
		cur = head;
		while (cur != nullptr) {
			// cur ��
			map[cur]->next = map[cur->next];
			map[cur]->random = map[cur]->random;
			cur = cur->next;
		}
		return map[head];
	}

	void destroyList(Node * head) {
		while (head != nullptr)
		{
			Node * tmp = head->next;
			delete head;
			head = tmp;
		}
		return;
	}

	Node * copyRandomList2(Node * head) {
		if (head == nullptr) {
			return nullptr;
		}
		Node * cur = head;
		Node * next = nullptr;
		// 1 -> 2 -> 3 -> null
		// 1 -> 1' -> 2 -> 2' -> 3 -> 3'
		while (cur != nullptr) {
			next = cur->next;
			cur->next = new Node(cur->value);
			cur->next->next = next;
			cur = next;
		}
		cur = head;
		Node * copy = nullptr;
		// 1 1' 2 2' 3 3'
		// �������� 1' 2' 3' randomָ��
		while (cur != nullptr) {
			next = cur->next->next;
			copy = cur->next;
			copy->random = cur->random != nullptr ? cur->random->next : nullptr;
			cur = next;
		}
		Node * res = head->next;
		cur = head;
		// �� �� ����һ��next�����ϣ�random��ȷ
		// next�����ϣ��������������
		while (cur != nullptr) {
			next = cur->next->next;
			copy = cur->next;
			cur->next = next;
			copy->next = next != nullptr ? next->next : nullptr;
			cur = next;
		}
		return res;
	}

}
