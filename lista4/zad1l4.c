#include <stdio.h>

/* Zadanie 1 lista 4. Program oblicza zagniezdzenie nawiasow.
 *
 * Autor: Klaudia Weigel */

void zagniezdzenie() {
    int c, z;
    z=0;

    printf("%d ", z); /* na poczatku ilosc nawiasow to 0 */
    c=getchar();
    while(c!=EOF && z>=0) {
        if(c=='{') z++;
        if(c=='}') z--;
        putchar(c);
        if(c=='\n') printf("%d ", z);
        c=getchar();
    }
    if(z<0) printf("\nBlad: brak nawiasow.\n");
    printf("\n");

}

int main(void) {
    zagniezdzenie();
    return 0;
}
