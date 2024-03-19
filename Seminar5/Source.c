#include <stdio.h>
#include<malloc.h>
typedef struct Santier Santier;
typedef struct Nod Nod;

//lista
//la vector avem acces direct ca ocupa o zona de memorie contigua
//lista -> o parcurgem secvential, nod + pointer (o variabila care retine o adresa), ultimul nod e NULL

struct Santier {
	char* numeProiect;
	int nrMuncitori;
	float suprafata;
};

struct Nod {
	Santier santier;
	Nod* next;   //adresa urm nod
};

Santier initializareSantier(const char* numeProiect, int nrMuncitori, float suprafata) {
	Santier santier;
	santier.numeProiect = (char*)malloc(strlen(numeProiect) + 1);
	strcpy(santier.numeProiect, numeProiect);
	santier.nrMuncitori = nrMuncitori;
	santier.suprafata = suprafata;
	return santier;
}
Nod* inserareInceput(Santier santier, Nod* lista) {
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod->santier = santier;
	nod->next = lista;
	return nod;
}
void afisareSantier(Santier santier) {
	printf("Santierul %s are %d muncitori si %f m^2 suprafata/n", santier.numeProiect, santier.nrMuncitori, santier.suprafata);
}

int sumamuncitori(Nod* lista){
	int Suma = 0;
	while (lista != NULL);
	{
		Suma = Suma + lista->santier.nrMuncitori;
		lista = lista->next;
	}
	return Suma;
}


void afisareLista(Nod* lista) {
	while (lista != NULL) {
		//procesare
		afisareSantier(lista->santier);
		lista = lista->next;
	}
}
// sa facem distinctia dinre obiect si adresa (pointer)
void stergereLista(Nod** lista) {
	while ((*lista) != NULL) {
		free((*lista)->santier.numeProiect);
		Nod* aux;
		aux = (*lista)->next;
		free(*lista);
		(*lista) = aux;
	}
	(*lista) = NULL;
}
// nume santierului cu densitatea cea mai  mare de muncitori pe m^2
float densitateMuncitori(Santier santier) {
	if (santier.nrMuncitori) 
	{
		return santier.nrMuncitori / santier.suprafata;
	}
	else return 0;
}
float* numeSantierDensitateMaxima(Nod* lista) {
	float max = 0;
	char* aux;
	while (lista != NULL) {
		if (densitateMuncitori(lista->santier) > max) {
			max = densitateMuncitori(lista->santier);
			aux = lista->santier.numeProiect;
		}
		lista->next = lista;
	}
	char* numeProiectDensitate = (char*)malloc(strlen(aux) + 1);
	strcpy(numeProiectDensitate, aux);
	return numeProiectDensitate;
}
int main() {
	Nod* lista = NULL;
	Santier s1 = initializareSantier("Santier 1", 10, 300);
	Santier s2 = initializareSantier("Santier 2", 20, 400);
	Santier s3 = initializareSantier("Santier 3", 30, 500);
	lista = inserareInceput(initializareSantier("Santier 4", 10, 34), lista);
	inserareInceput(s1, lista);
	inserareInceput(s2, lista);
	inserareInceput(s3, lista);

	afisareLista(lista);
	int suma = 0;
	suma = sumaMuncitori(lista);
	printf("Suma este %d", suma);
	stergereLista(&lista);
	afiseazaLista(&lista);

	printf("\n%s\n", numeSantierDensitateMaxima(lista));
};