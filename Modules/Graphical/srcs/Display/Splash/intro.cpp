/*
** EPITECH PROJECT, 2018
** student
** File description:
** 15/06/18
*/

#include <chrono>
#include "Core.hpp"

/**
 * @brief to center the sprite
 * @param id
 * @return
 */
std::unique_ptr<sf::Sprite> &Graphical::Core::createSplashIntro(const int &id)
{
	auto width = _sfml->getWindow().getSize().x;
	auto height = _sfml->getWindow().getSize().y;
	auto &sprite = _sfml->getBlock(id);
	float x = (width / 2.0f) -
			  ((sprite->getTexture()->getSize().x * sprite->getScale().x) /
			   2.0f);
	float y = (height / 2.0f) -
			  ((sprite->getTexture()->getSize().y * sprite->getScale().y) /
			   2.0f);
	sprite->setPosition(x, y);
	return sprite;
}

/**
 * @brief
 * @param id of sprite
 * @param time of each scan in second
 */
void Graphical::Core::printSplashIntro(const int &id, const float &atime)
{
	static sf::Uint8 alpha = 0;
	static bool visible = true;
	static long last = std::chrono::system_clock::now().time_since_epoch().count();
	auto &sprite = createSplashIntro(id);
	sf::Uint8 padding = 5;
	long time = static_cast<int>(atime * 1000000000);

	long now = std::chrono::system_clock::now().time_since_epoch().count();
	if (visible) {
		if (now <= last + time)
			alpha += alpha < (255 - padding) ? padding : 0;
		else {
			visible = false;
			last = std::chrono::system_clock::now().time_since_epoch().count();
		}
	} else {
		if (now <= last + time)
			alpha -= alpha > padding ? padding : 0;
		else
			_type = MENU;
	}
	sprite->setColor({200, 100, 100, alpha});
	_sfml->getWindow().draw(*sprite);
}

void Graphical::Core::printSplash(const int &id, const float &time)
{
	printSplashIntro(id, time);
}