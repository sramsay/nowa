/*
 * license.c
 *
 * This file is part of nowa. It contains display functions for the
 * version and license information.
 *
 * Written and maintained by Stephen Ramsay (sramsay on GitHub)
 *
 * Last Modified: Mon Dec 21 12:06:35 CST 2020
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

#include "license.h"

#include <config.h>
#include <stdio.h>

void print_version(void) {
  printf("%s %s\n", PACKAGE, PACKAGE_VERSION);
  printf("Copyright © %s by Stephen Ramsay\n", COPYRIGHT_DATES);
  printf(
      "License GPVv3+: GNU GPL version 3 or later "
      "<https://gnu.org/licenses.gpl.html>.\n");
  printf(
      "This is free software: you are free to change and redistribute it.\n");
  printf("There is NO WARRANTY, to the extent permitted by law.\n");
}
