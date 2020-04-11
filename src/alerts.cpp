#include "alerts.hpp"

#include <ctime>
#include <iomanip>
#include <nlohmann/json.hpp>
#include <sstream>

using std::endl;
using std::put_time;
using std::string;
using std::stringstream;

stringstream getAlerts(stringstream &rawJSON) {
  nlohmann::json alertsJSON;
  rawJSON >> alertsJSON;

  auto alert = alertsJSON["alert"];

	stringstream ss;

	auto headline{location["headline"].get<string>()};

	if (!alert.empty()) {
		ss << headline << endl; 
	} else {
		ss << "No active alerts" << endl;
	}

	return ss;
}


	/*
  auto region{location["region"].get<string>()};
  auto lat{location["lat"].get<float>()};
  auto lon{location["lon"].get<float>()};
  auto latDir{(lat >= 0) ? 'N' : 'S'};
  auto lonDir{(lon >= 0) ? 'E' : 'W'};
  auto epoch{location["localtime_epoch"].get<long>()};
  tm localtime = *std::localtime(&epoch);

  auto sunrise{astronomy["sunrise"].get<string>()};
  auto sunset{astronomy["sunset"].get<string>()};
  auto moonrise{astronomy["moonrise"].get<string>()};
  auto moonset{astronomy["moonset"].get<string>()};

  // This information is listed in the API docs, but unavailable in the JSON
  //
  // auto moonIllumination{astronomy["moon_illumination"].get<int>()};
  // auto moonPhase{astronomy["moon_phase"].get<string>()};

  stringstream ss;

  ss << "Current astronomical observations for " << name << ", " << region
     << " (" << lat << " " << latDir << ", " << lon << " " << lonDir << ")"
     << endl;
  ss << put_time(&localtime, "%A, %d %B %Y, %I:%M:%S %p %Z") << endl << endl;

  ss << "    Sunrise: " << sunrise << endl;
  ss << "    Sunset: " << sunset << endl;
  ss << endl;
  ss << "    Moonrise: " << moonrise << endl;
  ss << "    Moonset: " << moonset << endl << endl;

  // If this data is ever included in the JSON, this should work
  //
  // ss << endl;
  // ss << "    Moon Phase: " << moonIllumination << "% illuminated (" <<
  // moonPhase << ")" << endl << endl;

  return ss;

}
