#ifndef __CONDITIONS_INCLUDED__
#define __CONDITIONS_INCLUDED__

#include <sstream>

std::stringstream getConditions(std::stringstream &rawJSON);
std::string uvRisk(const float uvIndex);
std::string calculateWindChill(const float temp_f, const float wind_mph,
                               const std::string &unit);
std::string calculateHeatIndex(const float temp_f, const float humidity,
                               const std::string &unit);
float calculateDewPoint(const float temp_c, const float humidity);
std::string comfortScale(const float dewPoint);

#endif
