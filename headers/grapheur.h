#ifndef GRAPHEUR_H_
#define GRAPHEUR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <Windows.h>
#include <GLUT.H>

#define TAILLE_MAX 256
#define LARGEUR_FENETRE 800
#define HAUTEUR_FENETRE 600


struct TableauSt{
	float x;
	float y;
	struct TableauSt* suivant;
};
typedef struct TableauSt* Tableau;


Tableau insererDansTableau(Tableau t, double i);
Tableau creerListe();
void freeListe(Tableau Points);

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
void affichertexteXY(const float x, const float y, const char *str);
void bar(const float x0, const float y0, const float x1, const float y1);

char* convFloatString(float x);

// FONCTIONS DESSIN
void tracerQuadrillage();
void tracerAxes();
void changerCouleur(const float r, const float g, const float b);
void tracerPoint(const float x, const float y);
void tracerLigne(const float x1, const float y1, const float x2, const float y2);
void tracerLigneContinueDepart(const float x, const float y);
void tracerLigneContinueSuite(const float x, const float y);
void tracerLigneContinueFin(void);
Tableau tracerGraphiqueListe(Tableau Points);

// FONCTIONS TEST
void myKey(int c);
void myDraw(void);



#endif