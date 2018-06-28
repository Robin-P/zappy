# coding: utf-8
"""
Incantation class
"""

class Incantation:
    """
    Incantation class

    Returns:
        Incantation: class
    """

    def __init__(self):
        self.ressources = [
            [1, 1, 0, 0, 0, 0, 0],
            [2, 1, 1, 1, 0, 0, 0],
            [2, 2, 0, 1, 0, 2, 0],
            [4, 1, 1, 2, 0, 1, 0],
            [4, 1, 2, 1, 3, 0, 0],
            [6, 1, 2, 3, 0, 1, 0],
            [6, 2, 2, 2, 2, 2, 1],
        ]

    def compare_ressources(self, inventory, level):
        """
        Compare ressources of inventory to the level's one

        Args:
            inventory (dict): content of the bot's inventory
            level (int): level of the bot

        Returns:
            bool: has ressources to evolve
        """

        level -= 1
        return inventory['player'] == self.ressources[level][0] and \
               inventory['linemate'] == self.ressources[level][1] and \
               inventory['deraumere'] == self.ressources[level][2] and \
               inventory['sibur'] == self.ressources[level][3] and \
               inventory['mendiane'] == self.ressources[level][4] and \
               inventory['phiras'] == self.ressources[level][5] and \
               inventory['thystame'] == self.ressources[level][6]

    def missing_ressoures(self, inventory, level):
        """
        Returns missing ressources to evolve

        Args:
            inventory (dict): inventory
            level (int): level

        Returns:
            dict: needed res
        """

        level -= 1
        return {
            'player': self.ressources[level][0] - inventory['player'],
            'linemate': self.ressources[level][1] - inventory['linemate'],
            'deraumere': self.ressources[level][2] - inventory['deraumere'],
            'sibur': self.ressources[level][3] - inventory['sibur'],
            'mendiane': self.ressources[level][4] - inventory['mendiane'],
            'phiras': self.ressources[level][5] - inventory['phiras'],
            'thystame': self.ressources[level][6] - inventory['thystame']
        }
