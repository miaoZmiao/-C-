#pragma once
#ifndef Code03_PrintAllSubsquences_HPP
#define Code03_PrintAllSubsquences_HPP
#include <vector>
#include <string>
#include <set>
using namespace  std;

namespace PrintAllSubsquences
{
	void process1(const string & input, size_t index,
		vector<string> & ans, string path);


	vector<string> subs(const string & input)
	{
		vector<string> ans;
		process1(input, 0, ans, "");
		return ans;
	}

	void process1(const string & input, size_t index,
		vector<string> & ans, string path)
	{
		if (index == input.size())
		{
			ans.push_back(path);
			return;
		}
		// ��Ҫ indexλ�õ��ַ�
		process1(input, index + 1, ans, path);
		//Ҫindexλ�õ��ַ�
		process1(input, index + 1, ans, path + input[index]);
	}


	void process2(const string & input, int index,
		set<string> & sset, string path)
	{
		if (input.size() == index)
		{
			sset.insert(path);
			return;
		}
		// ��Ҫ indexλ�õ�
		process2(input, index + 1, sset, path);
		// Ҫ indexλ�õ�
		process2(input, index + 1, sset, path + input[index]);

	}

	vector<string> subsNoRepeat(const string & input)
	{
		vector<string> ans;
		set<string> st;
		process2(input, 0, st, "");
		for (auto s : st)
		{
			ans.push_back(s);
		}
		return ans;
	}



}




#endif