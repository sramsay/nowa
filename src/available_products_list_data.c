/*
 * available_products_list_data.c
 *
 * This file is part of nowa. It parses the incoming JSON into structs for
 * available NWS products.
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

#include "available_products_list_data.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "json.h"
#include "points_data.h"
#include "station_info.h"
#include "third_party/cJSON.h"
#include "utils.h"

size_t product_count;

struct product_id *init_available_products(char station_id[restrict static 1]) {
  char *available_product_list_url =
      malloc(60 * sizeof *available_product_list_url);
  if (!available_product_list_url) {
    fprintf(stderr, "Fatal Error: No available memory\n");
    free(available_product_list_url);
    exit(1);
  }

  construct_available_product_list_url(station_id, &available_product_list_url);

  cJSON *available_product_list_json = json_init(available_product_list_url);

  cJSON *graph_json =
      cJSON_GetObjectItemCaseSensitive(available_product_list_json, "@graph");

  // Error code
  cJSON *status_json = cJSON_GetObjectItemCaseSensitive(graph_json, "status");
  if (status_json) {
    cJSON *details_json =
        cJSON_GetObjectItemCaseSensitive(graph_json, "detail");
    printf("%s\n", details_json->valuestring);
    free(available_product_list_url);
    exit(1);
  }

  product_count = cJSON_GetArraySize(graph_json);
  struct product_id *product_list =
      malloc(product_count * sizeof *product_list);
  if (!product_list) {
    fprintf(stderr, "Fatal Error: No available memory\n");
    cJSON_Delete(available_product_list_json);
    cJSON_Delete(graph_json);
    free(available_product_list_url);
    exit(1);
  }

  cJSON *product_json = {0};
  int count = 0;
  cJSON_ArrayForEach(product_json, graph_json) {
    cJSON *product_code_json =
        cJSON_GetObjectItemCaseSensitive(product_json, "productCode");
    size_t product_code_size = strlen(product_code_json->valuestring) + 1;
    product_list[count].product_code = malloc(product_code_size);
    if (!product_list[count].product_code) {
      fprintf(stderr, "Fatal Error: No available memory\n");
      cJSON_Delete(available_product_list_json);
      cJSON_Delete(graph_json);
      free(available_product_list_url);
      exit(1);
    }
    strcpy(product_list[count].product_code, product_code_json->valuestring);

    cJSON *product_name_json =
        cJSON_GetObjectItemCaseSensitive(product_json, "productName");
    size_t product_name_size = strlen(product_name_json->valuestring) + 1;
    product_list[count].product_name = malloc(product_name_size);
    if (!product_list[count].product_name) {
      fprintf(stderr, "Fatal Error: No available memory\n");
      cJSON_Delete(available_product_list_json);
      cJSON_Delete(graph_json);
      free(available_product_list_url);
      exit(1);
    }
    strcpy(product_list[count].product_name, product_name_json->valuestring);

    count++;
  }

  cJSON_Delete(available_product_list_json);
  free(available_product_list_url);

  return product_list;
}

bool construct_available_product_list_url(char station_id[restrict static 1],
                                          char *available_product_list_url[]) {
  struct station_info sinfo = {0};
  if (!init_station(station_id, &sinfo)) {
    fprintf(stderr, "Error: %s", "Unable to retrieve station info.\n");
    return false;
  }

  char *lat_long = latlong_string(sinfo.latitude, sinfo.longitude);

  struct points_info points = {0};
  if (!init_points(lat_long, &points)) {
    fprintf(stderr, "Error: %s", "Unable to retrieve points data\n");
    return false;
  }

  sprintf(*available_product_list_url, "%s%s%s",
          "https://api.weather.gov/products/locations/", points.cwa, "/types");

  free(lat_long);
  cleanup_station_info(&sinfo);
  cleanup_points(&points);

  return true;
}
