/*
 * forecast.h
 *
 * This file is part of nowa. It exposes the print_forecast() and
 * print_forecast_json() functions.
 *
 * Written and maintained by Stephen Ramsay (sramsay on GitHub)
 *
 * Last Modified: Mon Dec 21 12:21:51 CST 2020
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

#ifndef FORECAST_INCLUDED
#define FORECAST_INCLUDED

#include <stdbool.h>

#define _XOPEN_SOURCE 600

bool print_forecast(char lat_long[restrict static 1]);
bool print_forecast_json(char station_id[restrict static 1]);

#endif
