/*
 * conditions_data.h
 *
 * This file is part of nowa. It exposes the current_conditions struct and
 * associated functions..
 *
 * Written and maintained by Stephen Ramsay (sramsay on GitHub)
 *
 * Last Modified: Mon Dec 21 12:32:49 CST 2020
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

#ifndef CONDITIONS_DATA_INCLUDED
#define CONDITIONS_DATA_INCLUDED

#include <stdbool.h>

typedef struct current_conditions current_conditions;

struct current_conditions {
  int elevation;
  int wind_direction;
  int pressure;
  int sl_pressure;
  int visibility;
  double temperature;
  double dewpoint;
  double wind_speed;
  double wind_gust;
  double max_temp_24;
  double min_temp_24;
  double precip_hour;
  double precip_3hour;
  double precip_6hour;
  double relative_humidity;
  double wind_chill;
  double heat_index;
  char* summary;
  char* timestamp;
  char* metar;
};

// Also includes cloudLayers, though it's not clear if this is useful.

bool init_conditions(char station_id[restrict static 1],
                     struct current_conditions* current);
bool construct_conditions_url(char station_id[restrict static 1],
                              char* conditions_url[static 1]);
void cleanup_conditions(struct current_conditions* current);

#endif
