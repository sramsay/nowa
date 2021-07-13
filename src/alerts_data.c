/*
 * alerts_data.c
 *
 * This file is part of nowa.  It parses the incoming JSON into the alert
 * struct.
 *
 * Written and maintained by Stephen Ramsay (sramsay on GitHub)
 *
 * Last Modified: Tue Jul 13 10:52:54 CDT 2021
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

#include "alerts_data.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json.h"
#include "third_party/cJSON.h"
#include "zoneinfo_data.h"

size_t alerts_count;

struct alert *init_alerts(char station_id[restrict static 1]) {
  struct zoneinfo zinfo = {0};
  if (!init_zoneinfo(station_id, &zinfo)) {
    fprintf(stderr, "Error: %s", "Unable to retrieve zone info\n");
    exit(1);
  }

  char *alerts_url = malloc(50 * sizeof *alerts_url);
  if (!alerts_url) {
    fprintf(stderr, "Fatal Error: No available memory\n");
    exit(1);
  }

  sprintf(alerts_url, "%s%s", "https://api.weather.gov/alerts/active/zone/",
          zinfo.id);
  cJSON *alerts_json = json_init(alerts_url);

  // Error code
  cJSON *status_json = cJSON_GetObjectItemCaseSensitive(alerts_json, "status");
  if (status_json) {
    cJSON *details_json =
        cJSON_GetObjectItemCaseSensitive(alerts_json, "detail");
    printf("%s\n", details_json->valuestring);
    exit(1);
  }

  cJSON *features_json =
      cJSON_GetObjectItemCaseSensitive(alerts_json, "features");

  alerts_count = cJSON_GetArraySize(features_json);
  struct alert *alerts_list = malloc(alerts_count * sizeof *alerts_list);
  if (!alerts_list) {
    fprintf(stderr, "Fatal Error: No available memory\n");
    exit(1);
  }

  cJSON *feature_json = {0};
  int count = 0;
  cJSON_ArrayForEach(feature_json, features_json) {
    cJSON *properties_json =
        cJSON_GetObjectItemCaseSensitive(feature_json, "properties");

    cJSON *headline_json =
        cJSON_GetObjectItemCaseSensitive(properties_json, "headline");
    size_t headline_size = strlen(headline_json->valuestring);
    alerts_list[count].headline = malloc(headline_size + 1);
    if (!alerts_list[count].headline) {
      fprintf(stderr, "Fatal Error: No available memory\n");
      exit(1);
    }

    strcpy(alerts_list[count].headline, headline_json->valuestring);

    cJSON *description_json =
        cJSON_GetObjectItemCaseSensitive(properties_json, "description");
    size_t description_size = strlen(description_json->valuestring);
    alerts_list[count].description = malloc(description_size + 1);
    if (!alerts_list[count].description) {
      fprintf(stderr, "Fatal Error: No available memory\n");
      exit(1);
    }
    strcpy(alerts_list[count].description, description_json->valuestring);

    cJSON *instruction_json =
        cJSON_GetObjectItemCaseSensitive(properties_json, "instruction");
    if (instruction_json->valuestring != NULL) {
      size_t instruction_size = strlen(instruction_json->valuestring);
      alerts_list[count].instruction = malloc(instruction_size + 1);
      if (!alerts_list[count].instruction) {
        fprintf(stderr, "Fatal Error: No available memory\n");
        exit(1);
      }
      strcpy(alerts_list[count].instruction, instruction_json->valuestring);
    } else {
      alerts_list[count].instruction = NULL;
    }

    count++;
  }

  free(zinfo.id);
  free(zinfo.name);
  free(zinfo.state);
  free(alerts_url);
  cJSON_Delete(alerts_json);

  return alerts_list;
}
