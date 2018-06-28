/*
** EPITECH PROJECT, 2018
** student
** File description:
** 11/06/18
*/

#include "Sfml.hpp"

std::unique_ptr<sf::Text> Graphical::Sfml::getText(const std::string &font_name, const std::string &line, const std::size_t &size,
						   const sf::Color &textColor,
						   const sf::Vector2f &position)
{
	std::unique_ptr<sf::Text> text(std::make_unique<sf::Text>());
	std::unique_ptr<sf::Font> &font = getFont(font_name);

	text->setFont(*font);
	text->setString(line);
	text->setCharacterSize(size);
	text->setFillColor(textColor);
	text->setPosition(position);
	return (text);
}

void Graphical::Sfml::text(const std::string &font_name, const std::string &line, const std::size_t &size,
						   const sf::Color &textColor,
						   const sf::Vector2f &position)
{
	sf::Text text;
	std::unique_ptr<sf::Font> &font = getFont(font_name);

	text.setFont(*font);
	text.setString(line);
	text.setCharacterSize(size);
	text.setFillColor(textColor);
	text.setPosition(position);
	_window.draw(text);
}