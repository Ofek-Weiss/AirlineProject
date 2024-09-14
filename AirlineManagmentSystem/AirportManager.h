#ifndef __AIR_MANAGER__
#define __AIR_MANAGER__

#include "Airport.h"
#include "list.h"
#include <stdio.h>
typedef struct
{
	LIST airports;
}AirportManager;


int		initManager(AirportManager* pManager, const char* fileName);
int		addAirport(AirportManager* pManager);
int		initAirport(Airport* pPort, AirportManager* pManager);
Airport* findAirportByCode(const AirportManager* pManager, const char* code);
int		checkUniqeCode(const char* code, const AirportManager* pManager);
void	printAirports(const AirportManager* pManager);
void	freeManager(AirportManager* pManager);
void	freeAirportArr(AirportManager* pManager);
int		compareByCode(const void* port1, const void* port2);
int		countAirport(const AirportManager* pManager);
int		saveManagerToFile(const AirportManager* pManager, const char* fileName);
int		readAirportFromFile(Airport* pPort, FILE* fp);
#endif