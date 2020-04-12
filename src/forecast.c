#include "forecast.h"

#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include "forecast_data.h"

bool print_forecast(char lat_long[restrict static 1]) {
  struct tm last_updated;
  struct forecast forecasts[14];

  init_forecast(lat_long, &last_updated, forecasts);

  char buf[53];  // TODO: ?? predictable size
  long ts = mktime(&last_updated) - timezone;
  localtime_r(&ts, &last_updated);
  strftime(buf, sizeof(buf), "Last Updated: %A, %d %B %Y, %I:%M:%S %p %Z",
           &last_updated);

  for (size_t i = 0; i < 14; i++) {
    printf("%s: %s\n", forecasts[i].name, forecasts[i].detailed_forecast);
  }

  return 0;
}
