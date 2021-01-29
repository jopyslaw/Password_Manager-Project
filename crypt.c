#include "header.h"
#include <stdio.h>

// Funkcja do szyfrowania hasla
void password_encryption(char *tab) // DO sprawdzenia
{
    for(int i=0; *(tab+i) != '\0'; i++)
    {
        if( *(tab+i) > 31 && *(tab+i) < 65) // liczby i znaki od 32 do 64 w ASCII
        {
            *(tab+i) += LETTER_SHIFT;
            if( *(tab+i) > 64)
            {
                *(tab+i) -= 33;
            }
        }
        else if(*(tab+i) > 64 && *(tab+i) < 97) // Litery duze od A do Z
        {
            *(tab+i) += LETTER_SHIFT;
            if( *(tab+i) > 96)
            {
                *(tab+i) -= 32;
            }
        }
        else if(*(tab+i) > 96 && *(tab+i) < 123) // Litery male od A do Z
        {
            *(tab+i) += LETTER_SHIFT;
            if( *(tab+i) > 122)
            {
                *(tab+i) -= 26;
            }
        }
    }
    return;
}

// Funkcja do odszyfrowania hasla
void password_decryption(char *tab) // Do sprawdzenia
{
    for(int i=0; *(tab+i) != '\0'; i++)
    {
        if( *(tab+i) > 31 && *(tab+i) < 65) // liczby od 0 do 9
        {
            *(tab+i) -= LETTER_SHIFT;
            if( *(tab+i) < 32)
            {
                *(tab+i) += 33;
            }

        }
        else if(*(tab+i) > 64 && *(tab+i) < 97) // Litery duze od A do Z
        {
            *(tab+i) -= LETTER_SHIFT;
            if( *(tab+i) < 65)
            {
                *(tab+i) += 32;
            }
        }
        else if(*(tab+i) > 96 && *(tab+i) < 123) // Litery male od A do Z
        {
            *(tab+i) -= LETTER_SHIFT;
            if( *(tab+i) < 97)
            {
                *(tab+i) += 26;
            }
        }
    }
    return;
}