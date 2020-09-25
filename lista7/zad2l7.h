/* Lista 7 zadanie 2. Plik nagłówkowy.
 * Autor: Klaudia Weigel */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct ptList;
typedef struct ptList PtList;

void wczytajDane(FILE*, PtList**, PtList**);
void drukujListe(PtList*);
void wyswietlPunktNum(PtList*, int);
void wyswietlWieksze(PtList*, int);
void wyswietlNazwa(PtList*, char*);
void zwolnijPamiec(PtList**);
