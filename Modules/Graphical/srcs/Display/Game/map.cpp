/*
** EPITECH PROJECT, 2018
** student
** File description:
** 12/06/18
*/

#include "Core.hpp"

Graphical::Pos<int> Graphical::Core::getEntityPos(const int &block)
{
	static std::map<char, Pos<int>> map = {
			{0, {0, 0}},
			{1, {1, 0}},
			{2, {2, 0}},
			{3, {0, 1}},
			{4, {2, 2}},
			{5, {2, 1}},
			{6, {0, 2}},
			{8, {1, 2}},
			{24, {1, 1}},
			{11, {1, 1}},
	};
	return map[block];
};

void Graphical::Core::dropThis(const int &id, const float &scale, const float &x, const float &y, const sf::Color &color)
{
	float elem = scale / 3.0f;
	auto &sprite = _sfml->getBlock(id);
	float size = sprite->getTexture()->getSize().x;
	sprite->setScale({elem / size, elem / size});
	sf::Color last = sprite->getColor();
	if (color != sf::Color::Transparent)
		sprite->setColor(color);
	auto pos = getEntityPos(id);
	sprite->setPosition(sf::Vector2f(x + elem * pos.x, y + elem * pos.y));
	_sfml->getScreen().draw(*sprite);
	sprite->setColor(last);
}

void Graphical::Core::dropStone(const int &id, const float &scale, const float &x, const float &y)
{
	float elem = scale / 3.0f;
	auto &sprite = _game->getCristals()->getSprite(id);
	float size =_game->getCristals()->getPadding();

	sprite->setScale({elem / size, elem / size});
	auto pos = getEntityPos(id);
	sprite->setPosition(sf::Vector2f(x + elem * pos.x, y + elem * pos.y));
	_sfml->getScreen().draw(*sprite);
}

void Graphical::Core::dropEgg(const int &id, const float &scale, const float &x, const float &y)
{
	float elem = scale / 3.0f;
	auto &sprite = _game->getAnimatedEggs()->getSprite(id);
	float size = _game->getAnimatedEggs()->getPadding();

	sprite->setScale({elem / size, elem / size});
	auto pos = getEntityPos(id);
	sprite->setPosition(sf::Vector2f(x + elem * pos.x, y + elem * pos.y));
	_sfml->getScreen().draw(*sprite);
}

void Graphical::Core::dropFood(const int &id, const float &scale, const float &x, const float &y)
{
	float elem = scale / 3.0f;
	auto &sprite = _game->getAnimatedFoods()->getSprite(id);
	float size = _game->getAnimatedFoods()->getPadding();

	sprite->setScale({elem / size, elem / size});
	auto pos = getEntityPos(id);
	sprite->setPosition(sf::Vector2f(x + elem * pos.x, y + elem * pos.y));
	_sfml->getScreen().draw(*sprite);
}

float Graphical::Core::findMapScale(const Pos<int> &pos)
{
	int max_y = pos.y, max_x = pos.x;
	float height = _sfml->getScreen().getSize().y, width = _sfml->getScreen().getSize().x;
	float scale = width / max_x;

	if (max_y * scale > height)
		scale = height / max_y;
	return (scale);
}

void Graphical::Core::printCaseInventory(const std::unique_ptr<Case> &block)
{
	std::map<int, sf::FloatRect> buttons;
	const std::size_t filterNb = 10;
	Pos<int> margin = _sfml->getMargin();
	float x = _sfml->getWindow().getSize().x - margin.x;
	margin.x /= 2;
	float padding = static_cast<float>(_sfml->getWindow().getSize().y) / filterNb;
	float y = 1;

	_caseSelected = block->getPos();
	for (int i = 1 ; i < 7 ; ++i) {
		if (block->getResource(i) > 0)
			createIcon(filterNb, 22, x, y, margin, padding, _game->getCristals()->getColor(i));
		_sfml->text("birdy", std::to_string(block->getResource(i)), 20, sf::Color::White, {x, y * padding});
		y += 1;
	}
	if (block->getResource(0) > 0)
		createIcon(filterNb, 7, x, y, margin, padding);
	_sfml->text("birdy", std::to_string(block->getResource(0)), 20, sf::Color::White, {x, y * padding});
	y += 1;
	if (!block->getEggsId().empty())
		createIcon(filterNb, 8, x, y, margin, padding);
	_sfml->text("birdy", std::to_string(block->getEggsId().size()), 20, sf::Color::White, {x, y * padding});
	y += 1;
	if (!block->getPlayersId().empty())
		createIcon(filterNb, 11, x, y, margin, padding);
	_sfml->text("birdy", std::to_string(block->getPlayersId().size()), 20, sf::Color::White, {x, y * padding});
	y += 1;
}

void Graphical::Core::printMap(const std::vector<std::unique_ptr<Case>> &map)
{

	float scale = findMapScale(_game->getMapper()->getSize());
	float marginX = (_sfml->getScreen().getSize().x / 2.0f) - (_game->getMapper()->getSize().x / 2.0f * scale);
	float marginY = (_sfml->getScreen().getSize().y / 2.0f) - (_game->getMapper()->getSize().y / 2.0f * scale);

	for (auto &block : map) {
		auto &sprite = _sfml->getBlock(0);
		float size = sprite->getTexture()->getSize().x;
		sprite->setScale({scale / size, scale / size});
		float x = marginX + (block->getPos().x * scale) + ((block->getPos().x * scale) / sprite->getTexture()->getSize().x);
		float y = marginY + (block->getPos().y * scale) + ((block->getPos().y * scale) / sprite->getTexture()->getSize().y);
		sprite->setPosition(sf::Vector2f(x, y));
		_sfml->getScreen().draw(*sprite);
		if (!_move && sprite->getGlobalBounds().contains(_sfml->getMousePosition().x, _sfml->getMousePosition().y))
			printCaseInventory(block);
		if (_filters[2]) {
			for (auto &resource : block->getResources()) {
				if (resource.second > 0 && resource.first > 0 && resource.first < 7)
					dropStone(resource.first, scale, x, y);
			}
			/*dropStone(1, scale, x, y);
			dropStone(2, scale, x, y);
			dropStone(3, scale, x, y);
			dropStone(4, scale, x, y);
			dropStone(5, scale, x, y);
			dropStone(6, scale, x, y);*/
		}
		if (_filters[7] && block->getResource(0) > 0)
			dropFood(7, scale, x, y);
		if (_filters[8] && !block->getEggsId().empty())
			dropEgg(8, scale, x, y);
		if (_filters[11] && (block->getPlayersId().size() == 1)) {
			auto &player = _game->getPlayer(block->getPlayersId()[0]);
			dropThis(24, scale, x, y, _game->getColor(player->getTeam()));
		} else if (_filters[11] && !block->getPlayersId().empty())
			dropThis(11, scale, x, y);
	}
}
