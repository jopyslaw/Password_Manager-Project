#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Gˆowne menu programu
void main_menu(int choice, int *w_end, user user)
{
    printf("Witaj w menedzerze hasel !!!\n");
    printf("Dostepne opcje:\n");
    printf("1. Logowanie\n");
    printf("2. Rejstracja\n");
    printf("3. Wylacz program\n");
    printf("Wybierz opcje: ");
    scanf("%d", &choice);
    fflush(stdin);

    switch(choice)
    {
        case 1:
            login_menu(user);
            break;
        case 2:
            register_menu(user);
            break;
        case 3:
            *w_end = 0;
            break;
        default:
            printf("Brak takiej opcji\n");
            break;
    }
}

// Menu rejstracji
void register_menu(user user)
{
    int check_register, check_login, check_password;
    system("cls");
    printf("Rejstracja nowego uzytkownika: \n");
    printf("Pamietaj maksymalna dlugosc hasla i loginu to 120 znakow dla kazdego\n");
    printf("Znaki ktore nie moga wystapic w nazwie uzytkownika to: spacja, dwukropki, cydzyslowia, |, ~, {, }\n");
    printf("Znaki ktore nie moga wystapic w hasle to: |, ~, {, }\n");
    while(strlen(user.login) > MAX_SIZE || strlen(user.password) > MAX_SIZE || strlen(user.login) == 0 || strlen(user.password) == 0 || check_login == 1 || check_password == 1)
    {
        printf("Podaj login: ");
        scanf("%[^\n]130s", user.login);
        fflush(stdin);
        printf("Podaj haslo: ");
        scanf("%[^\n]130s", user.password);
        fflush(stdin);
        if(strlen(user.login) > MAX_SIZE || strlen(user.password) > MAX_SIZE)
        {
            printf("Login lub haslo maja wiecej niz 120 znakow\n");
            continue;
        }
        if( (check_login = check_login_correct(user.login)) == 1)
        {
            printf("W loginie wystapily niedozwolone znaki\n");
            continue;
        }
        if( (check_password = check_password_correct(user.password)) == 1)
        {
            printf("W hasle wystapily niedozwolone znaki\n");
            continue;
        }
    }
    check_register = register_user(user);
    if(check_register == 0)
    {
        printf("\nOperacja przebiegla pomyslnie\n");
        return;
    }
    else
    {
        printf("\nOperacja nie mogla zostac wykonana pomyslnie\n");
        return;
    }
}

// Menu logowania
void login_menu(user user)
{
    int check_data, end=1, *w_end = &end;
    system("cls");
    printf("Logowanie uzytkownika: \n");
    printf("Podaj login: ");
    scanf("%[^\n]130s", user.login);
    fflush(stdin);
    printf("Podaj haslo: ");
    scanf("%[^\n]130s", user.password);
    fflush(stdin);
    check_data = check_login_data(user);
    if(check_data == 0)
    {
        while(end != 0)
        {
            user_menu(w_end, user);
        }
    }
    else
    {
        printf("Bledne dane logowania\n");
    }
}

// Menu uzytkownika
void user_menu(int *w_end, user user)
{
    int choice, check;
    printf("\nWitaj %s w menu uzytkownika oto dostepne opcje:\n", user.login);
    printf("1. Dodaj haslo\n");
    printf("2. Wyswietl hasla\n");
    printf("3. Wyloguj sie\n");
    printf("Wybierz interesujaca cie opcje: ");
    scanf("%d", &choice);
    fflush(stdin);
    
    switch(choice)
    {
        case 1:
            check = add_data(user);
            if(check == 0)
            {
                printf("Dane zostaly dodane");
            }
            else
            {
                printf("Wystapil blad. Dane nie zostaly dodane");
            }
            break;
        case 2:
            show_data(user);
            break;
        case 3:
            *w_end = 0;
            break;
        default:
            printf("Nie ma takiej opcji");
    }
}