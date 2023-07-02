#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

//fonction strsep pour le compilateur
char *strsep (char **stringp, const char *delim){
char *begin, *end;
begin = *stringp;
if (begin == NULL) return NULL;
end = begin + strcspn (begin, delim);
if (*end) {
*end++ = '\0';
 *stringp = end;
}
else *stringp = NULL;
return begin;
}

//structure du tableau de données
typedef char string[50];
typedef struct
{
	int age;
	string prof;
	int surface;
		
} Data;

//quelques constantes
#define RESULTATS_CSV "Resultats_temps/resultats.csv"
#define FICHIER_CSV "Fichiers/FD_INDREG_2018.csv"
#define col_age 6
#define col_prof 76
#define col_surf 85
#define LONGUEUR_MAX 1024
#define NB_LIGNE_FICHIER 19603272


/*
	La fonction calcul_temps permet de calculer le temps de chargement des données des colonnes 6,76 et 85 d'un fichier CSV
	préciser en paramètre selon un nombre de ligne préciser en paramètre et les données sont enregistrés dans un tableau du
	type struc Data précicer en paramètre
*/

int calculTemps(int nb_lignes,FILE *fichierCSV,Data tab[])
{
	clock_t debut = clock(); //variable début de chargement
    char ligne[LONGUEUR_MAX];// Creation tableau de caractere pour stocker ma ligne

	//fgets permet de lire une ligne d'un fichier file*
	fgets(ligne, LONGUEUR_MAX, fichierCSV);// On ignore la premiere ligne car elle ne comporte que les titres des colonnes
	
	// une boucle for pour pouvoir lire plusieures lignes
	for(int i=0; i<nb_lignes; ++i)
	{
		fgets(ligne, LONGUEUR_MAX, fichierCSV);
		char * texte = strdup(ligne); //pointeur qui alloue la mémoire de la ligne sur le tas

		if (texte == NULL){ //on test la bonne allocation de mémoire
			printf("Problème de mémoire sur ligne");
		}

		char* copieTexte = texte; //pointeur qui va se modifier à découpage de la ligne par strsep
        int index = 0;
        char* colonne; //pointeur pour enregistrer
        while(colonne != NULL)
        {
            colonne = strsep(&copieTexte, ";");//séparation des différents morceaux
            ++index; //index correspond à la colonne actuel

            if(index == col_age) //si on est sur la bonne colonne
            {
                tab[i].age = atoi(colonne); //enregistrement dans le tableau
            }
            if(index == col_prof)
            {
                strcpy(tab[i].prof, colonne);
            }
            if(index == col_surf)
            {
                tab[i].surface = atoi(colonne);          
                break;
            }
        }
        free(texte); //on libère la mémoire	
	}
	
	clock_t fin = clock(); //variable de fin chargement
    
    //calcul et conversion du temps en ms
	int duree = fin-debut;
	long int temps = 1000*duree/CLOCKS_PER_SEC;
	return(temps); //fonction retourne le temps de chargement
	
}


//La fonction verifFile permet juste de vérifier que les pointeur sur fichiers sont bien localisés
void verifFile(const char * fichier){
	if(fichier == NULL) //fopen() renvoie NULL si il y a une erreur avec le fichier
	{
		printf("ERREUR - Echec d'ouverture du fichier: %s\n", fichier);	
	}
	return;
}

// tri à Bulle d'un tableau type Data dans l'ordre croissant
int triBulle (Data tab[], int size){
	clock_t debut = clock();
	int i; 
	int j; 
	int tpm;
	
	for(i = size-2; i > 1; --i)
	{
		for(j = 0; j < i; ++j)
		{
			if(tab[j].age > tab[j+1].age)
			{
				tpm = tab[j].age;
				tab[j].age = tab[j+1].age;
				tab[j+1].age = tpm;
				
			}
		}
	}
	clock_t fin = clock();
	int temps = 1000*(fin-debut)/CLOCKS_PER_SEC;
	return temps;
}

// tri à insertion d'un tableau type Data dans l'ordre décroissant
int triInsertionD (Data tab[], int size)
{
	clock_t debut = clock();
    int i;
    int j;
    int val;

    for (i = 1; i<size-1 ;i++){
        val = tab[i].age;
        j= i;
        while (( j > 0) && (tab[j-1].age > val)) 
        {
            tab[j].age = tab[j-1].age;
            j = j-1;
        }
    }
	clock_t fin = clock();
	int temps = 1000*(fin-debut)/CLOCKS_PER_SEC;
	return temps;
}

// tri à insertion d'un tableau type Data dans l'ordre croissant
int triInsertionC (Data tab[], int size)
{
	clock_t debut = clock();
    int i;
    int j;
    int val;

    for (i = 1; i<size-1 ;i++){
        val = tab[i].age;
        j= i-1;
        while (( j >= 0) && (tab[j].age > val)) 
        {
            tab[j+1].age = tab[j].age;
            j = j-1;
        }
		tab[j+1].age = val;
    }
	clock_t fin = clock();
	int temps = 1000*(fin-debut)/CLOCKS_PER_SEC;
	return temps;
}

// tri à selection d'un tableau type Data dans l'ordre croissant
int triSelection(Data tab[], int size){
    clock_t debut = clock();
    int i= size-2, j, temp, pg;
    while(i > 0){
		pg = 0;
		for(j = 0 ; j < i ; j++){
			if (tab[j].age > tab[pg].age){
				pg = j;
			}
		}
		temp = tab[pg].age;
		tab[pg].age = tab[i].age;
		tab[i].age = temp;
		i = i-1;
    }
    clock_t fin = clock();
	int temps = 1000*(fin-debut)/CLOCKS_PER_SEC;
	return temps;
}


//fonction qui efface un tableau de data fournis en paramètre
void clearTab(Data tab[],int size){
    memset(tab,0,size);
}

//fonction qui mélange un tableau de data fournis en paramètre
void melange(Data tab[],int size){

    int i, j,temp;
    if( size == 1 )//taille du tableau doit être > 1 (logique)
        return;
     
    for( i=0; i< size-1; i++)//boucle pour parcourir le tableau
    {
        // j = on recupère un nombre aléatoire entre i and n-1 (inclus)
        j = i + rand() % (size-i);
        //on echange les valeurs de tab[i] et tab[j]
        temp = tab[i].age;
        tab[i].age = tab[j].age;
        tab[j].age = temp;
    }  
}

// Vérifie que le tableau de data fournis en paramètre est trié dans l'ordre croissant 
int verifTri(Data tab[], int size){
    int i=0, b = 1;
    for(i=0;i<(size-2);i++){
        if(tab[i].age>tab[i+1].age){
            b=0;
        }
    }
    return b;
}

//une recherche sans tri au préalable (le temps de chargement n'est pas optimisé)
int rechercheSequentielleSimple(int search, Data tab[], int size){
    int i,trouver = 0;
    //on parcours le tableau et si il trouve la fonction renvoie 1 sinon renvoie 0
        for(i=0;i<size;i++){
            if(tab[i].age == search){
                trouver = 1;
            }
        }
	return trouver;
}

//Le même type de recherche mais avec un tri ordre croissant au préalable
int rechercheSequentielleTri(int search, Data tab[], int size){
    int i=0,trouver=0,possible=1;
    //ont trie d'abord le tableau dans l'ordre croissant
    
    //on verifie que chaque case a un contenu plus petit que celui de la case suivante
    while ((i<size) && (possible==1) &&(trouver == 0)){
        if(tab[i].age == search){
           trouver = 1;
        }
        else if(tab[i].age > search){
            possible = 0;
        }
        else{
            i = i+1;
        }
    }
	return trouver;
}//renvoie 1 si l'objet est trouver sinon renvoie 0

//autre type de recherche (dichotomie) avec tri ordre croissant à faire au préalable(obligatoire)
int rechercheDichotomie(int search, Data tab[], int size){
    int i=0,j=size-1,trouver = 0;
    //on verifie que chaque case a un contenu plus petit que celui de la case suivante
    if (verifTri(tab,size) == 0){printf("erreur le tri est mal effectuer...");}
    else{
        while((i<= j) && (trouver == 0)){
           if(tab[(j+i)/2].age == search){
               trouver = 1;
           }
           else if(tab[(j+i)/2].age > search){
               j = (j+i)/2 -1;
           }else{
               i = (j+i)/2 +1;
            }
        }
    }
    return trouver;
}//renvoie 1 si l'objet est trouver sinon renvoie 0