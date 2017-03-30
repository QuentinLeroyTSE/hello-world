//Définition classe T2D

#include <iostream>
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

void T2D::fillTab(float* tabF, int sizeTF) {

	float x = tabF[0];
	int f = 0;
	int i = 0;
	int j = 0;
	while (f < sizeTF) {
		while (tabF[f] == x) { //tant qu'on est sur une même ligne
			tab_[i][j] = tabF[f + 2];
			j++;
			f = f + 3;
		}
		x = tabF[f];
		i++;
		j = 0;
	}
	cout << "nombre de ligne effective : " << i << endl << endl;
	/*for (int k = 0; k < i; k++) {
		cout << endl;
		for (int l = 0; l < 1280; l++) {
			cout << tab_[k][l] << " ";
		}
	}*/
}