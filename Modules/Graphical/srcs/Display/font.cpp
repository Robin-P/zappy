#include <string>
#include "Sfml.hpp"

std::unique_ptr<sf::Font> &Graphical::Sfml::getFont(const std::string &name)
{
	if (_fonts.find(name) == _fonts.end())
		throw std::logic_error(std::string("Unknown font: ") + name);
	return _fonts[name];
}

void Graphical::Sfml::createFont(const std::string &key, const std::string &path)
{
	std::unique_ptr<sf::Font> font = std::make_unique<sf::Font>();

	font->loadFromFile(_fontPath + path);
	_fonts[key] = std::move(font);
}

void Graphical::Sfml::createFont(const std::string &key, std::unique_ptr<sf::Font> &font)
{
	_fonts[key] = std::move(font);
}
