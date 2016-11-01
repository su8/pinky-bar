# 10/29/2016

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
# MA 02110-1301, USA.

# Neither GNU make, GNU sed, bash
# are used outside linux. No need
# to add more deps. than necessary.
# perl is installed out of the box
# in any desktop system. 

use strict;
use warnings;

sub reflace {
  my ($old,$new,$filename,$count) = @_;
  my $fh;
  my $x = 0;

  open($fh, '<:encoding(UTF-8)', $filename)
    or die "Could not open file '$filename' $!";
  my @arr = <$fh>;
  close($fh);

  if (1 == $count) {
    for (@arr) {
      if (9 == $x) {
        $_ = "$new\n";
        last;
      }
      $x++;
    }
  }
  else {
    for (@arr) {
      s/$old/$new/g;
    }
  }

  open($fh, '>:encoding(UTF-8)', $filename) 
    or die "Could not open file '$filename' $!";
  print $fh @arr;
  close($fh);
}

my ($amCF, $srcToAppend, $BSDLIBS) = "";
my $osEntered = uc $ARGV[0];

my $defTits = "m4_define([OSENTERED],[$osEntered])";
my $bsdCF = "-D_DEFAULT_SOURCE -L/usr/local/lib";
my $posixCF = "-D_POSIX_C_SOURCE=200112L";

if ($osEntered eq "FREEBSD") {
  $BSDLIBS = "-largp -ldevstat";
  $amCF = $bsdCF;
  $defTits = "m4_define([FREEBZD], [tits])";
  $srcToAppend = "freebsd_functions.c include/freebzd.h";
}
elsif ($osEntered eq "OPENBSD") {
  $BSDLIBS = "-largp -lossaudio";
  $amCF = $bsdCF;
  $defTits = "m4_define([OPENBZD], [forSure])";
  $srcToAppend = "openbsd_functions.c include/openbzd.h";
}
else {
  $amCF = $posixCF;
  $defTits = "m4_define([LINUKS], [cryMeAriver])";
  $srcToAppend = "linux_functions.c";
}

reflace("", "$defTits", "configure.ac", 1);
reflace("{amCF}", "$amCF", "src/Makefile.am", 0);
reflace("{srcFiles}", "$srcToAppend", "src/Makefile.am", 0);
reflace("{bzdlibs}", "$BSDLIBS", "src/Makefile.am", 0);
