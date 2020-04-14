#ifndef FORECAST_INCLUDED
#define FORECAST_INCLUDED

#include <stdbool.h>

#define _XOPEN_SOURCE 600

bool print_forecast(char lat_long[restrict static 1]);
bool print_forecast_json(char station_id[restrict static 1]);

#endif
