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

sub re_read {
  my ($filename) = @_;
  my $fh;

  open($fh, '<:encoding(UTF-8)', $filename)
    or die "Could not open file '$filename' $!";
  local $/ = undef; # <--- slurp mode
  my $concatArr = <$fh>;
  close($fh);

  return $concatArr;
}

sub re_write {
  my ($filename,$concatArr) = @_;
  my $fh;

  open($fh, '>:encoding(UTF-8)', $filename) 
    or die "Could not open file '$filename' $!";

  print $fh $concatArr;
  close($fh);
  return;
}

sub reflace_configure {
  my ($new) = @_;
  my $filename = "configure.ac";

  my @arr = split("\n", re_read($filename));
  $arr[9] = $new;
  my $concatArr = join("\n", @arr);

  re_write($filename,$concatArr);
  return;
}

sub reflace_many {
  my ($ag1,$ag2,$ag3,$ag4,$ag5,$ag6,$filename) = @_;
  my $concatArr = re_read($filename);

  $concatArr =~ s/$ag1/$ag2/g;
  $concatArr =~ s/$ag3/$ag4/g;
  $concatArr =~ s/$ag5/$ag6/g;

  re_write($filename,$concatArr);
  return;
}

sub reflace_single {
  my ($ag1,$ag2,$filename) = @_;
  my $concatArr = re_read($filename);

  $concatArr =~ s/$ag1/$ag2/g;
  re_write($filename,$concatArr);
  return;
}

my ($amCF, $srcToAppend, $bsdLibs) = ("", "", "");
my $osEntered = $ARGV[0] ? uc $ARGV[0] : die "No OS/Distro supplied.";

my $defTits = "m4_define([cuRos],[$osEntered])";
my $bsdCF = "-D_DEFAULT_SOURCE -L/usr/local/lib";
my $posixCF = "-D_POSIX_C_SOURCE=200112L";

if ($osEntered eq "FREEBSD") {
  $bsdLibs = "-largp -ldevstat";
  $amCF = $bsdCF;
  $defTits = "$defTits m4_define([FREEBZD], [tits])";
  $srcToAppend = "freebsd_functions.c include/freebzd.h";
}
elsif ($osEntered eq "OPENBSD") {
  $bsdLibs = "-largp -lossaudio";
  $amCF = $bsdCF;
  $defTits = "$defTits m4_define([OPENBZD], [forSure])";
  $srcToAppend = "openbsd_functions.c include/openbzd.h";
}
else {
  $amCF = $posixCF;
  $defTits = "$defTits m4_define([LINUKS], [cryMeAriver])";
  $srcToAppend = "linux_functions.c";
}

copy("src/Makefail.skel","src/Makefile.am")
  or die "Coudl not copy src/Makefail.skel $!";

reflace_configure("$defTits");
reflace_many(
  "{amCF}", $amCF,
  "{srcFiles}", $srcToAppend,
  "{bzdlibs}", $bsdLibs,
  "src/Makefile.am"
);
