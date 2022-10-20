#pragma once
#ifndef __ANY_HASH_GENERATE__
#define __ANY_HASH_GENERATE__

#include <functional>
// from boost (functional/hash):
// see http://www.boost.org/doc/libs/1_35_0/doc/html/hash/combine.html template
template <typename T>
inline void hash_combine(std::size_t &seed, const T &val) {
	seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}
// auxiliary generic functions to create a hash value using a seed
template <typename T> inline void hash_val(std::size_t &seed, const T &val) {
	hash_combine(seed, val);
}
template <typename T, typename... Types>
inline void hash_val(std::size_t &seed, const T &val, const Types &... args) {
	hash_combine(seed, val);
	hash_val(seed, args...);
}

template <typename... Types>
inline std::size_t hash_val(const Types &... args) {
	std::size_t seed = 0;
	hash_val(seed, args...);
	return seed;
}

struct pair_hash {
	template <class T1, class T2>
	std::size_t operator()(const std::pair<T1, T2> &p) const {
		return hash_val(p.first, p.second);
	}
};


struct pair_hash_x
{
	template <class T1, class T2>
	std::size_t operator()(const std::pair<T1, T2> & p) const
	{
		return std::hash<T1>()(p.first) ^ std::hash<T2>()(p.second);
	}

};

struct pair_hash_equal
{

	bool operator()(const std::pair<int, int> & p1, 
		const std::pair<int, int> & p2) const
	{
		bool isequal1 = ((p1.first == p2.first) 
			&& (p1.second == p2.second));
		bool isequal2 = ((p1.first == p2.second)
			&& (p1.second == p2.first));

		return isequal1 || isequal2;
	}

};



#endif