#ifndef GRAPHEUR_H_
#define GRAPHEUR_H_



void creerFenetre(GtkApplication *app, gpointer user_data);



int tracerGraphe(Point Coordonnees[], float echelle, int intervalleDebut, int intervalleFin, int pas);
int obtenirExpression(char* expression);
//int afficherErreur(typeerreur erreur);
int obtenirEchelle(float echelle, int intervalleDebut, int intervalleFin, int pas);






#endif