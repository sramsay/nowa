/*
 * forecast.c
 *
 * This file is part of nowa. It contains display functions for the current
 * 7-day forecast.
 *
 * Written and maintained by Stephen Ramsay (sramsay on GitHub)
 *
 * Last Modified: Mon Dec 21 12:05:35 CST 2020
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

#include "forecast.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "forecast_data.h"
#include "json.h"
#include "points_data.h"
#include "station_info.h"
#include "third_party/cJSON.h"
#include "utils.h"

bool print_forecast(char station_id[restrict static 1]) {
  struct tm last_updated;
  struct forecast forecasts[14];

  if (!init_forecast(station_id, &last_updated, forecasts)) {
    fprintf(stderr, "Error: %s", "Unable to retrieve forecast info.\n");
    return false;
  }

  struct station_info sinfo = {0};
  if (!init_station(station_id, &sinfo)) {
    fprintf(stderr, "Error: %s", "Unable to retrieve station info.\n");
    return false;
  }

  printf("Current forecast for %s (%s)\n", sinfo.name, station_id);

  char* dms_latitude = dd_to_dms(sinfo.latitude);
  char latdir = lat_dir(sinfo.latitude);
  char* dms_longitude = dd_to_dms(sinfo.longitude);
  char lngdir = lng_dir(sinfo.longitude);
  printf("%s %c, %s %c\n", dms_latitude, latdir, dms_longitude, lngdir);

  char* update_string = malloc(61 * sizeof(char));
  if (!update_string) {
    fprintf(stderr, "Fatal Error: Not enough memory\n");
    free(dms_latitude);
    free(dms_longitude);
    return false;
  }
  long ts = mktime(&last_updated) - timezone;
  localtime_r(&ts, &last_updated);
  strftime(update_string, 61, "Last Updated: %A, %d %B %Y, %I:%M:%S %p %Z",
           &last_updated);

  printf("%s\n\n", update_string);

  for (size_t i = 0; i < 14; i++) {
    printf("%s: %s\n", forecasts[i].name, forecasts[i].detailed_forecast);
    free(forecasts[i].name);
    free(forecasts[i].detailed_forecast);
  }

  cleanup_station_info(&sinfo);

  free(update_string);
  free(dms_latitude);
  free(dms_longitude);

  return 0;
}

bool print_forecast_json(char station_id[restrict static 1]) {
  struct station_info sinfo = {0};
  if (!init_station(station_id, &sinfo)) {
    fprintf(stderr, "Error: %s\n", "Unable to retrieve station data");
    return false;
  }

  char lat_long[41];
  sprintf(lat_long, "%f,%f", sinfo.latitude, sinfo.longitude);

  struct points_info points = {0};
  if (!init_points(lat_long, &points)) {
    fprintf(stderr, "Error: %s\n", "Unable to retrieve points data.");
    return false;
  }

  char* forecast_url = points.forecast_url;
  cJSON* forecast_json = json_init(forecast_url);
  char* output = cJSON_Print(forecast_json);
  puts(output);
  free(points.forecast_url);
  cJSON_Delete(forecast_json);
  free(output);

  return true;
}
