/*
 * station_list_data.h
 *
 * This file is part of nowa. It exposes the station struct and
 * associated functions.
 *
 * Written and maintained by Stephen Ramsay (sramsay on GitHub)
 *
 * Last Modified: Mon Dec 21 12:33:59 CST 2020
 *
 * Copyright © 2020 Stephen Ramsay
 *
 * nowa is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option) any
 * later version.
 *
 * nowa is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with nowa; see the file COPYING.  If not see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef STATION_LIST_DATA_INCLUDED
#define STATION_LIST_DATA_INCLUDED

#include <stdlib.h>

typedef struct station station;

struct station {
  char* station_id;
  char* name;
};

struct station* init_station_list(char lat_long[restrict static 1]);

extern size_t station_count;

#endif
