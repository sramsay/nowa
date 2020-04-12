#ifndef FORECAST_DATA_INCLUDED
#define FORECAST_DATA_INCLUDED

#include <stdbool.h>
#include <time.h>

typedef struct forecast_day forecast_day;

struct forecast {
  char* name;
  char* detailed_forecast;
};

bool init_forecast(char lat_long[restrict static 1], struct tm* last_updated,
                   struct forecast forecasts[static 14]);

#endif
