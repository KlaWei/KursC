/* Zadanie 2 lista 7. Plik z funkcjami.
 * Autor: Klaudia Weigel */

#include "zad2l7.h"

#define MAX_NAZWA 36

struct ptList {
    struct ptList *nast;
    float x;
    float y;
    float z;
    char nazwa[MAX_NAZWA];
};

void zwolnijPamiec(PtList **pocz) {
    PtList *pom;
    while ((pom=(*pocz))!=NULL) {
        (*pocz)=(*pocz)->nast;
        free(pom);
    }
}

/* Wstawia element na koniec listy. */
void wstaw(PtList **pocz, PtList **kon, float x, float y, float z, char* nazwa, int n) {
    PtList *pom;
    int i;
    pom=(PtList*)malloc(sizeof(PtList));
    for (i=0;i<n;i++) {
        pom->nazwa[i]=nazwa[i];
    }
    pom->x=x;
    pom->y=y;
    pom->z=z;
    pom->nast=NULL;
    
    if ((*pocz)==NULL) {
        (*pocz)=pom;
        (*kon)=pom;
    }
    else {
        (*kon)->nast=pom;
        (*kon)=pom;
    }
}

void wyswietlPunkt(PtList *p) {
    printf("%f %f %f %s\n", p->x, p->y, p->z, p->nazwa);
}

void drukujListe(PtList *pocz) {
    PtList *pom;
    pom=pocz;
    while (pom!=NULL) {
        wyswietlPunkt(pom);
        pom=pom->nast;
    }
}

/* Wyświetla punkt o numerze n, 0 jeśli takiego punktu nie ma. */
void wyswietlPunktNum(PtList *pocz, int n) {
    int i=1;
    PtList *pom;
    pom=pocz;
    while (i<n && pom!=NULL) {
        i++;
        pom=pom->nast;
    }
    if (i==n) {
        wyswietlPunkt(pom);
    }
    else printf("0\n");
}

/* Wyświetla punkty o pierwszej współrzędnej większej od n. */
void wyswietlWieksze(PtList *pocz, int n) {
    PtList *pom;
    pom=pocz;
    while (pom!=NULL) {
        if ((pom->x) > n) wyswietlPunkt(pom);
        pom=pom->nast;
    }
}

/* Sprawdza nazwie znajduje się dany napis zwraca 1 jeśli tak, 0-nie. */
int jestNapis(char *nazwa, char *napis, int sz) {
    int i, j, jest;
    jest=0;
    for (i=0;i<MAX_NAZWA-sz && jest==0;i++) {
        jest=1;
        for (j=0;j<sz && jest==1;j++) {
            if(nazwa[j+i]!=napis[j]) jest=0;
        }
    }
    return jest;
}

/* Wyświetla elementy w nazwie których znajduje się dany napis. */
void wyswietlNazwa(PtList *pocz, char *napis) {
    int sz, j;
    PtList *pom;
    pom=pocz;
    sz=strlen(napis);
    if(sz>MAX_NAZWA) return;
    
    while (pom!=NULL) {
        j=jestNapis(pom->nazwa, napis, sz);
        if(j==1) wyswietlPunkt(pom);
        pom=pom->nast;
    }
}

void wczytajDane(FILE *fp, PtList **pocz, PtList **kon) {
    float x, y, z;
    int c, i;
    char n[MAX_NAZWA];
    while (1) {
        if(fscanf(fp, "%f %f %f", &x, &y, &z)==EOF) break;
        while ((c=fgetc(fp))==' ') c=fgetc(fp);
        i=0;
        while (c!='\n' && i<MAX_NAZWA && c!=EOF) {
            n[i]=c;
            i++;
            c=fgetc(fp);
        }
        i--;
        while (n[i]==' ') i--; /* usuwa wiodące spacje */
        n[++i]='\0';
        if(strcmp("KONIEC", n)==0) break;
        wstaw(pocz, kon, x, y, z, n, i);
    }
}
