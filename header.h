#include <stdio.h>
#include <stdlib.h>
#define BUFF 150
#define LETTER_SHIFT 5
#define T_BUFF (BUFF+1)
#define P_BUFF (T_BUFF+13)
#define MAX_SIZE 121
#define MAX_GET 130
#define USER_DATA "users.txt"
#define DATA_PATH "UserData\\"
#define DIR_NAME "UserData"

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
    char url_login[T_BUFF];
}user_data;

// Menu
int create_file();

int create_directory();

void main_menu(int choice, int *w_end, user user);

void register_menu(user user);

void login_menu(user user);

int register_user(user user);

int user_exist(user user);

int check_login_data(user user);

void user_menu(int *w_end, user user);

int add_data(user user);

user_data fill_user_data();

void show_data(user user);

void path_to_file(user user, char *tab);

void password_encryption(char *tab);

void password_decryption(char *tab);

int check_password_correct(char *tab);

int check_login_correct(char *tab);


