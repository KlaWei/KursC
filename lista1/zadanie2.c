#include <stdio.h>

/* Program wczytyjący jedną liczbę i wypisujący jej rewers i
 * informację czy jest palindromem. Program zatrzymuje się
 * przy wprowadzeniu zera.
 * Autor: Klaudia Weigel
 */

/* Zwraca k-tą liczbę dziesiętna od końca */
int cyfra(int n, int k) {
    int wynik, i;

    for(i=0;i<k-1;i++) {
        n=n/10;
    }
    wynik=n%10;
    return wynik;
}

/* Sprawdza czy liczba n długości k jest palidromem.
 * Zwraca 1 jeśli jest, 0 jeśli nie. */
int jestPalindromem(int n, int k) {
    int ostatnia = k, pierwsza = 1, jest = 1;

    while (pierwsza<ostatnia && jest==1) {
        if(cyfra(n, pierwsza) != cyfra(n, ostatnia)) jest=0;
        ostatnia--;
        pierwsza++;
    }

    return jest;
}

/* Rekurencyjnie oblicza ilość cyfr liczby n. */
int iloscCyfr(int n) {
    if(n<10) return 1;
    else return iloscCyfr(n/10) + 1;
}

int main(void) {
    int liczba, ilCyfr, c, i;

    scanf("%d", &liczba);

    while(liczba!=0) {
        i=1;
        ilCyfr = iloscCyfr(liczba);
        while(i <= ilCyfr) {
            c = cyfra(liczba, i);
            printf("%d", c);
            i++;
        }
        if(jestPalindromem(liczba, ilCyfr) == 1) printf(" Jest palindromem\n");
        else printf(" Nie jest palidromem.\n");
        scanf("%d", &liczba);
    }

    return 0;
}
