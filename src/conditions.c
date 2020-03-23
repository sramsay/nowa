#include "conditions.h"

#include <stdio.h>

#include "json.h"

typedef struct currentConditions currentConditions;
struct currentConditions {
	char* summary;
	double temperature;
	double dewpoint;
	int wind_direction;
	double wind_speed;
};

static currentConditions current = { 0 };

void init_conditions(char* url) {
	cJSON* json = { 0 };
	json = json_init(url);

	cJSON* json_properties = cJSON_GetObjectItemCaseSensitive(json, "properties"); 

	cJSON* json_text_description = cJSON_GetObjectItemCaseSensitive(json_properties, "textDescription"); 
	cJSON* json_temperature = cJSON_GetObjectItemCaseSensitive(json_properties, "temperature");
	cJSON* json_dewpoint = cJSON_GetObjectItemCaseSensitive(json_properties, "dewpoint");
	cJSON* json_wind_direction = cJSON_GetObjectItemCaseSensitive(json_properties, "windDirection");
	cJSON* json_wind_speed = cJSON_GetObjectItemCaseSensitive(json_properties, "windSpeed");

	cJSON* json_temperature_v = cJSON_GetObjectItemCaseSensitive(json_temperature, "value");
	cJSON* json_dewpoint_v = cJSON_GetObjectItemCaseSensitive(json_dewpoint, "value");
	cJSON* json_wind_direction_v = cJSON_GetObjectItemCaseSensitive(json_wind_direction, "value");
	cJSON* json_wind_speed_v = cJSON_GetObjectItemCaseSensitive(json_wind_speed, "value");

	current.summary = json_text_description->valuestring;
	current.temperature = json_temperature_v->valuedouble;
	current.dewpoint = json_dewpoint_v->valuedouble;
	current.wind_direction = json_wind_direction_v->valueint;
	current.wind_speed = json_wind_speed_v->valuedouble;
	cJSON_Delete(json);
}

void print_conditions() {
	printf("Summary: %s\n", current.summary);
	printf("Temperature: %f\n", current.temperature);
}
