/* Zadanie 2 lista 6. Program wczytuje z pliku dane o książkąch do tablicy struktur.
 * Każdy wiersz pliku zawiera jedną informację w kolejności: autor, tytuł, rok wyd., ilość stron.
 * Nazwa pliku podawana jest jako pierwszy argument wywołania. Jako drugi argument 
 * podawana jest jedna z liter 'a', 'r', 't' oznaczająca opcje sortowania: a - według autora,
 * t - według tytułu, r - według roku.
 * Autor: Klaudia Weigel */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ksiazka {
    int rok;
    int strony;
    char autor[100];
    char tytul[100];
}; typedef struct ksiazka Ksiazka;

/* Funkcje porównujące dane elementy stuktury, wykorzystywane przez qsort */
int porownajRok(const void *a, const void *b) {
    return ((Ksiazka*)a)->rok - ((Ksiazka*)b)->rok;
}

int porownajAutor(const void *a, const void *b) {
    return strcmp(((Ksiazka*)a)->autor, ((Ksiazka*)b)->autor);
}

int porownajTytul(const void *a, const void *b) {
    return strcmp(((Ksiazka*)a)->tytul, ((Ksiazka*)b)->tytul);
}

void sortujIWypisz(Ksiazka *tk, int ik, char opcja) {
    int i;
    switch (opcja) {
        case 'a':
            qsort(tk, ik, sizeof(Ksiazka), porownajAutor);
            break;
        case 't':
            qsort(tk, ik, sizeof(Ksiazka), porownajTytul);
            break;
        case 'r':
            qsort(tk, ik, sizeof(Ksiazka), porownajRok);
            break;
        default:
            printf("Nieznana opcja.\n");
            break;
    }
    
    for (i=0;i<ik;i++) {
        printf("%s\n%s\n%d\n%d\n", tk[i].autor, tk[i].tytul, tk[i].rok, tk[i].strony);
    }
}

/* Pobiera linię z pliku o maksymalnej długości n, pomijając początkowe spacje */
char* pobierzLinie(FILE *fp, char *linia, int n) {
    int c;
    char *lp;
    c=fgetc(fp);
    lp=linia;
    while (c==' ') c=fgetc(fp);
    while (n>0 && c!=EOF && c!='\n') {
        (*lp++)=c;
        n--;
        c=fgetc(fp);
    }
    *lp = '\0';
    if(c==EOF && lp==linia) return NULL;
    else return linia;
}

/* Pobiera liczbę z linii pliku i zwraca jej wartość */
int pobierzLiczbe(FILE *fp, int *koniec) {
    int liczba, c;
    liczba=0;
    
    c=fgetc(fp);
    while(c==' ') c=fgetc(fp);
    while (c>='0' && c<='9') {
        liczba=liczba*10 + c-'0';
        c=fgetc(fp);
    }
    while(c!='\n' && c!=EOF) c=fgetc(fp);
    if(c==EOF) *koniec=1;
    return liczba;
}

/* Wczytuje do tablicy struktur dane z wejścia, zwraca długość tablicy */
int wczytajDane(FILE *fp, Ksiazka **tk, int sz_k) {
    int ik, koniec;
    koniec=0;
    ik=0;
    Ksiazka *pom;
    pom=*tk;
    
    while (koniec==0) {
        if(ik>=sz_k) { /* zwiększa tablice jeśli zabraknie miejsca */
            *tk = (Ksiazka*)realloc(*tk, (sz_k+10)*sizeof(Ksiazka));
            pom=(*tk)+sz_k;
            sz_k+=10;
        }
        if((pobierzLinie(fp, pom->autor, 100))==NULL) break;
        if((pobierzLinie(fp, pom->tytul, 100))==NULL) break;
        pom->rok = pobierzLiczbe(fp, &koniec);
        pom->strony = pobierzLiczbe(fp, &koniec);
        if(koniec==0) ik++;
        if(pom<((*tk)+ik)) pom++;
    }
    
    return ik;
}

int main(int argc, char *argv[]) {
    FILE *fp = NULL;
    Ksiazka *tk;
    int ik;
    char opcja;
    tk = (Ksiazka*)malloc(sizeof(Ksiazka)*10);
    if(argc>1) fp = fopen(argv[1], "r");
    
    if(fp==NULL) {
        printf("Blad wczytywania pliku\n");
        return 1;
    }
    
    ik = wczytajDane(fp, &tk, 10);
    
    if(argc>2) opcja = *argv[2];
    else {
        printf("Brak opcji sortowania.\n");
        return 1;
    }
    
    sortujIWypisz(tk, ik, opcja);
    
    fclose(fp);
    free(tk);
    
    return 0;
}
