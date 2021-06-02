/*
 * product.c
 *
 * This file is part of nowa. It contains display functions for
 * outputing particular NWS products.
 *
 * Written and maintained by Stephen Ramsay (sramsay on GitHub)
 *
 * Last Modified: Mon Dec 21 12:07:35 CST 2020
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

#include "product.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "json.h"
#include "product_data.h"
#include "third_party/cJSON.h"

bool print_product(char station_id[restrict static 1], char* product_code) {
  struct product* pd = malloc(sizeof(struct product));
  if (!pd) {
    fprintf(stderr, "Fatal Error: No available memory.\n");
    return false;
  }

  if (!init_product(station_id, pd, product_code)) {
    fprintf(stderr, "Error: %s", "Unable to retrieve requested product.\n");
		cleanup_product(pd);
    return false;
  }

  printf("%s", pd->product_code);
  printf("%s", pd->product_text);

  cleanup_product(pd);

  return true;
}

bool print_product_json(char station_id[restrict static 1],
                        char* product_code) {
  char* product_list_url = malloc(60);

  if (!product_list_url) {
    fprintf(stderr, "Fatal Error: No available memory\n");
    free(product_list_url);
    return false;
  }

  if (!construct_product_list_url(station_id, &product_list_url,
                                  product_code)) {
    fprintf(stderr, "Error: %s\n", "Unable to construct product URL.");
    free(product_list_url);
    return false;
  }
  cJSON* product_json = json_init(product_list_url);
  char* output = cJSON_Print(product_json);
  puts(output);
  cJSON_Delete(product_json);

  free(output);
  free(product_list_url);

  return true;
}
