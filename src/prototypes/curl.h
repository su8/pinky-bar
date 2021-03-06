/*
   04/04/2018

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
   MA 02110-1301, USA.
*/

#ifndef CURLLL_H_
#define CURLLL_H_

#if WITH_IP == 1
void get_ip(char *);
#endif /* WITH_IP */

#if WITH_GITHUB == 1
void get_github(char *);
#endif /* WITH_GITHUB */

#if WITH_REDDIT == 1
void get_reddit(char *);
#endif /* WITH_REDDIT */

#if WITH_PING == 1
void get_ping(char *, char *);
#endif /* WITH_PING */

#endif /* CURLLL_H_ */
