/*
** EPITECH PROJECT, 2018
** student
** File description:
** 15/06/18
*/
#pragma once

#include <map>
#include <unordered_map>
#include "Map.hpp"
#include "Cristals.hpp"
#include "Eggs.hpp"
#include "Foods.hpp"
#include "Player.hpp"

namespace Graphical {
	class Game {
	public:
		inline void setMapper(std::unique_ptr<Map> map) { _mapper = std::move(map); };
		inline const std::unique_ptr<Map> &getMapper() const { return _mapper; };
		inline void setCristals(std::unique_ptr<Cristals> cristals) { _animatedCristals = std::move(cristals); };
		inline const std::unique_ptr<Cristals> &getCristals() const { return _animatedCristals; };
		inline void setAnimatedEggs(std::unique_ptr<Eggs> eggs) { _animatedEggs = std::move(eggs); };
		inline const std::unique_ptr<Eggs> &getAnimatedEggs() const { return _animatedEggs; };
		inline void setAnimatedFoods(std::unique_ptr<Foods> foods) { _animatedFoods = std::move(foods); };
		inline const std::unique_ptr<Foods> &getAnimatedFoods() const { return _animatedFoods; };
		inline void addPlayer(std::unique_ptr<Player> player) { _players.emplace_back(std::move(player)); };
		inline std::unique_ptr<Player> &getPlayer(const int &id)
		{
			static std::unique_ptr<Player> empty;

			for (auto &player : _players)
				if (player->getId() == id)
					return player;
			return empty;
		};
		/* FUNCTION PTR_FUNCTION COMMUNICATION */
		int setSize(const std::vector<std::string> &array);
		int setCase(const std::vector<std::string> &array);
		int setTeam(const std::vector<std::string> &array);
		int setPlayer(const std::vector<std::string> &array);
		int setPlayerPosition(const std::vector<std::string> &array);
		int setPlayerLevel(const std::vector<std::string> &array);
		int setPlayerInventory(const std::vector<std::string> &array);
		int setPlayerExpulsion(const std::vector<std::string> &array);
		int setPlayerBroadcast(const std::vector<std::string> &array);
		int setPlayerStartIncantation(const std::vector<std::string> &array);
		int setPlayerEndIncantation(const std::vector<std::string> &array);
		int setPlayerLaying(const std::vector<std::string> &array);
		int setPlayerDropping(const std::vector<std::string> &array);
		int setPlayerCollecting(const std::vector<std::string> &array);
		int setPlayerDeath(const std::vector<std::string> &array);
		int setEgg(const std::vector<std::string> &array);
		int setEggHatching(const std::vector<std::string> &array);
		int setEndGame(const std::vector<std::string> &array);
		/*int setInitCom(const std::vector<std::string> &array);*/
		void getSizeServer(std::unique_ptr<Communication> &com);
		/* TOOLS */
		void addPlayerToTeam(const std::string &team, const int &playerId)
		{
			if (!isPlayerInTeam(team, playerId))
				_teams[team].push_back(playerId);
		};
		void addATeam(const std::string &team)
		{
			static int id = 0;

			if (!isTeamExist(team)) {
				_teamsId[team] = id;
				_teams[team] = std::vector<int>();
				++id;
			}

		};
		void removeATeam(const std::string &team)
		{
			if (isTeamExist(team)) {
				auto &aTeam = _teams[team];
				for (auto &player : aTeam)
					removePlayer(player);
				_teams.erase(_teams.find(team));
			}
		}
		inline const std::vector<int> &getATeam(const std::string &team) { return _teams[team]; };
		inline const std::unordered_map<std::string, std::vector<int>> &getTeams() const { return _teams; };
		inline bool isTeamExist(const std::string &team) { return _teams.find(team) != _teams.end(); };
		const std::unique_ptr<Player> &isPlayerExist(const int &id)
		{
			static std::unique_ptr<Player> notFound = nullptr;

			for (auto &player : _players)
				if (player->getId() == id)
					return player;
			return notFound;
		}
		inline bool isPlayerInTeam(const std::string &team, const int &id) { return std::find(_teams[team].begin(), _teams[team].end(), id) != _teams[team].end(); };
		void removePlayer(const int &id)
		{
			for (auto elem = _players.begin() ; elem != _players.end() ; ++elem) {
				auto &player = *elem;
				if (player->getId() == id) {
					_mapper->getCase(player->getPosition())->removePlayer(player->getId());
					_players.erase(elem);
					return ;
				}
			}

		}
		inline void addEgg(int id, int ownerId) { _eggs.push_back(std::make_unique<Egg>(id, ownerId)); };
		void removeEgg(const int &id)
		{
			for (auto elem = _eggs.begin() ; elem != _eggs.end() ; ++elem) {
				auto &egg = *elem;
				if (egg->getId() == id) {
					_eggs.erase(elem);
					return ;
				}
			}

		}
		sf::Color getColor(const std::string &team)
		{
			std::unordered_map<int, sf::Color> colors {
					{0, sf::Color::Cyan},
					{1, sf::Color::Green},
					{2, sf::Color::Yellow},
					{3, sf::Color::Blue},
					{4, sf::Color::Magenta},
					{5, sf::Color::Red},
			};
			int id = _teamsId[team];
			if (colors.find(id) == colors.end())
				return sf::Color::Transparent;
			return colors[_teamsId[team]];
		}
	private:
		std::unique_ptr<Map> _mapper;
		std::unique_ptr<Cristals> _animatedCristals;
		std::unique_ptr<Eggs> _animatedEggs;
		std::unique_ptr<Foods> _animatedFoods;
		std::vector<std::unique_ptr<Player>> _players;
		std::unordered_map<std::string, std::vector<int>> _teams; /* team name, player id*/
		std::unordered_map<std::string, int> _teamsId;
		std::vector<std::unique_ptr<Egg>> _eggs;
	};
}