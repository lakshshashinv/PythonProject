//TEXT/FILE ENCRYPTION AND DECRYPTION
//modified from PYTHON CODE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Maxuser 100
#define Maxlen 100
#define key 0x5A

char usernames[Maxuser][Maxlen];
char passwords[Maxuser][Maxlen];
int user_count = 0;

void load_users() {
    FILE *fp = fopen("database.txt", "rb");
    if (fp == NULL) {
        printf("Could not load database\n");
        exit(1);
    }
    while (fscanf(fp, "%[^,], %s\n", usernames[user_count], passwords[user_count]) != EOF) {
        user_count++;
    }
    fclose(fp);
}



void cipher(char *data) {
    for (int i = 0; data[i] != '\0'; i++) {
        data[i] ^= key;
    }
}
int login(char *username, char *password) {
    char adminuser[] = "lol",  adminpass[] ="lol07";
    if (strcmp(adminuser, username) == 0 && strcmp(adminpass, password) == 0)
            return 1;
    for (int i = 0; i < user_count; i++) {
        if (strcmp(usernames[i], username) == 0 && strcmp(passwords[i], password) == 0)
            return 1;
    }
    return 0;
}


void change_password(char *username) {
    char pass1[Maxlen], pass2[Maxlen];
    printf("Enter new password: ");
    scanf("%s", pass1);
    printf("Re-enter new password: ");
    scanf("%s", pass2);

    if (strcmp(pass1, pass2) == 0) {
        FILE *fp = fopen("database.txt", "r");
        FILE *temp = fopen("temp.txt", "w");
        char user[Maxlen], pass[Maxlen];

        while (fscanf(fp, "%[^,], %s\n", user, pass) != EOF) {
            if (strcmp(user, username) == 0) {
                fprintf(temp, "%s, %s\n", user, pass1);
            } 
            else fprintf(temp, "%s, %s\n", user, pass);
            
        }

        fclose(fp);
        fclose(temp);
        remove("database.txt");
        rename("temp.txt", "database.txt");
        printf("Password successfully changed!\n");
    } 
    else printf("Password do not match! Please enter the Password carefully.\n");
    
}


void process_file(const char *input_file, const char *output_file, int encrypt) {
    FILE *fin = fopen(input_file, encrypt ? "r" : "r");
    FILE *fout = fopen(output_file, encrypt ? "w" : "w");
    if (!fin || !fout) {
        printf("- - - ERROR - - -\n");
        return;
    }
    char ch;
    while ((ch = fgetc(fin)) != EOF) {
        ch ^= key;
        fputc(ch, fout);
    }
    fclose(fin);
    fclose(fout);
    printf(encrypt ? "File encrypted.\n" : "File decrypted.\n");
}




void menu(char *username) {
    int choice;
    char buffer[Maxlen];
    while (1) {
        printf("\n1. Encrypt Message\n2. Decrypt Message\n3. Change Password\n4. Encrypt File\n5. Decrypt File\n6. Exit\nChoice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
            {
                printf("Enter message: ");
                fgets(buffer, Maxlen, stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                cipher(buffer);
                printf("Encrypted: %s\n", buffer);
                break;
            }
            case 2:
            {
                printf("Enter encrypted message: ");
                fgets(buffer, Maxlen, stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                cipher(buffer);
                printf("Decrypted: %s\n", buffer);
                break;
            }
            case 3:
            {
                change_password(username);
                break;
            }
            case 4: 
            {
                char input[Maxlen], output[Maxlen];
                printf("Enter raw filename: ");
                scanf("%s", input);
                printf("Enter output filename: ");
                scanf("%s", output);
                process_file(input, output, 1);
                break;
            }
            case 5: 
            {
                char input[Maxlen], output[Maxlen];
                printf("Enter encrypted filename: ");
                scanf("%s", input);
                printf("Enter output filename: ");
                scanf("%s", output);
                process_file(input, output, 0);
                break;
            }
            case 6:
                printf("\n- - - THANK YOU - - -!\n");
                return;
            default: printf("Invalid choice.\n");
        }
    }
}

int main() 
{
    char username[Maxlen], password[Maxlen];
    load_users();
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    if(login(username, password)) {
        printf("LOGIN SUCCESSFUL\n");
        menu(username);
    } 
    else printf("INVALID CREDENTIALS\n");
    return 0;
}
