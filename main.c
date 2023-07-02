//on inclus les bibliothèques des fonctions de bases
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//création des différentes structures
typedef char string[50];
typedef struct
{
	int age;
	string prof;
	int surface;
		
} Data;

//on inclus notre fichier header afin de faire fonctionner nos fonctions dans le main
#include "function.h"

//on créer quelques constantes 
#define RESULTATS_CSV "Resultats_temps/resultats.csv"
#define RESULTATS_TRI_BULLE "Resultats_temps/tri/bulle.csv"
#define RESULTATS_TRI_SELECTION "Resultats_temps/tri/selection.csv"
#define RESULTATS_TRI_INSERTION "Resultats_temps/tri/insertion.csv"
#define RESULTATS_RECHERCHE_SEQUENTIELLE "Resultats_temps/recherche/sequentielle.csv"
#define RESULTATS_RECHERCHE_DICHOTOMIE "Resultats_temps/recherche/dichotomie.csv"
#define FICHIER_CSV "Fichiers/FD_INDREG_2018.csv"
#define NB_LIGNE_FICHIER 19603272
#define NB_COLONNE_FICHIER 97
#define LONGUEUR_MAX 1024

//on créer un tableau de la structure Data pour enregistrer les données
Data donnees[NB_LIGNE_FICHIER];



//La fonction main est la fonction principale. elle permet de gérer toutes les choix de l'utilisateur grâce à un switch 


int main(int argc, char *argv[]){

    /*Création de plusieurs pointeurs sur fichiers pour écrire les résultats et pour lire les données de notre fichiers csv
    option w pour write (debut de fichier) a pour write (fin de fichier), option r pour read
    */
   
    FILE * fichierCSV = fopen(FICHIER_CSV, "r");
    FILE * resultatsCSV = fopen(RESULTATS_CSV, "a"); 
    FILE * resultatsBULLE = fopen(RESULTATS_TRI_BULLE, "a");
    FILE * resultatsSELECTION = fopen(RESULTATS_TRI_SELECTION, "a");
    FILE * resultatsINSERTION = fopen(RESULTATS_TRI_INSERTION, "a");
    FILE * resultatsSEQUENTIELLE = fopen(RESULTATS_RECHERCHE_SEQUENTIELLE, "a");
    FILE * resultatsDICHOTOMIE = fopen(RESULTATS_RECHERCHE_DICHOTOMIE, "a");
	

    //fonction qui permet de vérifier que les fichiers sont bien créés
    verifFile(FICHIER_CSV);
    verifFile(RESULTATS_CSV);
    verifFile(RESULTATS_TRI_BULLE);
    verifFile(RESULTATS_TRI_SELECTION);
    verifFile(RESULTATS_TRI_INSERTION);
    verifFile(RESULTATS_RECHERCHE_SEQUENTIELLE);
    verifFile(RESULTATS_RECHERCHE_DICHOTOMIE);

    //Création de quelques variables
    int i,rep,choix = 0,bool=0, ordre = 0, temps, search,resultat,ch_recher;
    long lignes;

    //Petit message de Bienvenue =)
    printf("~~~~~~~Bonjour et Bienvenue dans le projet d'algorithmique et programmation~~~~~~\n\n");

    //Création d'une boucle pour afficher le menu qui s'arrête quand l'utilisateur quitte en choisissant l'option 0
    while (bool == 0){
		printf("Si vous voulez calculer le temps de chargement d'un nombre de lignes  --> taper 1\n");
        printf("Si vous voulez calculer de (1*10^5, 2*10^5 ... 10*10^5)  ---------------> taper 2\n");
        printf("Tri a bulle ------------------------------------------------------------> taper 3\n");
        printf("Tri a selection --------------------------------------------------------> taper 4\n");
        printf("Tri insertion (C/D)-----------------------------------------------------> taper 5\n");
        printf("Melangeur tableau ------------------------------------------------------> taper 6\n");
        printf("Effacer tableau --------------------------------------------------------> taper 7\n");
        printf("Recherche Sequentielle (S/T)--------------------------------------------> taper 8\n");
        printf("Recherche par Dichotomie -----------------------------------------------> taper 9\n");

		printf("Si vous voulez quitter -------------------------------------------------> taper 0\n\n");
        //Récupération du choix de l'utilisateur dans la variable choix
        printf("Votre choix : ");
		scanf("%d", &choix);
        printf("\n");

        //Création d'un menu switch afin de gérer les différentes options
       switch (choix){

            
            default://dans le cas ou une option non codé est rentrée
                printf("\n\n\n\n\n\n\n\n\n\n-------------------> Merci de choisir une option disponible <-------------------\n\n\n\n\n\n\n\n\n\n");
            break;

            case 0://on sors de la boucle et le programme se termine
                bool = 1;
                printf("Merci d'avoir utilise notre code");
            break;

            case 1:
                //on récupère le nombre de lignes à chargés
                printf("Combien de lignes voulez-vous charges ?\n");
                scanf("%ld", &lignes);
                //on vérifie que le nb de lignes>0 et <nb de ligne max
                while (lignes<0 || lignes>NB_LIGNE_FICHIER){ 
                    printf("Merci de respecter le nombre de lignes MAX\n");
                    printf("Combien de lignes voulez-vous charges ?\n");
                    scanf("%ld", &lignes);
                }
                //on récupère le nombre de fois on l'ont veux répéter l'opération
                printf("Combien de fois voulez-vous repeter l'operation ?\n");
                scanf("%d", &rep);
                //on lance la fontion et on affiche le temps
                for(int j=0;j<rep;j++){
                    temps = calculTemps(lignes,fichierCSV,donnees);
                    printf("Enregistrement :%d\n", j+1);
                    printf("#%ld lignes\n", lignes);
                    printf("- Temps de chargement : %d ms\n\n", temps);

                    //inscriptions des données dans le fichiers csv
                    fprintf(resultatsCSV,"%ld;%d\n",lignes, temps);
                }
            break;

            case 2:
            //on lance la fonction et on affiche les résultats de 10^5 à 10^6
                lignes = 100000;
                for (int j=0;j<10;++j){
                    temps = calculTemps(lignes,fichierCSV,donnees);//enregistrement du temps
                    fprintf(resultatsCSV,"%ld;%d\n",lignes, temps);//inscriptions des données dans le fichiers csv            	
                    printf("Enregistrement #%d:\n", j+1);
                    printf("#%ld lignes\n", lignes);
                    printf("- Temps de chargement : %d ms\n", temps);
                    //affichages de données
                    printf("- Age     = %d\n", donnees[1000*(j+1)].age);
                    printf("- Prof    = \"%s\"\n", donnees[1000*(j+1)].prof);
                    printf("- Surface = %d\n\n", donnees[1000*(j+1)].surface);
                    lignes = lignes + 100000;//on incrémente le nombre de ligne à + 10^5
                }
            break;

            case 3:
                printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ tri a bulle ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
                printf("Sur combien de lignes voulez-vous exploiter les donnees ?");//on récupère le nombre de lignes
                scanf("%ld", &lignes);
                while (lignes<0 || lignes>NB_LIGNE_FICHIER){ //on vérifie que le nb de lignes>0 et <nb de ligne max
                    printf("Merci de respecter le nombre de lignes MAX\n");
                    printf("Combien de lignes voulez-vous charges ?\n");
                    scanf("%ld", &lignes);
                }
                //on utilise la fonction pour enregistrer le tableau de donnees 
                calculTemps(lignes,fichierCSV,donnees);
                printf("age avant : %d \n", donnees[1].age);
                printf("age avant : %d \n", donnees[2].age);
                printf("age avant : %d \n", donnees[3].age);
                printf("Tri en cours...\n\n");
                //on utilise la fonction pour trier le tableau et on enregistre sont temps de chargement
                temps = triBulle(donnees,lignes);
                printf("age apres : %d \n", donnees[1].age);
                printf("age apres : %d \n", donnees[2].age);
                printf("age apres : %d \n\n", donnees[3].age);
                //affichage du temps de chargement
                printf("#%ld lignes\n", lignes);
                printf("- Temps de chargement : %d ms\n\n", temps);
                //inscriptions des données dans le fichiers csv
                fprintf(resultatsBULLE,"%ld;%d\n",lignes, temps);
            break;
            
            case 4://on repète la même chose que case 3 mais avec une autre fonction de tri
                printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ tri a Selection ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
                printf("Sur combien de lignes voulez-vous exploiter les donnees ?");
                scanf("%ld", &lignes);
                while (lignes<0 || lignes>NB_LIGNE_FICHIER){ 
                    printf("Merci de respecter le nombre de lignes MAX\n");
                    printf("Combien de lignes voulez-vous charges ?\n");
                    scanf("%ld", &lignes);
                }
                calculTemps(lignes,fichierCSV,donnees);
                printf("age avant : %d \n", donnees[1].age);
                printf("age avant : %d \n", donnees[2].age);
                printf("age avant : %d \n", donnees[3].age);
                printf("Tri en cours...\n\n");
                temps = triSelection(donnees,lignes);
                printf("age apres : %d \n", donnees[1].age);
                printf("age apres : %d \n", donnees[2].age);
                printf("age apres : %d \n\n", donnees[3].age);
                printf("#%ld lignes\n", lignes);
                printf("- Temps de chargement : %d ms\n\n", temps);
                fprintf(resultatsSELECTION,"%ld;%d\n",lignes, temps);
            
                /*
                N.B on pourrais utiliser temps = calculTemps() dans un premier temps et ensuite faire 
                un temps = temps + triSelection() pour avoir le temps de chargement total (chargement et tri)
                */
            break;

            case 5://cas identique que case 3 et case 4 avec une autre fonction de tri
                printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ tri a insertion ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
                printf("Sur combien de lignes voulez-vous exploiter les donnees ?");
                scanf("%ld", &lignes);
                while (lignes<0 || lignes>NB_LIGNE_FICHIER){ 
                    printf("Merci de respecter le nombre de lignes MAX\n");
                    printf("Combien de lignes voulez-vous charges ?\n");
                    scanf("%ld", &lignes);
                }
                calculTemps(lignes,fichierCSV,donnees);
                printf("Voulez-vous Trier dans l'ordre \nCroissant --> (1)\nou\nDécroissant --> (2)\n\n");
                scanf("%d", &ordre);
                while (ordre<0 || ordre>2){ 
                    printf("Merci de respecter les choix possibles\n");
                    printf("Voulez-vous Trier dans l'ordre \nCroissant --> (1)\nou\nDecroissant --> (2)\n\n");
                    scanf("%d", &ordre);
                }

                printf("age avant : %d \n", donnees[1].age);
                printf("age avant : %d \n", donnees[2].age);
                printf("age avant : %d \n\n", donnees[3].age);

                printf("Tri en cours...\n\n");
                if(ordre == 1){ temps = triInsertionC(donnees,lignes);}
                else{ temps = triInsertionD(donnees,lignes); }

                printf("age apres : %d \n", donnees[1].age);
                printf("age apres : %d \n", donnees[2].age);
                printf("age apres : %d \n\n", donnees[3].age);
                printf("#%ld lignes\n", lignes);
                printf("- Temps de chargement : %d ms\n\n", temps);
                fprintf(resultatsINSERTION,"%ld;%d\n",lignes, temps);
            break;

            case 6://appelle la fonction qui mélange le tableau donner en entrer
                printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ melangeur ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
                printf("age avant : %d \n", donnees[1].age);
                printf("age avant : %d \n", donnees[2].age);
                printf("age avant : %d \n\n", donnees[3].age);
                melange(donnees,NB_LIGNE_FICHIER);
                printf("Le tableau a bien ete melanger\n\n");
                printf("age apres : %d \n", donnees[1].age);
                printf("age apres : %d \n", donnees[2].age);
                printf("age apres : %d \n\n", donnees[3].age);
            break;

            case 7://appelle la fonction qui efface le tableau donner en entrer
                printf("Le tableau va etre effacer....\n");

                printf("age avant : %d \n", donnees[1].age);
                printf("age avant : %d \n", donnees[2].age);
                printf("age avant : %d \n\n", donnees[3].age);
                clearTab(donnees,NB_LIGNE_FICHIER);
                printf("age apres : %d \n", donnees[1].age);
                printf("age apres : %d \n", donnees[2].age);
                printf("age apres : %d \n\n", donnees[3].age);
                printf("Le tableau a bien ete effacer.\n\n");
            break;

            case 8:
                printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ recherche sequentielle ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
                printf("Sur combien de lignes voulez-vous exploiter les donnees ?");
                scanf("%ld", &lignes);
                while (lignes<0 || lignes>NB_LIGNE_FICHIER){ //on vérifie que le nb de lignes>0 et <nb de ligne max
                    printf("Merci de respecter le nombre de lignes MAX\n");
                    printf("Combien de lignes voulez-vous charges ?\n");
                    scanf("%ld", &lignes);
                }
                //on recupère le choix sur une recherche simple(tableau non trier) ou sequentielle
                printf("voulez vous effectuer :\nUne rechercher simple --> 1\nUne recherche avec tri sequentielle --> 2\n");
                scanf("%d", &ch_recher);
                while(ch_recher < 1 || ch_recher > 2 ){
                    printf("Merci de repondre avec un choix disponible\n");
                    printf("voulez vous effectuer :\nUne rechercher simple --> 1\nUne recherche avec tri sequentielle --> 2\n");
                    scanf("%d", &ch_recher);
                }
                //on charge les données
                printf("Chargement et tri des donnees en cours...\n");
                calculTemps(lignes,fichierCSV,donnees);

                //récupération de l'information à rechercher dans le tableau de données
                printf("Quel Age souhaitez-vous rechercher dans le tableau\n");
                scanf("%d", &search);
                clock_t debut = clock();
                if (ch_recher == 1){resultat = rechercheSequentielleSimple(search,donnees,lignes);}
                else{
                    triInsertionC(donnees, lignes);
                    if(verifTri(donnees,lignes) == 0){
                        printf("erreur le tri est mal effectuer...\n\n");
                        break;
                        }
                    resultat = rechercheSequentielleTri(search,donnees,lignes);
                }
                clock_t fin = clock();
	            temps = 1000*(fin-debut)/CLOCKS_PER_SEC;
                if (resultat == 1){
                    printf("Sur les %ld lignes, %d a ete trouve dans le tableau de donnees en %d ms\n\n\n", lignes, search, temps);
                }else{
                    printf("Sur les %ld lignes, %d n'as pas ete trouve dans le tableau. Temps: %d ms\n\n\n", lignes, search, temps);
                }
                //inscription des résultats dans un csv
                fprintf(resultatsSEQUENTIELLE,"%ld;%d;%d\n",lignes,temps,search);
            break;

            case 9://identique que case 8 mais avec une autre fonction de tri
                printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ recherche par dichotomie ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
                printf("Sur combien de lignes voulez-vous exploiter les donnees ?");
                scanf("%ld", &lignes);
                while (lignes<0 || lignes>NB_LIGNE_FICHIER){ 
                    printf("Merci de respecter le nombre de lignes MAX\n");
                    printf("Combien de lignes voulez-vous charges ?\n");
                    scanf("%ld", &lignes);
                }
                printf("Chargement et tri des donnees en cours...\n");
                calculTemps(lignes,fichierCSV,donnees);
                //ont trie d'abord le tableau dans l'ordre croissant
                triInsertionC(donnees, lignes);
                printf("Quel Age souhaitez-vous rechercher dans le tableau\n");
                scanf("%d", &search);
                clock_t debut2 = clock();
                resultat = rechercheDichotomie(search,donnees,lignes);
                clock_t fin2 = clock();
	            temps = 1000*(fin2-debut2)/CLOCKS_PER_SEC;
                if (resultat == 1){
                    printf("Sur les %ld lignes, %d a ete trouve dans le tableau de donnees en %d ms\n\n\n", lignes, search, temps);
                }else{
                    printf("Sur les %ld lignes, %d n'as pas ete trouve dans le tableau. Temps: %d ms\n\n\n", lignes, search, temps);
                }
                fprintf(resultatsDICHOTOMIE,"%ld;%d;%d\n",lignes,temps,search);
            break;

        }
    }
    //fermeture de tout les fichiers ouvert pour bien valider l'enregistrement
    fclose(resultatsCSV);
    fclose(resultatsBULLE);
    fclose(resultatsSELECTION);
    fclose(resultatsINSERTION);
    fclose(fichierCSV);
    fclose(resultatsSEQUENTIELLE);
    fclose(resultatsDICHOTOMIE);
}