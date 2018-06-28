/*
** EPITECH PROJECT, 2018
** student
** File description:
** 11/06/18
*/

#include "Core.hpp"

int manageArguments(int ac, char **av)
{
	if (ac == 2 && av[1] != nullptr && (std::string(av[1]) == "-h" || std::string(av[1]) == "--help"))
		std::cout << av[0] << " port_number" << std::endl;
	else if (ac != 2 || av[1] == nullptr)
		std::cerr << av[0] << " -h" << std::endl;
	else
		return 0;
	return 84;
}

int main(int ac, char **av)
{
	if (manageArguments(ac, av) == 84) return 84;
	Graphical::Core core;

	core.initPtrFunction();
	core.setCommunication(std::make_unique<Graphical::Communication>(std::stoi(av[1])));
	core.setDisplayer(std::make_shared<Graphical::Sfml>());
	core.setMusic(std::make_unique<Graphical::Music>());
	core.setGame(std::make_unique<Graphical::Game>());
	core.getGame()->setMapper(std::make_unique<Graphical::Map>());
	core.loop();
	return (0);
}

