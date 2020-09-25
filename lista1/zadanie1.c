#include <stdio.h>

/* Program wczytuje pary liczb ze standardowego wejścia w postaci:
 * liczba i ilość cyfr do napotkania wartości 0 w polu liczby lub ilości cyfr.
 * Autor: Klaudia Weigel*/


/* Zwraca k-tą liczbę dziesiętna od końca */
int cyfra(int n, int k) {
    int i;

    for(i=0;i<k-1;i++) n=n/10;

    return n%10;
}

int main(void) {
    int liczba, ilCyfr, c, i;

    scanf("%d %d", &liczba, &ilCyfr);

    /* Dopóki nie wprowadzono 0 wypisuje cyfry liczby w odwrotnej kolejności */
    while(liczba!=0 && ilCyfr!=0) {
        i=1;
        while(i <= ilCyfr) {
            /* Oblicza i-tą od końca cyfrę i wypisuje wynik. */
            c = cyfra(liczba, i);
            printf("%d", c);
            i++;
        }
        printf("\n");
        scanf("%d %d", &liczba, &ilCyfr);
    }

    return 0;
}
