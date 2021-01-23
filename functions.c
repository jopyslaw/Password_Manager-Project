#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void main_menu(int choice, int *w_end, user user)
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
            user_menu(w_end, user);
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

void user_menu(int *w_end, user user)
{
    int choice, check;
    printf("\nWitaj w menu uzytkownika oto dostepne opcje:\n");
    printf("1. Dodaj haslo\n");
    printf("2. Wyswietl hasla\n");
    printf("3. Wyloguj sie\n");
    printf("Wybierz interesujaca cie opcje: ");
    scanf("%d", &choice);

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

int add_data(user user)
{
    user_data data;
    char path[P_BUFF];
    path_to_file(user, path);
    if((file = fopen(path, "a")) == NULL)
    {
        printf("Blad z odczytem pliku");
        return 1;
    }
    data = fill_user_data();
    fprintf(file, "%s %s %s\n", data.website_url, data.url_login, data.url_password);
    fclose(file);
    return 0;
}

user_data fill_user_data()
{
    user_data data;
    system("cls");
    printf("Podaj nazwe strony: ");
    scanf("%s", data.website_url);
    printf("Podaj login: ");
    scanf("%s", data.url_login);
    printf("Podaj haslo: ");
    scanf("%s", data.url_password);
    return data;
}

void show_data(user user)
{
    char path[P_BUFF] = {0}, username[T_BUFF], password[T_BUFF], url[T_BUFF];
    path_to_file(user, path);
    if((file = fopen(path, "r")) == NULL)
    {
        printf("Blad dostepu do pliku");
        return;
    }
    printf("URL\t LOGIN\t PASSWORD\n");
    while(fscanf(file, "%s %s %s", url, username, password) != EOF)
    {
        printf("%s\t %s\t %s\n",url, username, password);
    }
    fclose(file);
    return;
}

void path_to_file(user user, char *tab)
{
    strcat(tab,DATA_PATH);
    strcat(tab,user.login);
    strcat(tab,".txt");
    tab++;
    return;
}