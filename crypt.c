#include "header.h"
#include <stdio.h>

// Funkcja do szyfrowania hasla
void password_encryption(char *tab)
{
    for(int i=0; *(tab+i) != '\0'; i++)
    {
        if( *(tab+i) > 47 && *(tab+i) < 58) // liczby od 0 do 9
        {
            *(tab+i) += LETTER_SHIFT;
            if( *(tab+i) > 57)
            {
                *(tab+i) -= 11;
            }
        }
        else if(*(tab+i) > 64 && *(tab+i) < 91) // Litery duze od A do Z
        {
            *(tab+i) += LETTER_SHIFT;
            if( *(tab+i) > 90)
            {
                *(tab+i) -= 26;
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
        if( *(tab+i) > 47 && *(tab+i) < 58) // liczby od 0 do 9
        {
            *(tab+i) -= LETTER_SHIFT;
            if( *(tab+i) < 48)
            {
                *(tab+i) += 11;
            }

        }
        else if(*(tab+i) > 64 && *(tab+i) < 91) // Litery duze od A do Z
        {
            *(tab+i) -= LETTER_SHIFT;
            if( *(tab+i) < 65)
            {
                *(tab+i) += 26;
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