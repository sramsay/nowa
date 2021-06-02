/*
 * json.h
 *
 * This file is part of nowa. It exposes the json_init() function.
 *
 * Written and maintained by Stephen Ramsay (sramsay on GitHub)
 *
 * Last Modified: Mon Dec 21 12:21:59 CST 2020
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

#ifndef JSON_INCLUDED
#define JSON_INCLUDED

#include "third_party/cJSON.h"

cJSON* json_init(char const url[restrict static 1]);

#endif
