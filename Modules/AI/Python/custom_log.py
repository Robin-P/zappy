# coding: utf-8
"""
Custom log class
"""

import logging


class Log:
    """
    Log class
    """

    def __init__(self):
        log_format = '%(levelname)s: (%(asctime)s) [%(relativeCreated)dms]\t-\t%(message)s'
        logging.basicConfig(filename="zappy.log", level=logging.DEBUG, filemode='w' \
                                                                     , format=log_format)
        self.logger = logging.getLogger()

    def info(self, msg):
        """
        Log info type message

        Args:
            msg (str): message to be written
        """

        self.logger.info(msg)

    def warning(self, msg):
        """
        Log warning type message

        Args:
            msg (str): message to be written
        """

        self.logger.warning(msg)
