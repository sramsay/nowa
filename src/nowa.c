#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "conditions.h"
#include "license.h"
#include "station_list.h"

struct MemoryStruct {
  char *memory;
  size_t size;
};

static void print_usage(void);

int main(int argc, char *argv[]) {
  static struct option long_options[] = {
      {"help", no_argument, (void *)0, 'h'},
      {"version", no_argument, (void *)0, 'V'},
      {"stationid", required_argument, 0, 's'},
      {"list-stations", required_argument, 0, 'l'},
      {0, 0, 0, 0}};

  int opt = 0;
  int option_index = 0;
  char *station_id = {0};

  for (;;) {
    opt = getopt_long(argc, argv, "hVs:l:", long_options, &option_index);

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
        if (print_stations(optarg) == 0) {
          return EXIT_SUCCESS;
        } else {
          return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
      case 's':
        station_id = optarg;
      case 'c':
        if (print_conditions(station_id) == 0) {
          return EXIT_SUCCESS;
        } else {
          return EXIT_FAILURE;
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
