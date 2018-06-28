# coding: utf-8
# author: Benoit Pingris
"""
 Hold connection with server
"""

import sys
import socket
import macro
from custom_log import Log

class Connect:
    """
     Connect class
    """

    def __init__(self, opt):
        self.opt = opt
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.logger = Log()

    def connect_to_serv(self):
        """
        Connect to server

        Returns:
            bool: Either connected to server or not
        """

        try:
            self.socket.connect((self.opt.machine, self.opt.port))
        except (ConnectionError, socket.gaierror) as _err:
            print('Can\'t connect to the server {}:{}'.format(self.opt.machine, self.opt.port))
            return False
        print('[+] Connected to {}:{}\n'.format(self.opt.machine, self.opt.port))
        return True

    def send_cmd(self, cmd):
        """
        Send command to server

        Args:
            cmd (str): command to be sent
        """
        self.logger.info('SENT : {}'.format(cmd))
        try:
            self.socket.send(cmd.encode())
        except BrokenPipeError as _err:
            print(macro.CONNECTION_LOST)
            sys.exit(macro.ERROR)


    def recv_all(self):
        """
        Receive all data from a response
        """

        data = b''
        try:
            while True:
                tmp = self.socket.recv(macro.BUFF_SIZE)
                data += tmp
                if len(tmp) < macro.BUFF_SIZE:
                    break
        except BrokenPipeError as _err:
            print(macro.CONNECTION_LOST)
            sys.exit(macro.ERROR)
        self.logger.info('RECEIVE : {}'.format(data.decode()))
        return data.decode().rstrip('\n')
