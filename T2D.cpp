//Définition classe T2D

#include <iostream>
#include <fstream>
#include <string>
#include "..\Include\T2D.h"

using namespace std;

T2D::T2D(int resX, int resY) {

	X_ = resX; //nombre de ligne du tableau
	Y_ = resY;
	tab_ = new float*[X_];
	for (int i = 0; i < X_; i++) {
		tab_[i] = new float[Y_]; //resY nbr de point par ligne = nbr de colonne
		for (int j = 0; j < Y_; j++) {
			tab_[i][j] = 0; //initialisé à 0
		}
	}
}

void T2D::fillTab(float* tabF, int sizeTF) {

	float x;
	int f = 0;
	int i; // lignes X
	int j; // colonnes Y
	int nbr_ligne = 0;

	while (f < sizeTF) {

		x = tabF[f];
		i = (int)((x * X_) / 365);

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


void T2D::exportobj(string name, float pos1, float pos2) {

	ofstream fichier(name); //crée le fichier revenu.txt s'il n'existe pas, efface le contenu s'il existe.
	if (!fichier.is_open()) cout << "Erreur d'ouverture" << endl;
	else {

		fichier << "# o pied" << endl;
		fichier << "# pos1: " << pos1 << endl;
		fichier << "# pos2: " << pos2 << endl;

		for (int i = 0; i < X_; i++) {
			for (int j = 0; j < Y_; j++) {
				if (tab_[i][j] != 0) {
					fichier << "v " << ((i * 365) / X_) << " " << ((j*0.125) - 80) << " " << tab_[i][j] << endl;
				}
			}
		}

		if (!fichier.good()) cout << "Erreur d'écriture" << endl;
		else cout << "Enregistrement terminé" << endl;
	}

}

void T2D::exportT2D(string name) {

	ofstream fichier(name); 
	if (!fichier.is_open()) cout << "Erreur d'ouverture" << endl;
	else {

		fichier << X_ << endl;
		fichier << Y_;

		for (int i = 0; i < X_; i++) {
			fichier << endl;
			for (int j = 0; j < Y_; j++) {
				fichier << tab_[i][j] << " ";
			}
		}

		if (!fichier.good()) cout << "Erreur d'ecriture" << endl;
		else cout << "Enregistrement termine" << endl;
	}

}


void T2D::pantalon(float alpha) {

	float min, max = 0;
	float moy = 0;
	int nbr_valeur = 0;
	for (int i = 0; i < X_; i++) {
		for (int j = 0; j < Y_; j++) {
			if (tab_[i][j] != 0) {
				moy += tab_[i][j];
				nbr_valeur++;
				if (tab_[i][j] > max) {
					max = tab_[i][j];
				}
			}
		}
	}
	moy = moy / nbr_valeur;
	cout << "moyenne = " << moy << endl;
	min = max;
	float ecartype = 0;
	float carre;
	for (int i = 0; i < X_; i++) {
		for (int j = 0; j < Y_; j++) {
			if (tab_[i][j] != 0) {
				carre = (tab_[i][j] - moy);
				ecartype += carre*carre;
				if (tab_[i][j] < min) {
					min = tab_[i][j];
				}
			}
		}
	}
	ecartype = ecartype / nbr_valeur;
	ecartype = sqrt(ecartype);
	cout << "ecart-type = " << ecartype << endl;
	cout << "min = " << min << endl;
	cout << "max = " << max << endl;

	//suppression points > u + aplha*sigma
	float seuil = moy + alpha * ecartype;
	for (int i = 0; i < X_; i++) {
		for (int j = 0; j < Y_; j++) {
			if (tab_[i][j] > seuil) {
				tab_[i][j] = 0;
			}
		}
	}

}