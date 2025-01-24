#include <stdio.h>
#include <stdlib.h>

int xor(int a, int b);

int main(int argc, char *argv[])
{
	if (argc == 3)
		printf("%d\n", xor(atoi(argv[1]), atoi(argv[2])));
	return (0);
}