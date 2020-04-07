#ifndef FORECAST_DATA_INCLUDED
#define FORECAST_DATA_INCLUDED

#include <time.h>
#include <stdbool.h>

typedef struct forecast_day forecast_day;

struct forecast {
	char name[500];
	char detailed_forecast[500];
};

bool init_forecast(char lat_long[restrict static 1], struct tm* last_updated, struct forecast forecasts[static 14]);

#endif
