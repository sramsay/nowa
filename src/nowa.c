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
      {"list-stations", required_argument, 0, 'l'},
      {"conditions", no_argument, 0, 'c'},
      {"forecast", no_argument, 0, 'f'},
      {"discussion", no_argument, 0, 'd'},
      {"air-quality", no_argument, 0, 'a'},
      {"alerts", no_argument, 0, 'x'},
      {"hazards", no_argument, 0, 'z'},
      {"totals", no_argument, 0, 't'},
      {"storm-report", no_argument, 0, 'r'},
      {"product", required_argument, 0, 'p'},
      {"list-products", no_argument, 0, 'i'},
      {"json", no_argument, 0, 'j'},
      {0, 0, 0, 0}};

  int option_index = 0;

  extern char* optarg;
  bool usage = false;
  bool version = false;
  bool list_stations = false;
  bool conditions = false;
  bool forecast = false;
  bool discussion = false;
  bool air_quality = false;
  bool alerts = false;
  bool hazards = false;
  bool totals = false;
  bool storm_report = false;
  bool product = false;
  bool list_products = false;
  bool json = false;

  char station[5];
  char* lat_long = {0};
  char* code = {0};

  for (;;) {
    int opt = getopt_long(argc, argv, "hVl:cfdaxztrp:ij", long_options,
                          &option_index);

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
      case 'l':
        list_stations = true;
        lat_long = optarg;
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
        air_quality = true;
        break;
      case 'x':
        alerts = true;
        break;
      case 'z':
        hazards = true;
        break;
      case 't':
        totals = true;
        break;
      case 'r':
        storm_report = true;
        break;
      case 'p':
        product = true;
        code = optarg;
        break;
      case 'i':
        list_products = true;
        break;
      case 'j':
        json = true;
        break;
      default:
        print_usage();
    }
  }

	// This whole block super kludgy.  And annoying.  Must figure out a better way.

  if (!list_stations && !version && !usage) {
    if (optind < argc) {
			// if (sizeof(station) > sizeof(argv[optind])) {
				strcpy(station, argv[optind]);
			// }
    } else {
      print_usage();
      return EXIT_SUCCESS;
    }
  }

  if (json) {
    if (list_stations) {
      if (!print_stations_json(lat_long)) {
        return EXIT_FAILURE;
      }
    }
    if (conditions) {
      if (!print_conditions_json(station)) {
        return EXIT_FAILURE;
      }
    }
    if (forecast) {
      if (!print_forecast_json(station)) {
        return EXIT_FAILURE;
      }
    }
    if (discussion) {
      if (!print_product_json(station, "AFD")) {
        return EXIT_FAILURE;
      }
    }
    if (air_quality) {
      if (!print_product_json(station, "AQI")) {
        return EXIT_FAILURE;
      }
    }
    if (alerts) {
      if (!print_alerts_json(station)) {
        return EXIT_FAILURE;
      }
    }
    if (hazards) {
      if (!print_product_json(station, "HWO")) {
        return EXIT_FAILURE;
      }
    }
    if (totals) {
      if (!print_product_json(station, "CLI")) {
        return EXIT_FAILURE;
      }
    }
    if (storm_report) {
      if (!print_product_json(station, "LSR")) {
        return EXIT_FAILURE;
      }
    }
    if (product) {
      if (!print_product_json(station, code)) {
        return EXIT_FAILURE;
      }
    }
    if (list_products) {
      if (!print_available_products_json(station)) {
        return EXIT_FAILURE;
      }
    }
    return EXIT_SUCCESS;
  }

  if (version) {
    print_version();
    return EXIT_SUCCESS;
  }
  if (usage) {
    print_usage();
    return EXIT_SUCCESS;
  }
  if (list_stations) {
    if (!print_stations(lat_long)) {
      return EXIT_FAILURE;
    }
  }
  if (conditions) {
    if (!print_conditions(station)) {
      return EXIT_FAILURE;
    }
  }
  if (forecast) {
    if (!print_forecast(station)) {
      return EXIT_FAILURE;
    }
  }
  if (discussion) {
    if (!print_product(station, "AFD")) {
      return EXIT_FAILURE;
    }
  }
  if (air_quality) {
    if (!print_product(station, "AQI")) {
      return EXIT_FAILURE;
    }
  }
  if (alerts) {
    if (!print_alerts(station)) {
      return EXIT_FAILURE;
    }
  }
  if (hazards) {
    if (!print_product(station, "HWO")) {
      return EXIT_FAILURE;
    }
  }
  if (totals) {
    if (!print_product(station, "CLI")) {
      return EXIT_FAILURE;
    }
  }
  if (storm_report) {
    if (!print_product(station, "LSR")) {
      return EXIT_FAILURE;
    }
  }
  if (product) {
    if (!print_product(station, code)) {
      return EXIT_FAILURE;
    }
  }
  if (list_products) {
		puts(station);
    if (!print_available_products(station)) {
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}

static void print_usage(void) {
  puts("Usage:");
  puts("  nowa --conditions \"KLNK\"");
  puts("  nowa --list-stations \"39.809734,-98.555620\"");
  putchar('\n');
  puts("Options:");
  puts("  -h  --help     Print this message");
  puts("  -V  --version  Print version number and license info");
  puts("");
  puts("  -c  --conditions     Current conditions");
  puts("  -f  --forecast       7-day forecast");
  puts("  -a  --air-quality    Air quality data");
  puts("  -d  --discussion     Scientific forecast discussion");
  puts("  -x  --alerts         Active alerts (if any)");
  puts("  -z  --hazards        Hazardous weather outlook");
  puts("  -t  --totals				 Yesterday's totals");
  puts("  -r  --storm-report   Local storm report");
  puts("  -i  --list-products  List available NWS product");
  putchar('\n');
  puts("  -l  --list-stations [lat,long]   Retrieve list of area stations");
  puts("  -p  --product [product code]     Request NWS product (if available)");
  putchar('\n');
  puts("  -j  --json                       Raw JSON output from NWS");
}
