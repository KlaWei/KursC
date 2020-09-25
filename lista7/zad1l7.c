/* Zadanie 1 lista 7. Program wczytuje współrzedne ze standardowego wejścia
 * i zapisuje je do listy.
 * Autor: Klaudia Weigel */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ptList {
    struct ptList *nast;
    float x;
    float y;
    float z;
    char nazwa[36];
}; typedef struct ptList PtList;

void wstaw(PtList **head, PtList **curr, float x, float y, float z, char* nazwa, int n) {
    PtList *a = (PtList*)malloc(sizeof(PtList));
    a->x = x;
    a->y = y;
    a->z = z;
    a->nast = NULL;
    int i;

    for(i=0; i<n; i++) {
        a->nazwa[i]=nazwa[i];
    }

    if((*head)==NULL) {
        (*head) = a;
        (*curr) = a;
        return;
    }
    (*curr)->nast = a;
    (*curr)=a;
}

void drukujListe(PtList *head) {
    PtList *pom=head;

    while(pom!=NULL) {
        printf("%f %f %f %s\n", pom->x, pom->y, pom->z, pom->nazwa);
        pom=pom->nast;
    }
}

void drukujElement(PtList *a) {
    printf("%f %f %f %s\n", a->x, a->y, a->z, a->nazwa);
}

int main() {
    PtList *head, *curr;
    head=NULL;
    curr=NULL;
    float x, y, z;
    char nazwa[36];
    int c, koniec, i, iloscEl;
    iloscEl=0;
    koniec=0;
    i=0;

    while(koniec==0) {
        if(scanf("%f %f %f", &x, &y, &z)==EOF) break;
        c=getchar();
        i=0;
        while(c==' ') c=getchar();
        while(c!='\n' && i<36 && c!=EOF) {
            nazwa[i++]=c;
            c=getchar();
        }
        nazwa[i]='\0';
        if(i>=6) {
            if(nazwa[0]=='K' && nazwa[1]=='O'&& nazwa[2]=='N' && nazwa[3]=='I' && nazwa[4]=='E' && nazwa[5]=='C') break;
        }

        wstaw(&head, &curr, x, y, z, nazwa, i);
        iloscEl++;
        if(c==EOF) break;
    }
    if(iloscEl>0) {
        printf("Pierwszy element: ");
        drukujElement(head);
        printf("Ostatni element: ");
        drukujElement(curr);
        printf("Wydrukowac cala liste? ");
        if((c=getchar())=='t') drukujListe(head);
    }

    return 0;
}

