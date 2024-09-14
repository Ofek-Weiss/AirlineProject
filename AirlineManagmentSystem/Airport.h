#ifndef __AIRPORT__
#define __AIRPORT__

#define IATA_LENGTH 3

typedef struct
{
	char* name;
	char* country;
	char	code[IATA_LENGTH + 1];
}Airport;

int		isSameAirport(const Airport* pPort1, const Airport* pPort2);
int		isAirportCode(const Airport* pPort1, const char* code);
int		initAirportNoCode(Airport* pPort);
int		getAirportName(Airport* pPort);
char*	allocateRightLength(char** wordsArray, int count, int totalLength);
void	changeNameOneWord(char* name, const char* word);
void	changeName(char* name, int count, char** wordsArray);

void    getAirportCode(char* code);
void	printAirport(const void* pPort);
void	freeAirport(void* val);

#endif