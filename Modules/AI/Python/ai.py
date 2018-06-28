# coding: utf-8
"""
Ai class
"""

from inventory import Inventory
from incantation import Incantation
import macro

class Ai:
    """
    Ai
    """

    def __init__(self):
        self.inventory = Inventory()
        self.incantation = Incantation()
        self.alive = True
        self.level = 1
        self.look = []
        self.cmd_queue = []
        self.state = macro.AI_LOOK

    def is_alive(self):
        """
        Returns wether bot is alive or not

        Returns:
            bool: Bot is alive
        """

        return self.alive


    def add_cmd(self, cmd):
        """
        Add command in queue

        Args:
            cmd (str): command
        """

        self.cmd_queue.append(cmd)

    def delete_cmd(self):
        """
        Remove first command of queue
        """

        self.cmd_queue.pop(0)


    def check_incantation(self):
        """
        Check if the bot can perform an incantation
        """
        return self.incantation.compare_ressources(self.inventory.bag, self.level)


    def update_look(self, data):
        """
        Update look
        Args:
            data (str): data
        """
        if not data or data == 'ko':
            return False
        data = data.replace('[', '') \
                   .replace(']', '') \
                   .split(',')
        nb_player = data[0].count('player')
        self.inventory.bag['player'] = nb_player
        self.look = data
        return True
