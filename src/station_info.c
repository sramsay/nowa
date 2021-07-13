/*
 * station_info.c
 *
 * This file is part of nowa. It parses the incoming JSON into a struct for
 * NWS station info
 *
 * Written and maintained by Stephen Ramsay (sramsay on GitHub)
 *
 * Last Modified: Tue Jul 13 11:06:11 CDT 2021
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

#include "station_info.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json.h"
#include "third_party/cJSON.h"

bool init_station(char station_id[restrict static 1],
                  struct station_info *info) {
  char *station_url = malloc(40 * sizeof *station_url);
  if (!station_url) {
    fprintf(stderr, "Fatal Error: No available memory\n");
    return false;
  }
  sprintf(station_url, "%s%s", "https://api.weather.gov/stations/", station_id);
  cJSON *station_json = json_init(station_url);

  // Error code
  cJSON *status_json = cJSON_GetObjectItemCaseSensitive(station_json, "status");
  if (status_json) {
    cJSON *details_json =
        cJSON_GetObjectItemCaseSensitive(station_json, "detail");
    printf("%s\n", details_json->valuestring);
    return false;
  }

  cJSON *geometry_json =
      cJSON_GetObjectItemCaseSensitive(station_json, "geometry");
  cJSON *coordinates_json =
      cJSON_GetObjectItemCaseSensitive(geometry_json, "coordinates");

  cJSON *longitude_json = cJSON_GetArrayItem(coordinates_json, 0);
  cJSON *latitude_json = cJSON_GetArrayItem(coordinates_json, 1);
  info->latitude = latitude_json->valuedouble;
  info->longitude = longitude_json->valuedouble;

  cJSON *properties_json =
      cJSON_GetObjectItemCaseSensitive(station_json, "properties");

  cJSON *elevation_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "elevation");
  cJSON *elevation_value_json =
      cJSON_GetObjectItemCaseSensitive(elevation_json, "value");
  info->elevation = elevation_value_json->valuedouble;

  cJSON *name_json = cJSON_GetObjectItemCaseSensitive(properties_json, "name");
  size_t name_size = strlen(name_json->valuestring);
  info->name = malloc(name_size + 1);
  if (!info->name) {
    fprintf(stderr, "Fatal Error: No available memory\n");
    free(station_url);
    return false;
  }
  strcpy(info->name, name_json->valuestring);

  cJSON *timezone_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "timeZone");
  size_t timezone_size = strlen(timezone_json->valuestring);
  info->timezone = malloc(timezone_size + 1);
  if (!info->timezone) {
    fprintf(stderr, "Fatal Error: No available memory\n");
    free(station_url);
    return false;
  }
  strcpy(info->timezone, timezone_json->valuestring);

  cJSON *forecast_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "forecast");
  size_t forecast_size = strlen(forecast_json->valuestring);
  info->forecast_url = malloc(forecast_size + 1);
  if (!info->forecast_url) {
    fprintf(stderr, "Fatal Error: No available memory\n");
    free(station_url);
    return false;
  }
  strcpy(info->forecast_url, forecast_json->valuestring);

  cJSON *county_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "county");
  if (county_json != NULL) {
    size_t county_size = strlen(county_json->valuestring);
    info->county_url = malloc(county_size + 1);
    strcpy(info->county_url, county_json->valuestring);

    cJSON *fire_weather_zone_json =
        cJSON_GetObjectItemCaseSensitive(properties_json, "fireWeatherZone");
    size_t fireweather_size = strlen(fire_weather_zone_json->valuestring);
    info->fire_weather_zone_url = malloc(fireweather_size + 1);
    if (!info->fire_weather_zone_url) {
      fprintf(stderr, "Fatal Error: No available memory\n");
      free(station_url);
      return false;
    }
    strcpy(info->fire_weather_zone_url, fire_weather_zone_json->valuestring);
  } else {
    info->fire_weather_zone_url = NULL;
  }

  free(station_url);
  cJSON_Delete(station_json);

  return true;
}

void cleanup_station_info(struct station_info *sinfo) {
  free(sinfo->name);
  free(sinfo->timezone);
  free(sinfo->forecast_url);
  free(sinfo->county_url);
  free(sinfo->fire_weather_zone_url);
}
