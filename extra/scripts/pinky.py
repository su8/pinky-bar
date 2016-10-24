# 
# Your script should always return a single string.
# Read line 2 again.
#
# pinky-bar will always call uzer_func,
# you can write other subroutines/functions
# but they should be called inside uzer_func
#
# Dont worry about the colorization, it's
# handled by pinky-bar.
#
# Semicolins are only mandatory when you write "one liners"
# python2 -c 'import time;print("{0}".format(time.tzname))'
#
# Dont blame me if you have the following environment variable
# export PYTHONOPTIMIZE=3
# The only way to describe it is caching nightmare.
import time

def uzer_func():
  rett = '{0} {1} {2}'.format("Hello", time.ctime(), 123)
  return rett
