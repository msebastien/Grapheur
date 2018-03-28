#ifndef GRAPHEUR_H_
#define GRAPHEUR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <Windows.h>
#include <GLUT.H>

#define TAILLE_MAX 256

struct TableauSt{
	float x;
	float y;
	struct TableauST* suivant;
}; typedef struct TableauSt* Tableau;

Point* creertableau ();

//int tracerGraphe(Point Coordonnees[], float echelle, int intervalleDebut, int intervalleFin, int pas);
//int obtenirExpression(char* expression);
//int afficherErreur(typeerreur erreur);
//int obtenirEchelle(float echelle, int intervalleDebut, int intervalleFin, int pas);

void InitialiserGraphique(int ac, char *av[],
	const char *NomFenetre, const int l, const int h, void(*Dessin)(void),
	void(*Touche)(int));

static void GlutRedimensionner(const int l, const int h);
static void GlutIdle(void);
static void GlutTouche(const unsigned char c, const int x, const int y);
static void GlutDraw(void);

static void Begin2DDisplay(void);
static void End2DDisplay(void);

static void InitDisplay(void);
void outtextxy(const float x, const float y, const char *str);
void bar(const float x0, const float y0, const float x1, const float y1);

// FONCTIONS DESSIN
void changerCouleur(const float r, const float g, const float b);
void tracerLigne(const float x1, const float y1, const float x2, const float y2);
void tracerLigneContinueDepart(const float x, const float y);
void tracerLigneContinueSuite(const float x, const float y);
void tracerLigneContinueFin(void);
void tracerGraphiqueTableau(Point tableauDesPoints[TAILLE_MAX]);

// FONCTIONS TEST
void myKey(int c);
void myDraw(void);



#endif