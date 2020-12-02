#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "alerts.h"
#include "conditions.h"
#include "forecast.h"
#include "product.h"
#include "license.h"
#include "station_list.h"

static void print_usage(void);

int main(int argc, char *argv[]) {

	if (argc == 1) {
		print_usage();
		return EXIT_SUCCESS;
	}

	// TODO: In this formulation, every individual weather switch "takes and
	// argument" but shouldn't it just return whatever information requested for
	// a required string argument (the station)?

  static struct option long_options[] = {
      {"help", no_argument, 0, 'h'},
      {"version", no_argument, 0, 'V'},
      {"list-stations", required_argument, 0, 'l'},
      {"conditions", required_argument, 0, 'c'},
      {"forecast", required_argument, 0, 'f'},
			{"discussion", required_argument, 0, 'd'},
			{"air-quality", required_argument, 0, 'a'},
      {"alerts", required_argument, 0, 'x'},
      {"json", no_argument, 0, 'j'},
      {0, 0, 0, 0}};

	int option_index = 0;;
	extern char* optarg;
  bool json = false;
	bool list_stations = false;
	bool conditions = false;
	bool forecast = false;
	bool discussion = false;
	bool air_quality = false;
	bool alerts = false;
	char* station = {0};
	char* lat_long = {0};

  for (;;) {
    int opt =
        getopt_long(argc, argv, "hVjc:l:f:d:a:x:", long_options, &option_index);

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
        json = true;
        break;
      case 'l':
				list_stations = true;
				lat_long = optarg;
        break;
      case 'c':
				conditions = true;
				station = optarg;
        break;
      case 'f':
				forecast = true;
				station = optarg;
        break;
      case 'd':
				discussion = true;
				station = optarg;
        break;
			case 'a':
				air_quality = true;
				station = optarg;
				break;
      case 'x':
				alerts = true;
				station = optarg;
        break;
      default:
        print_usage();
    }
  }

	if (json) {
		if (list_stations) {
			if (!print_stations_json(lat_long)) {
			return EXIT_FAILURE;
			}
		} else if (conditions) {
			if (!print_conditions_json(station)) {
				return EXIT_FAILURE;
			}
		} else if (forecast) {
			if (!print_forecast_json(station)) {
				return EXIT_FAILURE;
			}
		} else if (alerts) {
			if (!print_alerts_json(station)) {
				return EXIT_FAILURE;
			}
		}
	} else {
		if (list_stations) {
			if (!print_stations(lat_long)) {
			return EXIT_FAILURE;
			}
		} else if (conditions) {
			if (!print_conditions(station)) {
				return EXIT_FAILURE;
			}
		} else if (forecast) {
			if (!print_forecast(station)) {
				return EXIT_FAILURE;
			}
		} else if (discussion) {
			if (!print_product(station, "AFD")) {
				return EXIT_FAILURE;
			}
		} else if (air_quality) {
			if (!print_product(station, "AQI")) {
				return EXIT_FAILURE;
			}
		} else if (alerts) {
			if (!print_alerts(station)) {
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
	puts("");
	puts("  -l  --list-stations [lat,long]   Retrieve list of area stations");
	puts("  -c  --conditions [stationid]     Current conditions");
	puts("  -f  --forecast [stationid]       7-day forecast");
	puts("  -d  --discussion [stationid]     Scientific forecast discussion");
	puts("  -x  --alerts [stationid]         Active alerts (if any)");
	puts("");
	puts("  -j  --json                       Raw JSON output from NWS");
}
