/* Program wczytuje z wejścia wyrażenie arytmetyczne
 * w systemie ósemkowym z jednym operatorem: +,-,*,!(silnia). 
 * Ignoruje niedopuszczalne znaki przed wyrażeniem
 * oraz spacje pomiędzy liczbami i operatorem. 
 * Wyrażanie może być poprzedzone znakiem + lub -, po
 * którym wczytywana jest pierwsza liczba(ciąg cyfr mniejszych od 8 
 * zakończonych kropką) operator i druga liczba, jeśli operatorem
 * nie jest silnia. Po znaku nowej linii program wypisuje wynik
 * działania i wczytuje kolejny wiersz dopóki pierwszym
 * znakiem wiersza nie jest 0.

 * Autor: Klaudia Weigel */

#include <stdio.h>

/* wypisuje liczbę x w podanej bazie */
void WriteNum(int baza, int x) {
	if(x<0) {
		putchar('-');
		x*=-1;
	}
	if(x<baza) putchar((x%baza)+'0');
	else {
		WriteNum(baza, x/baza);
		putchar((x%baza)+'0');
	}
}

int silnia(int n) {
	if(n==0 || n==1) return 1;
	else return n*silnia(n-1);
}

int oblicz(int n, int m, int op) {
	switch (op) {
		case '!':
			return silnia(n);
			break;
		case '+':
			return n+m;
			break;
		case '-':
			return n-m;
			break;
		case '*':
			return n*m;
			break;
		case '/':
			if(m==0) return 0;
			else return n/m;
			break;
	}
	return 0;
}

int ReadNum(int baza, int* koniec) {
	int c, liczba, liczba2, operator, znak;
	char b;
	b = '0' + baza;
	liczba=0; liczba2=0;
	znak=1;
	
	c=getchar();
	if(c=='0') {
		(*koniec)=1;
		return 0;
	}
	
	while ((c<'0' || c>=b) && c!='+' && c!='-') c=getchar(); /* pomija niedopuszczalne znaki*/
	
	if(c=='+' || c=='-') {
		if(c=='-') znak = -1;
		c=getchar();
	}
	
	while (c!='.') {               /* czyta pierwszą liczbę */
		liczba = liczba*baza + (c-'0');
		c = getchar();
	}
	c=getchar();
	while (c==' ') c = getchar(); /* pomija spacje */
	operator = c;
	
	if(operator != '!') {  /* czyta drugą liczbę, jeśli działanie to nie silnia */
		c=getchar();
		while (c==' ') c = getchar();
		while (c!='.') {
			liczba2 = liczba2*baza + (c-'0');
			c = getchar();
		}
	}
	
	c=getchar();
	while (c!='\n') c=getchar();
	
	return znak*oblicz(liczba, liczba2, operator);
}

int main(void) {
	int n, koniec;
	koniec=0;
	
	n=ReadNum(8, &koniec);
	while (koniec==0) {
		WriteNum(8, n);
		putchar('\n');
		n=ReadNum(8, &koniec);
	}
	
	return 0;
}
