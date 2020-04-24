#ifndef UTILS_INCLUDE
#define UTILS_INCLUDE

#include <time.h>

double ftemp(double raw_temp);
double ctemp(double raw_temp);
char* dd_to_dms(const double coordinate);
double mps_to_mph(double mps);
double m_to_mi(double m);
char lat_dir(double latitude);
char lng_dir(double longitude);
int convert_iso8601(const char date_string[restrict static 1],
                    struct tm* date_data);
const char* bearing_to_compass_dir(int bearing);
char* comfort_scale(double dewpoint);
double pa_to_mb(int pascals);

#endif
