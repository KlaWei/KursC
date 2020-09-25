/* Zadanie 1 lista 5. Program wczytuje liczby 16 bitowe w pętli 
 * i wypisuje reprezentowaną przez nie datę. Pierwsze 3 bity to dzień tygodnia,
 * kolejne 5 to dzień miesiąca, kolejne 4 miesiąc, ostatnie 4 to rok. 
 * Program sprawdza czy wpisana data jest poprawna. Wejście kończy koniec pliku lub 0.
 * Autor: Klaudia Weigel */

#include <stdio.h>
#include <limits.h>

typedef unsigned short TypDaty;

/* Zamienia bity od l do p włącznie (licząc od lewej strony) z 0 na 1 */
TypDaty ZamienBity(TypDaty d, int l, int p) {
    TypDaty pom = SHRT_MAX;
    pom=pom>>(l-1);
    pom=pom<<((l-1)+(sizeof(unsigned short)*8-p));
    pom=pom>>(sizeof(unsigned short)*8-p);
    
    return d|pom;
}

/* Sprawdza poprawność daty */
TypDaty BladDaty(TypDaty data) {
    TypDaty poprawnosc=0;
    TypDaty i, rok=0, dzienTyg=0, dzien=0, mies=0;
    int bladDzien=0;
    i=1;
    while (i<=4) {
        dzienTyg = dzienTyg + (data&i);
        i*=2;
    }
    data = data>>3;
    i=1;
    while (i<=16) {
        dzien = dzien + (data&i);
        i*=2;
    }
    data = data>>5;
    i=1;
    while (i<=8) {
        mies = mies + (data&i);
        i*=2;
    }
    data = data>>4;
    i=1;
    while (i<=8) {
        rok = rok + (data&i);
        i*=2;
    }
    if (dzienTyg==0) {
        poprawnosc = ZamienBity(poprawnosc, 1, 3);
    }
    if(dzien==0) bladDzien=1;
    else if(dzien>29 && mies==2) bladDzien=1;
    else if(dzien>30 && (mies==4 || mies==6 || mies==9 || mies==11)) bladDzien=1;
    if(bladDzien==1) {
        poprawnosc = ZamienBity(poprawnosc, 4, 8);
    }
    if(mies==0 || mies>12) {
        poprawnosc = ZamienBity(poprawnosc, 9, 12);
    }
    if(rok==0 || rok>12) {
        poprawnosc = ZamienBity(poprawnosc, 13, 16);
    }
    
    return poprawnosc;
}

void WypiszDate(TypDaty data) {
    char *DniTyg[] = {"pon", "wto", "sro", "czw", "pt", "sob", "nd"};
    char *Mies[] = {"sty", "lut", "mar", "kwie", "maj", "czerw", "lip", "sie", "wrz", "paz", "lis", "gru"};
    char *Rok[] = {"smoka", "weza", "konia", "owcy", "kozy", "psa", "malpy", "koguta", "swini", "szczura", "tygrysa", "krolika"};
    
    TypDaty i, rok=0, dzienTyg=0, dzien=0, mies=0;
    TypDaty p;
    
    p = BladDaty(data);
    if(p!=0) {
        printf("Niepoprawne pola:\n");
        i=1;
        if((p&1)==1) printf("-dzien tygodnia\n");
        p = p>>3;
        if((p&1)==1) printf("-dzien miesiaca\n");
        p = p>>5;
        if((p&1)==1) printf("-miesiac\n");
        p = p>>4;
        if((p&1)==1) printf("-rok\n");
        return;
    }
    
    i=1;
    while (i<=4) { /* wczytuje dzień tygodnia */
        dzienTyg = dzienTyg + (data&i);
        i*=2;
    }
    data = data>>3;
    
    i=1;
    while (i<=16) { /* wczytuje dzień miesiąca */
        dzien = dzien + (data&i);
        i*=2;
    }
    data = data>>5;
    
    i=1;
    while (i<=8) { /* wczytuje miesiąc */
        mies = mies + (data&i);
        i*=2;
    }
    data = data>>4;
    
    i=1;
    while (i<=8) { /* wczytuje rok */
        rok = rok + (data&i);
        i*=2;
    }
    data = data>>4;
    
    printf("%s, %d %s, rok %s(%d)\n", DniTyg[dzienTyg-1], dzien, Mies[mies-1], Rok[rok-1], rok);
}

int main(void) {
    TypDaty data=0;
    int c, koniec=0;
    
    c=getchar();
    while (c!=EOF && koniec==0) {
        if(c>='0' && c<='9') {
            while (c>='0' && c<='9') {
                data = data*10 + c-'0';
                c=getchar();
            }
            if(data==0) koniec=1;
            else {
                WypiszDate(data);
                data=0;
            }
        }
        if(koniec==0) c=getchar();
    }
    
    return 0;
}