/*
** EPITECH PROJECT, 2018
** student
** File description:
** 16/06/18
*/
#pragma once

#include <memory>
#include <chrono>
#include "Sfml.hpp"

namespace Graphical {
	class Foods {
	public:
		Foods(std::shared_ptr<Graphical::Sfml> &sfml, const int &id)
				: _sfml(sfml), _id(id), _x(0), _y(0), _last(std::chrono::system_clock::now().time_since_epoch().count())
		{};

		~Foods() = default;

		void setX(std::unique_ptr<sf::Sprite> &sprite) {
			long now = std::chrono::system_clock::now().time_since_epoch().count();

			if (now > _last + 250000000) {
				_last = std::chrono::system_clock::now().time_since_epoch().count();
				_x += _padding;
				if (_x >= sprite->getTexture()->getSize().x)
					_x = 0;
			}
		}

		std::unique_ptr<sf::Sprite> &getSprite(const int &id)
		{
			(void) id;
			auto &sprite = _sfml->getBlock(_id);

			setX(sprite);
			sprite->setTextureRect({static_cast<int>(_x), static_cast<int>(_y), _padding, _padding});
			return sprite;
		}

		const int &getPadding() const { return _padding; };
	private:
		std::shared_ptr<Graphical::Sfml> _sfml;
		int _id;
		const int _padding = 64;
		std::size_t _x;
		std::size_t _y;
		long _last;
	};
}