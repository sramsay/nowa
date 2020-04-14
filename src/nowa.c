#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "alerts.h"
#include "conditions.h"
#include "conditions_data.h"
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
			{"json", no_argument, 0, 'j'},
      {0, 0, 0, 0}};

  int option_index = 0;
	bool json_output;

  for (;;) {
    int opt =
        getopt_long(argc, argv, "hVc:s:l:f:a:j", long_options, &option_index);

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
        if (!print_stations(optarg)) {
          return EXIT_FAILURE;
        }
				break;
      case 'c':
				if (json_output) {
					print_conditions_json(optarg);
				} else if (!print_conditions(optarg)) {
          return EXIT_FAILURE;
        }
				break;
      case 'f':
        if (!print_forecast(optarg)) {
          return EXIT_FAILURE;
        }
				break;
      case 'a':
        if (!print_alerts(optarg)) {
          return EXIT_FAILURE;
        }
				break;
      default:
        print_usage();
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
