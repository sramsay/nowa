/*
 * points_data.h
 *
 * This file is part of nowa. It exposes the point_info struct and
 * associated functions.
 *
 * Written and maintained by Stephen Ramsay (sramsay on GitHub)
 *
 * Last Modified: Tue Jul 13 11:28:24 CDT 2021
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

#ifndef POINTS_DATA_INCLUDED
#define POINTS_DATA_INCLUDED

#include <stdbool.h>

typedef struct points_info points_info;

struct points_info {
  char cwa[4];  // The forecast office
  char *forecast_url;
  char *forecast_hourly_url;
  char *forecast_grid_data_url;
  char *observation_stations_url;
  char *forecast_zone_url;
  char *county_url;
  char *fire_weather_zone_url;
  char *radar_station;
};
// This JSON also includes bearing and distance (from what, exactly? the
// forecast office?) and timezone.

bool init_points(char lat_long[restrict static 1], struct points_info *points);
void cleanup_points(struct points_info *points);

#endif
