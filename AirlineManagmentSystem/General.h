#ifndef __GENERAL__
#define __GENERAL__

#define MAX_STR_LEN 255

char*	getStrExactName(const char* msg);
char*	myGets(char* buffer, int size);
char*	getDynStr(char* str);
char**	splitCharsToWords(char* str,int* pCount,int* pTotalLength);
int		readStringFromFile(char* str, FILE* fp);




#endif

