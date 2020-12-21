/*
 * product_data.h
 *
 * This file is part of nowa. It exposes the product struct and associated
 * functions.
 *
 * Written and maintained by Stephen Ramsay (sramsay on GitHub)
 *
 * Last Modified: Mon Dec 21 12:33:49 CST 2020
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

#ifndef PRODUCT_DATA_INCLUDED
#define PRODUCT_DATA_INCLUDED

#include <stdbool.h>

typedef struct product product;

struct product {
  char* product_code;
  char* product_text;
};

bool init_product(char station_id[restrict static 1], struct product* pd,
                  char* product_code);
bool construct_product_list_url(char station_id[restrict static 1],
                                char* product_url[], char* product_code);
void cleanup_product(struct product* pd);

#endif
