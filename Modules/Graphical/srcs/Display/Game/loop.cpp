/*
** EPITECH PROJECT, 2018
** student
** File description:
** 15/06/18
*/

#include "Core.hpp"

void Graphical::Core::clear()
{
	if (_type == GAME) {
		_sfml->getScreen().clear();
	}
	_sfml->getWindow().clear();
}

void Graphical::Core::display()
{
	if (_type == GAME) {
		_sfml->displayScreen();
	}
	_sfml->getWindow().display();
}

int Graphical::Core::initGraphisms()
{
	_sfml->open(Graphical::Sfml::WINDOW);
	_sfml->createBlocks();
	return 0;
}

void Graphical::Core::initFilters()
{
	_filters[13] = false;
	_filters[18] = false;
	_filters[11] = true;
	_filters[2] = true;
	_filters[7] = true;
	_filters[8] = true;
	_filters[12] = false;
	_filters[25] = false;
	_filters[26] = !_music->isMute(); //audio on
}

int Graphical::Core::initAudios()
{
	_music->addEvent(Music::MUSIC, Music::CREATE, "main.ogg");
	_music->addEvent(Music::SOUND, Music::CREATE, "select.wav");
	return 0;
}

int Graphical::Core::initFonts()
{
	_sfml->createFont("birdy", "birdy.ttf");
	_sfml->createFont("comic", "comic.ttf");
	return 0;
}

int Graphical::Core::initAll()
{
	initFonts();
	initGraphisms();
	initFilters();
	initAudios();
	_game->setCristals(std::make_unique<Graphical::Cristals>(_sfml, 20));
	_game->setAnimatedEggs(std::make_unique<Graphical::Eggs>(_sfml, 21));
	_game->setAnimatedFoods(std::make_unique<Graphical::Foods>(_sfml, 23));
	return 0;
}

int Graphical::Core::loop()
{
	initAll();
	_music->addEvent(Music::MUSIC, Music::PLAY, "main", 50);
	while (_sfml->isOpen() && _com->isValidFd(_com->getSocket())) {
		manageEvent();
		_music->audioManager();
		readServer();
		clear();
		switch (_type) {
			case SPLASH_INTRO: printSplash(17, 0.8f); break;
			case PLAYERS_INFO: printPlayersPage(); break;
			case MENU: printMenu(); break;
			case GAME: printGame(); break;
			case EXIT: _sfml->close();
			default: break;
		}
		display();
	}
	return (0);
}