//Programme Traitement d'image 3D format obj


#include <iostream>
//#include <iomanip>
#include <fstream>
#include <string>
#include "Include\T2D.h"

using namespace std;

void main()
{

	string nom_fichier = "";
	cout << "nom du fichier : " << endl;
	cin >> nom_fichier;

	ifstream fichier(nom_fichier); //ouverture du fichier en mode texte
	
	if (!fichier.is_open()) {
		cout << "Erreur d'ouverture" << endl;
	}
	else {
		string mot = "";
		string pos1, pos2;

		//Gestion ent�te
		while (mot != "pos1:") {
			fichier >> mot;
		}
		fichier >> pos1;
		while (mot != "pos2:") {
			fichier >> mot;
		}
		fichier >> pos2;

		cout << "pos1: " << pos1 << endl;
		cout << "pos2: " << pos2 << endl;

		fichier.close();
	}

	ifstream frapide(nom_fichier, ios::in | ios::binary); //ouverture du fichier en mode bianaire

	if (!frapide.is_open()) {
		cout << "Erreur d'ouverture" << endl;
	}
	else {
		
		//calcul taille du fichier
		
		// sauvegarder la position courante 
		long pos = frapide.tellg();
		// se placer en fin de fichier 
		frapide.seekg(0, ios_base::end);
		// r�cup�rer la nouvelle position = la taille du fichier 
		long sizeFichier = frapide.tellg();
		// restaurer la position initiale du fichier 
		frapide.seekg(pos, ios_base::beg);
		cout << "size fichier : " << sizeFichier << endl;
		
		//lecture du fichier en mode binaire
		char* tabC = new char[sizeFichier];

		frapide.read((char *)&tabC[0], sizeFichier*sizeof(char));
		
		if (!frapide.good()) { cout << "Erreur de lecture" << endl; }
		else { cout << "Lecture terminee" << endl; }
		frapide.close();

		//compte du nombre de ligne
		char* v = "v";
		int nbr_ligne = 0;
		int i = 0;
		for (i; i < sizeFichier; i++) {
			if (tabC[i] == *v) {
				nbr_ligne++;
				i = i + 20; //histoire de gagner du temps
			}
		}

		cout << "nbr_ligne fichier, nombre de point : " << nbr_ligne << endl; // = nombre de point enfaite

		int sizeTF = nbr_ligne * 3;
		float* TabF = new float[sizeTF];
		cout << "sizeTF : " << sizeTF << endl;
		//recherche du 1er "v"
		i = 0;
		while (tabC[i] != *v) {
			i++;
		}
		//tabC[i] = v ici
		i = i + 2;
		char *esc = " ";
		char *n = "\n";
		string valeur = "";
		float fvaleur = 0;
		int f = 0;
		while (i < sizeFichier) {
			if (tabC[i] == *v) {
				i = i + 2;
			}
			while (tabC[i] != *esc && tabC[i] != *n) {
				valeur += tabC[i]; //tr�s long --> � optimiser
				i++;
			}
			fvaleur = stof(valeur);
			TabF[f] = fvaleur;
			valeur = "";
			f++;
			i++;
		}
		cout << "tableau float remmpli " << endl;
		/*cout.setf(ios::fixed);

		for (int j = 0; j < sizeTF; j++) {
			cout << setprecision(15) << TabF[j] << " ";
		}*/
		/*int pth = 0;
		for (int j = 0; j < sizeTF; j++) {
			if (TabF[j] >= 180) {
				pth++;
			}
		}
		cout << "nombre de point au-dessus de 180 mm : " << pth << endl;*/
		//Iniatialisation matrice 2D contenant les altitudes
		int resX = 1500; //366 mm / 0.25 mm = 1464; 0.25 : pas du moteur = r�solution en x 
		int resY = 1280;
		T2D t2d(resX, resY);
		
		t2d.fillTab(TabF, sizeTF);

	}//else ouverture

	system("pause");
}


