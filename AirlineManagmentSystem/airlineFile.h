#ifndef __AIRLINEFILE__
#define __AIRLINEFILE__

#include "Airline.h"
#include <stdio.h>

int		initAirlineFromFile(Airline* pComp, AirportManager* pManager, const char* fileName);
int		initManagerAndAirline(AirportManager* pManager, Airline* pCompany);
int		saveFlightToFile(const Flight* pFlight, FILE* file);
int		savePlaneToFile(const Plane* pPlane, FILE* file);
int		saveAirlineToFile(const Airline* pComp, const char* fileName);














#endif