/*
 * zoneinfo_data.c
 *
 * This file is part of nowa. It parses the incoming JSON into structs for
 * NWS zones
 *
 * Written and maintained by Stephen Ramsay (sramsay on GitHub)
 *
 * Last Modified: Tue Jul 13 11:54:34 CDT 2021
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

#include "zoneinfo_data.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json.h"
#include "station_info.h"
#include "third_party/cJSON.h"

bool init_zoneinfo(char station_id[restrict static 1], struct zoneinfo *info) {
  struct station_info sinfo = {0};
  if (!init_station(station_id, &sinfo)) {
    fprintf(stderr, "Error: %s", "Unable to retrieve station info\n");
    return false;
  }

  cJSON *zone_json =
      json_init(sinfo.forecast_url);  // This is actually a URL with a zone_id
                                      // and the resulting object is not real
                                      // forecast object

  // Error code
  cJSON *status_json = cJSON_GetObjectItemCaseSensitive(zone_json, "status");
  if (status_json) {
    cJSON *details_json = cJSON_GetObjectItemCaseSensitive(zone_json, "detail");
    printf("%s\n", details_json->valuestring);
    return false;
  }

  cJSON *properties_json =
      cJSON_GetObjectItemCaseSensitive(zone_json, "properties");

  cJSON *id_json = cJSON_GetObjectItemCaseSensitive(properties_json, "id");
  size_t id_size = strlen(id_json->valuestring);
  info->id = malloc(id_size + 1);
  if (!info->id) {
    fprintf(stderr, "Fatal Error: No available memory\n");
    return false;
  }
  strcpy(info->id, id_json->valuestring);

  cJSON *name_json = cJSON_GetObjectItemCaseSensitive(properties_json, "name");
  size_t name_size = strlen(name_json->valuestring);
  info->name = malloc(name_size + 1);
  strcpy(info->name, name_json->valuestring);

  cJSON *state_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "state");
  if (state_json->valuestring != NULL) {
    size_t state_size = strlen(state_json->valuestring);
    info->state = malloc(state_size + 1);
    if (!info->state) {
      fprintf(stderr, "Fatal Error: No available memory\n");
      return false;
    }
    strcpy(info->state, state_json->valuestring);
  } else {
    info->state = NULL;
  }

  cleanup_station_info(&sinfo);
  cJSON_Delete(zone_json);

  return true;
}
