#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "AirportManager.h"
#include "list.h"
#include "General.h"


int readAirportFromFile(Airport* pPort, FILE* fp) { // read airport from file and return 1 if success, 0 if failed
	if (!pPort || !fp)
		return 0;

	pPort->name = (char*)calloc(MAX_STR_LEN, sizeof(char));
	pPort->country = (char*)calloc(MAX_STR_LEN, sizeof(char));

	// Read airport, first line is name, second line is country, third line is code
	if (!readStringFromFile(pPort->name, fp) || !readStringFromFile(pPort->country, fp) || !readStringFromFile(pPort->code, fp)) {
		free(pPort->name);
		free(pPort->country);
		return 0;
	}
	return 1;
}


int initManager(AirportManager* pManager, const char* fileName)
{
	pManager->airports.head.next = NULL;
	NODE* temp = &pManager->airports.head;
	FILE* fp = fopen(fileName, "r");
	if (!fp)
		return 2;

	int airportCount;
	fscanf(fp, "%d\n", &airportCount);
	for (int i = 0; i < airportCount; i++)
	{
		Airport* pPort = (Airport*)calloc(1, sizeof(Airport));
		if (!pPort)
			return 0;

		if (!readAirportFromFile(pPort, fp))
		{
			free(pPort);
			fclose(fp);
			return 0;
		}

		temp = L_insert_sorted(&pManager->airports, pPort, compareByCode);
	}

	fclose(fp);
	return 1;
}



int	addAirport(AirportManager* pManager)
{
	Airport* newAirport = (Airport*)calloc(1, sizeof(Airport));
	if (!newAirport)//memory allocation failed
		return 0;

	if (!initAirport(newAirport, pManager))
	{
		freeAirport(newAirport);
		free(newAirport);
		return 0;
	}

	if(pManager->airports.head.next == NULL)
	{
		L_insert(&pManager->airports.head, newAirport);
		return 1;
	}

	NODE* sortedLocation = find_sorted_location(&pManager->airports.head, newAirport, compareByCode);

	L_insert(sortedLocation, newAirport);
	return 1;
}

int  initAirport(Airport* pPort, AirportManager* pManager)
{
	while (1)
	{
		getAirportCode(pPort->code);
		if (checkUniqeCode(pPort->code, pManager))
			break;

		printf("This code already in use - enter a different code\n");
	}

	return initAirportNoCode(pPort);
}



Airport* findAirportByCode(const AirportManager* pManager, const char* code)
{
	NODE* pNode = pManager->airports.head.next;
	while (pNode)
	{
		if (isAirportCode((Airport*)pNode->key, code))
			return (Airport*)pNode->key;
		pNode = pNode->next;
	}
	return NULL;
}


int checkUniqeCode(const char* code, const AirportManager* pManager)
{
	Airport* port = findAirportByCode(pManager, code);

	if (port != NULL)
		return 0;

	return 1;
}


void printAirports(const AirportManager* pManager)
{
	printf("There are %d airports\n", countAirport(pManager));
	int airportCount = L_print((LIST*)&pManager->airports, printAirport);
}

void	freeManager(AirportManager* pManager)
{
	freeAirportArr(pManager);
}


void	freeAirportArr(AirportManager* pManager)
{
	L_free(&pManager->airports, freeAirport);
}


int		compareByCode(const void* port1, const void* port2)
{
	return strcmp(((Airport*)port1)->code, ((Airport*)port2)->code);
}

int		countAirport(const AirportManager* pManager)
{
	return L_count((LIST*) & pManager->airports);
}



int		saveAirportToFile(const Airport* pPort, FILE* fp) // write airport to file
{
	fprintf(fp, "%s\n", pPort->name);
	fprintf(fp, "%s\n", pPort->country);
	fprintf(fp, "%s\n", pPort->code);
	return 1;
}



int		saveManagerToFile(const AirportManager* pManager, const char* fileName) // write airportManager to file
{
	FILE* fp = fopen(fileName, "w");
	if (!fp)
		return 0;

	int count = countAirport(pManager);
	fprintf(fp, "%d\n", count);

	NODE* pNode = pManager->airports.head.next;
	NODE* temp = pNode;


	while (temp)
	{
		saveAirportToFile((Airport*)temp->key, fp);
		temp = temp->next;
	}

	fclose(fp);
	return 1;
}

