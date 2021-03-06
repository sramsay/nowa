/*
 * conditions_data.c
 *
 * This file is part of nowa. It parses the incoming JSON into the
 * current_conditions struct
 *
 * Written and maintained by Stephen Ramsay (sramsay on GitHub)
 *
 * Last Modified: Tue Jul 13 11:14:25 CDT 2021
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

#define _GNU_SOURCE
#include "conditions_data.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json.h"
#include "third_party/cJSON.h"

bool init_conditions(char station_id[restrict static 1],
                     struct current_conditions *current) {
  char *conditions_url = malloc(60 * sizeof *conditions_url);
  if (!conditions_url) {
    fprintf(stderr, "Fatal Error: No available memory\n");
    free(conditions_url);
    return false;
  }
  construct_conditions_url(station_id, &conditions_url);

  cJSON *conditions_json = json_init(conditions_url);

  // Error code
  cJSON *status_json =
      cJSON_GetObjectItemCaseSensitive(conditions_json, "status");
  if (status_json) {
    cJSON *details_json =
        cJSON_GetObjectItemCaseSensitive(conditions_json, "detail");
    printf("%s\n", details_json->valuestring);
    return false;
  }

  cJSON *properties_json =
      cJSON_GetObjectItemCaseSensitive(conditions_json, "properties");

  // Elevation
  cJSON *elevation_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "elevation");
  cJSON *elevation_value_json =
      cJSON_GetObjectItemCaseSensitive(elevation_json, "value");
  current->elevation = elevation_value_json->valueint;

  // Wind Direction
  cJSON *wind_direction_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "windDirection");
  cJSON *wind_direction_value_json =
      cJSON_GetObjectItemCaseSensitive(wind_direction_json, "value");
  current->wind_direction = wind_direction_value_json->valueint;

  // Pressure
  cJSON *pressure_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "barometricPressure");
  cJSON *pressure_value_json =
      cJSON_GetObjectItemCaseSensitive(pressure_json, "value");
  current->pressure = pressure_value_json->valuedouble;

  // Sea Level Pressure
  cJSON *sl_pressure_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "seaLevelPressure");
  cJSON *sl_pressure_value_json =
      cJSON_GetObjectItemCaseSensitive(sl_pressure_json, "value");
  current->sl_pressure = sl_pressure_value_json->valuedouble;

  // Visibility
  cJSON *visibility_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "visibility");
  cJSON *visibility_value_json =
      cJSON_GetObjectItemCaseSensitive(visibility_json, "value");
  current->visibility = visibility_value_json->valueint;

  // Temperature
  cJSON *temperature_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "temperature");
  cJSON *temperature_value_json =
      cJSON_GetObjectItemCaseSensitive(temperature_json, "value");
  current->temperature = temperature_value_json->valuedouble;

  // Dewpoint
  cJSON *dewpoint_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "dewpoint");
  cJSON *dewpoint_value_json =
      cJSON_GetObjectItemCaseSensitive(dewpoint_json, "value");
  current->dewpoint = dewpoint_value_json->valuedouble;

  // Wind Speed
  cJSON *wind_speed_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "windSpeed");
  cJSON *wind_speed_value_json =
      cJSON_GetObjectItemCaseSensitive(wind_speed_json, "value");
  current->wind_speed = wind_speed_value_json->valuedouble;

  // Wind Gust
  cJSON *wind_gust_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "windGust");
  cJSON *wind_gust_value_json =
      cJSON_GetObjectItemCaseSensitive(wind_gust_json, "value");
  current->wind_gust = wind_gust_value_json->valuedouble;

  // Max Temperature Last 24 Hours
  cJSON *max_temp_24_json = cJSON_GetObjectItemCaseSensitive(
      properties_json, "maxTemperatureLast24Hours");
  cJSON *max_temp_24_value_json =
      cJSON_GetObjectItemCaseSensitive(max_temp_24_json, "value");
  current->max_temp_24 = max_temp_24_value_json->valuedouble;

  // Min Temperature Last 24 Hours
  cJSON *min_temp_24_json = cJSON_GetObjectItemCaseSensitive(
      properties_json, "minTemperatureLast24Hours");
  cJSON *min_temp_24_value_json =
      cJSON_GetObjectItemCaseSensitive(min_temp_24_json, "value");
  current->min_temp_24 = min_temp_24_value_json->valuedouble;

  // Precipitation Last Hour
  cJSON *precip_hour_json = cJSON_GetObjectItemCaseSensitive(
      properties_json, "precipitationLastHour");
  cJSON *precip_hour_value_json =
      cJSON_GetObjectItemCaseSensitive(precip_hour_json, "value");
  if (precip_hour_value_json) {
    current->precip_hour = precip_hour_value_json->valuedouble;
  }

  // Precipitation Last 3 Hours
  cJSON *precip_3hour_json = cJSON_GetObjectItemCaseSensitive(
      properties_json, "precipitationLast3Hours");
  cJSON *precip_3hour_value_json =
      cJSON_GetObjectItemCaseSensitive(precip_3hour_json, "value");
  if (precip_3hour_value_json) {
    current->precip_3hour = precip_3hour_value_json->valuedouble;
  }

  // Precipitation Last 6 Hours
  cJSON *precip_6hour_json = cJSON_GetObjectItemCaseSensitive(
      properties_json, "precipitationLast6Hours");
  cJSON *precip_6hour_value_json =
      cJSON_GetObjectItemCaseSensitive(precip_6hour_json, "value");
  if (precip_6hour_value_json) {
    current->precip_6hour = precip_6hour_value_json->valuedouble;
  }

  // Relative Humidity
  cJSON *relative_humidity_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "relativeHumidity");
  cJSON *relative_humidity_value_json =
      cJSON_GetObjectItemCaseSensitive(relative_humidity_json, "value");
  current->relative_humidity = relative_humidity_value_json->valuedouble;

  // Wind Chill
  cJSON *wind_chill_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "windChill");
  cJSON *wind_chill_value_json =
      cJSON_GetObjectItemCaseSensitive(wind_chill_json, "value");
  current->wind_chill = wind_chill_value_json->valuedouble;

  // Heat Index
  cJSON *heat_index_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "heatIndex");
  cJSON *heat_index_value_json =
      cJSON_GetObjectItemCaseSensitive(heat_index_json, "value");
  current->heat_index = heat_index_value_json->valuedouble;

  // Timestamp
  cJSON *timestamp_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "timestamp");
  if (!asprintf(&current->timestamp, "%s", timestamp_json->valuestring)) {
    fprintf(stderr, "Fatal Error: No available memory\n");
    free(conditions_url);
    return false;
  }

  // METAR
  cJSON *metar_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "rawMessage");
  if (!asprintf(&current->metar, "%s", metar_json->valuestring)) {
    fprintf(stderr, "Fatal Error: No available memory\n");
    free(conditions_url);
    return false;
  }

  // Summary
  cJSON *text_description_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "textDescription");
  if (!asprintf(&current->summary, "%s", text_description_json->valuestring)) {
    fprintf(stderr, "Fatal Error: No available memory.\n");
    free(conditions_url);
    return false;
  }

  free(conditions_url);
  cJSON_Delete(conditions_json);

  return true;
}

bool construct_conditions_url(char station_id[restrict static 1],
                              char *conditions_url[static 1]) {
  sprintf(*conditions_url, "%s%s%s", "https://api.weather.gov/stations/",
          station_id, "/observations/latest");
  return true;
}

void cleanup_conditions(struct current_conditions *current) {
  free(current->timestamp);
  free(current->metar);
  free(current->summary);
}
