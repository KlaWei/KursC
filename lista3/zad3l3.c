#include <stdio.h>

/* Zadanie 1 lista 3.
 * Autor: Klaudia Weigel */

void Kolo(int x0, int y0, int r) {
    int i, j;
    i=1; /* obecna pozycja w kolumnie (x) */
    j=1; /* obecna pozycja w wierszu (y) */
    while(j<=(r+y0)) {
        i=1;
        while(i<=(2*r+x0)) {
            if((0.5*0.5*((i-x0)*(i-x0))+(j-y0)*(j-y0)) <= (r*r)) printf("*");
            else printf(" ");
            i++;
        }
        printf("\n");
        j++;

    }
}

int main(void) {
   int x0, y0, r, kont;
   char c;
   kont=1;

   while(kont==1) {
      printf("Podaj pierwsza wspolrzedna: ");
      scanf("%d", &x0);
      printf("Podaj druga wspolrzedna: ");
      scanf("%d", &y0);
      printf("Podaj promien: ");
      scanf("%d", &r);

      Kolo(x0,y0,r);

      printf("Chcesz kontynuowac?(T/N)");
      scanf("\n%c", &c);

      if(c == 'N') kont=0;
      else printf("\n");

   }

   return 0;
}
