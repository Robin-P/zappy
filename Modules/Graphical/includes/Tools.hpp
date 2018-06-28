/*
** EPITECH PROJECT, 2018
** student
** File description:
** 11/06/18
*/
#pragma once

#include <iostream>
#include <vector>

namespace Graphical {
	template<typename T>
	struct Pos {
		T x;
		T y;
		Pos() = default;
		Pos(T X, T Y) : x(X), y(Y) {};
		~Pos() = default;
	};

	template<typename T>
	inline bool operator<(const Pos<T> &one, const Pos<T> &two) { return one.x < two.x || one.y < two.y; };

	__attribute__((unused)) static std::vector<std::string>
	explode(const std::string &str, char separator)
	{
		std::string tmp;
		std::vector<std::string> splited;

		for (auto &c: str) {
			if (c != separator)
				tmp += c;
			else if (c == separator && !tmp.empty()) {
				splited.push_back(tmp);
				tmp.clear();
			}
		}
		if (!tmp.empty())
			splited.push_back(tmp);
		return splited;
	}

	__attribute__((unused)) static std::string
	fusion(std::vector<std::string> &array, const char &sepChar)
	{
		bool sep = false;
		std::string result;

		for (auto &line : array) {
			if (sep)
				result += sepChar;
			result += line;
			sep = true;
		}
		return result;
	}
}