#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>


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
            return 1;
        }
        strcpy(enc_pass, user.password);
        password_encryption(enc_pass);
        fprintf(file, "%s %s\n", user.login, enc_pass);
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
        return 1; //Blad otwarcia pliku
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

// Funkcja sluzaca do logowania spawdzajaca czy haslo i login zgadzaja sie z tymi z bazy
int check_login_data(user user)
{
    char username[T_BUFF];
    char user_password[T_BUFF];
    if((file = fopen(USER_DATA, "r")) == NULL)
    {
        return 1; //Blad otwarcia pliku
    }
    while(fscanf(file,"%s %s",username, user_password) != EOF)
    {
        password_decryption(user_password); // Funkcja odpowiadajaca za dekodowania hasla
        if(strcmp(user.login, username)==0 && strcmp(user.password, user_password) == 0)
        {
            fclose(file);
            return 0;
        }
    }
    fclose(file);
    return 1; 
}


// Funkcja realizujaca dodawania hasla do bazy dla danego uzytkownika
int add_data(user user)
{
    user_data data;
    char path[P_BUFF];
    path_to_file(user, path);
    if((file = fopen(path, "a")) == NULL)
    {
        return 1; //Blad otwarcia pliku
    }
    data = fill_user_data();
    password_encryption(data.url_password);
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
    scanf("%[^\n]s", data.website_url);
    fflush(stdin);
    printf("Podaj login: ");
    scanf("%[^\n]s", data.url_login);
    fflush(stdin);
    printf("Podaj haslo: ");
    scanf("%[^\n]s", data.url_password);
    fflush(stdin);
    return data;
}

// Funkcja wyswietlajaca wszystkie hasla danego uzytkownika
void show_data(user user)
{
    char path[P_BUFF] = {0}, username[T_BUFF], password[T_BUFF], url[T_BUFF];
    path_to_file(user, path);
    if((file = fopen(path, "r")) == NULL)
    {
        return; //Blad otwarcia pliku
    }
    printf("URL\tLOGIN\tPASSWORD\n");
    while(fscanf(file, "%s %s %s", url, username, password) != EOF)
    {
        password_decryption(password);
        printf("%s \n\t%s\n \t\t%s\n",url, username, password);
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

int create_file()
{
    if ((file = fopen(USER_DATA, "a")) == NULL)
    {
        return 1;
    }
    return 0;
    fclose(file);
}

int create_directory()
{
    if(mkdir(DIR_NAME) == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
