#include <stdio.h>
#include <stdlib.h>

struct line
{
  int length;
  char contents[];
};


int main()
{
	int length;
	printf("Sizeof int: %ld, sizeof struct:%ld\n", sizeof(int), sizeof(struct line));
	printf("length? : ");
	scanf("%d", &length);

	struct line *thisline = malloc (sizeof(struct line) + length);
	thisline->length = length;

	printf("Enter string: ");
	scanf("%s", thisline->contents);

	printf("You entered %s\n", thisline->contents);
	printf("Sizeof: %ld\n", sizeof(struct line));
}