#pragma once
#ifndef Code05_HuffmanTree_HPP
#define Code05_HuffmanTree_HPP
#include "utility_func.hpp"
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <queue>
// ���ļ���ǣ���κ�byte���͵�ת��
// ��ôתbyte�Լ�������ֻ����huffman�㷨�������ȷʵ��
// �ַ���Ϊ�յ�ʱ���Լ�����߽��
// ʵ�ֵĴ���ͨ���˴�����������ԵĶ�����
// ���Դ�main���������ݿ�ʼ����

namespace Code05_HuffmanTree {

	unordered_map<char, int> countMap(string s)
	{
		unordered_map<char, int> ans;
		for (char c : s)
		{
			ans[c]++;
		}
		return ans;
	}

	struct Node {
		enum {
			leaf = 0,
			not_leaf =1
		};
		int count_ = 0;
		int type_ = leaf;
		Node* left = nullptr;
		Node* right = nullptr;
		Node(int c, int type = leaf) {
			count_ = c;
			type_ = type;
		}
		~Node() {
			if (left != nullptr)
			{
				delete left;
				left = nullptr;
			}
			if (right != nullptr)
			{
				delete right;
				right = nullptr;
			}
		}
	};

	struct NodeCompare {
		bool operator ()(Node * left ,Node * right)
		{
			return left->count_ > right->count_;
		}
	};

	// �������������ɴ�Ƶ��countMap�����ɹ����������
	// key : �ַ�
	// value: ���ַ������Ķ�������ʽ
	// ���磬Ƶ�ʱ� A��60, B:45, C:13 D:69 E:14 F:5 G:3
	// A 10
	// B 01
	// C 0011
	// D 11
	// E 000
	// F 00101
	// G 00100
	void fillForm(Node * head, string pre, 
		unordered_map<Node*, char> & nodes_to_words,
		unordered_map<char, string>& ans);
	unordered_map<char, string> huffmanForm(unordered_map<char, int> & wordcount) {
	
		unordered_map<char, string> ans;
		if (wordcount.size() == 1)
		{
			for (auto  key : wordcount) {
				ans[key.first] = "0";
			}
			return ans;
		}
		
		unordered_map<Node*, char> nodes_to_words;
		priority_queue<Node*, std::vector<Node*>, NodeCompare> pq;

		for (auto key : wordcount)
		{
			Node * node = new Node(key.second);
			nodes_to_words[node] = key.first;
			pq.push(node);
		}

		while (pq.size() > 1) {
			Node * a = pq.top(); pq.pop();
			Node * b = pq.top(); pq.pop();

			Node * node = new Node(b->count_+a->count_, Node::not_leaf);
			node->left = a;
			node->right = b;
			pq.push(node);
		}

		Node * root = pq.top(); pq.pop();

		fillForm(root, "", nodes_to_words, ans);
		delete root;
		return ans;
	}
	void fillForm(Node * cur, string pre, 
		unordered_map<Node*, char> & nodes_to_words,
		unordered_map<char, string>& ans) {
		if (cur->type_ == Node::leaf)
		{
			ans[nodes_to_words[cur]] = pre;
		}
		else
		{
			fillForm(cur->left, pre + "0", nodes_to_words, ans);
			fillForm(cur->right, pre + "1", nodes_to_words, ans);
		}
	}

	string huffmanEncode(string str, unordered_map<char, string> &huffmanForm) {
		string res;
		for (char c : str)
		{
			res += huffmanForm[c];
		}
		return res;
	}


	struct TrieNode {
		char c_;
		vector<TrieNode*> nexts_;
		TrieNode(char c = 0)
		{
			c_ = c;
			nexts_.resize(2, nullptr);
		}

		~TrieNode() {
			for (auto loc : nexts_)
			{
				if (loc != nullptr)
				{
					delete loc;
				}
			}
		}
	};
	TrieNode* createTrie(unordered_map<char, string> &huffmanForm);
	string huffmanDecode(string str, unordered_map<char, string> & huffmanForm)
	{
		string res;
		TrieNode * root = createTrie(huffmanForm);
		TrieNode * cur = root;
		for (int i = 0; i < str.size();i++)
		{
			char c = str[i];
			int index = (c == '0' ? 0 : 1);
			cur = cur->nexts_[index];
			if (cur->nexts_[0] == nullptr && cur->nexts_[1] == nullptr)
			{
				res.push_back(cur->c_);
				cur = root;
			}
		}
		delete root;
		return res;

		return res;
	}


	TrieNode* createTrie(unordered_map<char, string> &huffmanForm)
	{
		TrieNode * root = new TrieNode();
		for (auto key : huffmanForm)
		{
			string path = key.second;
			TrieNode * cur = root;
			for (char c : path)
			{
				int index =( c == '0' ?0 : 1);
				if (cur->nexts_[index] == nullptr)
				{
					cur->nexts_[index] = new TrieNode();
				}
				cur = cur->nexts_[index];
			}
			cur->c_ = key.first;
		}
		return root;
	}

}

void test_Code05_HuffmanTree() {
	// ���ݴ�Ƶ�����ɹ����������
	cout << "test_Code05_HuffmanTree begin" << endl;
	unordered_map<char, int>  wordcount;
	wordcount['A'] = 60;
	wordcount['B'] = 45;
	wordcount['C'] = 13;
	wordcount['D'] = 69;
	wordcount['E'] = 14;
	wordcount['F'] = 5;
	wordcount['G'] = 3;

	unordered_map<char, string> haffmancode = Code05_HuffmanTree::huffmanForm(wordcount);
	for (auto key : haffmancode)
	{
		cout << key.first << ":" << key.second << endl;
	}

	string str = "CBBBAABBACAABDDEFBA";
	cout << str << endl;
	unordered_map<char, int> cm = Code05_HuffmanTree::countMap(str);
	unordered_map<char, string> hf = Code05_HuffmanTree::huffmanForm(cm);
	string shuffmanEncode = Code05_HuffmanTree::huffmanEncode(str, hf);
	cout << "huffmanEncode:" << shuffmanEncode << endl;
	// huffmanDecode�ǹ��������뻹ԭ�ɵ�ԭʼ�ַ���
	string shuffmanDecode = Code05_HuffmanTree::huffmanDecode(shuffmanEncode, hf);
	cout << "huffmanDecode:" << shuffmanDecode << endl;
	cout << "======================" << endl;
	cout << "������������Կ�ʼ" << endl;
	// �ַ�����󳤶�
	int len = 500;
	// �����ַ�����
	int range = 26;
	// ������Խ��еĴ���
	int testTime = 1000;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<> dist(1, len);
	for (int i = 0; i < testTime; i++)
	{
		int N = dist(mt);
		string test = generatestr(N, 'a', 'z');
		unordered_map<char, int> wordcounts = Code05_HuffmanTree::countMap(test);
		unordered_map<char, string> form = Code05_HuffmanTree::huffmanForm(wordcounts);
		string encode = Code05_HuffmanTree::huffmanEncode(test, form);
		string decode = Code05_HuffmanTree::huffmanDecode(encode, form);
		if (decode != test)
		{
			cout << "������" << endl;
		}
	
	}

	cout << "test_Code05_HuffmanTree end" << endl;

}

#endif