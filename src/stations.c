#include "stations.h"

#include <pcre.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json.h"
#include "third_party/cJSON.h"

static char* construct_points_url(char lat_long[static 1]);

int print_stations(char lat_long[static 1]) {
  char* points_url = construct_points_url(lat_long);
  cJSON* points = json_init(points_url);

  // Error checking, cleanup.

  cJSON* points_properties =
      cJSON_GetObjectItemCaseSensitive(points, "properties");
  cJSON* observation_stations = cJSON_GetObjectItemCaseSensitive(
      points_properties, "observationStations");

  char* station_url = observation_stations->valuestring;

  cJSON* stations = json_init(station_url);

  cJSON* features = cJSON_GetObjectItemCaseSensitive(stations, "features");

  const cJSON* feature = NULL;  // TODO: NULL?
  cJSON_ArrayForEach(feature, features) {
    cJSON* station_properties =
        cJSON_GetObjectItemCaseSensitive(feature, "properties");
    cJSON* stationIdentifier = cJSON_GetObjectItemCaseSensitive(
        station_properties, "stationIdentifier");
    cJSON* name = cJSON_GetObjectItemCaseSensitive(station_properties, "name");
    printf("%s:\t%s\n", stationIdentifier->valuestring, name->valuestring);
  }

  free(points_url);
  cJSON_Delete(points);
  cJSON_Delete(stations);

  return 0;
}

static char* construct_points_url(char lat_long[static 1]) {
  char* regexStr = "(-?[0-9]*\\.[0-9]+),(-?[0-9]*\\.[0-9]+)";

  const char* pcreErrorStr = {0};
  int pcreErrorOffset = {0};
  pcre* regex =
      pcre_compile(regexStr, 0, &pcreErrorStr, &pcreErrorOffset, NULL);

  if (regex == NULL) {
    printf("Error: Could not compile '%s': %s\n", regexStr, pcreErrorStr);
    exit(1);
  }

  // Optimize the regex
  pcre_extra* pcreExtra = pcre_study(regex, 0, &pcreErrorStr);

  if (pcreErrorStr != NULL) {
    printf("ERROR: Could not study '%s': %s\n", regexStr, pcreErrorStr);
    exit(1);
  }

  int subStrVec[12] = {
      0};  // TODO: What's the number?  Total match string? or 12?
  int pcreExecRet = pcre_exec(regex, pcreExtra, lat_long, strlen(lat_long), 0,
                              0, subStrVec, 50);

  const char* latitude_match = {0};
  const char* longitude_match = {0};
  pcre_get_substring(lat_long, subStrVec, pcreExecRet, 1, &(latitude_match));
  pcre_get_substring(lat_long, subStrVec, pcreExecRet, 2, &(longitude_match));
  char* end = {0};
  double latitude = strtod(latitude_match, &end);
  double longitude = strtod(longitude_match, &end);

  char* url = malloc(53);
  sprintf(url, "%s%g,%g", "https://api.weather.gov/points/", latitude,
          longitude);

  pcre_free_substring(latitude_match);
  pcre_free_substring(longitude_match);
  pcre_free(regex);

  if (pcreExtra != NULL) {
#ifdef PCRE_CONFIG_JIT
    pcre_free_study(pcreExtra);
#else
    pcre_free(pcreExtra);
#endif
  }
  return url;
}
