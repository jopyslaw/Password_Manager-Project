#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Napisac sprawdzanie wpisywanych danych czy w hasle nie ma znakow specjalnych lub dodac szyfrowanie 

// Funkcja ktora sprawdza czy we wpisanym tekscie nie ma zakazanych znakow;

// Ustawic maksymalna dlugosc hasla na 120 znakow tak samo jak i loginu

// Do implementowac sprawdzanie poprawanosci znakow przy loginie i hasle

// Glowne menu
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

// Menu rejstracji
void register_menu(user user)
{
    int check_register, check_login, check_password;
    system("cls");
    printf("Rejstracja nowego uzytkownika: \n");
    printf("Pamietaj maksymalna dlugosc hasla i loginu to 120 znakow dla kazdego\n");
    printf("Znaki ktore nie moga wystapic w nazwie uzytkownika to: spacja, dwukropki, cydzyslowia, |, ~, {, }\n");
    printf("Znaki ktore nie moga wystapic w hasle to: |, ~, {, }\n");
    while(strlen(user.login) > MAX_SIZE || strlen(user.password) > MAX_SIZE || strlen(user.login) == 0 || strlen(user.password) == 0)
    {
        printf("Podaj login: ");
        scanf("%s", user.login);
        fflush(stdin);
        printf("Podaj haslo: ");
        scanf("%s", user.password);
        fflush(stdin);
        if(strlen(user.login) > MAX_SIZE || strlen(user.password) > MAX_SIZE)
        {
            printf("Login lub haslo maja wiecej nic 120 znakow lub sa puste");
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
        printf("\nOperacja nie mogla zostac wykonana pomyslnie. Taki login juz istnieje\n");
        return;
    }
}

// Funkcja odpowiadajaca za rejstracja uzytkownika 
int register_user(user user)
{
    int exist;
    char enc_pass[T_BUFF];
    exist = user_exist(user);
    if(exist == 0)
    {
        if((file = fopen(USER_DATA, "a")) == NULL)
        {
            printf("Blad otwarcia pliku");
            return 1;
        }
        strcpy(enc_pass, user.password);
        password_encryption(enc_pass);
        fprintf(file, "%s %s\n", user.login, user.password ); // user.password -> enc_pass
        fclose(file);
        return 0;
    }
    else
    {
        return 1;
    }
}

// Funkcja ktora sprawdza czy uzytkownik z dan¥ nazw¥ ju¾ istnieje
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
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0; 
        
}

// Menu logowania
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

// Funkcja sluzaca do logowania spawdzajaca czy haslo i login zgadzaja sie z tymi z bazy
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
        //password_decryption(user_password); // Funkcja odpowiadajaca za dekodowania hasla
        if(strcmp(user.login, username)==0 && strcmp(user.password, user_password) == 0)
        {
            fclose(file);
            return 0;
        }
    }
    fclose(file);
    return 1; 
}

// Menu uzytkownika
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

// Funkcja realizujaca dodawania hasla do bazy dla danego uzytkownika
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

// Funkcja slu¾aca do wypeˆnienia struktury danych user_data
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

// Funkcja wyswietlajaca wszystkie hasla danego uzytkownika
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

// Funkcja tworzaca sciezke do pliku gdzie ma zostac zapisany plik
void path_to_file(user user, char *tab)
{
    strcat(tab,DATA_PATH);
    strcat(tab,user.login);
    strcat(tab,".txt");
    tab++;
    return;
}

// Funkcja sprawdza czy w hasle nie wystepuja zabronione znaki
int check_password_correct(char *tab)
{
    int i=0;
    while(tab[i] != '\0')
    {
        if(tab[i] == 126 || tab[i] == 125 || tab[i] == 124 || tab[i] == 123)
        {
            return 1;
        }
        i++;
    }
    return 0;
}

// Funkcja sprawdza czy w loginie nie wystepuja zabronione znaki
int check_login_correct(char *tab)
{
    int i=0;
    while(tab[i] != '\0')
    {
        if(tab[i] == 126 || tab[i] == 125 || tab[i] == 124 || tab[i] == 123 || tab[i] == 32 || tab[i] == 58 || tab[i] == 34)
        {
            return 1;
        }
        i++;
    }
    return 0;
}