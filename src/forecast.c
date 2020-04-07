#include "forecast.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "forecast_data.h"

int print_forecast(char lat_long[restrict static 1]) {
	struct tm last_updated;
	//struct forecast* forecasts = malloc(sizeof(struct forecast) * 14); // TODO: 14 macro
	struct forecast forecasts[14];

	init_forecast(lat_long, &last_updated, forecasts);

	char buf[53]; // TODO: ?? predictable size
	long ts = mktime(&last_updated) - timezone;
	localtime_r(&ts, &last_updated);
  strftime(buf, sizeof(buf), "Last Updated: %A, %d %B %Y, %I:%M:%S %p %Z", &last_updated);
	//puts(buf);

	for (size_t i = 0; i < 14; i++) {
		printf("%s: %s\n", forecasts[i].name, forecasts[i].detailed_forecast);
	}

	return 0;
}
