/*
 * station_info.h
 *
 * This file is part of nowa. It exposes the station_info struct and
 * associated functions.
 *
 * Written and maintained by Stephen Ramsay (sramsay on GitHub)
 *
 * Last Modified: Tue Jul 13 11:38:43 CDT 2021
 *
 * Copyright © 2020-2021 Stephen Ramsay
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

#ifndef STATION_DATA_INCLUDED
#define STATION_DATA_INCLUDED

#include <stdbool.h>

typedef struct station_info station_info;

struct station_info {
  double latitude;
  double longitude;
  double elevation;  // meters
  char *name;
  char *timezone;
  char *forecast_url;
  char *county_url;
  char *fire_weather_zone_url;
};

bool init_station(char station_id[restrict static 1],
                  struct station_info *info);

void cleanup_station_info(struct station_info *sinfo);

#endif
