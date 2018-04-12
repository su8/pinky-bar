# -*- coding: utf-8 -*-
"""
Display system information gathered in pinkybar.

Configuration parameters:
    cache_timeout: refresh interval for this module (default 10)
    command: specify a path to pinkybar command, otherwise auto
        eg '~/.cache/bin/pinkybar' (default None)
    format: display format for this module (default '{output}')

Format placeholders:
    {output} format for pinkybar output

@author lasers

SAMPLE OUTPUT
{'full_text': 'pinkybar', 'color': '#ffc0cb'}
"""

from os.path import expanduser
STRING_ERROR = 'invalid command'


class Py3status:
    """
    """
    # available configuration parameters
    cache_timeout = 10
    command = None
    format = '{output}'

    def post_config_hook(self):
        if self.command:
            self.command = expanduser(self.command)
        else:
            self.command = self.py3.check_commands(
                ['pinkybar', expanduser('~/.cache/bin/pinkybar')]
            )
        if not self.command or not self.py3.check_commands(self.command):
            raise Exception(STRING_ERROR)

    def pinkybar(self):
        output = self.py3.command_output(self.command).strip()
        pinkybar_data = {'output': self.py3.safe_format(output)}

        return {
            'cached_until': self.py3.time_in(self.cache_timeout),
            'full_text': self.py3.safe_format(self.format, pinkybar_data),
        }


if __name__ == "__main__":
    """
    Run module in test mode.
    """
    from py3status.module_test import module_test
    module_test(Py3status)
