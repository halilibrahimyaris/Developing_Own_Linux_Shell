#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
Bu sınıfta girilen iki adet sayının çıkarılması için gereken fonksiyon 
ve değerlerin sayı olup olmadığının kontrol fonksiyonları bulunmaktadır
*/
int main(int argc, char *argv[])
{
    int i = 0;
    if (isNumber(argv[0]) && isNumber(argv[1]))
    {
         //Eğer girilen parametreler sayi ise integer a cast edilir ve islem degeri return edilir.
        int birinci = atoi(argv[0]);
        int ikinci = atoi(argv[1]);
        return cikar(birinci, ikinci);
    }
    else{
        printf("there is an undigit char");
    }

    return 0;
}
//girilen iki sayının cikarildigi fonksiyon
int cikar(int a, int b)
{
    int toplam = 0;
    toplam = a - b;
    return toplam;
}

//girilen parametrenin numara olup olmadigini kontrol eden fonksiyon.
int isNumber(char a[])
{
    int i ;
    int length = 0;
    length = strlen(a);
    for (i = 0; i < length; i++)
    {
        if (!isdigit(a[i]))
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
}