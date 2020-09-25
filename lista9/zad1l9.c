/* Zadanie 1 lista 9. Program dla każdej liczby z kwadratu
 * [-1, 1]x[-1, 1] iteruje 200 razy przekształcenie zn=zn-1*zn-1 - c.
 * Jeśli kwadrat normy jest mniejszy od 4 to punkt jest drukowany.
 * Jako dwa pierwsze argumenty wywołania można podać rozdzielczość.
 * Jako kolejne dwa można wpisać wartość stałej c, część reczywista i
 * urojona. Domyślna rozdzielczość to 40x20, c=0.1+0.83i. 
 * Autor: Klaudia Weigel */

#include <stdio.h>
#include <stdlib.h>

struct zespolona {
    double real;
    double imag;
}; typedef struct zespolona Zespolona;

Zespolona dodaj(Zespolona x, Zespolona y) {
    Zespolona z;
    z.real=x.real+y.real;
    z.imag=x.imag+y.imag;
    return z;
}

Zespolona pomnoz(Zespolona x, Zespolona y) {
    Zespolona z;
    z.real=x.real*y.real - x.imag*y.imag;
    z.imag=x.real*y.imag + x.imag*y.real;
    return z;
}

Zespolona odejmij(Zespolona x, Zespolona y) {
    Zespolona z;
    z.real=x.real-y.real;
    z.imag=x.imag-y.imag;
    return z;
}

double kwNormy(Zespolona z) {
    return z.imag*z.imag + z.real*z.real;
}

void fraktal(int szer, int wys, Zespolona c) {
    Zespolona z, z1;
    double xmax, xmin, ymax, ymin;
    int i, j, iter;
    xmax=1.0; ymax=1.0;
    xmin=-1.0; ymin=-1.0;
    
    z.real=xmin; /*punkt początkowy*/
    z.imag=ymax;
    
    double szerPix=(xmax-xmin)/szer;
    double wysPix=(ymax-ymin)/wys;
    
    for (i=0;i<wys;i++) {
        z.real=xmin;
        for (j=0;j<szer;j++) {
            iter=0;
            z1.imag=z.imag;
            z1.real=z.real;
            while (iter<200 && kwNormy(z1)<4) {
                z1=odejmij(pomnoz(z1, z1), c);
                iter++;
            }
            if(iter==200) printf("O");
            else printf(" ");
            
            z.real+=szerPix;
        }
        printf("\n");
        z.imag-=wysPix;
    }
}

int main(int argc, char *argv[]) {
    int szer=40, wys=20;
    Zespolona c;
    c.imag=0.83;
    c.real=0.1;
    if (argc>2) {
        szer=atoi(argv[1]);
        wys=atoi(argv[2]);
    }
    if (argc>4) {
        c.real=atof(argv[3]);
        c.imag=atof(argv[4]);
    }
    
    fraktal(szer, wys, c);
    
    return 0;
}