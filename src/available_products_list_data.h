/*
 * available_products_list_data.h
 *
 * This file is part of nowa. It exposes the product_id struct and associated
 * functions.
 *
 * Written and maintained by Stephen Ramsay (sramsay on GitHub)
 *
 * Last Modified: Wed Jun 02 10:47:56 CDT 2021
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

#ifndef AVAILABLE_PRODUCTS_LIST_DATA_INCLUDED
#define AVAILABLE_PRODUCTS_LIST_DATA_INCLUDED

#include <stdbool.h>
#include <stdlib.h>

typedef struct product_id product_id;

struct product_id {
  char* product_code;
  char* product_name;
};

struct product_id* init_available_products(char station_id[restrict static 1]);

bool construct_available_product_list_url(char station_id[restrict static 1],
                                          char* available_product_list_url[]);

extern size_t product_count;

#endif
