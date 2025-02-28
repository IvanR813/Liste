#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cvor CVOR;
typedef CVOR* PCVOR;

struct cvor {
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
	novi->sledeci = NULL;

	if (*glava == NULL)
	{
		*glava = novi;
	}
	else
	{
		PCVOR poslednji = *glava;
		while (poslednji->sledeci != NULL)
		{
			poslednji = poslednji->sledeci;
		}
		poslednji->sledeci = novi;
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

	novi->sledeci = *glava;
	*glava = novi;
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
		PCVOR poslednji = (*glava)->sledeci;
		PCVOR pretposlednji = *glava;
		while (poslednji->sledeci != NULL)
		{
			pretposlednji = poslednji;
			poslednji = poslednji->sledeci;
		}
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
	if (n > brojElemenata - 1 || n < 0)
	{
		puts("Indeks van granica liste!");
		return;
	}
	else if (n == brojElemenata - 1)
	{
		PCVOR poslednji = *glava;
		while (poslednji->sledeci != NULL)
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
		for (int i = 0; i < n; i++)
		{
			tekuci = tekuci->sledeci;
		}
		PCVOR novi = malloc(sizeof(CVOR));
		PCVOR posle = tekuci->sledeci;
		novi->info = broj;
		novi->sledeci = posle;
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
	if (n == 0)
	{
		PCVOR prvi = *glava;
		*glava = prvi->sledeci;
		free(prvi);
		return;
	}
	PCVOR pre = *glava;
	for (int i = 1; i < n; i++)
	{
		pre = pre->sledeci;
	}

	PCVOR zaBrisanje = pre->sledeci;
	pre->sledeci = zaBrisanje->sledeci;
	free(zaBrisanje);
}

int suma(PCVOR glava)
{
	int suma = 0;
	PCVOR cvor = glava;
	while (cvor != NULL)
	{
		suma += cvor->info;
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
