#include "forecast_data.h"

#include <time.h>
#include <string.h>
#include <stdio.h>

#include "points_data.h"
#include "json.h"
#include "utils.h"

#include "third_party/cJSON.h"

void init_forecast(char lat_long[restrict static 1], struct tm* last_updated, struct forecast forecasts[static 14]) {
	struct points_info* points = init_points(lat_long);

	char* forecast_url = points->forecast_url;

	puts(forecast_url);

	cJSON* forecast_json = json_init(forecast_url);

	cJSON* properties_json = cJSON_GetObjectItemCaseSensitive(forecast_json, "properties");
	cJSON* updated_json = cJSON_GetObjectItemCaseSensitive(properties_json, "updated");


	char* timestamp = updated_json->valuestring;
	tzset();
	convert_iso8601(timestamp, last_updated);

	cJSON* periods_json = cJSON_GetObjectItemCaseSensitive(properties_json, "periods");

	cJSON* period_json = {0};
	int count = 0;
	cJSON_ArrayForEach(period_json, periods_json) { 
		cJSON* name_json = cJSON_GetObjectItemCaseSensitive(period_json, "name");
		cJSON* detailed_forecast_json = cJSON_GetObjectItemCaseSensitive(period_json, "detailedForecast");
		strcpy(forecasts[count].name, name_json->valuestring);
		strcpy(forecasts[count].detailed_forecast, detailed_forecast_json->valuestring);
		count++;
	}

	free(forecast_url);
	cJSON_Delete(forecast_json);
}





