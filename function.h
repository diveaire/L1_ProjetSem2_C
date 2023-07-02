int calculTemps(int nb_lignes,FILE *fichierCSV,Data tab[]);
void verifFile(const char * fichier);
int triBulle (Data tab[], int size);
int triInsertionD (Data tab[], int size);
int triInsertionC (Data tab[], int size);
int triSelection(Data tab[], int size);
void clearTab(Data tab[],int size);
void melange(Data tab[],int size);
int verifTri(Data tab[], int size);
int rechercheSequentielleSimple(int search, Data tab[], int size);
int rechercheSequentielleTri(int search, Data tab[], int size);
int rechercheDichotomie(int search, Data tab[], int size);

char *strsep (char **stringp, const char *delim);
