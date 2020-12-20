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
      {"list-stations", no_argument, 0, 's'},
      {"conditions", no_argument, 0, 'c'},
      {"forecast", no_argument, 0, 'f'},
      {"discussion", no_argument, 0, 'd'},
      {"air-quality", no_argument, 0, 'a'},
      {"alerts", no_argument, 0, 'x'},
      {"hazards", no_argument, 0, 'z'},
      {"totals", no_argument, 0, 't'},
      {"storm-report", no_argument, 0, 'r'},
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
  bool air_quality = false;
  bool alerts = false;
  bool hazards = false;
  bool totals = false;
  bool storm_report = false;
  bool product = false;
  bool list_products = false;

  char* station_id = malloc(5);
  char* lat_long = malloc(25);
  char* code = malloc(4);

  for (;;) {
    int opt = getopt_long(argc, argv, "hVji:s:cfdaxztrp:l", long_options,
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
      case 'j':
        json = true;
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
        if (strlen(optarg) > 25) {
          fprintf(
              stderr,
              "Lat/long precision is limited to seven decimal places (which is "
              "close to\nthe accuracy limits of GPS-based systems)\n");
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
      if (air_quality) {
        if (!print_product_json(station_id, "AQI")) {
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
      if (hazards) {
        if (!print_product_json(station_id, "HWO")) {
          free(station_id);
          free(lat_long);
          free(code);
          return EXIT_FAILURE;
        }
      }
      if (totals) {
        if (!print_product_json(station_id, "CLI")) {
          free(station_id);
          free(lat_long);
          free(code);
          return EXIT_FAILURE;
        }
      }
      if (storm_report) {
        if (!print_product_json(station_id, "LSR")) {
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
    if (air_quality) {
      if (!print_product(station_id, "AQI")) {
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
    if (hazards) {
      if (!print_product(station_id, "HWO")) {
        free(station_id);
        free(lat_long);
        free(code);
        return EXIT_FAILURE;
      }
    }
    if (totals) {
      if (!print_product(station_id, "CLI")) {
        free(station_id);
        free(lat_long);
        free(code);
        return EXIT_FAILURE;
      }
    }
    if (storm_report) {
      if (!print_product(station_id, "LSR")) {
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
  puts("  -a  --air-quality    Air quality forecast");
  puts("  -d  --discussion     Scientific forecast discussion");
  puts("  -x  --alerts         Active alerts (if any)");
  puts("  -z  --hazards        Hazardous weather outlook");
  puts("  -t  --totals         Yesterday's totals");
  puts("  -r  --storm-report   Local storm report");
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
