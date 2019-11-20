#include <stdio.h>
#include "mesinkata.h"

int main(){
	char InputString[51];

	scanf("%s", InputString);
	StartReadingKata(InputString);
	printf("%d", IsKataSame("jAiKo", 5));
	return 0;
}