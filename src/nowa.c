/*
 * nowa.c
 *
 * This file is part of nowa.
 *
 * Written and maintained by Stephen Ramsay (sramsay on GitHub)
 *
 * This file is part of nowa.  It contains the main and usage functions, and
 * processes command-line options.
 *
 * Last Modified: Mon Dec 21 11:14:10 CST 2020
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

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "alerts.h"
#include "available_products_list.h"
#include "conditions.h"
#include "forecast.h"
#include "license.h"
#include "product.h"
#include "station_list.h"

static void print_usage(void);

int main(int argc, char* argv[]) {
  if (argc == 1) {
    print_usage();
    return EXIT_SUCCESS;
  }

  static struct option long_options[] = {
      {"help", no_argument, 0, 'h'},
      {"version", no_argument, 0, 'V'},
      {"station-id", required_argument, 0, 'i'},
      {"list-stations", required_argument, 0, 's'},
      {"conditions", no_argument, 0, 'c'},
      {"forecast", no_argument, 0, 'f'},
      {"discussion", no_argument, 0, 'd'},
      {"alerts", no_argument, 0, 'a'},
      {"product", required_argument, 0, 'p'},
      {"list-products", no_argument, 0, 'l'},
      {"json", no_argument, 0, 'j'},
      {0, 0, 0, 0}};

  int option_index = 0;

  extern char* optarg;
  bool station = false;
  bool usage = false;
  bool version = false;
  bool json = false;
  bool list_stations = false;
  bool conditions = false;
  bool forecast = false;
  bool discussion = false;
  bool alerts = false;
  bool product = false;
  bool list_products = false;

  char* station_id = malloc(5);
  char* lat_long = malloc(42);
  char* code = malloc(4);

  for (;;) {
    int opt =
        getopt_long(argc, argv, "hVi:s:cfdap:lj", long_options, &option_index);

    if (opt == -1) {
      break;
    }

    switch (opt) {
      case '?':
        break;
      case 'h':
        usage = true;
        break;
      case 'V':
        version = true;
        break;
      case 'i':
        if (strlen(optarg) > 5) {
          fprintf(stderr, "Station ids are comprised of four letters\n");
          free(station_id);
          free(lat_long);
          free(code);
          return EXIT_SUCCESS;
        } else {
          strcpy(station_id, optarg);
        }
        station = true;
        break;
      case 's':
        if (strlen(optarg) > 42) {
          fprintf(
              stderr,
              "Lat/long precision is limited to fifteen decimal places (which "
              "already exceeds the accuracy limits of GPS-based systems)\n");
          free(station_id);
          free(lat_long);
          free(code);
          return EXIT_SUCCESS;
        } else {
          strcpy(lat_long, optarg);
        }
        list_stations = true;
        break;
      case 'c':
        conditions = true;
        break;
      case 'f':
        forecast = true;
        break;
      case 'd':
        discussion = true;
        break;
      case 'a':
        alerts = true;
        break;
      case 'p':
        product = true;
        if (strlen(optarg) > 4) {
          fprintf(stderr, "Product codes are comprised of three letters\n");
          free(station_id);
          free(lat_long);
          free(code);
          return EXIT_SUCCESS;
        } else {
          strcpy(code, optarg);
        }
        break;
      case 'l':
        list_products = true;
        break;
      case 'j':
        json = true;
        break;
      default:
        print_usage();
    }
  }

  if (json) {
    if (list_stations) {
      if (!print_stations_json(lat_long)) {
        free(station_id);
        free(lat_long);
        free(code);
        return EXIT_FAILURE;
      }
    }
    if (station) {
      if (conditions) {
        if (!print_conditions_json(station_id)) {
          free(station_id);
          free(lat_long);
          free(code);
          return EXIT_FAILURE;
        }
      }
      if (forecast) {
        if (!print_forecast_json(station_id)) {
          free(station_id);
          free(lat_long);
          free(code);
          return EXIT_FAILURE;
        }
      }
      if (discussion) {
        if (!print_product_json(station_id, "AFD")) {
          free(station_id);
          free(lat_long);
          free(code);
          return EXIT_FAILURE;
        }
      }
      if (alerts) {
        if (!print_alerts_json(station_id)) {
          free(station_id);
          free(lat_long);
          free(code);
          return EXIT_FAILURE;
        }
      }
      if (product) {
        if (!print_product_json(station_id, code)) {
          free(station_id);
          free(lat_long);
          free(code);
          return EXIT_FAILURE;
        }
      }
      if (list_products) {
        if (!print_available_products_json(station_id)) {
          free(station_id);
          free(lat_long);
          free(code);
          return EXIT_FAILURE;
        }
      }
    } else {
      puts(
          "Requires a station id in addition to data request (e.g. "
          "--conditions -i KLNK)");
      free(station_id);
      free(lat_long);
      free(code);
      return EXIT_SUCCESS;
    }
    return EXIT_SUCCESS;
  }

  if (version) {
    print_version();
    free(station_id);
    free(lat_long);
    free(code);
    return EXIT_SUCCESS;
  }
  if (usage) {
    print_usage();
    free(station_id);
    free(lat_long);
    free(code);
    return EXIT_SUCCESS;
  }

  if (list_stations) {
    if (!print_stations(lat_long)) {
      free(station_id);
      free(lat_long);
      free(code);
      return EXIT_FAILURE;
    }
  } else if (station) {
    if (conditions) {
      if (!print_conditions(station_id)) {
        free(station_id);
        free(lat_long);
        free(code);
        return EXIT_FAILURE;
      }
    }
    if (forecast) {
      if (!print_forecast(station_id)) {
        free(station_id);
        free(lat_long);
        free(code);
        return EXIT_FAILURE;
      }
    }
    if (discussion) {
      if (!print_product(station_id, "AFD")) {
        free(station_id);
        free(lat_long);
        free(code);
        return EXIT_FAILURE;
      }
    }
    if (alerts) {
      if (!print_alerts(station_id)) {
        free(station_id);
        free(lat_long);
        free(code);
        return EXIT_FAILURE;
      }
    }
    if (product) {
      if (!print_product(station_id, code)) {
        free(station_id);
        free(lat_long);
        free(code);
        return EXIT_FAILURE;
      }
    }
    if (list_products) {
      if (!print_available_products(station_id)) {
        free(station_id);
        free(lat_long);
        free(code);
        return EXIT_FAILURE;
      }
    }
  } else {
    puts("Requires a station id (e.g. -i KLNK)");
    free(station_id);
    free(lat_long);
    free(code);
    return EXIT_SUCCESS;
  }

  free(station_id);
  free(lat_long);
  free(code);

  return EXIT_SUCCESS;
}

static void print_usage(void) {
  puts("Usage:");
  puts("  nowa --conditions --station-id \"KLNK\"");
  puts("  nowa --list-stations \"39.809734,-98.555620\"");
  puts("  nowa --product HWO --station-id \"KLNK\"");
  putchar('\n');
  puts("Options:");
  puts("  -c  --conditions     Current conditions");
  puts("  -f  --forecast       7-day forecast");
  puts("  -d  --discussion     Scientific forecast discussion");
  puts("  -a  --alerts         Active alerts (if any)");
  puts("  -l  --list-products  List available NWS product");
  putchar('\n');
  puts("  -s  --list-stations [lat,long]   Retrieve list of area stations");
  puts("  -p  --product [product code]     Request NWS product (if available)");
  puts("  -i  --station-id [ID]            Station id");
  puts("");
  puts("  -j  --json                       Raw JSON output from NWS");
  puts("");
  puts("  -h  --help     Print this message");
  puts("  -V  --version  Print version number and license info");
  putchar('\n');
}
