#include <stdio.h>

int	main(void)
{
	printf("-1 = %x\n-2147483648 = %x\n", (unsigned int)-1, (unsigned int)-2147483648);
	printf("-2 = %x\n-2147483649 = %x\n", (unsigned int)-2, (unsigned int)-2147483649);
	printf("0x80000000 = %u\n0x7fffffff = %u\n", 0x80000000, 0x7fffffff);
	return(0);
}
