# 11/01/2016

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

use strict;
use warnings;

use File::Copy;
use List::Util qw(any);

sub re_read {
  my ($filename) = @_;
  my $derefs = $$filename;
  my $fh;

  open($fh, '<:encoding(UTF-8)', $derefs)
    or die "Could not open file '$derefs' $!";
  local $/ = undef; # <--- slurp mode
  my $concatArr = <$fh>;
  close($fh);

  return \$concatArr;
}

sub re_write {
  my ($filename,$concatArr) = @_;
  my $derefs = $$filename;
  my $fh;

  open($fh, '>:encoding(UTF-8)', $derefs) 
    or die "Could not open file '$derefs' $!";

  print $fh $$concatArr;
  close($fh);
  return;
}

sub reflace_configure {
  my ($new) = @_;
  my $filename = "configure.ac";
  my @arr = split("\n",${re_read(\$filename)});

  if ($arr[9]) {
    $arr[9] = $$new;
  }
  my $concatArr = join("\n", @arr);

  re_write(\$filename,\$concatArr);
  return;
}

sub reflace_many {
  my ($arr,$filename) = @_;
  my $derefFilename = $$filename;
  my @arr2 = @$arr;
  my ($x,$arrLen) = (0,$#arr2);
  my $derefs = ${re_read(\$derefFilename)};

  for (; $x <= $arrLen; $x++) {
    $derefs =~ s/${$arr2[$x][0]}/${$arr2[$x][1]}/g;
  }
  re_write(\$derefFilename,\$derefs);
  return;
}

sub reflace_single {
  my ($ag1,$ag2,$filename) = @_;
  my $derefFilename = $$filename;
  my $derefs = ${re_read(\$derefFilename)};

  $derefs =~ s/$$ag1/$$ag2/g;
  re_write(\$derefFilename,\$derefs);
  return;
}


{

  if (-1 == $#ARGV) {
    die "No OS/Distro supplied.";
  }

  my $osEntered = uc $ARGV[0];
  my @osArr = (
    "ARCHLINUX","DEBIAN",
    "GENTOO","SLACKWARE",
    "RHEL","FRUGALWARE",
    "ANGSTROM","FREEBSD","OPENBSD"
  );
  my $hasMatch = any { $_ eq $osEntered } @osArr;
  if ($hasMatch eq "") {
    die "Invalid OS/Distro supplied.";
  }

  my $srcMake = "src/Makefile.am";
  my $defTits = "m4_define([cuRos],[$osEntered])";
  my $bsdCF = "-D_DEFAULT_SOURCE -L/usr/local/lib";
  my $posixCF = "-D_POSIX_C_SOURCE=200112L";
  my ($amStr, $srcStr, $bsdStr) = ("{amCF}","{srcFiles}","{bzdlibs}");
  my ($amCF, $srcToAppend, $bsdLibs) = ("", "", "");

  if ($osEntered eq "FREEBSD") {
    $bsdLibs = "-largp -ldevstat";
    $amCF = \$bsdCF;
    $defTits = "$defTits m4_define([FREEBZD], [tits])";
    $srcToAppend = "freebsd_functions.c include/freebzd.h";
  }
  elsif ($osEntered eq "OPENBSD") {
    $bsdLibs = "-largp -lossaudio";
    $amCF = \$bsdCF;
    $defTits = "$defTits m4_define([OPENBZD], [forSure])";
    $srcToAppend = "openbsd_functions.c include/openbzd.h";
  }
  else {
    $amCF = \$posixCF;
    $defTits = "$defTits m4_define([LINUKS], [cryMeAriver])";
    $srcToAppend = "linux_functions.c";
  }

  copy("src/Makefail.skel",$srcMake)
    or die "Could not copy src/Makefail.skel $!";

  reflace_configure(\$defTits);

  my @hugeArr = (
    [\$amStr, \$$amCF],
    [\$srcStr, \$srcToAppend],
    [\$bsdStr, \$bsdLibs]
  );
  reflace_many(\@hugeArr,\$srcMake);
}
