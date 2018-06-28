//
// EPITECH PROJECT, 2018
// arcade
// File description:
// sfml class
//

#include "Sfml.hpp"

void Graphical::Sfml::mouseScrollEvent(sf::Event &event)
{
	sf::View view = _screen.getView();

	if (event.mouseWheelScroll.delta > 0) {
		_zoom = 1.10f;
		_zoomRank += 1;
	}
	else if (event.mouseWheelScroll.delta < 0) {
		_zoom = 0.90f;
		_zoomRank -= 1;
	}
	view.zoom(_zoom);
	_screen.setView(view);
}