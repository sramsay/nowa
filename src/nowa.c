#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "alerts.h"
#include "conditions.h"
#include "forecast.h"
#include "license.h"
#include "station_list.h"

static void print_usage(void);

int main(int argc, char *argv[]) {

	if (argc == 1) {
		print_usage();
		return EXIT_SUCCESS;
	}

  static struct option long_options[] = {
      {"help", no_argument, (void *)0, 'h'},
      {"version", no_argument, (void *)0, 'V'},
      {"stationid", required_argument, 0, 's'},
      {"list-stations", required_argument, 0, 'l'},
      {"conditions", required_argument, 0, 'c'},
      {"forecast", required_argument, 0, 'f'},
      {"alerts", required_argument, 0, 'a'},
      {"json", no_argument, 0, 'j'},
      {0, 0, 0, 0}};

	extern int optind;
	extern char* optarg;
	char* station = {0};
  bool json_output = false;
	bool conditions = false;

  for (;;) {
    int opt =
        getopt_long(argc, argv, "hVc:s:l:f:a:j", long_options, &optind);

    if (opt == -1) {
      break;
    }

    switch (opt) {
      case '?':
        break;
      case 'h':
        print_usage();
        break;
      case 'V':
        print_version();
        break;
      case 'j':
        json_output = true;
        break;
      case 'l':
        if (json_output) {
          print_stations_json(optarg);
        } else if (!print_stations(optarg)) {
          return EXIT_FAILURE;
        }
        break;
      case 'c':
				conditions = true;
				station = optarg;
        break;
      case 'f':
        if (json_output) {
          print_forecast_json(optarg);
        } else if (!print_forecast(optarg)) {
          return EXIT_FAILURE;
        }
        break;
      case 'a':
        if (json_output) {
          print_alerts_json(optarg);
        } else if (!print_alerts(optarg)) {
          return EXIT_FAILURE;
        }
        break;
      default:
        print_usage();
    }
  }

	if (json_output) {
		if (conditions) {
			if (!print_conditions_json(station)) {
				return EXIT_FAILURE;
			}
		}
	} else {
		if (conditions) {
			if (!print_conditions(station)) {
				return EXIT_FAILURE;
			}
		}
	}



  return EXIT_SUCCESS;
}

static void print_usage(void) {
  puts("Usage:");
  puts("  nowa --list-stations \"39.809734,-98.555620\"");
  puts("");
  puts("Options:");
  puts("  -h  --help     Print this message");
  puts("  -V  --version  Print version number and license info");
}
