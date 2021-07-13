/*
 * utils.h
 *
 * This file is part of nowa. It exposes various utility functions.
 *
 * Written and maintained by Stephen Ramsay (sramsay on GitHub)
 *
 * Last Modified: Tue Jul 13 11:53:45 CDT 2021
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

#ifndef UTILS_INCLUDE
#define UTILS_INCLUDE

#include <time.h>

double ftemp(double raw_temp);
double ctemp(double raw_temp);
char *dd_to_dms(const double coordinate);
double mps_to_mph(double mps);
double kph_to_mph(double kph);
double m_to_mi(double m);
char lat_dir(double latitude);
char lng_dir(double longitude);
int convert_iso8601(const char date_string[restrict static 1],
                    struct tm *date_data);
const char *bearing_to_compass_dir(int bearing);
char *comfort_scale(double dewpoint);
double pa_to_mb(int pascals);
char *latlong_string(double latitude, double longitude);

#endif
