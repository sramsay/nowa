#include "conditions.h"

#include <stdlib.h>
#include <stdio.h>

#include "conditions_data.h"

int print_conditions(char station_id[restrict static 1]) {

	struct currentConditions* current = init_conditions(station_id);
  printf("Summary: %s\n", current->summary);
  printf("Temperature: %f\n", current->temperature);

	free(current);
	return 0;
}
