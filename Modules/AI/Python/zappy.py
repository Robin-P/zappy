# coding: utf-8
"""
 Zappy class
"""

import random
import socket
import signal
import sys
import time
import macro
from connect import Connect
from ai import Ai

class Zappy:
    """
     Hold everythings for the zappy's ai
    """

    def __init__(self, arg):
        self.opt = arg
        self.connect = Connect(arg)
        self.bot = Ai()
        self.last_cmd = None


    def begin_connection(self):
        """
        Start connection with server
        """
        print(self.recv())
        self.send(self.opt.team)
        res = self.recv()
        if res == 'ko':
            print(macro.INV_TEAM_NAME)
            return False
        res = list(filter(None, res.split('\n')))
        try:
            connection_left = int(res[0])
            if connection_left <= 0:
                print(macro.TOO_MANY_CLIENTS)
                return False
        except ValueError as err:
            print(err)
            return False
        if len(res) == 1:
            res = self.recv()
            if res == 'ko':
                return False
        elif len(res) == 2:
            res = res[1]
        res = res.split(' ')
        try:
            self.opt.x_width = int(res[0])
            self.opt.y_height = int(res[1])
        except ValueError as err:
            print(err)
            return False
        print('{} connection(s) left'.format(connection_left))
        return True


    def send(self, cmd):
        """
        Send command to server

        Args:
            cmd (str): command to be sent
        """
        print('Command : {}'.format(cmd))
        if not cmd.endswith('\n'):
            cmd += '\n'
        self.connect.send_cmd(cmd)


    def recv(self):
        """
        Receive response

        Returns:
            str: response of the server
        """
        # res = self.connect.recv_response()
        res = self.connect.recv_all()
        if 'dead' in res:
            print('Dead :(')
            print('\nDisconnected from {}:{}'.format(self.opt.machine, self.opt.port))
            self.connect.socket.close()
            sys.exit(0)
        return res


    def refresh_invent(self):
        """
        Refresh content of inventory
        """
        self.send(macro.INVENTORY)
        self.bot.inventory.fill(self.recv())


    def look_around(self):
        """
        Look for ressources
        """
        self.send(macro.LOOK)
        self.bot.update_look(self.recv())


    def search_food(self):
        """
        Search for food

        Returns:
            bool: take food or not
        """

        nb_food = self.bot.look[0].count('food')
        if nb_food > 0:
            for i in range(nb_food):
                self.send('Take food')
                if self.recv() == 'ko':
                    return False
            return True
        i = 0
        j = 2
        while i < len(self.bot.look):
            if (self.bot.look[i].count('food')) > 0:
                self.send('Forward')
                return False if self.recv() == 'ko' else True
            i += j
            j += 2
        self.send(random.choice([macro.RIGHT, macro.LEFT]))
        self.send(macro.FORWARD)
        self.recv()
        return True if self.recv() == 'ok' else False


    def search_minerals(self):
        """
        Search for minerals
        """

        needed_res = self.bot.incantation.missing_ressoures(self.bot.inventory.bag, self.bot.level)
        res = [x.replace('[', '').replace(']', '') for x in self.bot.look]
        for key, value in needed_res.items():
            if key in res[0] and key != 'player':
                nb_el = res[0].count(key)
                for _i in range(min(nb_el, value)):
                    self.send('Take {}'.format(key))
                    _res = self.recv()
        self.send(macro.FORWARD)
        self.send(random.choice([macro.RIGHT, macro.LEFT]))
        self.recv()
        self.recv()
        # self.ask_for_help(needed_res)
        return True


    def ask_for_help(self, res):
        """
        Send a message to all to ask for help
        """
        if res['player'] > 0:
            self.send('Broadcast help')
            print(self.recv())


    def run(self):
        """
        Run forever
        """
        start = time.time()
        while self.bot.is_alive():
            time.sleep(0.25)
            end = time.time()
            if end - start > 2:
                self.bot.inventory.pretty_print()
                start = time.time()
            self.refresh_invent()
            self.look_around()
            if self.bot.inventory.bag['food'] < 10:
                self.search_food()
            else:
                self.search_minerals()
            if self.bot.check_incantation():
                self.perform_incantation()
        return macro.SUCCESS


    def launch(self):
        """
        Launch the bot

        Returns:
            int: Works fine or not
        """

        def signal_handler(_signal, _frame):
            """
            handle sigint signal

            Args:
                _signal (signal): signal
                _frame (unknown): _
            """
            print('\nDisconnected from {}:{}'.format(self.opt.machine, self.opt.port))
            self.connect.socket.shutdown(socket.SHUT_RDWR)
            self.connect.socket.close()
            sys.exit(0)


        if not self.connect.connect_to_serv() or not self.begin_connection():
            return macro.ERROR
        print(macro.FORK_SUCCESS if self.fork_it() else macro.FORK_FAIL)
        signal.signal(signal.SIGINT, signal_handler)
        return self.run()


    def perform_incantation(self):
        """
        Perform incantation
        """
        self.send(macro.INCANTATION)
        res = self.recv()
        print(macro.START_INCANT_FAILED if res == 'ko' else macro.INCANT_IN_PROG)
        res = self.recv()
        print(macro.INCANT_FAILED if res == 'ko' else macro.INCANT_SUCCESS)
        if res != 'ok':
            self.bot.level += 1
            print(res)


    def fork_it(self):
        """
        Send fork command to server
        """
        self.send(macro.FORK)
        return False if self.recv() == 'ko' else True
