#include "Projet.h"
#include "grapheur.h"


/**
* main
*
* La fonction principale avec deux arguments permettant de r�cup�rer les �l�ments en ligne de comment.
*
* Dans  cet  exemple  les  fonctions  (dites  callback)  myDraw  et  myKey  sont  install�es  ici  par
* l'appel  InitGraph  en  tant  que fonctions  r�agissantes  aux  �v�nements  de  "re-dessinage"  (pour  myDraw)
* et  aux  �v�nements  d'appui  sur  une  touche  du
* clavier (myKey).
�
* @parma ac : nombre de parametres
* @parma av : tableau contenant les parametres
*
*/
int main(int argc, char* argv[]) {
	
	/*char* expression = NULL;
	
	printf("Bienvenue dans Grapheur\n");
	printf("Entrez une expression fonctionnelle : \n");
	
	gets(expression);*/
	
	InitialiserGraphique(argc, argv, "Grapheur", 800, 600, myDraw, myKey);

	return EXIT_SUCCESS;
}