/* Pawel Masluch, nr albumu 262955, projekt 2.2 */

#include<stdio.h>
#include<stdlib.h>


const int MAX_N = 5; /* maksymalna liczba rownan */


double det(int n, int w, int * stare_kolumny, double ** A) /* Obliczenie wyznacznika za pomoca rozwiniecia Laplaca ; zalozenie: rozwijamy wzgledem (najwyzszego) wiersza nr w */
{
	/* Znaczenie ponizszych zmiennych omowione w dalszej czesci funkcji */
	
	int i, j, k, znak; 
	int * nowe_kolumny;
	double wyn;
	
	
  	if( n == 1 ) /* warunek brzegowy */
	{
		return A[w][ stare_kolumny[0] ]; /* zwracamy jedyny element macierzy A */
	}
	else
  	{
	  	nowe_kolumny = (int *) malloc( ( n - 1 ) * sizeof( *nowe_kolumny ) ); /* nowa tablica z numerami kolumn */
	
	    wyn = 0; /* wynikowy wyznacznik - poczatkowo wyznacznik wynosi 0 */
	    
		znak = 1; /* ( minus jedynka ) w odpowiedniej potedze - poczatkowo mamy wartosc 1 */
	
	
	    for(i=0; i<=n-1; ++i) /* liczymy wyznacznik */
	    {
			k = 0;
	
		    for(j=0; j<=n-2; ++j) /* wypelniamy tablice nowe_kolumny */
		    {
				if(k == i) /* ignorujemy i-ta kolumne */
				{
					k++;
				}
				
		        nowe_kolumny[j] = stare_kolumny[ k++ ]; /* poza i-ta kolumna reszta numerow kolumn trafi do tablicy nowe_kolumny */
		    }
		
		
		    wyn += znak * A[w][ stare_kolumny[i] ] * det( n - 1, w + 1, nowe_kolumny, A ); /* aktualizacja wyniku */
		
		    znak = -znak; /* w kolejnym obrocie petli mamy zmiane znaku */
	
	    }
	
	    free( nowe_kolumny ); /* zwalniamy pamiec */
	
	    return wyn; /* wynikowy wyznacznik */
	}
}


void podmiana(double ** A, int j, double * b, int n) /* podmiana tablicy b oraz kolumny macierzy A o numerze j */
{
	double pom;
	
	int i;
	
	for(i=0; i<=n-1; ++i) /* zamiana elementow */
	{
		pom = A[i][j];
		
		A[i][j] = b[i];
		
		b[i] = pom;
	}
}


int Get_Int(int a, int b) /* Wczytanie liczby calkowitej z zakresu [a,b] */
{
	int r; /* to chcemy wczytac */
	
	while( 1 )
	{
		if( scanf( "%d", &r ) == 1 ) /* jesli cos wczytalismy */
		{
			if( getchar() != '\n' ) /* jesli mamy inne znaki niz cyfry */
			{
				printf( "Podaj liczbe calkowita z zakresu [%d,%d]: ", a, b );
				
				while( getchar() != '\n' );
				
				continue;
			}
			
			if( r >= a  &&  r <= b ) /* mamy poprawne wejscie */
			{
				break;
			}
			else /* jestesmy poza przedzialem */
			{
				printf( "Podano liczbe calkowita spoza przedzialu [%d,%d]. Podaj liczbe raz jeszcze: ", a, b );
			}
		}
		else
		{
			while( getchar() != '\n' );
			
			printf( "Podaj liczbe calkowita z zakresu [%d,%d]: ", a, b );
		}
	}
	
	return r;
}


double Get_Double() /* Wczytanie liczby zmiennoprzecinkowej */
{
	double r; /* to chcemy wczytac */
	
	printf( "\nPodaj liczbe zmiennoprzecinkowa: " );
	
	while( 1 )
	{
		if( scanf( "%lf", &r ) == 1 ) /* jesli cos wczytalismy */
		{
			if( getchar() != '\n' ) /* jesli mamy inne znaki niz cyfry */
			{
				printf( "Podaj poprawna liczbe zmiennoprzecinkowa: " );
				
				while( getchar() != '\n' );
				
				continue;
			}
			else
			{
				break;
			}
		}
		else
		{
			while( getchar() != '\n' );
			
			printf( "Podaj poprawna liczbe zmiennoprzecinkowa: " );
		}
	}
	
	return r;
}


int main()
{
	int n; /* liczba rownan */
	
	int i, j; /* zmienne pomocnicze (indeksy) */
	
	int kolejny; /* czy chcemy kolejny uklad rownan */
	
	int Wg; /* wynacznik glowny */
	
	int var; /* czy istnieje niezerowy wyznacznik dla pewnej niewiadomej */
	
	double ** A; /* macierz */
	
	double * x; /* wynikowa tablica niewiadomych */
	
	double * b; /* tablica wyrazow wolnych */
	
	int * stare_kolumny; /* tablica do funkcji obiczajacej wyznacznik */
	
	double * W; /* tablica kolejnych wyznacznikow */
	
	
	/* Tworzenie macierzy A */
	
  	A = (double **) malloc( MAX_N * sizeof( **A ) );

  	for(i=0; i<=MAX_N-1; ++i)
  	{
    	A[i] = ( double *) malloc( MAX_N * sizeof( *A[i] ) );
  	}
	
	
	/* Tworzenie tablicy b */
	
	b = (double *) malloc( MAX_N * sizeof( *b ) );
	
	
	/* Tworzenie tablicy stare_kolumny */
  	
  	stare_kolumny = (int *) malloc( MAX_N * sizeof( *stare_kolumny ) );


	/* Wypelnienie tablicy stare_kolumny */
	
  	for(i=0; i<=MAX_N-1; ++i)
  	{
  		stare_kolumny[i] = i;
	}
	
	
	/* Tworzenie tablicy x */
	
	x = (double *) malloc( MAX_N * sizeof( *x ) );
	
	
	/* Tworzenie tablicy W */
	
	W = (double *) malloc( MAX_N * sizeof( *W ) );
	
	
	do
	{
		/* Wczytanie danych */
		
		printf( "Podaj liczbe rownan, czyli liczbe calkowita z zakresu [%d,%d]: ", 1, MAX_N );
	
		n = Get_Int( 1, MAX_N ); /* wczytanie liczby rownan */
		
		
		printf( "\n\n" );
		
		for(i=0; i<=n-1; ++i)
		{
			printf( "\n\nPodaj wspolczynniki rownania nr %d oraz wyraz wolny:\n", i + 1 );
			
			for(j=0; j<=n-1; ++j)
			{
				A[i][j] = Get_Double();
			}
			
			b[i] = Get_Double();
		}
		
		
		Wg = det( n, 0, stare_kolumny, A ); /* wyznacznik glowny */
		
		var = 0; /* jak na razie nie istnieje niezerowy wyznacznik dla pewnej niewiadomej, dlatego inicjujemy te zmienna wartoscia zero */
		
		
		/* Obliczenie wyznacznikow dla poszczegolnych zmiennych */
		
		for(j=0; j<=n-1; ++j)
		{
			podmiana( A, j, b, n ); /* teraz j-ta kolumna macierzy A to tablica b, natomiast tablica b zawiera j-ta kolumne macierzy A  */
			
			W[j] = det( n, 0, stare_kolumny, A );
			
			if( W[j] != 0.0 ) /* jesli mamy niezerowy wyznacznik dla pewnej niewiadomej */
			{
				var = 1;
			}
			
			podmiana( A, j, b, n ); /* teraz j-ta kolumna macierzy A oraz tablica b sa na swoich miejscach poczatkowych */
		}
		
		
		/* Okreslenie rozwiazania */
		
		if( Wg != 0.0 ) /* wyznacznik glowny jest niezerowy, czyli uklad rownan jest oznaczony */
		{
			/* Obliczenie wynikow */
			
			for(i=0; i<=n-1; ++i)
			{
				x[i] = W[i] / Wg; /* wynik dla i-tej niewiadomej */
			}
			
			
			/* Wypisywanie wynikow */
			
			printf( "\n\nUklad rownan jest oznaczony - oto rozwiazanie:\n" );
			
			for(i=0; i<=n-1; ++i)
			{
				printf( "x_%d = %lf\n", i + 1, x[i] );
			}
			
			printf( "\n\n" );
		}
		else /* wyznacznik wynosi zero, czyli uklad rownan jest nieoznaczony albo sprzeczny */
		{
			if( var == 1 )
			{
				printf( "\n\nUklad rownan jest sprzeczny\n" );
			}
			else /* var == 0 */
			{
				printf( "\n\nUklad rownan jest nieoznaczony albo sprzeczny\n" );
			}
		}
		
		printf( "\n\nCzy rozwiazujemy kolejny uklad rownan (0 - nie , 1 - tak) ? : " );
		
		kolejny = Get_Int( 0, 1 );
	}
	while( kolejny == 1 );
	
	
	/* Zwalnianie pamieci */
  	
  	free( x );
  	
  	free( b );
  	
  	free( stare_kolumny );
  	
  	free( W );
  	
  	
  	for(i=0; i<=MAX_N-1; ++i)
  	{
  		free( A[i] );
	}

  	free( A );
	
	
	/* Koniec dzialania programu */
	
	return 0;
}
