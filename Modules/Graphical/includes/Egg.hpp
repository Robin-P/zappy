/*
** EPITECH PROJECT, 2018
** student
** File description:
** 13/06/18
*/
#pragma once

namespace Graphical {
	class Egg {
	public:
		Egg(int id, int ownerId) : _id(id), _ownerId(ownerId) {};
		~Egg() = default;
		inline const int &getId() const	{ return _id; };
		inline const int &getOwnerId() const { return _ownerId; };
	private:
		int _id;
		int _ownerId;
	};
}