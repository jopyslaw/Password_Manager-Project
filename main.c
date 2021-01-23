#include "header.h"
#include <stdio.h>

int main()
{
    int choice, end=1;
    int *w_end = &end;
    user user;
    while(end != 0)
    {
        main_menu(choice, w_end, user);
    }
    return 0;
}