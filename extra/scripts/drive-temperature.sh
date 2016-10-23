#!/usr/bin/env bash

# 10/23/2016 

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

# Edit /dev/sda according to
# your operating system drive naming
# convetion

while true; do
  sudo smartctl -a /dev/sda | \
    perl -Mstrict -Mwarnings -ne '
      my ($fifed_txt) = $_;
      my @arr = split(" ", $fifed_txt);

      if ($arr[1] and lc $arr[1] eq "temperature_celsius") {
        printf("%d\n",(($arr[9] and $arr[9] =~ /\d+/) ? $arr[9] : 0));
      }' > /tmp/pinkytemp

  sleep 20
done &
