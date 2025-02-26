#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cvor CVOR;
typedef CVOR* PCVOR;

struct cvor {
	PCVOR prethodni;
	int info;
	PCVOR sledeci;
};

void dodaj_na_kraj(PCVOR* glava, int broj)
{
	PCVOR novi = malloc(sizeof(CVOR));
	if (novi == NULL)
	{
		fprintf(stderr, "Neuspela alokacija memorije!\n");
		exit(EXIT_FAILURE);
	}
	novi->info = broj;

	if (*glava == NULL)
	{
		novi->sledeci = NULL;
		novi->prethodni = NULL;
		*glava = novi;
	}
	else
	{
		PCVOR poslednji = *glava;
		while(poslednji->sledeci != NULL)
		{
		    poslednji = poslednji->sledeci;
		}
		poslednji->sledeci = novi;
		novi->prethodni = poslednji;
		novi->sledeci = NULL;
	}
}
void dodaj_na_pocetak(PCVOR* glava, int broj)
{
	PCVOR novi = malloc(sizeof(CVOR));
	if (novi == NULL)
	{
		fprintf(stderr, "Neuspela alokacija memorije!\n");
		exit(EXIT_FAILURE);
	}
	novi->info = broj;

	if (*glava == NULL)
	{
		novi->sledeci = NULL;
		novi->prethodni = NULL;
		*glava = novi;
	}
	else
	{
		novi->prethodni = NULL;
		novi->sledeci = *glava;
		(*glava)->prethodni = novi;
		*glava = novi;
	}
}
void ispisi(PCVOR glava)
{
	if (glava == NULL)
	{
		puts("Lista je prazna!");
		return;
	}
	PCVOR tekuci = glava;
	printf("Lista elemenata: ");
	do
	{
		printf("%d ", tekuci->info);
		tekuci = tekuci->sledeci;
	} while (tekuci != NULL);
	printf("\n");
}
void obrisi_listu(PCVOR* glava)
{
	if (*glava == NULL)
	{
		return;
	}
	PCVOR tekuci = *glava;
	PCVOR sledeci;
	while (tekuci != NULL)
	{
		sledeci = tekuci->sledeci;
		free(tekuci);
		tekuci = sledeci;
	}
	*glava = NULL;
}
int izbaci_sa_pocetka(PCVOR* glava)
{
	int broj = -1;
	if (*glava == NULL)
	{
		printf("Lista je prazna!\n");
		return broj;
	}
	PCVOR cvor = *glava;
	if (cvor->sledeci == NULL)
	{
		broj = cvor->info;
		free(cvor);
		*glava = NULL;
	}
	else
	{
		PCVOR drugi = (*glava)->sledeci;
		drugi->prethodni = NULL;
		*glava = drugi;
		broj = cvor->info;
		free(cvor);
	}
	return broj;
}
int izbaci_sa_kraja(PCVOR* glava)
{
	int broj = -1;
	if (*glava == NULL)
	{
		printf("Lista je prazna!\n");
		return broj;
	}
	PCVOR cvor = *glava;
	if (cvor->sledeci == NULL)
	{
		broj = cvor->info;
		free(cvor);
		*glava = NULL;
	}
	else
	{
		PCVOR poslednji = *glava;
		while(poslednji->sledeci != NULL)
		{
		    poslednji = poslednji->sledeci;
		}
		PCVOR pretposlednji = poslednji->prethodni;
		pretposlednji->sledeci = NULL;
		broj = poslednji->info;
		free(poslednji);
	}
	return broj;
}
void sortiraj_listu(PCVOR glava) {
	if (glava == NULL || glava->sledeci == NULL) {
		return;
	}
	PCVOR prvi, drugi;
	for (prvi = glava; prvi != NULL; prvi = prvi->sledeci)
	{
		for (drugi = prvi->sledeci; drugi != NULL; drugi = drugi->sledeci)
		{
			if (prvi->info > drugi->info)
			{
				int temp = prvi->info;
				prvi->info = drugi->info;
				drugi->info = temp;
			}
		}
	}
}
void dodaj_nakon(PCVOR* glava, int n, int broj)
{
	if (*glava == NULL)
	{
		printf("Lista je prazna!\n");
		return;
	}
	int brojElemenata = 0;
	PCVOR tekuci = *glava;
    while (tekuci != NULL)
    {
        brojElemenata++;
        tekuci = tekuci->sledeci;
    }
	tekuci = *glava;
	if(n > brojElemenata-1 || n < 0)
	{
	    puts("Indeks van granica liste!");
	    return;
	}
    else if(n == brojElemenata - 1)
    {
        PCVOR poslednji = *glava;
        while(poslednji->sledeci != NULL)
        {
            poslednji = poslednji->sledeci;
        }
        PCVOR novi = malloc(sizeof(CVOR));
        novi->info = broj;
        novi->sledeci = NULL;
        poslednji->sledeci = novi;
    }
    else
    {
        for(int i = 0; i < n; i++)
        {
            tekuci = tekuci->sledeci;
        }
    	PCVOR novi = malloc(sizeof(CVOR));
	    PCVOR posle = tekuci->sledeci;
	    novi->info = broj;
	    novi->sledeci = posle;
	    posle->prethodni = novi;
	    novi->prethodni = tekuci;
	    tekuci->sledeci = novi;
    }
}
void izbaci_sa_pozicije(PCVOR* glava, int n)
{
    if (*glava == NULL)
    {
        printf("Lista je prazna!\n");
        return;
    }
    PCVOR tekuci = *glava;
    int brojElemenata = 0;
    while (tekuci != NULL)
    {
        brojElemenata++;
        tekuci = tekuci->sledeci;
    }
    if (n < 0 || n >= brojElemenata)
    {
        puts("Indeks van granica liste!");
        return;
    }
    if (n == brojElemenata - 1)
    {
        PCVOR poslednji = *glava;
        PCVOR pretposlednji = NULL;

        if (brojElemenata == 1) 
        {
            *glava = NULL;
            free(poslednji);
            return;
        }
        while (poslednji->sledeci != NULL)
        {
            poslednji = poslednji->sledeci;
        }

        pretposlednji = poslednji->prethodni;
        pretposlednji->sledeci = NULL;
        free(poslednji);
    }
    else if (n == 0)
    {
        PCVOR prvi = *glava;

        if (brojElemenata == 1)
        {
            *glava = NULL;
            free(prvi);
            return;
        }
        PCVOR drugi = prvi->sledeci;
        drugi->prethodni = NULL;
        *glava = drugi;
        free(prvi);
    }
    else
    {
        PCVOR cvor = *glava;
        for (int i = 0; i < n; i++)
        {
            cvor = cvor->sledeci;
        }
        PCVOR pre = cvor->prethodni;
        PCVOR posle = cvor->sledeci;
        if (pre != NULL) pre->sledeci = posle;
        if (posle != NULL) posle->prethodni = pre;
        free(cvor);
    }
}

int suma(PCVOR glava)
{
	int suma = 0;
	PCVOR cvor = glava;
	while(cvor!=NULL)
	{
	    suma+=cvor->info;
	    cvor = cvor->sledeci;
	}
	return suma;
}


int main()
{
	PCVOR glava = NULL;
	dodaj_na_kraj(&glava, 6);
	dodaj_na_kraj(&glava, 4);
	dodaj_na_pocetak(&glava, 2);
	dodaj_na_pocetak(&glava, 23);
	printf("Suma elemenata liste je:%d\n", suma(glava));
	dodaj_nakon(&glava, 5, 69);
	printf("Suma elemenata liste je:%d\n", suma(glava));
	ispisi(glava);
	izbaci_sa_pozicije(&glava, 2);
	ispisi(glava);
	sortiraj_listu(glava);
	ispisi(glava);
	obrisi_listu(&glava);
	ispisi(glava);
	dodaj_na_pocetak(&glava, 23);
	dodaj_na_pocetak(&glava, 25);
	izbaci_sa_kraja(&glava);
	ispisi(glava);

	obrisi_listu(&glava);

	return 0;
}
