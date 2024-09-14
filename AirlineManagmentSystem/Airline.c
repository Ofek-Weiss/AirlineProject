#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "General.h"
#include "Airline.h"


void	initAirline(Airline* pComp) //initiate the airline without File
{
	pComp->name = getStrExactName("Enter Airline name");
	pComp->flightArr = NULL;
	pComp->flightCount = 0;
	pComp->planeArr = NULL;
	pComp->planeCount = 0;
	pComp->type = NotSorted;
}


int	addFlight(Airline* pComp, const AirportManager* pManager)
{
	if (countAirport(pManager) < 2) // if there are less than 2 airports
	{
		printf("There are not enough airport to set a flight\n");
		return 0;
	}
	if (pComp->planeCount == 0)
	{
		printf("There is no plane in company\n");
		return 0;
	}

	Flight* pFlight = (Flight*)calloc(1, sizeof(Flight)); //allocate memory for the flight
	if (!pFlight)
		return 0;

	Plane* thePlane = FindAPlane(pComp); //find a plane for the flight
	printAirports(pManager);
	initFlight(pFlight, thePlane, pManager);

	pComp->flightArr = (Flight**)realloc(pComp->flightArr, (pComp->flightCount + 1) * sizeof(Flight*));
	if (!pComp->flightArr)
	{
		free(pFlight);
		return 0;
	}
	pComp->flightArr[pComp->flightCount] = pFlight;
	pComp->flightCount++;
	return 1;
}

int		addPlane(Airline* pComp) //add a plane to the airline
{
	pComp->planeArr = (Plane*)realloc(pComp->planeArr, (pComp->planeCount + 1) * sizeof(Plane));
	if (!pComp->planeArr)
		return 0;
	initPlane(&pComp->planeArr[pComp->planeCount], pComp->planeArr, pComp->planeCount);
	pComp->planeCount++;
	return 1;
}

Plane*	FindAPlane(Airline* pComp)
{
	printf("Choose a plane from list, type its serial Number\n");
	generalArrayFunction(pComp->planeArr, pComp->planeCount, sizeof(Plane), printOnePlane);
	int sn;
	Plane* temp = NULL;
	do {
		scanf("%d", &sn);
		temp = findPlaneBySN(pComp->planeArr, pComp->planeCount, sn);
		if (!temp)
			printf("No plane with that serial number! Try again!\n");
	} while (temp == NULL);

	return temp;
}


void	printCompany(const Airline* pComp)
{
	printf("Airline %s\n", pComp->name);
	printf("\n -------- Has %d planes\n", pComp->planeCount);
	generalArrayFunction(pComp->planeArr, pComp->planeCount, sizeof(Plane), printOnePlane);
	printf("\n\n -------- Has %d flights\n", pComp->flightCount);
	generalArrayFunction(pComp->flightArr, pComp->flightCount, sizeof(Flight*), printOneFlight);
}


void	doPrintFlightsWithPlaneType(const Airline* pComp)
{
	ePlaneType type = getPlaneType();
	int count = 0;
	printf("Flights with plane type %s:\n", GetPlaneTypeStr(type));
	for (int i = 0; i < pComp->flightCount; i++)
	{
		if (isPlaneTypeInFlight(pComp->flightArr[i], type))
		{
			printFlight(pComp->flightArr[i]);
			count++;
		}
	}
	if (count == 0)
		printf("Sorry - could not find a flight with plane type %s:\n", GetPlaneTypeStr(type));
	printf("\n");
}


void	freeCompany(Airline* pComp)
{
	generalArrayFunction(pComp->flightArr, pComp->flightCount, sizeof(Flight*), freeFlight);
	free(pComp->flightArr);
	generalArrayFunction(pComp->planeArr, pComp->planeCount, sizeof(Plane), freeTheValuesOfPlane);
	free(pComp->planeArr);
	free(pComp->name);
}


void	sortFlight(Airline* pComp) //sort the flights
{
	if (pComp == NULL || pComp->flightCount == 0) //if there are no flights to sort or the company is not initiated;
	{
		printf("There are no flights to sort\n");
		return;
	}
	FlightSortState type = getSortType();

	switch (type)
	{
		case 1:
			qsort(pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareFlightsBySourceCode);
			pComp->type = SortBySourceCode;
			break;
		case 2:
			qsort(pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareFlightsByDestCode);
			pComp->type = SortByDestinationCode;
			break;
		case 3:
			qsort(pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareFlightsByDate);
			pComp->type = SortByDate;
			break;
	}
}


int		compareFlightsBySourceCode(const void* flight1, const void* flight2)
{
	Flight* f1 = *(Flight**)flight1;
	Flight* f2 = *(Flight**)flight2;
	return strcmp(f1->sourceCode, f2->sourceCode);
}

int		compareFlightsBySourceCodeForFind(const void* flight1, const void* flight2)
{
	Flight* f1 = (Flight*)flight1;
	Flight* f2 = *(Flight**)flight2;
	return strcmp(f1->sourceCode, f2->sourceCode);
}


int		compareFlightsByDestCode(const void* flight1, const void* flight2)
{
	Flight* f1 = *(Flight**)flight1;
	Flight* f2 = *(Flight**)flight2;
	return strcmp(f1->destCode, f2->destCode);
}

int		compareFlightsByDestCodeForFind(const void* flight1, const void* flight2)
{
	Flight* f1 = (Flight*)flight1;
	Flight* f2 = *(Flight**)flight2;
	return strcmp(f1->destCode, f2->destCode);
}

int		compareFlightsByDate(const void* flight1, const void* flight2)
{
	Flight* f1 = *(Flight**)flight1;
	Flight* f2 = *(Flight**)flight2;
	return compareByDate(f1, f2);
}

int		compareFlightsByDateForFind(const void* flight1, const void* flight2)
{
	Flight* f1 = (Flight*)flight1;
	Flight* f2 = *(Flight**)flight2;
	return compareByDate(f1, f2);
}


int		compareFlightsByType(const Flight* f1, const Flight* f2, FlightSortState type)
{
	switch (type)
	{
	case SortBySourceCode:
		return strcmp(f1->sourceCode, f2->sourceCode);
	case SortByDestinationCode:
		return strcmp(f1->destCode, f2->destCode);
	case SortByDate:
		return compareByDate(f1, f2);
	default:
		return 0;
	}
}

FlightSortState getSortType() //get the type of sorting
{
	printf("\nBase on what field do you want to sort?\n");
	int temp;
	do {
		for (int i = 0; i < NofTypes-1; i++)
			printf("Enter %d for %s\n", i+1, SortTitle[i]);
		scanf("%d", &temp);
	} while (temp < 0 || temp >= NofTypes);
	return (FlightSortState)temp;
}

int 	compareByDate(const void* flight1, const void* flight2)//compare the date of the flights for sorting
{
	Date* d1 = &((Flight*)flight1)->date;
	Date* d2 = &((Flight*)flight2)->date;

	if (d1->year > d2->year)
		return 1;
	if (d1->year < d2->year)
		return -1;
	if (d1->month > d2->month)
		return 1;
	if (d1->month < d2->month)
		return -1;
	if (d1->day > d2->day)
		return 1;
	if (d1->day < d2->day)
		return -1;
	return 0;
}

int 	isFlightArrSorted(const Airline* pComp)
{
	FlightSortState type = getSortType();
	for (int i = 0; i < pComp->flightCount; i++)
	{
		if (compareFlightsByType(pComp->flightArr[i], pComp->flightArr[i + 1], type) > 0)
			return 0;
	}
	return 1;
}



void	findFlightBySourceCode(const Airline* pComp)
{
	char code[IATA_LENGTH + 1];
	strcpy(code, getStrExactName("\t Origin: Enter airport code  - 3 UPPER CASE letters")); 
	Flight temp;
	strcpy(temp.sourceCode, code);
	Flight** found = (Flight**)bsearch(&temp, pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareFlightsBySourceCodeForFind);
	if (found)
	{
		printf("Flight found, ");
		printFlight(*found);
	}
	else
		printf("Flight was not found\n");
}


void	findFlightByDestCode(const Airline* pComp)
{
	char code[IATA_LENGTH + 1];
	strcpy(code, getStrExactName("Destination:\t Enter airport code  - 3 UPPER CASE letters"));
	Flight temp;
	strcpy(temp.destCode, code);
	Flight** found = (Flight**)bsearch(&temp, pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareFlightsByDestCodeForFind);
	if (found)
	{
		printf("\nFlight found, ");
		printFlight(*found);
	}
	else
		printf("No flight to %s\n", code);
}


void	findFlightByDate(const Airline* pComp)
{
	Date date;
	getCorrectDate(&date);
	Flight temp;
	temp.date = date;
	Flight** found = (Flight**)bsearch(&temp, pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareFlightsByDateForFind);
	if (found)
	{
		printf("Flight found, ");
		printFlight(*found);
	}
	else
		printf("No flight at %d/%d/%d\n", date.day, date.month, date.year);
}


void	findFlight(const Airline* pComp) // find a flight by the type of sorting (only if sorted)
{
	if(pComp->type == NotSorted)
	{
		printf("The search cannot be performed, array not sorted\n");
		return;
	}

	switch(pComp->type)
	{
		case SortBySourceCode:
			findFlightBySourceCode(pComp);
			break;
		case SortByDestinationCode:
			findFlightByDestCode(pComp);
			break;
		case SortByDate:
			findFlightByDate(pComp);
			break;
	}
}

void	printFlightArr(Flight** arr, int size)
{
	for (int i = 0; i < size; i++)
		printFlight(arr[i]);
}


void	printPlanesArr(Plane* arr, int size)
{
	for (int i = 0; i < size; i++)
		printPlane(&arr[i]);
}


void freeFlight(void* pFlight)
{
	// nothing to free
}

void freePlane(void* pPlane)
{
	free(pPlane);
}

void printOneFlight(void* pFlight)
{
	Flight* temp = *(Flight**)pFlight;
	printFlight(temp);
}

void printOnePlane(void* pPlane)
{
	printPlane((Plane*)pPlane);
}



void generalArrayFunction(void* array, size_t elementCount, size_t elementSize, void(*f)(void* element))
{
	for (size_t i = 0; i < elementCount; i++)
		f((char*)array + i * elementSize);
}
