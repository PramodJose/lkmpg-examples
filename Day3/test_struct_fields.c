#include <stdio.h>

struct Fields
{
	char *name;
	int roll;
	int marks;
	char grade;
	int arr[];
};

void main(void)
{
	struct Fields st1 =
	{
		.grade = 'A',
		.roll = 13,
		marks: 75,
		name : "Abhishek",
	};
	
	struct Fields *p = &st1;
	//int arr[0] = {1};
	//printf("%s\n", );
	//printf("%s\n", p);

	//printf("grade: %c, roll: %d, marks: %d, name: %s\n", st1.grade, st1.roll, st1.marks, st1.name);
}