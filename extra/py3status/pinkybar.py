# -*- coding: utf-8 -*-
"""
Display system information gathered in pinkybar.

Configuration parameters:
    cache_timeout: refresh interval for this module (default 10)
    command: specify a path to pinkybar command, otherwise auto
        eg '~/.cache/bin/pinkybar' (default None)
    format: display format for this module (default '{output}')
    pythonpath: specify PYTHONPATH to use for scripts (default None)

Format placeholders:
    {output} format for pinkybar output

@author lasers

SAMPLE OUTPUT
pinkybar
[
    {'full_text': u'pinky', 'color': '#ee82ee'},
    {'full_text': u'bar', 'color': '#00bfff'},
]
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
    pythonpath = None

    def post_config_hook(self):
        if self.command:
            self.command = expanduser(self.command)
        else:
            self.command = self.py3.check_commands(
                ['pinkybar', expanduser('~/.cache/bin/pinkybar')]
            )
        if not self.command or not self.py3.check_commands(self.command):
            raise Exception(STRING_ERROR)
        if self.pythonpath:
            self.command = 'PYTHONPATH={} {}'.format(
                self.pythonpath, self.command
            )
        self.shell = bool(self.pythonpath)

    def pinkybar(self):
        try:
            output = self.py3.command_output(self.command, shell=self.shell)
        except self.py3.CommandError as ce:
            output = ce.output
            if 'pinkybar' in ce.error:
                output = ce.error
                self.py3.error(' '.join(output.splitlines()[0].split()[2:]))

        output = output.strip()

        return {
            'cached_until': self.py3.time_in(self.cache_timeout),
            'full_text': self.py3.safe_format(
                self.format, {'output': self.py3.safe_format(output)}
            )
        }


if __name__ == "__main__":
    """
    Run module in test mode.
    """
    from py3status.module_test import module_test
    module_test(Py3status)
