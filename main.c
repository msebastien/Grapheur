#include "Projet.h"
#include "grapheur.h"


/**
* main
*
* La fonction principale avec deux arguments permettant de récupérer les éléments en ligne de comment.
*
* Dans  cet  exemple  les  fonctions  (dites  callback)  myDraw  et  myKey  sont  installées  ici  par
* l'appel  InitGraph  en  tant  que fonctions  réagissantes  aux  évènements  de  "re-dessinage"  (pour  myDraw)
* et  aux  évènements  d'appui  sur  une  touche  du
* clavier (myKey).
µ
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