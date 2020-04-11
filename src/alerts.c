#include "alerts.h"

#include <stdio.h>
#include <stdbool.h>

#include "alerts_data.h"

extern size_t alerts_count;

bool print_alerts(char station_id[restrict static 1]) {
	struct alert* alerts = init_alerts(station_id);

	for (size_t i = 0; i < alerts_count; i++) {
		printf("%s\n", alerts[i].headline);
		printf("%s\n", alerts[i].description);
		printf("%s\n", alerts[i].instruction);
	}

	return true;

}
