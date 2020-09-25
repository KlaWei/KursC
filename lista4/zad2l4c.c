/* Zadanie 2 lista 4. Program formatuje plik wejściowy z kodem w języku C.
 * Po nawiasie otwierającym, dalsza część kodu zaczyna się w kolejnym wierszu,
 * wcięta o 4*zagnieżdżenie spacji. Nawias zamykający wypisywany jest w osobnym wierszu.
 * Po nawiasie zamykającym ciało funkcji wypisywany jest komentarz z jej deklaracją.
 * Program zakłada, że długość wiersza nie przekracza 1000 znaków.
 * Autor: Klaudia Weigel */

#include <stdio.h>

#define MAX_WIERSZ 1000 /* maksymalna długość wiersza */

/* wczytuje wiersz do tablicy i zwraca jego długość */
int wiersz(char* w) {
    int i, c;
    
    c=getchar();
    for (i=0;c!=EOF && c!='\n';i++) {
        w[i]=c;
        c=getchar();
    }
    if(c=='\n') {
        w[i]='\n';
        i++;
    }
    w[i]='\0';
    return i;
}

/* kopiuje tablicę */
void kopiuj(char* w, int dlw, char* cp) {
    int i;
    
    for (i=0;i<dlw;i++) {
        cp[i]=w[i];
    }
}

void formatuj() {
    int c, z, i, j, p; /* c-obecny znak, p-poprzedni znak, i-indeks w wierszu */
    int dlw, dlp; /* długości wiersza obecnego i poprzedniego */
    char nazwa[MAX_WIERSZ], w[MAX_WIERSZ], prev[MAX_WIERSZ];
    z=0; /* poziom zagnieżdżenia */
    dlw=wiersz(w);
    
    while (dlw>0 && z>=0) {
        i=0;
        c=w[i];
        
        /* formatuje obecny wiersz */
        while (c!='\0' && z>=0) {
            if(p=='\n') { /* nowy wiersz - wstawia odpowiednią ilość spacji */
                while (c==' ') c=w[++i];
                if(c!='}') for(j=0;j<4*z;j++) putchar(' ');
            }
            if(c=='{') { 
                z++;
                if(z==1) { /* sprawdza czy nazwa funkcji jest w tym czy poprzednim wieszu */
                    if(p=='\n') kopiuj(prev, dlp, nazwa);
                    else kopiuj(w, dlw, nazwa);
                }
                putchar(c);
                
                j=i+1; /* sprawdza czy po nawiasie jest znak \n ewentualnie poprzedzony spacjami */
                while (w[j]==' ') j++;
                if(w[j]=='\n') { i=j; c=w[i]; }
                else c='\n';
            }
            if(c=='}') {
                z--;
                if(p!='\n') putchar('\n');
                for(j=0;j<4*z;j++) putchar(' ');
                putchar(c);
                
                j=i+1;
                while (w[j]==' ') j++;
                if(w[j]=='\n') { i=j; c=w[i]; }
                else c='\n';
                
                if (z==0) {
                    printf(" // ");
                    for (j=0; nazwa[j]!=')';j++) {
                        putchar(nazwa[j]);
                    }
                    putchar(')');
                }
            }
            
            putchar(c);
            p=c;
            c=w[++i];
        }
        if(z<0) printf("Błąd: brakujące nawiasy.\n");
        dlp=dlw;
        kopiuj(w, dlw, prev);
        dlw=wiersz(w);
    }
    
}

int main(void) {
    formatuj();
    return 0;
}