/*
 * forecast_data.h
 *
 * This file is part of nowa. It exposes the forecast_day struct and
 * associated functions.
 *
 * Written and maintained by Stephen Ramsay (sramsay on GitHub)
 *
 * Last Modified: Sat Apr 24 10:16:06 CDT 2021
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

#ifndef FORECAST_DATA_INCLUDED
#define FORECAST_DATA_INCLUDED

#include <stdbool.h>
#include <time.h>

typedef struct forecast_day forecast_day;

struct forecast {
  char* name;
  char* detailed_forecast;
};

bool init_forecast(char lat_long[restrict static 1], struct tm* last_updated,
                   struct forecast forecasts[static 14]);

#endif
