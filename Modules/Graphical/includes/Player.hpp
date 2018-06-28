/*
** EPITECH PROJECT, 2018
** student
** File description:
** 11/06/18
*/

#pragma once
#include <map>
#include "Tools.hpp"

namespace Graphical {
	enum orientation {
		NORTH = 1,
		EST,
		SOUTH,
		WEST,
	};
	class Player {
	public:
		Player(const int &id, const Pos<int> &pos, const orientation &rota, const std::size_t &level, const std::string &team)
				: _id(id), _pos(pos), _rotation(rota), _level(level), _team(team)
		{
			for (std::size_t i = 0 ; i < _size ; ++i)
				_resources[i] = 0;
		};

		~Player() = default;

		void setPosition(const Graphical::Pos<int> &pos)
		{
			/*if (_pos.x == pos.x && _pos.y != pos.y)
				_rotation = pos.y > _pos.y ? 180 : 0;
			else if (_pos.y == pos.y && _pos.x != pos.x)
				_rotation = pos.x > _pos.x ? 90 : 270;*/
			_pos = pos;
		};
		void setRotation(const orientation &rotation) { _rotation = rotation; };
		void setLevel(const std::size_t &level) { _level = level; };
		const int &getId() const { return _id; };
		const Pos<int> &getPosition() const { return _pos; };
		const orientation &getRotation() const { return _rotation; };
		const std::size_t &getLevel() const { return _level; };
		const std::string &getTeam() const { return _team; };
		void addResource(int id, std::size_t nb) { _resources[id] += nb; };
		const std::size_t &getResource(const int &id) { return _resources[id]; };
		const std::map<int, std::size_t> &getResources() const { return _resources; };
	private:
		const int _id;
		Pos<int> _pos;
		orientation _rotation;
		std::size_t _level;
		const std::string _team;
		std::map<int, std::size_t> _resources;
		const std::size_t _size = 7;
	};
}