#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int i;
    int f = fork();

    if (f == 0) // eger cocuk process ise
    {
        // argv[0] programimizin adidir
        i = execl(argv[1], argv[2], argv[3]); // programlar agrumanlar ile execute edilir
         //perror("exec2: execve failed\n");
    }
    else
    {
        wait(&i); // cocuk processin terminate edilmesi beklenir. ve islem sonucu yazdirilir
        if (strcmp("cikar", argv[1]) == 0)
        {
            printf("%s - %s = %d\n", argv[2], argv[3], WEXITSTATUS(i));
        }
        if (strcmp("topla", argv[1]) == 0)
        {
            printf("%s + %s = %d\n", argv[2], argv[3], WEXITSTATUS(i));
        }
    }

    return 0; 
}