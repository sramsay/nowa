#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "alerts.h"
#include "conditions.h"
#include "forecast.h"
#include "license.h"
#include "station_list.h"

static void print_usage(void);

int main(int argc, char *argv[]) {
  static struct option long_options[] = {
      {"help", no_argument, (void *)0, 'h'},
      {"version", no_argument, (void *)0, 'V'},
      {"stationid", required_argument, 0, 's'},
      {"list-stations", required_argument, 0, 'l'},
      {"conditions", required_argument, 0, 'c'},
      {"forecast", required_argument, 0, 'f'},
      {"alerts", required_argument, 0, 'a'},
      {0, 0, 0, 0}};

  // TODO: Maybe station_ids, lat_longs, and any other identifiers should just
  // be arguments to the various switches.

  int option_index = 0;

  for (;;) {
    int opt =
        getopt_long(argc, argv, "hVc:s:l:f:a:", long_options, &option_index);

    if (opt == -1) {
      break;
    }

    switch (opt) {
      case '?':
        break;
      case 'h':
        print_usage();
        return EXIT_SUCCESS;
      case 'V':
        print_version();
        return EXIT_SUCCESS;
      case 'l':
        if (!print_stations(optarg)) {
          return EXIT_FAILURE;
        } else {
          return EXIT_SUCCESS;
        }
        return EXIT_SUCCESS;
      case 'c':
        if (!print_conditions(optarg)) {
          return EXIT_FAILURE;
        } else {
          return EXIT_SUCCESS;
        }
      case 'f':
        if (!print_forecast(optarg)) {
          return EXIT_FAILURE;
        } else {
          return EXIT_SUCCESS;
        }
      case 'a':
        if (!print_alerts(optarg)) {
          return EXIT_FAILURE;
        } else {
          return EXIT_SUCCESS;
        }
      default:
        print_usage();
        return EXIT_SUCCESS;
    }
  }
}

static void print_usage(void) {
  puts("Usage:");
  puts("  nowa --list-stations \"39.809734,-98.555620\"");
  puts("");
  puts("Options:");
  puts("  -h  --help     Print this message");
  puts("  -V  --version  Print version number and license info");
}
