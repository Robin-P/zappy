/*
** EPITECH PROJECT, 2018
** student
** File description:
** 12/06/18
*/
#pragma once

#include <random>
#include <memory>
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Tools.hpp"
#include "Egg.hpp"

namespace Graphical {
	class Case {
	public:
		explicit Case(const Pos<int> &pos) : _pos(pos.x, pos.y)
		{
			for (std::size_t i = 0 ; i <= _size ; ++i) _resources[i] = 0;
		};

		~Case() = default;

		inline void removeResource(const int &id, const std::size_t &nb) { if (_resources[id] > 0) _resources[id] -= nb;	};
		inline void addResource(const int &id, const std::size_t &nb) { _resources[id] += nb; };
		inline const std::size_t &getResource(const int &id) { return _resources[id]; };
		inline const std::map<int, std::size_t> &getResources() { return _resources; };
		inline void addEgg(const int &id) { _eggsId.push_back(id); };
		inline const std::vector<int> getEggsId() const { return _eggsId; };
		inline const Pos<int> &getPos() const { return _pos; };
		inline bool isPlayerInCase(const int &id) { return std::find(_playerId.begin(), _playerId.end(), id) != _playerId.end(); };
		inline void addPlayer(const int &id) { if (!isPlayerInCase(id)) _playerId.push_back(id); };
		inline void removePlayer(const int &id) { if (isPlayerInCase(id)) _playerId.erase(std::find(_playerId.begin(), _playerId.end(), id)); };
		inline const std::vector<int> &getPlayersId() const { return _playerId; };
	private:
		Pos<int> _pos;
		std::map<int, std::size_t> _resources;
		const std::size_t _size = 6;
		std::vector<int> _eggsId; /* contain id of egg */
		std::vector<int> _playerId; /* contain id of player */
	};

	class Map {
	public:
		Map(const Pos<int> &size = {0, 0}) : _size(size) {};
		~Map() {};

		void initMap()
		{
			static std::default_random_engine generator;
			std::uniform_int_distribution<int> random(1, 6);

			for (int y = 0 ; y < _size.y ; ++y) {
				for (int x = 0 ; x < _size.x; ++x) {
					Pos<int> pos(x, y);
					std::unique_ptr<Case> aCase = std::make_unique<Case>(pos);
					//aCase->addResource(random(generator), 1);
					/*aCase->addResource(0, 1);
					aCase->addResource(1, 1);
					aCase->addResource(2, 1);
					aCase->addResource(3, 1);
					aCase->addResource(4, 1);
					aCase->addResource(5, 1);
					aCase->addResource(6, 1);
					aCase->addEgg(0);*/
					_map.emplace_back(std::move(aCase));
				}
			}
		};

		inline void setSize(const Pos<int> &size) { _size = size; };
		inline const Pos<int> &getSize() const { return _size; };
		inline const std::vector<std::unique_ptr<Case>> &getMap() const { return _map; };
		const std::unique_ptr<Case> &getCase(const Pos<int> &pos) const
		{
			static std::unique_ptr<Case> notFound = nullptr;

			for (auto &elem : _map)
				if (elem->getPos().x == pos.x && elem->getPos().y == pos.y)
					return elem;
			return notFound;
		};
	private:
		Pos<int> _size;
		std::vector<std::unique_ptr<Case>> _map;

	};
}