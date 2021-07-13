/*
 * alerts_data.h
 *
 * This file is part of nowa. It exposes the alert struct and associated
 * functions.
 *
 * Written and maintained by Stephen Ramsay (sramsay on GitHub)
 *
 * Last Modified: Tue Jul 13 10:51:54 CDT 2021
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

#ifndef ALERTS_DATA_INCLUDED
#define ALERTS_DATA_INCLUDED

#include <stdlib.h>

typedef struct alert alert;

struct alert {
  char *headline;
  char *description;
  char *instruction;
};

struct alert *init_alerts(char zone_id[restrict static 1]);

extern size_t alerts_count;

#endif
