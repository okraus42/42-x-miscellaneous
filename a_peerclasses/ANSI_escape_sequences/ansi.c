#include <stdio.h>

int main(void)
{
    // ANSI escape codes for colors 30-37 are foreground colors, 40-47 are background colors
    // 0-7 are the standard colors: black, red, green, yellow, blue, magenta, cyan, white
    int ansii = 0;
    printf("Ansi codes\n");
    while (ansii < 107)
    {
        printf("\033[%dmANSII CODE: %3d \033[0m\n", ansii, ansii);
        ansii++;
    }
    return 0;
}