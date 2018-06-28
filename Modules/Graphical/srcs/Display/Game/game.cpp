/*
** EPITECH PROJECT, 2018
** student
** File description:
** 15/06/18
*/

#include <chrono>
#include "Core.hpp"

std::unique_ptr<sf::Sprite> &Graphical::Core::createIcon(const std::size_t &totalElem, const int &id, const float &x, const float &y, const Pos<int> &margin, const float &padding, const sf::Color &color)
{
	auto &sprite = _sfml->getBlock(id);
	
	int cmp = static_cast<int>(_sfml->getWindow().getSize().y / totalElem);
	float scaller = cmp <= margin.x ? _sfml->getWindow().getSize().y / totalElem : margin.x;
	sprite->setScale(scaller / static_cast<float>(sprite->getTexture()->getSize().x),
					 scaller / static_cast<float>(sprite->getTexture()->getSize().y));
	
	sprite->setPosition(x, y * padding);
	sf::Color last = sprite->getColor();
	if (color != sf::Color::Transparent)
		sprite->setColor(color);
	_sfml->getWindow().draw(*sprite);
	sprite->setColor(last);
	return sprite;
}

sf::FloatRect Graphical::Core::createFilter(const std::size_t &totalElem, const int &id, const float &x, const float &y, const Pos<int> &margin, const float &padding)
{
	sf::Color color = (_filters[id] ? sf::Color::Green : sf::Color::Red);
	auto &sprite = _sfml->getBlock(id);
	
	int cmp = static_cast<int>(_sfml->getWindow().getSize().y / totalElem);
	float scaller = cmp < margin.x ? _sfml->getWindow().getSize().y / totalElem : margin.x;
	sprite->setScale(scaller / sprite->getTexture()->getSize().x,
					 scaller / sprite->getTexture()->getSize().y);
	
	sprite->setPosition(x, y * padding);
	sf::Color last = sprite->getColor();
	sprite->setColor(color);
	createIcon(totalElem, 15, x, y, margin, padding);
	_sfml->getWindow().draw(*sprite);
	sprite->setColor(last);
	return (sprite->getGlobalBounds());
}

std::map<int, sf::FloatRect> Graphical::Core::printFilters()
{
	std::map<int, sf::FloatRect> buttons;
	const std::size_t filterNb = 9;
	Pos<int> margin = _sfml->getMargin();
	margin.x /= 2;
	float x = _sfml->getWindow().getSize().x - margin.x;
	float padding = static_cast<float>(_sfml->getWindow().getSize().y) / filterNb;
	float y = 0;

	buttons[13] = createFilter(filterNb, 13, x, y, margin, padding);
	y += 1;
	buttons[26] = createFilter(filterNb, (!_filters[26] ? 26 : 27), x, y, margin, padding);
	y += 1;
	buttons[25] = createFilter(filterNb, 25, x, y, margin, padding);
	y += 1;
	buttons[18] = createFilter(filterNb, (_filters[18] ? 18 : 19), x, y, margin, padding);
	y += 1;
	buttons[11] = createFilter(filterNb, 11, x, y, margin, padding);
	y += 1;
	buttons[2] = createFilter(filterNb, 2, x, y, margin, padding);
	y += 1;
	buttons[7] = createFilter(filterNb, 7, x, y, margin, padding);
	y += 1;
	buttons[8] = createFilter(filterNb, 8, x, y, margin, padding);
	y += 1;
	buttons[12] = createFilter(filterNb, 12, x, y, margin, padding);
	return buttons;
}

void Graphical::Core::manageEventFiltersResult()
{
	_move = _filters[18];
	if (_filters[13]) {
		_type = MENU;
		_filters[13] = false;
	}
	if ((_filters[26] && _music->isMute()) ||
		(!_filters[26] && !_music->isMute()))
		_music->addEvent(Music::AUDIO, Music::SWAP, "");
	if (_filters[12]) { //reset all filter
		for (auto &filter : _filters) {
			if (filter.first != 13 && filter.first != 18 && filter.first != 26)
				filter.second = true;
		}
		_filters[12] = false;
	}
	if (_filters[25]) {
		resetView();
		_filters[25] = false;
	}
}

long Graphical::Core::eventFilters(const std::map<int, sf::FloatRect> &buttons)
{
	long result = 0;
	sf::Vector2f position(sf::Mouse::getPosition(_sfml->getWindow()));

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		return 0;
	for (auto &button : buttons) {
		if (button.second.contains(position)) {
			_music->addEvent(Music::SOUND, Music::PLAY, "select");
			_filters[button.first] = !_filters[button.first];
			result = 300000000; // antispam
		}
	}
	manageEventFiltersResult();
	return result;
}

void Graphical::Core::printInventoryCases()
{
	const std::size_t filterNb = 10;
	Pos<int> margin = _sfml->getMargin();
	float x = _sfml->getWindow().getSize().x - margin.x;
	margin.x /= 2;
	float padding = static_cast<float>(_sfml->getWindow().getSize().y) / filterNb;
	float y = 0;

	createIcon(filterNb, 15, x, y, margin, padding);
	createIcon(filterNb, 14, x, y, margin, padding);
	y +=1;
	while (y < 10) {
		auto &sprite = createIcon(filterNb, 15, x, y, margin, padding);
		if (y == 9 && sf::Mouse::isButtonPressed(sf::Mouse::Left)) { // player button, not generic, sorry
			sf::Vector2f position(sf::Mouse::getPosition(_sfml->getWindow()));
			if (sprite->getGlobalBounds().contains(position))
				_type = PLAYERS_INFO;
		}
		y += 1;
	}
}

void Graphical::Core::printToolbar()
{
	auto &player = _sfml->getBlock(16);
	player->setScale(_sfml->getMargin().x, _sfml->getWindow().getSize().y);
	player->setPosition(_sfml->getWindow().getSize().x - _sfml->getMargin().x, 0);
	_sfml->getWindow().draw(*player);
}

void Graphical::Core::printGame()
{
	printToolbar();
	printInventoryCases();
	printMap(_game->getMapper()->getMap());
	auto buttons = printFilters();


	std::chrono::system_clock::time_point time = std::chrono::system_clock::now();
	long now = time.time_since_epoch().count() ;

	if (now > _antiSpam) {
		auto antiSpam = eventFilters(buttons);
		if (antiSpam > 0)
			_antiSpam = now + antiSpam;
	}
}