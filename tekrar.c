#include <stdio.h>
#include <stdlib.h>
/*
Bu sınıfta isterlerimizden biri olan kullanıcı tarafından girilen bir parametreyi
yine kullanıcıdan aldığımız sayı kadar tekrar bastırma gerçekleştirilmiştir.
*/
int main(int argc, char *argv[])
{
    int i = 0;                       //while döngüsü için belirlenmiş bir değişken
    int repeatCount = atoi(argv[2]); // kullanıcıdan alınan tekrar adedinin saklandığı değiken tanımı..

    while (i < repeatCount)
    {
        //Döngünün içerisinde girilen adet kadar kelimenin yazılması işlemi gerçekleşmektedir.
        printf("%s\n", argv[1]);
        i++;
    }
    return 0;
}