#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#define MAXLIST 100 // max number of commands to be supported
#define clear() printf("\033[H\033[J")
//Burada bizden istenen clear fonksiyonunun gerceklestirilebilmesi icin bu char sequence kullanılmıştır.


int takeParams(char *input)
{
    //Burada kendi shellimden parametreleri aliyorum. Bunları bir buffer a kopyaliyorum.
    // Burada add_history metodu normal shellde olan yon tuslari ile yukari asagi yaptigimizde
    // eski komutların getirilmesini saglar.
    char *buffer;
    buffer = readline("\nmyshell>>> ");
    if (strlen(buffer) != 0)
    {
        add_history(buffer);
        strcpy(input, buffer);
        return 0;
    }
    else
    {
        return 1;
    }
}

void execArgs(char **parsed)
{
    int pid = fork();
    int i;

    if (pid == -1)
    {
        printf("\nFailed forking child..");
        return;
    }
    else if (pid == 0)
    {
        i = execv(parsed[0], parsed);
        //printf("\nCould not execute command..");
        if (i < 0)
        {
            //printf("\n Could not execute command");
        }
        exit(0);
    }
    else
    {
        wait(&i);
    }
}

int myCommandHandler(char **parsedParams)
{
    /*
    Burada kullanicidan aldigim komutlarin kontorlunu sagladıgım bir yapi kurmaya calistim.
    if else yerine switch case yapısını kullandım ve bizden istenen komutlara gore yapilmasi gereken
    islemleri atadım.

    */

    int commandCount = 6, i, condStmt = 0;
    char *commands[commandCount];
    pid_t p2;
    commands[0] = "exit";
    commands[1] = "cd";
    commands[2] = "cat";
    commands[3] = "clear";
    commands[4] = "islem";
    commands[5] = "tekrar";
    //Bu kisimda bir switch case yapsi kullandim ve komutlarin yapacaklari isleri atadim.

    for (i = 0; i < commandCount; i++)
    {
        if (strcmp(parsedParams[0], commands[i]) == 0)
        {
            condStmt = i + 1;
            break;
        }
    }

    switch (condStmt)
    {
    case 1:
        printf("\nGoodbye\n");
        exit(0);

    case 2:
        chdir(parsedParams[1]);
        return 1;
    case 3:
        p2 = fork();
        if (p2 == 0)
        {
            execv("/bin/cat", parsedParams);
        }
        return 1;
    case 4:
        clear();
        return 1;
    case 5:
        execArgs(parsedParams);
        return 1;
    case 6:
        execArgs(parsedParams);
        return 1;
    default:
        break;
    }

    return 0;
}

void splitSpace(char *str, char **parsed)
{
    /*
    Burada kullanıcıdan aldigim parametre dizisini " "(bosluk) karakterine gore bolme islemi uyguluyorum.
    */
    int i;

    for (i = 0; i < MAXLIST; i++)
    {
        parsed[i] = strsep(&str, " ");

        if (parsed[i] == NULL)
        {
            break;
        }
    }
}

void splitOr(char *str, char **parsed)
{
    /*
    Burada kullanicinin tek seferde birden fazla komut calistirma istegi icin "|" karakterine göre
    ayirma islemine tabi tutuyorum. MAXLIST 100 olarak tanimlandigi icin ard arda 100 komut calistirilebilir.
    */
    int i;
    for (i = 0; i < MAXLIST; i++)
    {
        parsed[i] = strsep(&str, "|");
        if (parsed[i] == NULL)
        {
            break;
        }
    }
}
//main fonksiyonun icinde uc adet degisken tanimladim bunlar vasitasi ile alinan komutlarin islemlerni gerceklestirdim
int main()
{
    
    char userInput[MAXLIST] = {NULL};
    char *parsedComms[MAXLIST] = {NULL};
    char *processes[MAXLIST] = {NULL};
    int bekle = 1;
    int i;

    /*
    burada exit olana kadar calisacak bir while dongusu tanimladim 
    */
    while (1)
    {
        if (takeParams(userInput))// surekli inout alimi
        {
            continue;
        }

        splitOr(userInput, processes);//or karakterine gore bolme
        for (i = 0; i < MAXLIST; i++)
        {

            if (processes[i] == NULL)
            {
                break;
            }

            else
            {
                splitSpace(processes[i], parsedComms);// space karakterine gore bolme
                if (myCommandHandler(parsedComms))
                {
                }
                else
                {
                    printf("yanlis bir komut girdiniz\n");
                }
            }
        }
    }
    return 0;
}
