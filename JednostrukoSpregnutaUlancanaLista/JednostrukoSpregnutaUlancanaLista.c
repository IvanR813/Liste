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

	if (*glava == NULL)
	{
		novi->sledeci = novi;
		*glava = novi;
	}
	else
	{
		PCVOR poslednji = *glava;
		while (poslednji->sledeci != *glava)
		{
			poslednji = poslednji->sledeci;
		}
		poslednji->sledeci = novi;
		novi->sledeci = *glava;
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
		novi->sledeci = novi;
		*glava = novi;
	}
	else
	{
		PCVOR poslednji = *glava;
		while (poslednji->sledeci != *glava)
		{
			poslednji = poslednji->sledeci;
		}
		poslednji->sledeci = novi;
		novi->sledeci = *glava;
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
	} while (tekuci != glava);
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
	do
	{
		sledeci = tekuci->sledeci;
		free(tekuci);
		tekuci = sledeci;
	} while (tekuci != *glava);
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
	if (cvor == cvor->sledeci)
	{
		broj = cvor->info;
		free(cvor);
		*glava = NULL;
	}
	else
	{
		PCVOR drugi = (*glava)->sledeci;
		PCVOR poslednji = *glava;
		while (poslednji->sledeci != *glava)
		{
			poslednji = poslednji->sledeci;
		}
		poslednji->sledeci = drugi;
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
	if (cvor == cvor->sledeci)
	{
		broj = cvor->info;
		free(cvor);
		*glava = NULL;
		return broj;
	}
	else
	{
		PCVOR pretposlednji = *glava;
		PCVOR poslednji = (*glava)->sledeci;
		while (poslednji->sledeci != *glava)
		{
			pretposlednji = poslednji;
			poslednji = poslednji->sledeci;
		}
		pretposlednji->sledeci = *glava;
		broj = poslednji->info;
		free(poslednji);
	}
	return broj;
}
void sortiraj_listu(PCVOR glava) {
	if (glava == NULL || glava->sledeci == glava) {
		return;
	}

	int broj = 0;
	PCVOR prvi, drugi;
	for (prvi = glava; prvi != glava || broj == 0; prvi = prvi->sledeci)
	{
		if (prvi == glava)
			broj = 1;
		for (drugi = prvi->sledeci; drugi != glava; drugi = drugi->sledeci)
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
	PCVOR tekuci = *glava;
	for (int i = 1; i < n; i++)
	{
		tekuci = tekuci->sledeci;
		if (tekuci == *glava)
		{
			printf("Indeks van granica liste!\n");
			return;
		}
	}

	PCVOR novi = malloc(sizeof(CVOR));
	PCVOR posle = tekuci->sledeci;
	novi->info = broj;
	novi->sledeci = posle;
	tekuci->sledeci = novi;
}
void izbaci_sa_pozicije(PCVOR* glava, int n)
{
	if (*glava == NULL)
	{
		printf("Lista je prazna!\n");
		return;
	}
	PCVOR tekuci = *glava;
	if (n == 0)
	{
		if (*glava == (*glava)->sledeci)
		{
			free(*glava);
			*glava = NULL;
			return;
		}
		*glava = (*glava)->sledeci;
		PCVOR prethodni = *glava;
		while (prethodni->sledeci != tekuci)
			prethodni = prethodni->sledeci;
		prethodni->sledeci = *glava;
		free(tekuci);
		return;
	}
	for (int i = 0; i < n; i++)
	{
		tekuci = tekuci->sledeci;
		if (tekuci == *glava)
		{
			printf("Indeks van granica liste!\n");
			return;
		}
	}
	if (tekuci == tekuci->sledeci)
	{
		free(tekuci);
		*glava = NULL;
		return;
	}
	PCVOR pre = *glava;
	while (pre->sledeci != tekuci)
		pre = pre->sledeci;
	PCVOR posle = tekuci->sledeci;
	pre->sledeci = posle;
	free(tekuci);
}
//
int suma(PCVOR glava)
{
	int suma = 0;
	int signal = 0;
	for (PCVOR cvor = glava; cvor != glava || signal == 0; cvor = cvor->sledeci)
	{
		signal = 1;
		suma += cvor->info;
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
	dodaj_na_kraj(&glava, 61);
	dodaj_na_kraj(&glava, 8);
	dodaj_na_pocetak(&glava, 5);
	dodaj_na_pocetak(&glava, 232);
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
	ispisi(glava);
	dodaj_na_pocetak(&glava, 25);
	ispisi(glava);
	izbaci_sa_kraja(&glava);
	ispisi(glava);

	return 0;
}
