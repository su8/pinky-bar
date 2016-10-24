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
use strict;
use warnings;

use Time::Piece;

sub uzer_func {
  my $t = localtime;
  my $rett = sprintf("%s %s %d", "Hello", $t->cdate, 123);

  return $rett;
}
