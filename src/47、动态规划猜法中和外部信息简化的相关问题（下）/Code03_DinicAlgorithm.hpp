#pragma once
#ifndef Code03_DinicAlgorithm_HPP
#define Code03_DinicAlgorithm_HPP
#include "utility_func.hpp"
#include <iostream>
#include <queue>
// �����������:
// https://lightoj.com/problem/internet-bandwidth
// ����һ��DinicAlgorithm�㷨����
// �����´���ճ������ҳ���ṩ��java������������
// ����Ҫ�޸��κ����ݿ���ֱ��ͨ��
// �뿴��ҳ�ϵ���Ŀ���������main������д��ȥ�˽����ģ����÷�
namespace Code03_DinicAlgorithm {

	struct Edge {
		int from;
		int to;
		int available;
		Edge() {}
		Edge(int a, int b, int c) {
			from = a;
			to = b;
			available = c;
		}
	};


	class Dinic {
	public:
		int N;
		vector<vector<int>> nexts;
		vector<Edge> edges;
		vector<int> depth;
		vector<int> cur;
		Dinic(int nums) {
			N = nums + 1;
			
			for (int i = 0; i <= N; i++) {
				nexts.push_back(vector<int>());
			}
			edges.resize(N);
			depth.resize(N);
			cur.resize(N);
		}

		void addEdge(int u, int v, int r) {
			int m = edges.size();
			edges.push_back(Edge(u, v, r));
			nexts[u].push_back(m);
			edges.push_back(Edge(v, u, 0));
			nexts[v].push_back(m + 1);
		}

		int maxFlow(int s, int t) {
			int flow = 0;
			while (bfs(s, t)) {
				std::fill(cur.begin(), cur.end(), 0);
				flow += dfs(s, t, INT_MAX);
				std::fill(depth.begin(), depth.end(), 0);
			}
			return flow;
		}

		bool bfs(int s, int t) {
			std::queue<int> queue;
			queue.push(s);
			vector<bool> visited(N, false);
			visited[s] = true;
			while (!queue.empty()) {
				int u = queue.front();
				queue.pop();
				for (int i = 0; i < nexts[u].size(); i++) {
					Edge e = edges[nexts[u][i]];
					int v = e.to;
					if (!visited[v] && e.available > 0) {
						visited[v] = true;
						depth[v] = depth[u] + 1;
						if (v == t) {
							break;
						}
						queue.push(v);
					}
				}
			}
			return visited[t];
		}

		// ��ǰ������s�㣬s�ɱ�
		// ����Ŀ����t��t�̶�����
		// r���յ�������
		// �ռ�����������Ϊ������أ�ans <= r
		int dfs(int s, int t, int r) {
			if (s == t || r == 0) {
				return r;
			}
			int f = 0;
			int flow = 0;
			// s��������߿�ʼ�� -> cur[s]
			for (; cur[s] < nexts[s].size(); cur[s]++) {
				int ei = nexts[s][cur[s]];
				Edge e = edges[ei];
				Edge o = edges[ei ^ 1];
				if (depth[e.to] == depth[s] + 1 && (f = dfs(e.to, t, std::min(e.available, r))) != 0) {
					e.available -= f;
					o.available += f;
					flow += f;
					r -= f;
					if (r <= 0) {
						break;
					}
				}
			}
			return flow;
		}

	};
	class Solution {
	public:


	};
}

using Dinic = Code03_DinicAlgorithm::Dinic;
void test_Code03_DinicAlgorithm() {
	
	cout << "test_Code03_DinicAlgorithm begin" << endl;
	int testCases = 0;
	cin >> testCases;
	int n = 0;
	int s = 0;
	int t = 0;
	int m = 0;
	int from = 0;
	int to = 0;
	int weight = 0;
	for (int i = 0; i < testCases; i++)
	{
		cin >> n;
		cin >> s;
		cin >> t;
		cin >> m;
		Dinic dinic (n);
		for (int j = 0; j < m; j++) {
			cin >> from ;
			cin >> to ;
			cin >> weight ;
			dinic.addEdge(from, to, weight);
			dinic.addEdge(to, from, weight);
		}
		int ans = dinic.maxFlow(s, t);
		cout << "Case " << i << ": " << ans << endl;
	}
	cout << "test_Code03_DinicAlgorithm end" << endl;

}


#endif