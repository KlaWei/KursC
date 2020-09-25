#include <stdio.h>

/* Zadanie 1, druga lista.
 * Wczytuje liczbę i wypisuje w formacie
 * dziesiętnym, ósemkowym i binarnym.
 * Autor: Klaudia Weigel
 * Data: 20.10.2016 */

void WriteNum(int baza, int x) {
    int cyfra, i;
    int l[100];
    int iloscCyfr=0;

    if(x<0) {
        putchar('-');
        x*=-1;
    }

    while (x>0) {
        cyfra = x%baza;
        l[iloscCyfr] = cyfra;
        x = x/baza;
        iloscCyfr++;
    }
    for(i=iloscCyfr-1;i>=0;i--) {
        putchar(l[i]+'0');
    }
    putchar('\n');
}

/* wczytyje liczbę ze standardowego wejścia. */
int ReadNum(int baza) {
    int c, liczba, obecna, znak;
    char b = '0' + baza;

    liczba=0;
    znak=1;

    c=getchar();

    while(c!='+' && c!='-' && (c<'0' || c>=b)) {
        c=getchar();
    }

    if(c=='+' || c=='-') {
        if(c=='-') znak = -1;
        c=getchar();
    }

    while(c!='.') {
        obecna = c - '0';
        liczba = liczba*baza + obecna;

        c=getchar();
    }
    return liczba*znak;
}

int main(void) {
    int c;

    c = ReadNum(10);
    WriteNum(10,c);
    WriteNum(8,c);
    WriteNum(2,c);

    return 0;
}
