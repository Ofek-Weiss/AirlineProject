#include "Airline.h"
#include "General.h"
#include "AirportManager.h"
#include "Flight.h"
#include "Plane.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int initAirlineFromFile(Airline* pComp, AirportManager* pManager, const char* fileName) // if file exists
{
	FILE* file = fopen(fileName, "rb");
	if (!file) return 0;

	int nameSize;

	if (fread(&nameSize, sizeof(int), 1, file) != 1)
	{
		fclose(file);
		return 0;
	}

	pComp->name = (char*)malloc(nameSize * sizeof(char));

	if (fread(pComp->name, sizeof(char), nameSize, file) != nameSize)
	{
		fclose(file);
		return 0;
	}

	if (fread(&pComp->planeCount, sizeof(int), 1, file) != 1)
	{
		fclose(file);
		return 0;
	}

	pComp->planeArr = (Plane*)malloc(pComp->planeCount * sizeof(Plane));

	for (int i = 0; i < pComp->planeCount; i++)
	{

		if (fread(&pComp->planeArr[i].serialNum, sizeof(int), 1, file) != 1)
		{
			fclose(file);
			return 0;
		}

		if (fread(&pComp->planeArr[i].type, sizeof(int), 1, file) != 1)
		{
			fclose(file);
			return 0;
		}
	}

	if (fread(&pComp->flightCount, sizeof(int), 1, file) != 1)
	{
		fclose(file);
		return 0;
	}

	pComp->flightArr = (Flight**)malloc(pComp->flightCount * sizeof(Flight*));

	for(int i=0; i<pComp->flightCount; i++)
	{
		pComp->flightArr[i] = (Flight*)malloc(sizeof(Flight));
		if (!pComp->flightArr[i])
		{
			fclose(file);
			return 0;
		}
		if (fread(pComp->flightArr[i]->sourceCode, sizeof(char), IATA_LENGTH, file) != IATA_LENGTH)
		{
			fclose(file);
			return 0;
		}
		pComp->flightArr[i]->sourceCode[IATA_LENGTH] = '\0';
		if (fread(pComp->flightArr[i]->destCode, sizeof(char), IATA_LENGTH, file) != IATA_LENGTH)
		{
			fclose(file);
			return 0;
		}
		pComp->flightArr[i]->destCode[IATA_LENGTH] = '\0';
		if (fread(&pComp->flightArr[i]->flightPlane.serialNum, sizeof(int), 1, file) != 1)
		{
			fclose(file);
			return 0;
		}

		if (fread(&pComp->flightArr[i]->date.day, sizeof(int), 1, file) != 1)
		{
			fclose(file);
			return 0;
		}
		if (fread(&pComp->flightArr[i]->date.month, sizeof(int), 1, file) != 1)
		{
			fclose(file);
			return 0;
		}
		if (fread(&pComp->flightArr[i]->date.year, sizeof(int), 1, file) != 1)
		{
			fclose(file);
			return 0;
		}

		pComp->flightArr[i]->flightPlane.type = findPlaneBySN(pComp->planeArr, pComp->planeCount, pComp->flightArr[i]->flightPlane.serialNum)->type;
		pComp->type = NotSorted;

	}
	return 1;
	fclose(file);
}


int initManagerAndAirline(AirportManager* pManager, Airline* pCompany)
{
	if (initManager(pManager, TEXT_FILE_NAME) == 0)
		return 0;

	if (!initAirlineFromFile(pCompany, pManager, BIN_FILE_NAME))
	{
		initAirline(pCompany);
		return 0;
	}
	return 1;
}


int saveFlightToFile(const Flight* pFlight, FILE* file) // write flight to file
{

	if (fwrite(pFlight->sourceCode, sizeof(char), IATA_LENGTH, file) != IATA_LENGTH)
		return 0;
	if (fwrite(pFlight->destCode, sizeof(char), IATA_LENGTH, file) != IATA_LENGTH)
		return 0;
	if (fwrite(&pFlight->flightPlane.serialNum, sizeof(int), 1, file) != 1)
		return 0;
	if (fwrite(&pFlight->date.day, sizeof(int), 1, file) != 1)
		return 0;
	if (fwrite(&pFlight->date.month, sizeof(int), 1, file) != 1)
		return 0;
	if (fwrite(&pFlight->date.year, sizeof(int), 1, file) != 1)
		return 0;
	return 1;
}


int savePlaneToFile(const Plane* pPlane, FILE* file) // write plane to file
{
	if (fwrite(&pPlane->serialNum, sizeof(int), 1, file) != 1)
		return 0;
	if (fwrite(&pPlane->type, sizeof(int), 1, file) != 1)
		return 0;
	return 1;
}


int saveAirlineToFile(const Airline* pComp, const char* fileName) // write airline to file
{
	FILE* file = fopen(fileName, "wb");
	if (!file)
		return 0;

	int nameSize = (int)strlen(pComp->name) + 1;

	if (fwrite(&nameSize, sizeof(int), 1, file) != 1)
	{
		fclose(file);
		return 0;
	}

	if (fwrite(pComp->name, sizeof(char), nameSize, file) != nameSize)
	{
		fclose(file);
		return 0;
	}

	if (fwrite(&pComp->planeCount, sizeof(int), 1, file) != 1)
	{
		fclose(file);
		return 0;
	}

	for (int i = 0; i < pComp->planeCount; i++)
	{
		if (!savePlaneToFile(&pComp->planeArr[i], file))
		{
			fclose(file);
			return 0;
		}
	}

	if (fwrite(&pComp->flightCount, sizeof(int), 1, file) != 1)
	{
		fclose(file);
		return 0;
	}

	for (int i = 0; i < pComp->flightCount; i++)
	{
		if (!saveFlightToFile(pComp->flightArr[i], file))
		{
			fclose(file);
			return 0;
		}
	}

	fclose(file);
	return 1;
}
