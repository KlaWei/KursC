/* Zadanie 2 lista 8. Program drukuje spiralę prawoskrętną wymiaru
 * nxn, gdzie n jest liczbą podaną jako pierwszy argument wywołania.
 * Jeśli podany jest drugi argument z nazwą pliku, program zapisuje obrazek
 * w formacie PPN w podanym pliku. Jeśli liczba w spirali jest pierwsza
 * wypisywany jest piksel żółty, jeśli nie-niebieski. 
 * Autor: Klaudia Weigel */

#include <stdio.h>
#include <stdlib.h>

/* Wypisuje k-ty wiersz spirali rozmiaru nxn */
void wierszSpirali(int n, int k) {
    int i;
    if (n%2==0) {
        if (k==n) {
            for (i=n*n;i>n*n-n;i--) {
                printf("%4d", i);
            }
        }
        else {
            wierszSpirali(n-1, k);
            printf("%4d", n*n-2*n+k+1);
        }
    }
    if (n%2!=0) {
        if (k==1) {
            for (i=n*n-n+1;i<=n*n;i++) {
                printf("%4d", i);
            }
        }
        else {
            printf("%4d", n*n-n-k+2);
            wierszSpirali(n-1, k-1);
        }
    }
}

int czyPierwsza(int n) {
    int i, p;
    p=1;
    for (i=2;i<n/2 && p==1;i++) {
        if(n%i==0) p=0;
    }
    return p;
}

void wypiszZolty(FILE *fp) {
    fprintf(fp, "255 255 0\n");
}

void wypiszNiebieski(FILE *fp) {
    fprintf(fp, "0 0 255\n");
}

void wierszSpiraliPlik(int n, int k, FILE* fp) {
    int i;
    if (n%2==0) {
        if (k==n) {
            for (i=n*n;i>n*n-n;i--) {
                if(czyPierwsza(i)==1) wypiszZolty(fp);
                else wypiszNiebieski(fp);
            }
        }
        else {
            wierszSpiraliPlik(n-1, k, fp);
            if(czyPierwsza(n*n-2*n+k+1)==1) wypiszZolty(fp);
            else wypiszNiebieski(fp);
        }
    }
    if (n%2!=0) {
        if (k==1) {
            for (i=n*n-n+1;i<=n*n;i++) {
                if(czyPierwsza(i)==1) wypiszZolty(fp);
                else wypiszNiebieski(fp);
            }
        }
        else {
            if(czyPierwsza(n*n-n-k+2)==1) wypiszZolty(fp);
            else wypiszNiebieski(fp);
            wierszSpiraliPlik(n-1, k-1, fp);
        }
    }
}

int main(int argc, char *argv[]) {
    int n,i;
    FILE *fp;
    fp=NULL;
    if (argc>1) n=atoi(argv[1]);
    else n=17;
    for (i=1;i<=n;i++) {
        wierszSpirali(n, i);
        printf("\n");
    }
    if(argc>2) {
        fp=fopen(argv[2], "w");
        if(fp==NULL) {
            printf("Blad wczytywania pliku\n");
            return 1;
        }
        fprintf(fp, "P3 %d %d 255\n", n, n);
        for (i=1;i<=n;i++) {
            wierszSpiraliPlik(n, i, fp);
        }
    }
    
    fclose(fp);
    
    return 0;
}