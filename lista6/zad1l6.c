/* Zadanie 1 lista 6. Sprawdza czy podane na wejściu słowa są
 * palindromami. Dopuszczalna długość słów to 80 znaków.
 * Autor: Klaudia Weigel */

#include <stdio.h>
#include <stdlib.h>

void revers(char *t) {
    char *p;
    char *k;
    char m;
    p=t; k=t;
    while(*k != '\0') k++;
    k--;

    while(p<k) {
        m = *p;
        *p = *k;
        *k = m;
        p++;
        k--;
    }

    p=t;
    printf("\nrewers: ");
    while(*p != '\0')  {
        printf("%c", *p);
        p++;
    }
    printf("\n");
}

int palindrom(char *t) {
    int palindrom;
    palindrom=1;
    char *p; char *k;
    p=t;
    k=t;
    while(*k != '\0') k++;
    k--;

    while(p<k && palindrom==1) {
        if((*p)!=(*k)) palindrom=0;
        p++;
        k--;
    }
    return palindrom;
}

int main(void) {
    int c, i;
    i=0;
    char *p;
    char *s = malloc(sizeof(char)*80);
    char *a=s;

    c=getchar();
    while(c!=EOF) {
        a=s;
        i=0;
        while(((c>='a' && c<='z') || (c>='A' && c<='Z')) && i<80) {
            *a=c; a++;
            c=getchar();
            i++;
        }
        *a='\0';
        c=palindrom(s);
        revers(s);
        if(c==1) {
            printf("PALINDROM: ");
            p=s;
            while(*p != '\0') {
                printf("%c", *p);
                p++;
            }
            printf("\n");

        }
        c=getchar();
    }

    c=palindrom(s);

    return 0;
}
