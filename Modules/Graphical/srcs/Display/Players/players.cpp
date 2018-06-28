/*
** EPITECH PROJECT, 2018
** student
** File description:
** 18/06/18
*/

#include "Core.hpp"

void Graphical::Core::printPlayerInfo(std::unique_ptr<Player> &player, const int &padding, const Pos<float> &pos)
{
	int y = 0;
	auto size = static_cast<std::size_t>(padding / 4);

	_sfml->text("birdy", "Id:" + std::to_string(player->getId()), size, sf::Color::White, {pos.x, (y * size) + (pos.y * padding)});
	y += 1;
	_sfml->text("birdy", "Team:" + player->getTeam(), size, sf::Color::White, {pos.x, (y * size) + (pos.y * padding)});
	y += 1;
	_sfml->text("birdy", "Level:" + std::to_string(player->getLevel()), size, sf::Color::White, {pos.x, (y * size) + (pos.y * padding)});
}

void Graphical::Core::printPlayerInventory(std::unique_ptr<Player> &player, const int &padding, const Pos<float> &pos)
{
	auto nbCases = player->getResources().size();

	createIcon(nbCases, 15, (0 + 2) * padding, pos.y, {static_cast<int>(pos.x), 0}, padding);
	createIcon(nbCases, 7, (0 + 2) * padding, pos.y, {static_cast<int>(pos.x), 0}, padding);
	_sfml->text("birdy", std::to_string(player->getResource(0)), static_cast<std::size_t >(padding / 4), sf::Color::White, {
			static_cast<float>((0 + 2) * padding), pos.y * padding});
	for (std::size_t index = 1 ; index < nbCases ; ++index) {
		auto i = static_cast<int>(index);
		createIcon(nbCases, 15, (index + 2) * padding, pos.y, {static_cast<int>(pos.x), 0}, padding);
		createIcon(nbCases, 22, (index + 2) * padding, pos.y, {static_cast<int>(pos.x), 0}, padding, _game->getCristals()->getColor(i));
//		std::cerr << i << ":" << player->getResource(i) << std::endl;
		_sfml->text("birdy", std::to_string(player->getResource(i)), static_cast<std::size_t >(padding / 4), sf::Color::White, {
				static_cast<float>((i + 2) * padding), pos.y * padding});
	}
}

void Graphical::Core::printPlayers()
{
	auto &aCase = _game->getMapper()->getCase(_caseSelected);
	if (!aCase)
		return ;
	auto &players = aCase->getPlayersId();

	const std::size_t filterNb = players.size() < 10 ? 10 : players.size();
	Pos<int> margin = {static_cast<int>(_sfml->getWindow().getSize().x), 0};
	int padding = static_cast<int>(_sfml->getScreen().getSize().y / filterNb);
	float x = 0;
	float y = 0;

	for (auto &aPlayer : players) {
		auto &player = _game->getPlayer(aPlayer);
		if (player) {
			auto &icon = createIcon(filterNb, 15, x, y, margin, padding);
			createIcon(filterNb, 24, x, y, margin, padding, _game->getColor(player->getTeam()));
			printPlayerInfo(player, padding, {icon->getScale().x * icon->getTexture()->getSize().x, y});
			printPlayerInventory(player, padding, {icon->getScale().x * icon->getTexture()->getSize().x, y});
			++y;
		}
	}
}

void Graphical::Core::printTeams()
{
	const std::size_t filterNb = (_game->getTeams().size() > 10 ? _game->getTeams().size() : 10);
	Pos<int> margin = _sfml->getMargin();
	margin.x = 400;
	margin.x /= 2;
	float padding = static_cast<float>(_sfml->getWindow().getSize().y) / filterNb;
	float x = _sfml->getWindow().getSize().x - margin.x;
	float y = 0;
	auto size = static_cast<std::size_t>(padding / 4);

	_sfml->text("birdy", "Team list:", size, sf::Color::White, {x - 160, (y * size) + (y * padding)});
	for (auto &team : _game->getTeams()) {
		createIcon(filterNb, 15, x, y, margin, padding);
		createIcon(filterNb, 28, x, y, margin, padding, _game->getColor(team.first));
		_sfml->text("birdy", team.first, size, sf::Color::Yellow, {x, y * padding});
		y += 1;
	}
}

void Graphical::Core::printButtons()
{
	const std::size_t filterNb = 10;
	Pos<int> margin = _sfml->getMargin();
	margin.x /= 2;
	float padding = static_cast<float>(_sfml->getWindow().getSize().y) / filterNb;
	float x = _sfml->getWindow().getSize().x - margin.x;
	float y = 0;

	auto &sprite = createIcon(filterNb, 15, x, y, margin, padding);
	createIcon(filterNb, 13, x, y, margin, padding);
	sf::Vector2f position(sf::Mouse::getPosition(_sfml->getWindow()));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && sprite->getGlobalBounds().contains(position)) {
		_antiSpam = std::chrono::system_clock::now().time_since_epoch().count() + 1000000000;
		_type = GAME;
	}
}

void Graphical::Core::printPlayersPage()
{
	printPlayers();
	printButtons();
	printTeams();
}