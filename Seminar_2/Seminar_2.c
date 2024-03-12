#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
struct Farmacie
{
	char* denumire;
	int nr_angajati;
	float* salarii;
	int an_infiintare;
};
struct Farmacie initializare(const char* denumire, int nr_angajati, float* salarii, int an_infiintare)
{
	struct Farmacie f;
	f.nr_angajati = nr_angajati;
	f.an_infiintare = an_infiintare;
	f.denumire = malloc((strlen(denumire) + 1) * sizeof(char));
	strcpy(f.denumire, denumire);
	f.salarii = malloc(sizeof(float) * nr_angajati);
	for (int i = 0; i < nr_angajati; i++)
	{
		f.salarii[i] = salarii[i];
	}
	return f;
}

void afisareFarmacie(struct Farmacie f)
{
	printf("Denumire: %s, infiintata in: %d", f.denumire, f.an_infiintare);
	printf(", nr. angajati: %d, cu salariile: ", f.nr_angajati);
	for (int i = 0; i < f.nr_angajati; i++)
		printf("%5.2f, ", f.salarii[i]);
	printf("\n");
}

struct Farmacie copiere(struct Farmacie f) {
	struct Farmacie f1;
	f1.an_infiintare = f.an_infiintare;
	f1.denumire = malloc((strlen(f.denumire) + 1) * sizeof(char));
	strcpy(f1.denumire, f.denumire);

	f1.salarii = malloc(sizeof(float) * f.nr_angajati);

	f1.nr_angajati = f.nr_angajati;
	for (int i = 0; i < f.nr_angajati; i++)
		f1.salarii[i] = f.salarii[i];

	return f1;

}

struct Farmacie* adaugaFarmacieInVector(struct Farmacie* farmacii, struct Farmacie f, int* nr) {
	*nr = *nr + 1;
	struct Farmacie* aux = malloc(sizeof(struct Farmacie) * (*nr));

	for (int i = 0; i < *nr - 1; i++) {
		aux[i] = farmacii[i];
	}
	aux[*nr - 1] = copiere(f);

	return aux;
}

int calculNrAngajati(struct Farmacie* farmacii, int nr) {
	int nrAngajatiTotal = 0;
	for (int i = 0; i < nr; i++) {
		nrAngajatiTotal += farmacii[i].nr_angajati;
	}

	return nrAngajatiTotal;
}

void main() {
	int a = 8;
	float* v = malloc(sizeof(float) * 2);
	v[0] = 200.4;
	v[1] = 300.5;
	struct Farmacie f = initializare("Tei", 2, v, 2001);
	afisareFarmacie(f);

	int nrFarmacii = 1;

	struct Farmacie* farmacii;
	farmacii = malloc(sizeof(struct Farmacie));
	farmacii[0] = copiere(f);


	struct Farmacie f1 = initializare("Catena", 2, v, 1990);
	farmacii = adaugaFarmacieInVector(farmacii, f1, &nrFarmacii);

	float v2[4] = { 3700, 3800, 3100, 2555 };
	struct Farmacie f2 = initializare("Dona", 4, v2, 1997);
	farmacii = adaugaFarmacieInVector(farmacii, f2, &nrFarmacii);

	//afisareFarmacie(farmacii[0]);

	for (int i = 0; i < nrFarmacii; i++) {
		afisareFarmacie(farmacii[i]);
	}

	int nrTotalAngajati = calculNrAngajati(farmacii, nrFarmacii);
	printf("\nNr total de angajati = %d", nrTotalAngajati);

	free(v);
	free(f.denumire);
	free(f.salarii);
	for (int i = 0; i < nrFarmacii; i++) {
		free(farmacii[i].denumire);
		free(farmacii[i].salarii);
	}
	free(f1.denumire); free(f1.salarii);
	free(f2.denumire); free(f2.salarii);
	free(farmacii);

}