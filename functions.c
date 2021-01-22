#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void main_menu(int choice, int *w_end, user user, user_data data)
{
    printf("Witaj w menedzerze hasel !!!\n");
    printf("Dostepne opcje:\n");
    printf("1. Logowanie\n");
    printf("2. Rejstracja\n");
    printf("3. Wylacz program\n");
    printf("Wybierz opcje: ");
    scanf("%d", &choice);

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

void register_menu(user user)
{
    int check_register;
    system("cls");
    printf("Rejstracja nowego uzytkownika: \n");
    printf("Podaj login: ");
    scanf("%s", user.login);
    fflush(stdin);
    printf("Podaj haslo: ");
    scanf("%s", user.password);
    fflush(stdin);
    check_register = register_user(user);
    if(check_register == 0)
    {
        printf("\nOperacja przebiegla pomyslnie\n");
        return;
    }
    else
    {
        printf("\nOperacja nie mogla zostac wykonana pomyslnie. Taki login juz istnieje\n");
        return;
    }
}

int register_user(user user)
{
    int exist;
    exist = user_exist(user);
    if(exist == 0)
    {
        if((file = fopen(USER_DATA, "a")) == NULL)
        {
            printf("Blad otwarcia pliku");
            return 1;
        }
        fprintf(file, "%s %s\n", user.login, user.password);
        fclose(file);
        return 0;
    }
    else
    {
        return 1;
    }
}

int user_exist(user user)
{
    char user_tab[T_BUFF];
    if((file = fopen(USER_DATA, "r")) == NULL)
    {
        printf("Blad otwarcia pliku");
        return 1;
    }
    while (fscanf(file,"%s %*s",user_tab)==1)
    {
        if( strcmp(user.login, user_tab) == 0)
        {
            return 1;
        }
    }
    return 0; 
        
}

void login_menu(user user)
{
    int check_data, end=1, *w_end = &end;
    system("cls");
    printf("Logowanie uzytkownika: \n");
    printf("Podaj login: ");
    scanf("%s", user.login);
    fflush(stdin);
    printf("Podaj haslo: ");
    scanf("%s", user.password);
    fflush(stdin);
    check_data = check_login_data(user);
    if(check_data == 0)
    {
        while(end != 0)
        {
            user_menu(w_end);
        }
    }
    else
    {
        printf("Bledne dane logowania");
    }
}

int check_login_data(user user)
{
    char username[T_BUFF];
    char user_password[T_BUFF];
    if((file = fopen(USER_DATA, "r")) == NULL)
    {
        printf("Blad otwarcia pliku");
        return 1;
    }
    while(fscanf(file,"%s %s",username, user_password) != EOF)
    {
        if(strcmp(user.login, username)==0 && strcmp(user.password, user_password) == 0)
        {
            return 0;
        }
    }
    return 1; 
}

void user_menu(int *w_end)
{
    int choice;
    system("cls");
    printf("Witaj w menu uzytkownika oto dostepne opcje:\n");
    printf("1. Dodaj haslo\n");
    printf("2. Wyswietl hasla\n");
    printf("3. Wyloguj sie\n");
    printf("Wybierz interesujaca cie opcje: ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            break;
        case 2:
            break;
        case 3:
            *w_end = 0;
            break;
        default:
            printf("Nie ma takiej opcji");
    }
}