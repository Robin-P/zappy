#!/usr/bin/env python3
# coding: utf-8
"""
 Zappy AI in python3
"""

import sys
from args import Args
from zappy import Zappy
import macro

def main():
    """
    Main function
    """

    args = Args(sys.argv)
    if args.parse_args() == macro.ERROR:
        return macro.ERROR
    zappy = Zappy(args)
    return zappy.launch()


if __name__ == '__main__':
    sys.exit(main())
