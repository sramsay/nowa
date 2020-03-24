#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "third_party/cJSON.h"

#include "conditions.h"
#include "json.h"
#include "license.h"
#include "stations.h"

struct MemoryStruct {
  char *memory;
  size_t size;
};

static void print_usage(void);

int main(int argc, char *argv[]) {
  static struct option long_options[] = {
      {"help", no_argument, (void *)0, 'h'},
      {"version", no_argument, (void *)0, 'V'},
			{"stations", required_argument, 0, 's'},
      {0, 0, 0, 0}};

  int opt = 0;
  int option_index = 0;

  for (;;) {
    opt = getopt_long(argc, argv, "hVs:", long_options, &option_index);

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
			case 's':
				print_stations(optarg);
      default:
        print_usage();
        return EXIT_SUCCESS;
    }
  }

	char* url = "https://api.weather.gov/stations/KLNK/observations/latest";

  init_conditions(url);
	print_conditions();

  return EXIT_SUCCESS;
}

static void print_usage(void) {
  puts("Usage: drouth [options]...:");
  puts("  -h [--help]     Print this message");
  puts("  -V [--version]  Print version number and license info");
}
