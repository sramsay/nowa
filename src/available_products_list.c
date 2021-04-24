/*
 * available_products_list.c
 *
 * This file is part of nowa. It contains display functions listing available
 * NWS products.
 *
 * Written and maintained by Stephen Ramsay (sramsay on GitHub)
 *
 * Last Modified: Sat Apr 24 10:13:03 CDT 2021
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

#include "available_products_list.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "available_products_list_data.h"
#include "json.h"
#include "third_party/cJSON.h"

bool print_available_products(char station_id[restrict static 1]) {
  struct product_id* product_list = init_available_products(station_id);

  printf("%s %s:\n\n", "Forecast Office Products Available for", station_id);
  puts("Code  Description");
  puts("----  -----------");
  for (size_t i = 0; i < product_count; i++) {
    printf("%s   %s\n", product_list[i].product_code,
           product_list[i].product_name);
    free(product_list[i].product_code);
    free(product_list[i].product_name);
  }

  free(product_list);

  return true;
}

bool print_available_products_json(char station_id[restrict static 1]) {
  char* available_product_list_url = malloc(60);
  if (!available_product_list_url) {
    fprintf(stderr, "Fatal Error: No available memory\n");
    return false;
  }

  construct_available_product_list_url(station_id, &available_product_list_url);

  cJSON* available_product_list_json = json_init(available_product_list_url);
  char* output = cJSON_Print(available_product_list_json);
  puts(output);

  free(available_product_list_url);
  cJSON_Delete(available_product_list_json);

  return true;
}
