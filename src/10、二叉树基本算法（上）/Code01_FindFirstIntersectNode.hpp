#pragma once
#include "utility_func.hpp"
#include <algorithm>
#include <string>
namespace Code01_FindFirstIntersectNode {

	struct Node {
		int value;
		Node * next = nullptr;
		Node(int v) {
			value = v;
		}
	};

	class FindFirstIntersectNode {

	public:
		Node * getIntersectNode(Node * head1, Node * head2) {
			if (head1 == nullptr || head2 == nullptr) {
				return nullptr;
			}
			Node * loop1 = getLoopNode(head1);
			Node * loop2 = getLoopNode(head2);
			if (loop1 == nullptr && loop2 == nullptr) {
				return noLoop(head1, head2);
			}
			if (loop1 != nullptr && loop2 != nullptr) {
				return bothLoop(head1, loop1, head2, loop2);
			}
			return nullptr;
		}
		// �ҵ������һ���뻷�ڵ㣬����޻�������null
		Node * getLoopNode(Node * head) {
			if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
				return nullptr;
			}
			// n1 ��  n2 ��
			Node * slow = head->next; // n1 -> slow
			Node * fast = head->next->next; // n2 -> fast
			while (slow != fast) {
				if (fast->next == nullptr || fast->next->next == nullptr) {
					return nullptr;
				}
				fast = fast->next->next;
				slow = slow->next;
			}

			// slow fast  ����
			fast = head; // n2 -> walk again from head
			while (slow != fast) {
				slow = slow->next;
				fast = fast->next;
			}
			// ����
			// L = �ǻ����ֵĳ��ȣ�
			// ������������Ҫ����L�ĳ��ȣ������ߵ����ϣ�����õ�Ϊ����0�̶ȵ�
			// C = ������ĳ���
			// �ӻ�����̶ȵ㿪ʼ�ߣ���Ҫ��C���ȣ������ٴλص�����0�̶ȵ�
			// slow �� fast ͬʱ����㿪ʼ��
			// ����ͬʱ��ʼ�ߣ��ڻ��ϵ�c�̶�����
			// slow �ߵĳ���Ϊ L + c
			// fast �ߵĳ���Ϊ L + c + C
			// �й�ϵ: L+c+C = 2*(L+c)
			// չ��: L + c + C = 2L + 2c
			// ����֮��:
			// C = L + c
			// ��ʱ Fast �� 0��ʼ�� ��Ҫ�� L���ߵ�����0��
			// slow �ڻ��ϵ�c�㣬Ҳ��Ҫ��L��Ҳ���ߵ����ϵ�0��(��Ϊ L = C - c)
			return slow;
		}
		// ������������޻������ص�һ���ཻ�ڵ㣬������뽻������null
		Node * noLoop(Node * head1, Node * head2) {
			if (head1 == nullptr || head2 == nullptr) {
				return nullptr;
			}
			Node * cur1 = head1;
			Node * cur2 = head2;
			int n = 0;
			while (cur1->next != nullptr) {
				n++;
				cur1 = cur1->next;
			}
			while (cur2->next != nullptr) {
				n--;
				cur2 = cur2->next;
			}
			if (cur1 != cur2) {
				return nullptr;
			}
			// n  :  ����1���ȼ�ȥ����2���ȵ�ֵ
			cur1 = n > 0 ? head1 : head2; // ˭����˭��ͷ���cur1
			cur2 = cur1 == head1 ? head2 : head1; // ˭�̣�˭��ͷ���cur2
			n = std::abs(n);
			while (n != 0) {
				n--;
				cur1 = cur1->next;
			}
			while (cur1 != cur2) {
				cur1 = cur1->next;
				cur2 = cur2->next;
			}
			return cur1;
		}
		// ������������޻������ص�һ���ཻ�ڵ㣬������ཻ������null
		Node * bothLoop(Node * head1, Node * loop1, Node * head2, Node * loop2) {
		
			Node * cur1 =  nullptr;
			Node * cur2 = nullptr;
			if (loop1 == loop2) {
				cur1 = head1;
				cur2 = head2;
				int n = 0;
				while (cur1 != loop1) {
					n++;
					cur1 = cur1->next;
				}
				while (cur2 != loop2) {
					n--;
					cur2 = cur2->next;
				}
				cur1 = n > 0 ? head1 : head2;
				cur2 = cur1 == head1 ? head2 : head1;
				n = std::abs(n);
				while (n != 0) {
					n--;
					cur1 = cur1->next;
				}
				while (cur1 != cur2) {
					cur1 = cur1->next;
					cur2 = cur2->next;
				}
				return cur1;
			}
			else {
				cur1 = loop1->next;
				while (cur1 != loop1) {
					if (cur1 == loop2) {
						return loop1;
					}
					cur1 = cur1->next;
				}
				return nullptr;
			}
		}

	};

	void destroyList(Node * head) {
		while (head != nullptr)
		{
			Node * tmp = head->next;
			delete head;
			head = tmp;
		}
		return;
	}

	void test_main() {
		FindFirstIntersectNode ff;
		// 1->2->3->4->5->6->7->null
		Node * head1 = new Node(1);
		head1->next = new Node(2);
		head1->next->next = new Node(3);
		head1->next->next->next = new Node(4);
		head1->next->next->next->next = new Node(5);
		head1->next->next->next->next->next = new Node(6);
		head1->next->next->next->next->next->next = new Node(7);

		// 0->9->8->6->7->null
		Node * head2 = new Node(0);
		head2->next = new Node(9);
		head2->next->next = new Node(8);
		head2->next->next->next = head1->next->next->next->next->next; // 8->6
		Node * intersect = ff.getIntersectNode(head1, head2);
		cout << (intersect!=nullptr? std::to_string(intersect->value):"null") << endl;
		head2->next->next->next = nullptr;
		destroyList(head1); head1 = nullptr;
		destroyList(head2); head2 = nullptr;
		// 1->2->3->4->5->6->7->4...
		head1 = new Node(1);
		head1->next = new Node(2);
		head1->next->next = new Node(3);
		head1->next->next->next = new Node(4);
		head1->next->next->next->next = new Node(5);
		head1->next->next->next->next->next = new Node(6);
		head1->next->next->next->next->next->next = new Node(7);
		head1->next->next->next->next->next->next = head1->next->next->next; // 7->4
		
		// 0->9->8->2...
		head2 = new Node(0);
		head2->next = new Node(9);
		head2->next->next = new Node(8);
		head2->next->next->next = head1->next; // 8->2
		intersect = ff.getIntersectNode(head1, head2);
		cout << (intersect != nullptr ? std::to_string(intersect->value) : "null") << endl;
		head2->next->next->next = nullptr;
		destroyList(head2); head2 = nullptr;
		// 0->9->8->6->4->5->6..
		head2 = new Node(0);
		head2->next = new Node(9);
		head2->next->next = new Node(8);
		head2->next->next->next = head1->next->next->next->next->next; // 8->6
		intersect = ff.getIntersectNode(head1, head2);
		cout << (intersect != nullptr ? std::to_string(intersect->value) : "null") << endl;
		head2->next->next->next = nullptr;
		destroyList(head2); head2 = nullptr;
		head1->next->next->next->next->next->next = nullptr;
		destroyList(head1); head1 = nullptr;
	}

}


void test_Code01_FindFirstIntersectNode() {

	cout << "test_Code01_FindFirstIntersectNode begin" << endl;
	Code01_FindFirstIntersectNode::test_main();
	cout << "test_Code01_FindFirstIntersectNode end" << endl;
}