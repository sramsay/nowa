#include "alerts.h"

#include <stdbool.h>
#include <stdio.h>

#include "alerts_data.h"

extern size_t alerts_count;

bool print_alerts(char station_id[restrict static 1]) {
  struct alert* alerts = init_alerts(station_id);

	if (alerts_count == 0) {
		puts("No active alerts.");
	} else {
		for (size_t i = 0; i < alerts_count; i++) {
			printf("### %s\n\n", alerts[i].headline);
			printf("%s\n\n", alerts[i].description);
			printf("%s\n\n", alerts[i].instruction);

			free(alerts[i].headline);
			free(alerts[i].description);
			free(alerts[i].instruction);
		}
	}

	free(alerts);

  return true;
}
