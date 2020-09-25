/* Lista 10 zadanie 1. Kalkulator wykonany przy użyciu biblioteki gtk. Możliwe operacje
 * to mnożenie, dodawanie, odejmowanie, dzielenie, obliczanie sinusa lub cosinusa w trybie
 * szesnastkowym lub dziesiętnym. 
 * Autor: Klaudia Weigel */

#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <gtk/gtk.h>

struct przycisk {
    char *opis, *wyjscie;
    int posX, lenX, posY, lenY; /* pozycja przycisku */
    GtkWidget *widget;
}; typedef struct przycisk Przycisk;
Przycisk tab[] = {
       {"NumLock","",0,1,0,1,NULL}, {"/","/",1,1,0,1,NULL}, {"*","*",2,1,0,1,NULL}, {"-","-",3,1,0,1,NULL},
	   {"7","7",0,1,1,1,NULL}, {"8","8",1,1,1,1,NULL}, {"9","9",2,1,1,1,NULL},{"+","+",3,1,1,1,NULL},
	   {"4","4",0,1,2,1,NULL}, {"5","5",1,1,2,1,NULL}, {"6","6",2,1,2,1,NULL},
	   {"1","1",0,1,3,1,NULL}, {"2","2",1,1,3,1,NULL}, {"3","3",2,1,3,1,NULL}, {"Enter","\n",3,1,2,1,NULL},
	   {"0","0",0,2,4,1,NULL}, {".",".",2,1,4,1,NULL}, {"CE","CE",3,1,3,2,NULL}, {"Sin","Sin ",2,1,5,1,NULL}, 
       {"Radiany", "Radiany",0,2,5,1,NULL}, {"Tryb10","Tryb10",0,2,6,1,NULL}, {"Cos","Cos ",3,1,5,1,NULL}
};

Przycisk tab16[] = {{"A","A",0,1,7,1,NULL}, {"B","B",1,1,7,1,NULL}, {"C","C",2,1,6,1,NULL},{"D","D",3,1,6,1,NULL},
         {"E","E",2,1,7,1,NULL}, {"F","F",3,1,7,1,NULL}};

int stopnie=1;
int tryb16=1;
static GtkWidget *text;

/* Funkcja zamieniająca liczbę zmiennoprzecinkową z systemu dziesiętnego
 * na szestnastkowy. Wynik zapisywany jest jako tablica char */
void dec_to_hex(int calk, double ulam, int n, char *wynik) {
    char calkowita[n];
    char hex[16]={'0', '1', '2', '3', '4', '5', '6', '7', '8',
       '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    int liczba;
    int i, iw=1, iw2=0;
    for (i=0;i<n;i++) {
        wynik[i]='0';
    }
    calkowita[0]=hex[calk%16];
    calk=calk/16;
    while (calk>0) { /* zamienia część całkowitą liczby na system 16 */
        liczba=calk%16;
        calkowita[iw]=hex[liczba];
        calk=calk/16;
        iw++;
    }
    for (i=iw-1;i>=0;i--) {
        wynik[iw2]=calkowita[i];
        iw2++;
    }
    wynik[iw2]='.';
    for (i=iw2+1;i<n;i++) {
        ulam=ulam*16;
        liczba=(int)ulam;
        ulam=ulam-liczba;
        wynik[i]=hex[liczba];
        
    }
}

double obliczWynik(double l1, double l2, char op) {
    double l3;
    switch (op) {
        case '+':
            l3=l1+l2;
            break;
        case '*':
            l3=l1*l2;
            break;
        case '/':
            if(l2!=0) l3=l1/l2;
            else l3=0;
            break;
        case '-':
            l3=l1-l2;
            break;
        case 's':
            if(stopnie==1) l3=sin((M_PI/180)*l2);
            else l3=sin(l2);
            break;
        case 'c':
            if(stopnie==1) l3=cos((M_PI/180)*l2);
            else l3=cos(l2);
            break;
    }
    return l3;
}

/* Oblicza wynik w trybie 16 */
void calc16(GtkWidget *text) {
    char *wyrazenie=(char*)gtk_entry_get_text(GTK_ENTRY(text));
    int n=gtk_entry_get_text_length(GTK_ENTRY(text));
    double l1=0, l2=0, l3;
    int i, ia=2, ib=2, znak=0;
    char a[n+2], b[n+2], c[n+2], *endptA, *endptB, op='#';
    a[0]='0'; a[1]='x'; b[0]='0'; b[1]='x';
    
    for (i=2;i<n+2;i++) {
        a[i]='0'; b[i]='0';
    }
    
    for (i=0;i<n;i++) {
        if(wyrazenie[i]=='-' && znak==0) znak=-1;
        else if(op=='#' && (('0'<=wyrazenie[i] && wyrazenie[i]<='9') || (wyrazenie[i]>='A' && wyrazenie[i]<='F') ||
           wyrazenie[i]=='.')) {
            if(i<n-1 && wyrazenie[i+1]=='o');
            else {
                a[ia]=wyrazenie[i]; ia++;
                if(znak==0) znak=1;
            }
        }
        else if (op!='#' && (('0'<=wyrazenie[i] && wyrazenie[i]<='9') || (wyrazenie[i]>='A' && wyrazenie[i]<='F') ||
            wyrazenie[i]=='.')) {
            if(i<n-1 && wyrazenie[i+1]=='o');
            else {
                b[ib]=wyrazenie[i]; ib++;
            }
        }
        else if(i<n-2 && (wyrazenie[i]=='S' && wyrazenie[i+1]=='i' && wyrazenie[i+2]=='n')) op='s';
        else if(wyrazenie[i]=='*' || wyrazenie[i]=='-' || wyrazenie[i]=='+' || wyrazenie[i]=='/') op=wyrazenie[i];
        if(i<n-2 && (wyrazenie[i]=='C' && wyrazenie[i+1]=='o' && wyrazenie[i+2]=='s')) op='c';
    }
    a[ia]='.';
    b[ib]='.';
    
    l1=strtod(a, &endptA);
    l1=l1*znak;
    l2=strtod(b, &endptB);
    l3=obliczWynik(l1, l2, op);
    
    gint tmp_pos = gtk_entry_get_text_length(GTK_ENTRY(text));
    gtk_editable_delete_text(GTK_EDITABLE(text), 0, tmp_pos);
    tmp_pos=0;
    if(l3<0) {
        l3=l3*(-1);
        gtk_editable_insert_text(GTK_EDITABLE(text), "-", -1, &tmp_pos);
        tmp_pos=1;
    }
    dec_to_hex((int)l3, l3-(int)l3, n+2, c);
    gtk_editable_insert_text(GTK_EDITABLE(text), (gchar*)c, n+2, &tmp_pos);
}

void calc(GtkWidget *text) {
    if(tryb16==1) {
        calc16(text);
        return;
    }
    printf("tu");
    char *wyrazenie=(char*)gtk_entry_get_text(GTK_ENTRY(text));
    int n=gtk_entry_get_text_length(GTK_ENTRY(text));
    int i, ia=0, ib=0, znak=0;
    double l1, l2, l3;
    
    char a[n], b[n], c[n]; /* tablice na pierwszą i drugą liczbę oraz wynik */
    for (i=0;i<n;i++) {
        a[i]='0'; b[i]='0';
    }
    char op='#';
    for (i=0;i<n;i++) {
        if(wyrazenie[i]=='-' && znak==0) znak=-1; /* sprawdza czy pierwsza liczba jest ujemna */
        else if(op=='#' && (('0'<=wyrazenie[i] && wyrazenie[i]<='9') || wyrazenie[i]=='.')) {
            a[ia]=wyrazenie[i]; ia++;
            if(znak==0) znak=1;
        }
        else if (op!='#' && (('0'<=wyrazenie[i] && wyrazenie[i]<='9') || wyrazenie[i]=='.')) {
            b[ib]=wyrazenie[i]; ib++;
        }
        else if(i<n-2 && (wyrazenie[i]=='S' && wyrazenie[i+1]=='i' && wyrazenie[i+2]=='n')) op='s';
        else if(i<n-2 && (wyrazenie[i]=='C' && wyrazenie[i+1]=='o' && wyrazenie[i+2]=='s')) op='c';
        else if((wyrazenie[i]=='*' || wyrazenie[i]=='-' || wyrazenie[i]=='+' || wyrazenie[i]=='/')) op=wyrazenie[i];
    }
    a[ia]='.'; /* koniec liczby */
    b[ib]='.';
    l1=atof(a);
    l1=l1*znak;
    l2=atof(b);
    printf("l1=%lf, l2=%lf, op=%c\n", l1, l2, op);
    
    l3=obliczWynik(l1, l2, op);
    sprintf(c, "%lf", l3); /* zamienia l3 na tablicę znaków */
    gint tmp_pos = gtk_entry_get_text_length(GTK_ENTRY(text));
    gtk_editable_delete_text(GTK_EDITABLE(text), 0, tmp_pos);
    tmp_pos=0;
    gtk_editable_insert_text(GTK_EDITABLE(text), (gchar*)c, -1, &tmp_pos); /* drukuje wynik */
}


static void wyjscie_przyciskiem(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}


static void wypisz_wprowadzony_tekst( GtkWidget *widget, GtkWidget *text) {
    calc(text);
    const gchar *wejscie;
    wejscie = gtk_entry_get_text (GTK_ENTRY (text));
    printf("GTK-test wprowadzono: %s\n", wejscie);
}

/* Podejmuje odpowiednie działanie jeśli przycisk został wciśnięty */
static void przycisk(GtkWidget *widget, gpointer data) {
    gint tmp_pos = gtk_entry_get_text_length(GTK_ENTRY(text));
    
    if(strcmp((gchar*)data, "CE")==0) { /* usuwa tekst w polu wejściowym */
        gint tmp_pos = gtk_entry_get_text_length(GTK_ENTRY(text));
        gtk_editable_delete_text(GTK_EDITABLE(text), 0, tmp_pos);
    }
    else if(strcmp((gchar*)data, "Stopnie")==0) { /* zamienia napis na przycisku */
        tab[19].opis="Radiany";
        tab[19].wyjscie="Radiany";
        
        gtk_button_set_label(GTK_BUTTON(tab[19].widget), "Radiany");
        g_signal_connect(G_OBJECT(tab[19].widget), "clicked", G_CALLBACK(przycisk), (gpointer)tab[19].wyjscie);
        
        stopnie=1;
    }
    else if(strcmp((gchar*)data, "Radiany")==0) {
        tab[19].opis="Stopnie";
        tab[19].wyjscie="Stopnie";
        
        gtk_button_set_label(GTK_BUTTON(tab[19].widget), "Stopnie");
        g_signal_connect(G_OBJECT(tab[19].widget), "clicked", G_CALLBACK(przycisk), (gpointer)tab[19].wyjscie);
        
        stopnie=0;
    }
    else if (strcmp((gchar*)data, "Tryb10")==0) {
        int i;
        tryb16=0;
        int n=sizeof(tab16)/sizeof(Przycisk);
        tab[20].opis="Tryb16";
        tab[20].wyjscie="Tryb16";
        gtk_button_set_label(GTK_BUTTON(tab[20].widget), "Tryb16");
        g_signal_connect(G_OBJECT(tab[20].widget), "clicked", G_CALLBACK(przycisk), (gpointer)tab[20].wyjscie);
        for (i=0;i<n;i++) {
            gtk_widget_hide(tab16[i].widget);
        }
    }
    else if(strcmp((gchar*)data, "Tryb16")==0) { /* pokazuje przyciski do obliczeń szesnastkowych */
        int i;
        int n=sizeof(tab16)/sizeof(Przycisk);
        tryb16=1;
        tab[20].opis="Tryb10";
        tab[20].wyjscie="Tryb10";
        gtk_button_set_label(GTK_BUTTON(tab[20].widget), "Tryb10");
        g_signal_connect(G_OBJECT(tab[20].widget), "clicked", G_CALLBACK(przycisk), (gpointer)tab[20].wyjscie);
        for (i=0;i<n;i++) {
            gtk_widget_show(tab16[i].widget);
        }
    }
    else if(strcmp((gchar*)data, "\n") == 0) calc(text); /* Enter oblicza wynik */
    else 
        gtk_editable_insert_text(GTK_EDITABLE(text), (gchar*)data, -1, &tmp_pos);
}

/* Wstawia przyciski do kalkulatora */
void wstaw_przyciski(GtkWidget *grid) {
    int n=sizeof(tab)/sizeof(Przycisk), i;
    int m=sizeof(tab16)/sizeof(Przycisk);
    
    for (i=0;i<n;i++) {
        tab[i].widget = gtk_button_new_with_label(tab[i].opis);
        g_signal_connect(G_OBJECT(tab[i].widget), "clicked", G_CALLBACK(przycisk), (gpointer)tab[i].wyjscie);
        gtk_grid_attach(GTK_GRID(grid), tab[i].widget, tab[i].posX, tab[i].posY, tab[i].lenX, tab[i].lenY);
    }
    for (i=0;i<m;i++) {
        tab16[i].widget = gtk_button_new_with_label(tab16[i].opis);
        gtk_widget_hide (tab16[i].widget);
        g_signal_connect(G_OBJECT(tab16[i].widget), "clicked", G_CALLBACK(przycisk), (gpointer)tab16[i].wyjscie);
        gtk_widget_hide (tab16[i].widget);
        gtk_grid_attach(GTK_GRID(grid), tab16[i].widget, tab16[i].posX, tab16[i].posY, tab16[i].lenX, tab16[i].lenY);
        gtk_widget_show(tab16[i].widget);
        gtk_widget_hide (tab16[i].widget);
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(window),"GTK - panel numeryczny");
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    g_signal_connect(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *box1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    gtk_container_add(GTK_CONTAINER(window), box1);

    GtkWidget *button;
    text = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(text), 50);
    g_signal_connect(G_OBJECT(text), "activate",
		      G_CALLBACK(wypisz_wprowadzony_tekst),
		     (gpointer) text);
    gtk_entry_set_text(GTK_ENTRY(text), "Wprowadz");
    gint tmp_pos = gtk_entry_get_text_length(GTK_ENTRY(text));
    gtk_editable_insert_text(GTK_EDITABLE(text), " jakis tekst", -1, &tmp_pos);
    gtk_editable_select_region(GTK_EDITABLE(text), 0, gtk_entry_get_text_length(GTK_ENTRY(text)));
    gtk_box_pack_start(GTK_BOX(box1), text, TRUE, TRUE, 0);
    
    tmp_pos = gtk_entry_get_text_length(GTK_ENTRY(text));
    gtk_editable_delete_text(GTK_EDITABLE(text), 0, tmp_pos);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_box_pack_start(GTK_BOX(box1), grid, TRUE, TRUE, 0);

    button=gtk_label_new(tab[0].opis);	
    gtk_grid_attach(GTK_GRID(grid), button, tab[0].posX, tab[0].posY, tab[0].lenX, tab[0].lenY);
    
    wstaw_przyciski(grid);

    GtkWidget *box2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    button = gtk_button_new_with_label("Koniec");
    g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(wyjscie_przyciskiem), NULL);
    gtk_box_pack_start(GTK_BOX(box2), button, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box1), box2, TRUE, TRUE, 0);

    gtk_widget_show_all(window);  
    gtk_main();

    return 0;
}
