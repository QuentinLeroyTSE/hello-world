//ouverture d'un fichier T2D
/* Ce main() permet l'ouverture et la lecture d'un fichier texte T2D (matrice 2D de float représentant les z).
Le fichier à ouvrir doit se trouver dans le répertoire courant de l'execution du programme. 
Ne pas oublier de rajouter ".txt" au nom du fichier lors de la saisie du nom dans le programme.

Le programme, à partir du fichier texte, crée un tableau 2D de float, utilisable comme une matrice et contenant normalement 
1437 lignes et 1280 colonnes, remplie de 0 et des valeurs des coordonnées en z du pieds.
Ce tableau est: "tab_"
Accès à une case du tableau: tab_[i][j]; i parcourant les lignes, et j les colonnes.

A partir de la borne:
"INSERER VOTRE CODE A PARTIR D'ICI"

La tableau existe et est rempli, vous pouvez insérer votre algorithme ou votre fonction à tester sur tab_.

Info: 
tab_ est un pointeur vers un pointeur de float.
Donc tab_[i][j] est un float.

*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void main() {

	string nom_fichier = "";
	cout << "nom du fichier : " << endl;
	cin >> nom_fichier;

	//ouverture du fichier en mode texte, récupération info nbr ligne et colonne
	ifstream fichier1(nom_fichier);
	int resX, resY;
	if (!fichier1.is_open()) { cout << "Erreur d'ouverture" << endl; }
	else {
		fichier1 >> resX;
		fichier1 >> resY;
		fichier1.close();
	}
	//ouverture du fichier en mode bianaire
	ifstream fichier(nom_fichier, ios::in | ios::binary); 
	if (!fichier.is_open()) { cout << "Erreur d'ouverture" << endl; }
	else {
		//calcul taille du fichier
		long pos = fichier.tellg();
		fichier.seekg(0, ios_base::end);
		long sizeFichier = fichier.tellg();
		fichier.seekg(pos, ios_base::beg);
		cout << "size fichier : " << sizeFichier << endl;
		//lecture du fichier en mode binaire
		char* tabC = new char[sizeFichier];
		fichier.read((char *)&tabC[0], sizeFichier*sizeof(char));
		if (!fichier.good()) { cout << "Erreur de lecture" << endl; }
		else { cout << "Lecture terminee" << endl; }
		fichier.close();

		//Déclaration de la matrice 2D
		float **tab_;
		tab_ = new float*[resX]; // resX nombre de ligne
		for (int i = 0; i < resX; i++) { // resY nombre de colonne
			tab_[i] = new float[resY]; 
			for (int j = 0; j < resY; j++) {
				tab_[i][j] = 0; //initialisé à 0
			}
		}
		char *esc = " ";
		char *n = "\n";
		char *zero = "0";
		//gestion en-tête
		int head = 0;
		int i = 0;
		while (head < 2) {
			if (tabC[i] == *n) { 
				head++; 
			}
			i++;
		}
		//lecture
		string valeur = "";
		float fvaleur = 0;
		int fi = 0;
		int fj = 0;
		while (i < sizeFichier) {
			if (tabC[i] == *esc) { fj++; }
			if (fj == 1280) { 
				fi++; 
				fj = 0;
			}
			if (tabC[i] != *zero && tabC[i] != *esc && tabC[i] != *n) {
				while (tabC[i] != *esc) {
					valeur += tabC[i]; 
					i++;
				}
				fvaleur = stof(valeur);
				tab_[fi][fj] = fvaleur;
				valeur = "";
			}
			i++;
		}
		/*************************************/
		/* INSERER VOTRE CODE A PARTIR D'ICI */
		/*************************************/








		/********************/
		/*FIN DE VOTRE CODE */
		/*EXPORTATION EN OBJ*/
		/********************/
		
		//nom du fichier crée:
		string name = "NewFile.obj";
		ofstream fichier(name); //crée le fichier revenu.txt s'il n'existe pas, efface le contenu s'il existe.
		if (!fichier.is_open()) cout << "Erreur d'ouverture" << endl;
		else {

			fichier << "# o pied" << endl;
			fichier << "# pos1: " << "0" << endl;
			fichier << "# pos2: " << "0" << endl;

			for (int i = 0; i < resX; i++) {
				for (int j = 0; j < resY; j++) {
					if (tab_[i][j] != 0) {
						fichier << "v " << ((i * 365) / resX) << " " << ((j*0.125) - 80) << " " << tab_[i][j] << endl;
					}
				}
			}

			if (!fichier.good()) cout << "Erreur d'ecriture" << endl;
			else cout << "Enregistrement termine" << endl;
		}

		system("pause");
	}
}