#pragma once
#ifndef Code05_BobDie_HPP
#define Code05_BobDie_HPP
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

//��Ŀ��
//����5��������N��M��row��col��k
//��ʾ��N*M�������ϣ���Bob��ʼ��(row, col)λ��
//Bobһ��Ҫ����k������ÿ������ȸ��������������ĸ�������һ����λ
//�κ�ʱ��BobֻҪ�뿪N*M�����򣬾�ֱ������
//����k��֮��Bob����N*M������ĸ���


namespace Code05_BobDie {

	class Solution
	{
	public:
		double livePosibility1(int row, int col, int k, int N, int M) {
			return (double)process1(row, col, k, N, M) / pow(4, k);
		}
		int process1(int row, int col, int k, int N, int M) {
			if (row < 0 || row == N || col < 0 || col == M)
			{
				return 0;
			}
			if (k == 0)
			{
				return 1;
			}
			int ways = 0;
			ways += process1(row - 1, col, k - 1, N, M);
			ways += process1(row, col + 1, k - 1, N, M);
			ways += process1(row + 1, col, k - 1, N, M);
			ways += process1(row, col - 1, k - 1, N, M);
			return ways;
		}

		// ��̬�滮����
		double livePosibility2(int row, int col, int k, int N, int M) {
			return (double)dpways(row, col, k, N, M) / pow(4, k);
		}
		// ����ʹ�ÿռ��Ż�����
		int dpways(int row, int col, int k, int N, int M)
		{
			// �൱�� k = 0 ��ʱ�� row col �ı仯����
			vector<vector<int>> dpmatrix(N+1, vector<int>(M+1, 0));
			vector<vector<int>> nextdpmatrix(N+1, vector<int>(M+1, 0));
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < M; j++)
				{
					dpmatrix[i][j] = 1;
				}
			}
			
			for (int step = 1; step <= k; step++)
			{
				for (int i = 0; i < N ; i++)
				{
					for (int j = 0; j < M; j++)
					{
						int ways = 0;
						if (i - 1 >= 0)
						{
							ways += dpmatrix[i - 1][j];
						}
						if (j + 1 < M)
						{
							ways += dpmatrix[i][j+1];
						}
						if (i + 1 < N)
						{
							ways += dpmatrix[i + 1][j];
						}
						if (j - 1 >= 0)
						{
							ways += dpmatrix[i][j-1];
						}
						nextdpmatrix[i][j] = ways;
					}
				}
				dpmatrix.swap(nextdpmatrix);
			}
			return dpmatrix[row][col];
		}



	};


}

void test_Code05_BobDie() {
	
	cout << "test_Code05_BobDie begin" << endl;

	Code05_BobDie::Solution sln;
	cout << "���Կ�ʼ" << endl;
	double elapse_force = 0.0;
	double elapse_dp = 0.0;
	stop_watch st;
	st.start();
	double p1 = sln.livePosibility1(6, 6, 10, 50, 50);
	st.stop();
	elapse_force = st.elapsed_ms();
	st.start();
	double p2 = sln.livePosibility2(6, 6, 10, 50, 50);
	st.stop();
	elapse_dp = st.elapsed_ms();
	cout << "���Խ���" << endl;
	cout << "p1:" << p1 << " p2:" << p2 << endl;
	cout << "average elapse(ms)" << endl;
	cout << "force:"<< elapse_force << "ms" << endl;
	cout << "dp:" << elapse_dp << "ms" << endl;
	cout << "test_Code05_BobDie end" << endl;
//	ĳ�β�����ʾ
//	p1:0.997021 p2 : 0.997021
//	average elapse(ms)
//	force : 3.622ms
//	dp : 1.06ms

}

#endif