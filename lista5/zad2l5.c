/* Zadanie 2 lista 5. Program wczytuje w pętli pary dat w postaci czwórek liczb
 * w kolejności dzień tygodnia, dzień miesiąca, miesiąc, rok.
 * Na wyjściu wypisuje daty wraz z ich liczbowymi reprezentacjami zapisanymi na 16 bitach,
 * oraz odległość pomiędzy podanymi datami. Jeśli daty są niepoprawne, wypisuje błędne pola.
 * Wejście kończy podanie dnia tygodnia 0. 
 * Autor: Klaudia Weigel */

#include <stdio.h>
#include <limits.h>

typedef unsigned short TypDaty;

struct data {
    TypDaty liczba;
    short rok;
    short mies;
    short dzienTyg;
    short dzienMies;
    int liczbaDni;
}; typedef struct data Data;

/* Oblicza liczbową reprezentację daty i zwraca ją jako wynik */
TypDaty ZrobDate(short dt, short d, short m, short rok) {
    TypDaty data;
    data=0;
    data = data|rok;
    data = data<<4;
    data = data|m;
    data = data<<5;
    data = data|d;
    data = data<<3;
    data = data|dt;
    
    return data;
}

/* Oblicza ilość dni które upłynęły do danej daty */
int IloscDni(Data d) {
    int i, ilosc;
    ilosc=0;
    
    for (i=1;i<d.rok;i++) {
        if(i%4==0) ilosc+=366;
        else ilosc+=365;
    }
    switch (d.mies) {
        case 1: break;
        case 2: ilosc+=31; break;
        case 3: ilosc+=59; break;
        case 4: ilosc+=90; break;
        case 5: ilosc+=120; break;
        case 6: ilosc+=151; break;
        case 7: ilosc+=181; break;
        case 8: ilosc+=212; break;
        case 9: ilosc+=243; break;
        case 10: ilosc+=273; break;
        case 11: ilosc+=304; break;
        case 12: ilosc+=335; break;
    }
    if((d.rok%4)==0 && d.mies>2) ilosc++;
    ilosc+=d.dzienMies;
    
    return ilosc;
}

/* Oblicza odległość pomiędzy dwoma datami w dniach */
int Odleglosc(Data d1, Data d2) {
    int odl;
    odl=0;
    d1.liczbaDni = IloscDni(d1);
    d2.liczbaDni = IloscDni(d2);
    
    if(d1.liczbaDni>d2.liczbaDni) return d1.liczbaDni-d2.liczbaDni;
    else return d2.liczbaDni-d1.liczbaDni;
    
}

/* Zamienia bity od l do p włącznie (licząc od lewej strony) z 0 na 1 */
TypDaty ZamienBity(TypDaty d, int l, int p) {
    TypDaty pom = SHRT_MAX;
    pom=pom>>(l-1);
    pom=pom<<((l-1)+(sizeof(unsigned short)*8-p));
    pom=pom>>(sizeof(unsigned short)*8-p);
    
    return d|pom;
}

/* Sprawdza poprawność daty */
TypDaty BladDaty(Data d) {
    int bladDzien;
    bladDzien=0;
    TypDaty poprawnosc=0;
    
    if (d.dzienTyg==0) {
        poprawnosc = ZamienBity(poprawnosc, 1, 3);
    }
    if(d.dzienMies==0) bladDzien=1;
    else if(d.dzienMies>28 && d.mies==2 && (d.rok%4)!=0) bladDzien=1;
    else if(d.dzienMies>29 && d.mies==2 && (d.rok%4)==0) bladDzien=1;
    else if(d.dzienMies>30 && (d.mies==4 || d.mies==6 || d.mies==9 || d.mies==11)) bladDzien=1;
    if(bladDzien==1) {
        poprawnosc = ZamienBity(poprawnosc, 4, 8);
    }
    if(d.mies==0 || d.mies>12) {
        poprawnosc = ZamienBity(poprawnosc, 9, 12);
    }
    if(d.rok==0 || d.rok>12) {
        poprawnosc = ZamienBity(poprawnosc, 13, 16);
    }
    
    return poprawnosc;
}

void WypiszDate(Data d) {
    char *DniTyg[] = {"pon", "wto", "sro", "czw", "pt", "sob", "nd"};
    char *Mies[] = {"sty", "lut", "mar", "kwie", "maj", "czerw", "lip", "sie", "wrz", "paz", "lis", "gru"};
    char *Rok[] = {"smoka", "weza", "konia", "owcy", "kozy", "psa", "malpy", "koguta", "swini", "szczura", "tygrysa", "krolika"};
    
    printf("%s, %d %s, rok %s(%d), ", DniTyg[d.dzienTyg-1], d.dzienMies, Mies[d.mies-1], Rok[d.rok-1], d.rok);
    printf("reprezentacja liczbowa: %d\n", d.liczba);
}

void SprawdzIWypisz(Data d1, Data d2) {
    TypDaty p1, p2;
    short blad1, blad2;
    blad1=0; blad2=0;
    d1.liczba = ZrobDate(d1.dzienTyg, d1.dzienMies, d1.mies, d1.rok);
    d2.liczba = ZrobDate(d2.dzienTyg, d2.dzienMies, d2.mies, d2.rok);
    
    p1=BladDaty(d1);
    if(p1!=0) {
        blad1=1;
        printf("Niepoprawne pola w pierwszej dacie:\n");
        if((p1&1)==1) printf("-dzien tygodnia\n");
        p1 = p1>>3;
        if((p1&1)==1) printf("-dzien miesiaca\n");
        p1 = p1>>5;
        if((p1&1)==1) printf("-miesiac\n");
        p1 = p1>>4;
        if((p1&1)==1) printf("-rok\n");
    }
    
    p2=BladDaty(d2);
    if(p2!=0) {
        blad2=1;
        printf("Niepoprawne pola w drugiej dacie:\n");
        if((p2&1)==1) printf("-dzien tygodnia\n");
        p2 = p2>>3;
        if((p2&1)==1) printf("-dzien miesiaca\n");
        p2 = p2>>5;
        if((p2&1)==1) printf("-miesiac\n");
        p2 = p2>>4;
        if((p2&1)==1) printf("-rok\n");
    }
    
    if(blad1==0) {
        printf("Pierwsza data: ");
        WypiszDate(d1);
    }
    if(blad2==0) {
        printf("Druga data: ");
        WypiszDate(d2);
    }
    
    if(blad1==0 && blad2==0) printf("Ilosc dni pomiedzy datami: %d\n", Odleglosc(d1, d2));
}

int main(void) {
    short dt1, dzien1, m1, r1;
    short dt2, dzien2, m2, r2;
    Data data1, data2;
    
    /* wczytuje daty i sprawdza zakres liczb */
    while (1) {
        scanf("%hd", &dt1);
        if(dt1==0) break;
        scanf("%hd %hd %hd", &dzien1, &m1, &r1);
        scanf("%hd", &dt2);
        if(dt2==0) break;
        scanf("%hd %hd %hd", &dzien2, &m2, &r2);
        
        if(dt1>0 && dt1<=7) data1.dzienTyg=dt1;
        else data1.dzienTyg=0;
        if(dzien1>0 && dzien1<=31) data1.dzienMies=dzien1;
        else data1.dzienMies=0;
        if(m1>0 && m1<=12) data1.mies=m1;
        else data1.mies=0;
        if(r1>0 && r1<=12) data1.rok=r1;
        else data1.rok=0;
            
        if(dt2>0 && dt2<=7) data2.dzienTyg=dt2;
        else data2.dzienTyg=0;
        if(dzien2>0 && dzien2<=31) data2.dzienMies=dzien2;
        else data2.dzienMies=0;
        if(m2>0 && m2<=12) data2.mies=m2;
        else data2.mies=0;
        if(r2>0 && r2<=12) data2.rok=r2;
        else data2.rok=0;
        SprawdzIWypisz(data1, data2);
    }
    
    return 0;
}