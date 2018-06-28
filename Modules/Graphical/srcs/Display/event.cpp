/*
** EPITECH PROJECT, 2018
** student
** File description:
** 15/06/18
*/

#include "Core.hpp"

int Graphical::Core::switchResolution()
{
	if (_sfml->getWindowType() == Graphical::Sfml::WINDOW) {
		_sfml->close();
		_sfml->open(Graphical::Sfml::FULLSCREEN);
	} else if (_sfml->getWindowType() == Graphical::Sfml::FULLSCREEN) {
		_sfml->close();
		_sfml->open(Graphical::Sfml::WINDOW);
	}
	return 0;
}

int Graphical::Core::moveMapView(const sf::Vector2f& offset)
{
	auto view = _sfml->getScreen().getView();
	view.move(offset);
	_sfml->getScreen().setView(view);
	return 0;
}

int Graphical::Core::keyManager(sf::Event &event)
{
	switch (event.key.code) {
		case sf::Keyboard::Tab: switchResolution();	break;
		case sf::Keyboard::Escape : _type = MENU; break;
		case sf::Keyboard::Left : moveMapView({-1, 0}); break;
		case sf::Keyboard::Right : moveMapView({1, 0}); break;
		case sf::Keyboard::Down : moveMapView({0, 1}); break;
		case sf::Keyboard::Up : moveMapView({0, -1}); break;
		default: break;
	}
	return (0);
};

void Graphical::Core::resetView()
{
	sf::View view = _sfml->getScreen().getView();
	view.setCenter((_sfml->getWindow().getSize().x - _sfml->getMargin().x) / 2.0f, _sfml->getWindow().getSize().y / 2.0f);

	float pad = 0.1f;
	if (_sfml->getZoomRank() > 0)
		pad = -0.1f;
	while (_sfml->getZoomRank() != 0) {
		view.zoom(1 + pad);
		if (pad < 0)
			_sfml->setZoomRank(_sfml->getZoomRank() - 1);
		else
			_sfml->setZoomRank(_sfml->getZoomRank() + 1);
	}
	_sfml->getScreen().setView(view);
}

void Graphical::Core::mouseEvent(const sf::Event &event, const bool &move)
{
	(void) event;
	sf::View view = _sfml->getScreen().getView();
	sf::Vector2i mousePos = sf::Mouse::getPosition(_sfml->getWindow());
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

		if (!(mousePos.x > 0 &&
			  mousePos.y > 0 &&
			  mousePos.x < static_cast<int>(_sfml->getWindow().getSize().x - _sfml->getMargin().x) &&
			  mousePos.y < static_cast<int>(_sfml->getWindow().getSize().y)))
			return;
		sf::Vector2f mouseScreenPos = _sfml->getScreen().mapPixelToCoords(mousePos, _sfml->getScreen().getView());
		_sfml->setMousePosition({static_cast<int>(mouseScreenPos.x), static_cast<int>(mouseScreenPos.y)});
		mousePos.x = static_cast<int>(
				(mousePos.x / static_cast<float>(_sfml->getScreen().getSize().x)) *
				(view.getSize().x));
		mousePos.y = static_cast<int>(
				(mousePos.y / static_cast<float>(_sfml->getScreen().getSize().y)) *
				(view.getSize().y));
		mousePos.x = static_cast<int>(mousePos.x - (view.getSize().x / 2));
		mousePos.y = static_cast<int>(mousePos.y - (view.getSize().y / 2));
		if (move)
			view.move(mousePos.x, mousePos.y);
	} else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		return resetView();
	_sfml->getScreen().setView(view);
}

int Graphical::Core::manageEvent()
{
	sf::Event event{};

	while (_sfml->getWindow().pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			_sfml->close();
		else if (event.type == sf::Event::KeyPressed)
			keyManager(event);
		else if (event.type == sf::Event::Resized) {
			_sfml->getWindow().setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
			_sfml->setScreen({_sfml->getWindow().getSize().x - _sfml->getMargin().x, _sfml->getWindow().getSize().y});
		} else if (_type == GAME && event.type == sf::Event::MouseWheelScrolled)
			_sfml->mouseScrollEvent(event);
		else if (_type == GAME && event.type == sf::Event::MouseButtonPressed)
			mouseEvent(event, _move);
	}
	return (0);
}