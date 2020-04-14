#include "alerts.h"

#include <stdbool.h>
#include <stdio.h>

#include "alerts_data.h"
#include "json.h"
#include "third_party/cJSON.h"
#include "zoneinfo_data.h"

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

bool print_alerts_json(char station_id[restrict static 1]) {
  struct zoneinfo zinfo = {0};
  if (!init_zoneinfo(station_id, &zinfo)) {
    fprintf(stderr, "Error: %s\n", "Unable to retrieve zone info.");
    return false;
  }

  char* alerts_url = malloc(50);
  sprintf(alerts_url, "%s%s", "https://api.weather.gov/alerts/active/zone/",
          zinfo.id);
  cJSON* alerts_json = json_init(alerts_url);
  char* output = cJSON_Print(alerts_json);
  puts(output);
  free(zinfo.id);
  free(zinfo.name);
  free(zinfo.state);
  free(alerts_url);
  cJSON_Delete(alerts_json);
  free(output);

  return true;
}
