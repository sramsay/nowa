/*
 * alerts.c
 *
 * This file is part of nowa. It contains display functions related
 * to weather alerts.
 *
 * Written and maintained by Stephen Ramsay (sramsay on GitHub)
 *
 * Last Modified: Tue Jul 13 10:52:02 CDT 2021
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

#include "alerts.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "alerts_data.h"
#include "json.h"
#include "third_party/cJSON.h"
#include "zoneinfo_data.h"

bool print_alerts(char station_id[restrict static 1]) {
  struct alert *alerts = init_alerts(station_id);

  if (alerts_count == 0) {
    puts("No active alerts.");
  } else {
    for (size_t i = 0; i < alerts_count; i++) {
      printf("### %s\n\n", alerts[i].headline);
      printf("%s\n\n", alerts[i].description);
      if (alerts[i].instruction != NULL) {
        printf("%s\n\n", alerts[i].instruction);
      }

      free(alerts[i].headline);
      free(alerts[i].description);
      free(alerts[i].instruction);
    }
  }

  free(alerts);

  return true;
}

bool print_alerts_json(char station_id[restrict static 1]) {
  struct zoneinfo zinfo = {0};
  if (!init_zoneinfo(station_id, &zinfo)) {
    fprintf(stderr, "Error: %s\n", "Unable to retrieve zone info.");
    return false;
  }

  char *alerts_url = malloc(50 * sizeof *alerts_url);
  if (alerts_url) {
    sprintf(alerts_url, "%s%s", "https://api.weather.gov/alerts/active/zone/",
            zinfo.id);
  } else {
    fprintf(stderr, "Fatal Error: No available memory\n");
    return false;
  }

  cJSON *alerts_json = json_init(alerts_url);
  char *output = cJSON_Print(alerts_json);
  puts(output);
  free(zinfo.id);
  free(zinfo.name);
  free(zinfo.state);
  free(alerts_url);
  cJSON_Delete(alerts_json);
  free(output);

  return true;
}
