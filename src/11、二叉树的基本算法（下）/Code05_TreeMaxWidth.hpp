#pragma once
#include "treeNode.hpp"
#include <unordered_map>
#include <queue>
#include <algorithm>
#include "scope_guard.h"
namespace Code05_TreeMaxWidth {
	int maxWidthUseMap(Node * head) {
		if (head == nullptr) {
			return 0;
		}
		queue<Node *> queue;
		queue.push(head);
		// key �� ��һ�㣬value
		unordered_map<Node*, int> levelMap;
		levelMap.insert({ head, 1 });
		int curLevel = 1; // ��ǰ������ͳ����һ��Ŀ��
		int curLevelNodes = 0; // ��ǰ��curLevel�㣬���Ŀǰ�Ƕ���
		int max = 0;
		while (!queue.empty()) {
			Node * cur = queue.front();
			queue.pop();
			int curNodeLevel = levelMap[(cur)];
			if (cur->left != nullptr) {
				levelMap.insert({ cur->left, curNodeLevel + 1 });
				queue.push(cur->left);
			}
			if (cur->right != nullptr) {
				levelMap.insert({ cur->right, curNodeLevel + 1 });
				queue.push(cur->right);
			}
			if (curNodeLevel == curLevel) {
				curLevelNodes++;
			}
			else {
				max = std::max(max, curLevelNodes);
				curLevel++;
				curLevelNodes = 1;
			}
		}
		max = std::max(max, curLevelNodes);
		return max;
	}


	int maxWidthNoMap(Node * head) {
		if (head == nullptr) {
			return 0;
		}
		queue<Node*> queue;
		queue.push(head);
		Node * curEnd = head; // ��ǰ�㣬���ҽڵ���˭
		Node * nextEnd = nullptr; // ��һ�㣬���ҽڵ���˭
		int max = 0;
		int curLevelNodes = 0; // ��ǰ��Ľڵ���
		while (!queue.empty()) {
			Node * cur = queue.front();
			queue.pop();
			if (cur->left != nullptr) {
				queue.push(cur->left);
				nextEnd = cur->left;
			}
			if (cur->right != nullptr) {
				queue.push(cur->right);
				nextEnd = cur->right;
			}
			curLevelNodes++;
			if (cur == curEnd) {
				max = std::max(max, curLevelNodes);
				curLevelNodes = 0;
				curEnd = nextEnd;
			}
		}
		return max;
	}

	void test_main() {
		int maxLevel = 10;
		int maxValue = 100;
		int testTimes = 1000;
		for (int i = 0; i < testTimes; i++) {
			Node * head = generatetree(maxLevel);
			scope_guard sg([head]() {
				if (head != nullptr)
				{
					delete head;
				}
			});
			if (maxWidthUseMap(head) != maxWidthNoMap(head)) {
				cout << "Oops" << endl;
				break;
			}
		}
	}
}

void test_Code05_TreeMaxWidth() {

	cout << "test_Code05_TreeMaxWidth begin" << endl;
	Code05_TreeMaxWidth::test_main();
	cout << "test_Code05_TreeMaxWidth end" << endl;
}