/*
** EPITECH PROJECT, 2018
** student
** File description:
** 11/06/18
*/
#pragma once

#include <memory>
#include <vector>
#include "Player.hpp"
#include "Sfml.hpp"
#include "Communication.hpp"
#include "Egg.hpp"
#include "Music.hpp"
#include "Game.hpp"

namespace Graphical {
	class Core {
	public:
		enum GAME_MOD {
			SPLASH_INTRO,
			PLAYERS_INFO,
			MENU,
			GAME,
			EXIT,
			NO_SOUND,
		};
		Core()
		{
			_type = SPLASH_INTRO;
			_move = false;
			_antiSpam = std::chrono::system_clock::now().time_since_epoch().count();
		};
		~Core() = default;
		inline void setDisplayer(std::shared_ptr<Sfml> sfml) { _sfml = std::move(sfml); };
		inline void setCommunication(std::unique_ptr<Communication> com) { _com = std::move(com); };
		inline void setMusic(std::unique_ptr<Music> music) { _music = std::move(music); };
		inline void setGame(std::unique_ptr<Game> game) { _game = std::move(game); };
		inline const std::unique_ptr<Communication> &getCommunication() const { return _com; };
		inline const std::shared_ptr<Sfml> &getDisplayer() const { return _sfml; };
		inline const std::unique_ptr<Music> &getMusic() const { return _music; };
		inline std::unique_ptr<Game> &getGame() { return _game; };
		void printGame();
		std::map<GAME_MOD, sf::FloatRect> createButtons();
		void printMenu();
		int loop();
		void initPtrFunction();
		int manageFd();
		int readServer();
		int manageEvent();
		int keyManager(sf::Event &event);
		int setInitCom(const std::vector<std::string> &array);
		void dropThis(const int &id, const float &scale, const float &x, const float &y, const sf::Color &color = sf::Color::Transparent);
		void dropStone(const int &id, const float &scale, const float &x, const float &y);
		void dropEgg(const int &id, const float &scale, const float &x, const float &y);
		void dropFood(const int &id, const float &scale, const float &x, const float &y);
		float findMapScale(const Pos<int> &pos);
		void printMap(const std::vector<std::unique_ptr<Case>> &map);
		Pos<int> getEntityPos(const int &block);
		void initFilters();
		std::map<int, sf::FloatRect> printFilters();
		sf::FloatRect createFilter(const std::size_t &totalElem, const int &id, const float &x, const float &y, const Pos<int> &margin, const float &padding);
		std::unique_ptr<sf::Sprite> &createIcon(const std::size_t &totalElem, const int &id, const float &x, const float &y, const Pos<int> &margin, const float &padding, const sf::Color &color = sf::Color::Transparent);
		long eventFilters(const std::map<int, sf::FloatRect> &filters);
		void setMovePossibility(const bool &move) { _move = move; };
		const bool &getMovePossibility() { return _move; };
		void printCaseInventory(const std::unique_ptr<Case> &block);
		void mouseEvent(const sf::Event &event, const bool &move);
		void printInventoryCases();
		void printToolbar();
		void display();
		void clear();
		int initAll();
		int initGraphisms();
		int initAudios();
		int switchResolution();
		int moveMapView(const sf::Vector2f& offset);
		sf::FloatRect createButton(std::unique_ptr<sf::Sprite> &sprite, const sf::Vector2f &position);
		void printSplashIntro(const int &id, const float &time);
		void printSplash(const int &id, const float &time);
		int initFonts();
		std::unique_ptr<sf::Sprite> &createSplashIntro(const int &id);
		void manageEventFiltersResult();
		void printPlayersPage();
		void printPlayers();
		void printTeams();
		void printButtons();
		void printPlayerInfo(std::unique_ptr<Player> &player, const int &padding, const Pos<float> &pos);
		void printPlayerInventory(std::unique_ptr<Player> &player, const int &padding, const Pos<float> &pos);
		void resetView();
	private:
		std::shared_ptr<Sfml> _sfml;
		std::unique_ptr<Communication> _com;
		std::unique_ptr<Music> _music;
		std::unique_ptr<Game> _game;
		GAME_MOD _type;
		std::map<std::string, std::function<int(const std::vector<std::string> &)>> _ptr_function;
		std::map<int, bool> _filters;
		bool _move;
		Pos<int> _caseSelected;
		long _antiSpam;
	};
}