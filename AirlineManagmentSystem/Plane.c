#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "General.h"
#include "Plane.h"



void	initPlane(Plane* pPlane, Plane* planeArr, int planeCount)
{
	pPlane->serialNum = getPlaneSN(planeArr, planeCount);
	pPlane->type = getPlaneType();
}

ePlaneType getPlaneType()
{
	int option;
	printf("\n\n");
	do {
		printf("Please enter one of the following types\n");
		for (int i = 0; i < eNofPlaneTypes; i++)
			printf("%d for %s\n", i, PlaneTypeStr[i]);
		scanf("%d", &option);
	} while (option < 0 || option >= eNofPlaneTypes);
	getchar();
	return (ePlaneType)option;
}

const char* GetPlaneTypeStr(int type)
{
	if (type < 0 || type >= eNofPlaneTypes)
		return NULL;
	return PlaneTypeStr[type];
}

int getPlaneSN(Plane* planeArr, int planeCount)
{
	int num;
	int unique = 0;
	do {
		printf("Enter plane serial number - between %d to %d\n", MIN_SN, MAX_SN);
		scanf("%d", &num);
		if (num >= MIN_SN && num <= MAX_SN)
			unique = isSerialNumUnique(planeArr, planeCount, num);
	} while (!unique);
	return num;
}

int		isSerialNumUnique(Plane* planeArr, int planeCount, int num)
{
	for (int i = 0; i < planeCount; i++)
	{
		if (planeArr[i].serialNum == num)
			return 0;
	}
	return 1;
}

Plane* findPlaneBySN(Plane* planeArr, int count, int sn)
{
	for (int i = 0; i < count; i++)
		if (planeArr[i].serialNum == sn)
			return &planeArr[i];
	return NULL;
}

void	printPlane(const Plane* pPlane)
{
	printf("Plane: serial number:%d, type %s\n", pPlane->serialNum, PlaneTypeStr[pPlane->type]);

}



void freeTheValuesOfPlane(void* val)
{
	//nothing to free
}
