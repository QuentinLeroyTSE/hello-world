//Définition classe T2D

#include <iostream>
#include <fstream>
#include <string>
#include "..\Include\T2D.h"

using namespace std;

T2D::T2D(int resX, int resY) {

	tailleTab_ = resX; //nombre de ligne du tableau
	tab_ = new float*[tailleTab_];
	for (int i = 0; i < tailleTab_; i++) {
		tab_[i] = new float[resY]; //resY nbr de point par ligne = nbr de colonne
		for (int j = 0; j < resY; j++) {
			tab_[i][j] = 0; //initialisé à 0
		}
	}
}

void T2D::fillTab(float* tabF, int sizeTF, int resX) {

	float x;
	int f = 0;
	int i; // lignes X
	int j; // colonnes Y
	int nbr_ligne = 0;

	while (f < sizeTF) {

		x = tabF[f];
		i = (int)((x * resX) / 365);

		while (tabF[f] == x) { //tant qu'on est sur une même ligne
			
			j = (int) ((tabF[f + 1]+80) / 0.125); //troncature
			tab_[i][j] = tabF[f + 2];
			f = f + 3;
		}
		
		nbr_ligne++;
		j = 0;

	}
	cout << "nombre de ligne effective : " << nbr_ligne << endl << endl;
	
}


void T2D::exportobj(string name, float pos1, float pos2, int resX, int resY) {

	ofstream fichier(name); //crée le fichier revenu.txt s'il n'existe pas, efface le contenu s'il existe.
	if (!fichier.is_open()) cout << "Erreur d'ouverture" << endl;
	else {

		fichier << "# o pied" << endl;
		fichier << "# pos1: " << pos1 << endl;
		fichier << "# pos2: " << pos2 << endl;

		for (int i = 0; i < resX; i++) {
			for (int j = 0; j < resY; j++) {
				if (tab_[i][j] != 0) {
					fichier << "v " << ((i * 365) / resX) << " " << ((j*0.125) - 80) << " " << tab_[i][j] << endl;
				}
			}
		}

		if (!fichier.good()) cout << "Erreur d'écriture" << endl;
		else cout << "Enregistrement terminé" << endl;
	}

}

void T2D::exportT2D(string name, int resY) {

	ofstream fichier(name); 
	if (!fichier.is_open()) cout << "Erreur d'ouverture" << endl;
	else {

		fichier << tailleTab_ << endl;
		fichier << resY;

		for (int i = 0; i < tailleTab_; i++) {
			fichier << endl;
			for (int j = 0; j < resY; j++) {
				fichier << tab_[i][j] << " ";
			}
		}

		if (!fichier.good()) cout << "Erreur d'ecriture" << endl;
		else cout << "Enregistrement termine" << endl;
	}

}