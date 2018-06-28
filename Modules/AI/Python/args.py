# coding: utf-8
"""
 Args

Class that hold arguments

"""

import macro

class Args:
    """
     Holds arguments manager
    """

    def __init__(self, argv):
        self.argv = argv
        self.port = 0
        self.machine = "localhost"
        self.team = None
        self.fct = {
            '-p': self.parse_port,
            '-h': self.parse_machine,
            '-n': self.parse_team,
            '-help': self.usage,
            '--help': self.usage
        }


    def usage(self, ret=0):
        """
        Print usage

        Args:
            ret (int): returned value
        """
        print("""USAGE: {} -p port -n name -h machine
    port is the port number
    name is the name of the team
    machine is the name of the machine; localhost by default""".format(self.argv[0]))
        return ret

    def parse_port(self, arg):
        """
        Get port number

        Args:
            arg (str): port number
        """

        self.port = int(arg)


    def parse_machine(self, arg):
        """
        Get machine name

        Args:
            arg (str): Server's address
        """

        self.machine = arg


    def parse_team(self, arg):
        """
        Get team name

        Args:
            arg (str): Team's name
        """

        self.team = arg


    def check_valid(self):
        """
        Check if parameters are valid

        Returns:
            bool: parameters valid or not
        """
        if self.port <= 0:
            print('Port must be superior to 0.\n')
            self.usage()
            return False
        if self.team == None:
            print('You must specify a team name.\n')
            self.usage()
            return False
        return True

    def parse_args(self):
        """
        Parse CLI arguments
        """
        for i in range(len(self.argv)):
            for key, value in self.fct.items():
                if self.argv[i] in ['-help', '--help']:
                    return self.usage()
                if key == self.argv[i]:
                    try:
                        value(self.argv[i + 1])
                    except IndexError as _err:
                        return self.usage(ret=macro.ERROR)
        return macro.SUCCESS if self.check_valid() else macro.ERROR
