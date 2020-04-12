#include "forecast_data.h"

#include <string.h>

#include "json.h"
#include "points_data.h"
#include "third_party/cJSON.h"
#include "utils.h"

bool init_forecast(char lat_long[restrict static 1], struct tm* last_updated,
                   struct forecast forecasts[static 14]) {
  struct points_info points = {0};
  init_points(lat_long, &points);

  char* forecast_url = points.forecast_url;

  cJSON* forecast_json = json_init(forecast_url);

  cJSON* properties_json =
      cJSON_GetObjectItemCaseSensitive(forecast_json, "properties");
  cJSON* updated_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "updated");

  char* timestamp = updated_json->valuestring;
  convert_iso8601(timestamp, last_updated);

  cJSON* periods_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "periods");

  cJSON* period_json = {0};
  int count = 0;
  cJSON_ArrayForEach(period_json, periods_json) {
    cJSON* name_json = cJSON_GetObjectItemCaseSensitive(period_json, "name");
		size_t name_size = strlen(name_json->valuestring);
		forecasts[count].name = malloc(name_size + 1);
    strcpy(forecasts[count].name, name_json->valuestring);
    cJSON* detailed_forecast_json =
        cJSON_GetObjectItemCaseSensitive(period_json, "detailedForecast");
		size_t detailed_forecast_size = strlen(detailed_forecast_json->valuestring);
		forecasts[count].detailed_forecast = malloc(detailed_forecast_size + 1);
    strcpy(forecasts[count].detailed_forecast,
           detailed_forecast_json->valuestring);
    count++;
  }

  cJSON_Delete(forecast_json);

  return true;
}
