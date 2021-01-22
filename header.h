#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFF 150
#define T_BUFF (BUFF+1)
#define USER_DATA "users.txt"

FILE *file;

typedef struct User
{
    char login[T_BUFF];
    char password[T_BUFF];
}user;

typedef struct User_data
{
    char website_url[T_BUFF];
    char url_password[T_BUFF];
}user_data;

// Menu
void main_menu(int choice, int *w_end, user user, user_data data);

void register_menu(user user);

void login_menu(user user);

int register_user(user user);

int user_exist(user user);

int check_login_data(user user);

void user_menu(int *w_end);