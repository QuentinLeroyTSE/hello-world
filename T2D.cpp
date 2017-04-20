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

		fichier << "# o pied" << endl << endl;
		fichier << "# pos1: " << pos1 << endl;
		fichier << "# pos2: " << pos2 << endl << endl;

		float u;
		for (int i = 0; i < X_; i++) {
			for (int j = 0; j < Y_; j++) {
				if (tab_[i][j] != 0) {
					u = i;
					fichier << "v " << ((u * 365) / X_) << " " << ((j*0.125) - 80) << " " << tab_[i][j] << endl;
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


void T2D::ouverture() {

	for (int i = 0; i < X_; i++) {
		tab_[i][0] = 0; //1ere colonne
		tab_[i][Y_-1] = 0; //derniere colonne
	}
	for (int j = 1; j < Y_ - 1; j++) {
		tab_[0][j] = 0; //1ere ligne
		tab_[X_-1][j] = 0; // derniere ligne
	}
	//déclaration du masque binaire = tab_ en binaire
	int **mask= new int*[X_];
	for (int i = 0; i < X_; i++) {
		mask[i] = new int[Y_];
		for (int j = 0; j < Y_; j++) {
			mask[i][j] = 0; //initialisé à 0
		}
	}
	//remplissage du masque
	for (int i = 0; i < X_; i++) {
		for (int j = 0; j < Y_; j++) {
			if (tab_[i][j] != 0) {
				mask[i][j] = 1;
			}
		}
	}
	/*********/
	/*EROSION*/
	/*********/
	//déclaration tableau de stockage temporaire case à effacer
	int **temp = new int*[X_];
	for (int i = 0; i < X_; i++) {
		temp[i] = new int[Y_];
		for (int j = 0; j < Y_; j++) {
			temp[i][j] = 1; //initialisé à 1
		}
	}
	//erosion
	//à chaque case qu'il faut mettre à 0, c'est temp qui passe à 0, ensuite on multiplie avec mask
	bool zero = false;
	for (int i = 1; i < X_-1; i++) { //attention au bord
		for (int j = 1; j < Y_-1; j++) {
			//parcours voisinnage
			for (int ki = -1; ki <= 1; ki++) {
				for (int kj = -1; kj <= 1; kj++) {
					if (mask[i + ki][j + kj] == 0) {
						zero = true;
					}
				}
			}
			if (zero == true) {
				temp[i][j] = 0;
			}
			zero = false;
		}
	}
	//Multiplication mask * temp
	for (int i = 0; i < X_; i++) {
		for (int j = 0; j < Y_; j++) {
			mask[i][j] = mask[i][j] * temp[i][j];
		}
	}
	/**************************/
	/*Dilation (sur le masque)*/
	/**************************/
	//réinnitialisation de temp à 0
	for (int i = 0; i < X_; i++) {
		for (int j = 0; j < Y_; j++) {
			temp[i][j] = 0;
		}
	}
	//dilatation du masque
	bool un = false;
	for (int i = 1; i < X_ - 1; i++) { //attention au bord
		for (int j = 1; j < Y_ - 1; j++) {
			//parcours voisinnage
			for (int ki = -1; ki <= 1; ki++) {
				for (int kj = -1; kj <= 1; kj++) {
					if (mask[i + ki][j + kj] == 1) {
						un = true;
					}
				}
			}
			if (un == true) {
				temp[i][j] = 1;
			}
			un = false;
		}
	}
	// mask = temp
	for (int i = 0; i < X_; i++) {
		for (int j = 0; j < Y_; j++) {
			mask[i][j] = temp[i][j];
		}
	}
	/***************/
	/*FIN OUVERTURE*/
	/***************/
	//tab_ * mask (application du masque d'ouverture à l'image réelle) (masque binaire)
	for (int i = 0; i < X_; i++) {
		for (int j = 0; j < Y_; j++) {
			tab_[i][j] = tab_[i][j] * mask[i][j];
		}
	}
}

void T2D::contour() {

	//l'image est déjà nettoyée.
	//déclaration du masque binaire = tab_ en binaire
	int **mask = new int*[X_];
	for (int i = 0; i < X_; i++) {
		mask[i] = new int[Y_];
		for (int j = 0; j < Y_; j++) {
			mask[i][j] = 0; //initialisé à 0
		}
	}
	//remplissage du masque (toutes les valeures != 0 deviennent 1)
	for (int i = 0; i < X_; i++) {
		for (int j = 0; j < Y_; j++) {
			if (tab_[i][j] != 0) {
				mask[i][j] = 1;
			}
		}
	}
	//déclaration tableau de stockage temporaire case à effacer
	int **temp = new int*[X_];
	for (int i = 0; i < X_; i++) {
		temp[i] = new int[Y_];
		for (int j = 0; j < Y_; j++) {
			temp[i][j] = 0; //initialisé à 0
		}
	}
	//détection du contour et lissage du contour
	int diff = 0;
	int value;
	int nbr = 0;
	float moy = 0;
	for (int i = 1; i < X_ - 1; i++) { //attention au bord
		for (int j = 1; j < Y_ - 1; j++) {
			//parcours voisinnage
			value = mask[i][j];
			for (int ki = -1; ki <= 1; ki++) {
				for (int kj = -1; kj <= 1; kj++) {
					if (mask[i + ki][j + kj] != value) {
						diff++;
					}
				}
			}
			if (diff >= 3) {
				/**/
				temp[i][j] = 1;
				/**/
				/*
				for (int ki = -1; ki <= 1; ki++) {
					for (int kj = -1; kj <= 1; kj++) {
						if (tab_[i + ki][j + kj] != 0) { nbr++; } //on compte le nbr de valeur != de 0 ds le voisinnage
						moy += tab_[i + ki][j + kj];
					}
				}
				moy = moy / nbr;
				tab_[i][j] = moy;
				moy = 0;
				nbr = 0;*/
			}
			diff = 0;
		}
	}
	/*tab_ * temp : conservation du contour uniquement*/
	for (int i = 0; i < X_; i++) {
		for (int j = 0; j < Y_; j++) {
			tab_[i][j] = tab_[i][j] * temp[i][j];
		}
	}
}