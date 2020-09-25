/* Zadnie 2 lista 7. Program wczytuje z pliku informacje o punkcie 
 * geometrycznym: współrzędne x, y, z oraz nazwę (max 36 znaków). Nazwa pliku
 * podana jest jako pierwszy argument wywołania. Jako kolejne argumenty 
 * wywyołanie podaje się opcje wydruku: print-drukuje całą listę punktów;
 * higher 'liczba'-drukuje wszystkie punkty których pierwsza współrzędna jest
 * większa niż podana liczba; search 'napis'-drukuje punkty w których znajduje
 * się podany napis; point 'liczba'-drukuje punkt o numerze 'liczba'.
 * Autor: Klaudia Weigel */

#include "zad2l7.h"

int main(int argc, char *argv[]) {
    FILE *fp = NULL;
    PtList *pocz, *kon; /* wskaźniki na początek i koniec listy */
    float k; 
    int a;
    pocz=NULL;
    kon=NULL;
    if(argc>1) fp = fopen(argv[1], "r");
    
    if(fp==NULL) {
        printf("Blad wczytywania pliku\n");
        return 1;
    }
    wczytajDane(fp, &pocz, &kon);
    if (argc==3) {
        if (strcmp("print", argv[2])==0) drukujListe(pocz);
    }
    else if (argc==4) {
        if (strcmp("point", argv[2])==0) {
            a=atoi(argv[3]);
            wyswietlPunktNum(pocz, a);
        }
        else if (strcmp("higher", argv[2])==0) {
            k=(float)atof(argv[3]);
            wyswietlWieksze(pocz, k);
        }
        else if (strcmp("search", argv[2])==0) {
            wyswietlNazwa(pocz, argv[3]);
        }
    }
    
    fclose(fp);
    zwolnijPamiec(&pocz);
    
    return 0;
}
