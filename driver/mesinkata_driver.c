#include <stdio.h>
#include "mesinkata.h"

int main()
{
	char InputString[51];

	scanf("%s", InputString);
	StartReadingKata(InputString);
	printf("%d", IsKataSame("jAiKo", 5));

	scanf("%s", InputString);
	StartReadingKata(InputString);
	printf("%d", IsKataSame("End_Turn", 8));

	scanf("%s", InputString);
	StartReadingKata(InputString);
	printf("%d", IsKataSame("Exit", 4));

	return 0;
}