#include <stdio.h>

int main(void)
{
    // ANSI escape codes for colors 30-37 are foreground colors, 40-47 are background colors
    // 0-7 are the standard colors: black, red, green, yellow, blue, magenta, cyan, white
    int ansii = 30;
    printf("Ansi codes 30-38, 40-48\n");
    while (ansii < 38)
    {
        printf("\033[%dm%3d \033[0m", ansii, ansii);
        ansii++;
    }
    ansii = 40;
    while (ansii < 48)
    {
        printf("\033[%dm%3d \033[0m", ansii, ansii);
        ansii++;
    }
    printf("\n\nAnsi codes 90-97, 100-107\n");
    ansii = 90;
    while (ansii < 98)
    {
        printf("\033[%dm%3d \033[0m", ansii, ansii);
        ansii++;
    }
    ansii = 100;
    while (ansii < 108)
    {
        printf("\033[%dm%3d \033[0m", ansii, ansii);
        ansii++;
    }
    ansii = 0;
    printf("\n\n\nAnsi codes 48;5;0-15\n");
    while (ansii < 16)
    {
        printf("\033[48;5;%dm%3d \033[0m", ansii, ansii);
        if (ansii % 16 == 15)
            printf("\n");
        ansii++;
    }
    printf("\nAnsi codes 48;5;16-231\n");
    while (ansii < 232)
    {
        if (((ansii - 16) / 18 & 1) == 0)
        {
            printf("\033[48;5;%dm%3d \033[0m", ansii, ansii);
            if ((ansii - 16) % 18 == 17)
                printf("\n");
        }
        ansii++;
    }
    ansii = 16;
    while (ansii < 232)
    {
        if (((ansii - 16) / 18 & 1) != 0)
        {
            printf("\033[48;5;%dm%3d \033[0m", ansii, ansii);
            if ((ansii - 16) % 18 == 17)
                printf("\n");
        }
        ansii++;
    }
    printf("\nAnsi codes 48;5;232-255\n");
    while (ansii < 256)    {
        printf("\033[48;5;%dm%3d \033[0m", ansii, ansii);
        if ((ansii - 232) % 12 == 11)
            printf("\n");
        ansii++;
    }
    return 0;
}