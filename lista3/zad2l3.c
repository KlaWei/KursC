#include <stdio.h>

/* Zadanie 2 lista 3. Program pyta się w pętli jaki obiekt narysowac.
 * Możliwe opcje: p/P - prostokąt, t/T - trójkąt, c/C - choinka, k/K - koło,
 * w/W - wyjście. Układ współrzędnych rozpoczyna się w punkcie (0,0).
 * Punkt na osi x to numer w wierszu, punkt na osi y to numer wiersza.
 * Odległość na osi x jest 2 razy mniejsza niż odległość na osi y.
 * Długość(promień, wysokość, dł. boku) liczona jest względem osi y.
 * Autor: Klaudia Weigel */

/* Rysuje prostokąt o skrajnych punktach (minx, miny) i (maxx, maxy) */
void prostokat(int minx, int miny, int maxx, int maxy) {
    int x, y;
    x=0; y=0;
    
    /* punkt poczatkowy na osi y */
    while (y<miny) {
        printf("\n");
        y++;
    }
    y=0;
    
    while (y<=maxy-miny) {
        x=0;
        while (x<=maxx) {
            if(x>=minx) printf("*");
            else printf(" ");
            x++;
        }
        y++;
        printf("\n");
    }
    
}

/* Rysuje choinkę o czubku w (x0, y0) i wysokości r */
void choinka(int x0, int y0, int r) {
    int x, y;
    x=0; y=0;
    
    while (y<y0) {
        printf("\n");
        y++;
    }
    
    y=0;
    while (y<r) {
        x=0;
        while (x<=(2*x0)) {
            if(x>=x0-y && x<=x0+y) printf("*");
            else printf(" ");
            x++;
        }
        printf("\n");
        y++;
    }
    
    y=0;
    while (y<(r/4) || y<1) {
        x=0;
        while (x<x0) {
            printf(" ");
            x++;
        }
        printf("|");
        printf("\n");
        y++;
    }
    
}

/* Rysuje trójkąt o lewym górnym rogu w (x0, y0) i długości
 * boku r, zaczynającego w tym punkcie */
void trojkat(int x0, int y0, int r) {
    int x, y, s;
    x=0; y=0; s=0; /* s- ilość gwiazdek do odjęcia na każdym poziomie */
    
    while (y<y0) {
        printf("\n");
        y++;
    }
    y=0;
    while (y<(r+1)/2) {
        x=0;
        while(x<x0+2*r) {
            if(x>=x0+2*s && x<x0+2*r-2*s) printf("*");
            else printf(" ");
            x++;
        }
        printf("\n");
        s++;
        y++;
        
    }
}

/* Rysuje koło o środku w punkcie (x0, y0) i promieniu r */
void kolo(int x0, int y0, int r) {
    int x, y;
    x=0; y=0;
    
    while (y<=(r+y0)) {
        x=0;
        while (x<=2*r+x0) {
            if(((0.5*0.5)*(x-x0)*(x-x0)+(y-y0)*(y-y0))<=(r*r)) printf("*");
            else printf(" ");
            x++;
        }
        printf("\n");
        y++;
    }
}


void wczytajLiczby(int* liczby, int ilosc) {
    int n, liczba, c;
    n=0; liczba=0;
    
    c=getchar();
    while (c!='\n') {
        if(c>='0' && c<='9') {
            while (c>='0' && c<='9') {
                liczba=10*liczba + (c-'0');
                c=getchar();
            }
            if(n<ilosc) liczby[n]=liczba;
            n++;
            liczba=0;
        }
        if(c!='\n') c=getchar();
    }
}

void WczytajDane() {
    int kont, c, wybor;
    int liczby[4];
    kont=1;
    
    while (kont==1) {
        printf("Jaki obiekt narysowac?(P/T/C/K/W)\n");
        c=getchar();
        wybor=c;
        while (c!='\n') c=getchar();
        
        switch (wybor) {
            case 'P': case 'p':
                printf("Podaj min x, min y, max x, max y: ");
                wczytajLiczby(liczby, 4);
                prostokat(liczby[0], liczby[1], liczby[2], liczby[3]);
                break;
            case 'T': case 't':
                printf("Podaj wspolrzedne gornego lewego punktu (x0, y0) i dlugosc gornego boku: ");
                wczytajLiczby(liczby, 3);
                trojkat(liczby[0], liczby[1], liczby[2]);
                break;
            case 'C': case 'c':
                printf("Podaj wspolrzedne czubka choinki(x0, y0) i wysokosc: ");
                wczytajLiczby(liczby, 3);
                choinka(liczby[0], liczby[1], liczby[2]);
                break;
            case 'K': case 'k':
                printf("Podaj wspolrzedne srodka(x0, y0) i promien: ");
                wczytajLiczby(liczby, 3);
                kolo(liczby[0], liczby[1], liczby[2]);
                break;
            case 'W': case 'w':
                kont=0;
                break;
            default:
                printf("Nie ma takiej opcji.\n");
                break;
        }
    }
}

int main(void) {
    
    WczytajDane();
    return 0;
}
