#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAXLINE 80

typedef struct {
    char id[15];
    char password[15];
}User;

User users[100];
User user;

int login_count = 0;
int signUp_count = 0;
int succcess_signUp = 0;

void initialSet();
void menu();
void menu1();
void login();
void signUp();
void record();
void typing(int n);
void readAndWrite(FILE* f, int n);
int sizeOfFILE(FILE* f);
void getTypingResult(int correctNum, int fileSize, double t, int n);

int main(void)
{
    initialSet();
    menu();
}

void initialSet()
{
    FILE* fp = fopen("Privacy.txt", "r+");
    int size = fseek(fp, 0, SEEK_END);
    fseek(fp, 0, SEEK_SET);

    int n = 0;
    int i;
    for (i = 0; i < 100; i++) {
        if (n != EOF) {
            n = fscanf(fp, "%s%s", &users[i].id, &users[i].password);
        }
        else
            break;
    }

    fclose(fp);
}

void menu()
{
    system("clear");
    FILE* f = fopen("a.txt", "r+");
    int n;

    if (succcess_signUp != 0)
        printf("Sign up is complete.\n");

    printf("---------------------------\n");
    printf("|       TYPING TEST       |\n");
    printf("---------------------------\n");
    printf("       1. sign in\n");
    printf("       2. sign up\n");
    printf("       3. record\n");
    printf("       4. exit\n\n");
    printf("Enter the options : ");
    scanf("%d", &n);

    switch (n) {
    case 1:
        login();
        break;
    case 2:
        signUp();
        break;
    case 3:
        record();
        break;
    case 4:
    default:
        exit(0);
        break;
    }
}

void menu1()
{
    int n;
    system("clear");
    printf("---------------------------\n");
    printf("|           MENU          |\n");
    printf("---------------------------\n");
    printf("   1. Test\n");
    printf("   2. Ulleungdo And Dokdo\n");
    printf("   3. Kimchi\n");
    printf("   4. exit\n\n");
    printf("Enter the options : ");
    scanf("%d", &n);

    switch (n)
    {
    case 1:
    case 2:
    case 3:
        typing(n);
        break;
    case 4:
    default:
        exit(0);
        break;
    }
}

void login()
{
    system("clear");

    if (login_count != 0)
        printf("You entered the wrong ID or password. Try again.\n");

    printf("ID : "); scanf("%s", &user.id);
    printf("Password : "); scanf("%s", &user.password);

    int i;
    for (i = 0; i < 100; i++) {
        if (!(strcmp(user.id, users[i].id)) && !(strcmp(user.password, users[i].password))) {
            menu1();
            return;
        }
    }
    login_count++;
    login();
}

void signUp()
{
    system("clear");
    FILE* fp = fopen("Privacy.txt", "a+");

    if (signUp_count != 0)
        printf("ID that already exists.\n");

    printf("ID : "); scanf("%s", &user.id);

    int i;
    for (i = 0; i < 100; i++) {
        if (!strcmp(user.id, users[i].id)) {
            signUp_count++;
            signUp();
        }
    }
    fprintf(fp, "%s ", &user.id);

    printf("Password : "); scanf("%s", &user.password);
    fprintf(fp, "%s\n", &user.password);
    fclose(fp);

    initialSet();
    succcess_signUp++;
    menu();
}

void record()
{
    system("clear");

    FILE* rec = fopen("record.txt", "r+");
    char buf[100];
    char wait;

    printf("---------------------------------------------RECORD-----------------------------------------------\n");
    printf("UserID          Title                TypingSpeed(char/sec)  Accuracy     Date\n");
    printf("--------------------------------------------------------------------------------------------------\n");
    while (fgets(buf, MAXLINE, rec) != NULL) {
        puts(buf);
    }

    getchar();
    printf("\n\nPlease press any key and enter : ");
    scanf("%c", &wait);
    menu();
}

void typing(int n)
{
    FILE* text;
    char buf1[MAXLINE];
    char buf2[MAXLINE];
    int correct_num = 0;
    fgets(buf2, MAXLINE, stdin);

    system("clear");
    if (n == 1) {
        text = fopen("Test.txt", "r");
        fseek(text, 0, SEEK_SET);
        printf("-------------------------------------------------------------------------------\n");
        printf("-------------------------------------TEST--------------------------------------\n");
        printf("-------------------------------------------------------------------------------\n\n");
        readAndWrite(text, 1);
        fclose(text);
    }
    else if (n == 2) {
        text = fopen("UlleungdoAndDokdo.txt", "r");
        printf("-------------------------------------------------------------------------------\n");
        printf("------------------------------Ulleungdo And Dokdo------------------------------\n");
        printf("-------------------------------------------------------------------------------\n\n");
        readAndWrite(text, 2);
        fclose(text);
    }
    else {
        text = fopen("Kimchi.txt", "r");
        printf("-------------------------------------------------------------------------------\n");
        printf("------------------------------------Kimchi-------------------------------------\n");
        printf("-------------------------------------------------------------------------------\n\n");
        readAndWrite(text, 3);
        fclose(text);
    }

}

void readAndWrite(FILE* f, int n)
{
    char buf1[MAXLINE];
    char buf2[MAXLINE];
    int correct_num = 0;
    struct timeval start, end;

    gettimeofday(&start, NULL);

    fseek(f, 0, SEEK_SET);
    while (fgets(buf1, MAXLINE, f) != NULL) {
        int i = 0;
        puts(buf1);
        fgets(buf2, MAXLINE, stdin);
        while (buf1[i] != '\0') {
            if (buf1[i] == buf2[i])
                correct_num++;
            i++;
        }
        printf("\n");
    }

    gettimeofday(&end, NULL);
    double duration = (double)(end.tv_usec - start.tv_usec) / 1000000 + (double)(end.tv_sec - start.tv_sec);

    getTypingResult(correct_num, sizeOfFILE(f), duration, n);
}

int sizeOfFILE(FILE* f)
{
    fseek(f, 0, SEEK_END);
    int size = ftell(f);
    fseek(f, 0, SEEK_SET);

    return size;
}

void getTypingResult(int correctNum, int fileSize, double t, int n)
{
    char c;
    time_t date;
    time(&date);
    char* title;

    if (n == 1)
        title = "Test";
    else if (n == 2)
        title = "Ulleungdo And Dokdo";
    else
        title = "Kimchi";

    system("clear");
    printf("---------------------------TYPING RESULT-----------------------------\n");
    printf("UserID                   TypingSpeed(char/sec)           Accuracy\n");
    printf("%-24s %-31.2f %.2f%%\n\n\n\n\n\n\n\n", user.id, correctNum / t * 60, (double)correctNum / fileSize * 100);

    FILE* rec = fopen("record.txt", "a+");
    fprintf(rec, "%-16s%-21s%-23.2f%-13.2f%s", user.id, title, correctNum / t * 60, (double)correctNum / fileSize * 100, ctime(&date));

    fclose(rec);
    printf("Try again?(enter y/n) : ");
    scanf("%c", &c);
    if (c == 'y' || c == 'Y')
        menu1();
    else
        exit(0);
}
