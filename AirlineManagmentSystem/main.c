#include <stdio.h>
#include <stdlib.h>
#include "Airline.h"
#include "AirportManager.h"
#include "General.h"
#include "AirlineFile.h"

int main()
{
	AirportManager	manager;
	Airline			company;

	initManagerAndAirline(&manager, &company);

	int option;
	int stop = 0;

	do
	{
		printf("Please choose one of the following options\n");
		printf("0 - Add Airport\n");
		printf("1 - add Plane\n");
		printf("2 - Add Flight\n");
		printf("3 - Print Airline\n");
		printf("4 - Print all airports\n");
		printf("5 - Print all flights with plane type\n");
		printf("6 - Sort Flight\n");
		printf("7 - Find Flight\n");
		printf("-1 - Quit\n");
		scanf("%d", &option);
		
		switch (option)
		{
		case 0:
			if (!addAirport(&manager))
				printf("Error adding airport\n");
			printf("\n");
			break;
		case 1:
			if (!addPlane(&company))
				printf("Error adding plane\n");
			printf("\n");
			break;
		case 2:
			if (!addFlight(&company, &manager))
				printf("Error adding flight\n");
			printf("\n");
			break;

		case 3:
			printCompany(&company);
			printf("\n");
			break;

		case 4:
			printAirports(&manager);
			printf("\n");
			break;

		case 5:
			doPrintFlightsWithPlaneType(&company);
			printf("\n");
			break;

		case 6:
			sortFlight(&company);
			printf("\n");
			break;

		case 7:
			findFlight(&company);
			printf("\n");
			break;

		case -1:
			printf("Bye bye\n");
			stop = 1;
			break;

		default:
			printf("Wrong option\n");
			printf("\n");
			break;
		}
	} while (!stop);
		
	saveManagerToFile(&manager, TEXT_FILE_NAME);
	saveAirlineToFile(&company, BIN_FILE_NAME);
	freeManager(&manager);
	freeCompany(&company);
	
	return 1;
}

