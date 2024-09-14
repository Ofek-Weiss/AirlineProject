#ifndef __COMP__
#define __COMP__

#include "Flight.h"
#include "AirportManager.h"

#define TEXT_FILE_NAME "airport_authority.txt"
#define BIN_FILE_NAME "airline.bin"


typedef enum {
	NotSorted,
	SortBySourceCode,
	SortByDestinationCode,
	SortByDate,
	NofTypes 
} FlightSortState;
static const char* SortTitle[NofTypes] = { "Source Code", "Dest Code", "Date", "NotSorted" };


typedef struct
{
	char* name;
	int				flightCount;
	Flight**		flightArr;
	int				planeCount;
	Plane*			planeArr;
	FlightSortState	type;
}Airline;

void			initAirline(Airline* pComp);
int				addFlight(Airline* pComp, const AirportManager* pManager);
int				addPlane(Airline* pComp);
Plane*			FindAPlane(Airline* pComp);
void			printCompany(const Airline* pComp);
void			doPrintFlightsWithPlaneType(const Airline* pComp);
void			freeCompany(Airline* pComp);
void			sortFlight(Airline* pComp);
int				compareFlightsBySourceCode(const void* flight1, const void* flight2);
int				compareFlightsByDestCode(const void* flight1, const void* flight2);
int				compareFlightsByDate(const void* flight1, const void* flight2);
int				compareFlightsBySourceCodeForFind(const void* flight1, const void* flight2);
int				compareFlightsByDestCodeForFind(const void* flight1, const void* flight2);
int				compareFlightsByDateForFind(const void* flight1, const void* flight2);
int				compareByDate(const void* flight1, const void* flight2);
FlightSortState getSortType();
void			freeFlight(void* pFlight);
int 			isFlightArrSorted(const Airline* pComp);
void			findFlight(const Airline* pComp);
void			findFlightBySourceCode(const Airline* pComp);
void			findFlightByDestCode(const Airline* pComp);
void			findFlightByDate(const Airline* pComp);
void			generalArrayFunction(void* arr, size_t elementCount, size_t elementSize, void(*f)(void* element));
void			freePlane(void* pPlane);
void			printOneFlight(void* pFlight);
void			printOnePlane(void* pPlane);
int				compareFlightsByType(const Flight* f1, const Flight* f2, FlightSortState type);
int				compareFlightsBySourceCodeForFind(const void* flight1, const void* flight2);
void			printFlightArr(Flight** arr, int size);
void			printPlanesArr(Plane* arr, int size);


#endif

