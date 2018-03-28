#include "Projet.h"
#include "grapheur.h"

int bascule = 0;
static int NumeroFenetre;
static int Largeur, Hauteur;
static void(*AppliDessin)(void);
static void(*AppliTouche)(int);

Tableau creerListe() {
	Tableau t;
	t = NULL;
	t = malloc (sizeof (struct TableauSt))

	for (double i = -1; i < 1; i += 0.01) {
		t = insererDansTableau(t, i);
	}

	return t;
}
Tableau insererDansTableau(Tableau t, double i){
	// Nouveau maillon
	Tableau Points = NULL;
	if(t != NULL) {
		Points = malloc(sizeof(struct TableauSt));

		// Initilaisation de ses champs
		Points->x = i;
		Points->y = cos(i);
		
		// Insertion en tête de liste
	
		Points->suivant = t;
	}

	return Points;
}

void freeListe(Tableau Points){
	if (Points->suivant == NULL){
		free(Points);
	}else {
		freeListe(Points->suivant);
		free(Points);
	}
}

Point* creertableau() {
	Point tableau_evaluateur[TAILLE_MAX];
		for (float i = -10.0; i <= 10.0; i+=0.01) {
			for (int j = 0; j < TAILLE_MAX; j++){
			tableau_evaluateur[j].x = (double)i; // x
			tableau_evaluateur[j].y = sin((double)i); // f(x)
		}
	}
		return tableau_evaluateur;
}

/**
* GlutRedimensionner
*
* Cette procedure permet de gerer la taille de la fenetre quand (redimensionnee)
* (Fonction de callback pour glutReshapeFunc)
* @parma w largeur de la fenetre gl
* @parma h hauteur de la fenetre gl
*/

static void GlutRedimensionner(const int l, const int h)
{
	Largeur = l;
	Hauteur = h;
	glViewport(0, 0, Largeur, Hauteur);
}


static void GlutIdle(void)
{
	  //glutPostRedisplay();
}

static void GlutTouche(const unsigned char c, const int x, const int y)
{
	switch (c)
	{
	default:
		if (AppliTouche) (*AppliTouche)(c);
		break;
	}
	glutPostRedisplay();
}

static void Begin2DDisplay(void)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-1, 1, -1.0, 1.0, 0.5, 1.5);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0.0F, 0.0F, -1.0F);
}

static void End2DDisplay(void)
{
	/* Fin du trace, retour au parametres normaux */
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

static void InitDisplay(void)
{
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glClearColor(0.0F, 0.0F, 0.0F, 0.0F);
}

static void GlutDraw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Begin2DDisplay();
	if (AppliDessin) (*AppliDessin)();
	End2DDisplay();
	glutSwapBuffers();
}

/**
* outtextxy
*
* Cette proc�dure permet d'ecrit une chaine de charact�re s dans une zone de texte d�finie par les coordonn�es x et y
*
* @parma x abscisse du point (coint gauche superieur) de la zone de texte
* @parma y ordonn�e du point (coint gauche superieur) de la zone de texte
* @parma s tableau de charct�res
*
*/
void outtextxy(const float x, const float y, const char *str)
{
	const char *s = str;

	glRasterPos2f(x, y);
	while (*s != '\0')
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *s++);
	}
}

void bar(const float x0, const float y0, const float x1, const float y1)
{
	glBegin(GL_QUADS);
	glVertex2f(x0, y0);
	glVertex2f(x0, y1);
	glVertex2f(x1, y1);
	glVertex2f(x1, y0);
	glEnd();
}

/**
* InitialiserGraphique
*
* Procedure d'initialisation de la fenetre et de l'environement OpenGL
* L'initialisation de GLUT se trouve dans la procedure
* principale, elle necessite l'emploie des argument de
* la ligne de commande
*
* @parma ac
* @parma av[]
* @parma WinName definit le nom (titre) de la fentre d'affichage
* @parma w definit la largeur de la fenetre
* @parma h definit la hauteur de la fenetre
* @parma Draw definit une methode de tracage
* @parma Key definit une methode permettant la detection des touche du clavier
* @parma c entier designant le code ascii d'une touche
*
*/
void InitialiserGraphique(int ac, char *av[],
	const char *NomFenetre, const int l, const int h, void(*Dessin)(void),
	void(*Touche)(int))
{
	Largeur = l;
	Hauteur = h;

	glutInit(&ac, av);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(Largeur, Hauteur);

	NumeroFenetre = glutCreateWindow(NomFenetre);

	glutReshapeFunc(GlutRedimensionner); /* fonction appelee qd fenetre redimensionnee */

	glutIdleFunc(GlutIdle); /* fonction appelee en boucle */
	AppliTouche = Touche;

	glutKeyboardFunc(GlutTouche); /* GlutTouche est appelée lorsqu'une touche est appuyée*/
	AppliDessin = Dessin;

	glutDisplayFunc(GlutDraw);
	
	InitDisplay(); 
	glutMainLoop();

}

//changer la couleur
void changerCouleur(const float r, const float g, const float b) {
	glColor3f(r, g, b);
}

//tracer une ligne entre 2 points
void tracerLigne(const float x1, const float y1, const float x2, const float y2) {
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}


//tracer une ligne en continu
void tracerLigneContinueDepart(const float x, const float y) {
	glBegin(GL_LINE_STRIP);
	glVertex2f(x, y);
}

void tracerLigneContinueSuite(const float x, const float y) {
	glVertex2f(x, y);
}

void tracerLigneContinueFin() {
	glEnd();
}

//tracer le graphique de la fonction rentrée
/*void tracerGraphiqueTableau(Point tableauDesPoints[TAILLE_MAX]) {
	changerCouleur(0.0F, 0.0F, 1.0F);
	
	glBegin(GL_LINE_STRIP);
	glVertex2f(tableauDesPoints[0].x, tableauDesPoints[0].y);
	glVertex2f(tableauDesPoints[1].x, tableauDesPoints[1].y);
	glEnd();
	
	//tracerLigneContinueDepart(tableauDesPoints[0].x, tableauDesPoints[0].y);

	for (int i = 2; i < TAILLE_MAX; i++) {//paramètre TAILLE_TABLEAU à définir
		//tracerLigneContinueSuite(tableauDesPoints[i].x, tableauDesPoints[i].y);
		glBegin(GL_LINE_STRIP);
		glVertex2f(tableauDesPoints[i].x, tableauDesPoints[i].y);
		glVertex2f(tableauDesPoints[i+1].x, tableauDesPoints[i+1].y);
		glEnd();
	}
	//tracerLigneContinueFin();
}*/
//même chose avec une liste chainée
Tableau tracerGraphiqueListe(Tableau Points) {
	Tableau Ret = Points;

	glBegin(GL_LINE_STRIP);
	glVertex2f(Points->x, Points->y);
	while (Points->suivant != NULL) {
		Points = Points->suivant;
		glVertex2f(Points->x, Points->y);
	}
	glEnd();
	return Ret;
}

//trouver le centre des axes
float centreDesAxes() {
	float ret = 0;
	/*if (ordonneeALOrigine < -1 || ordoneeALOrigine > 1) {
		ret = ordoneeALOrigine;
	}*/
	return ret;
}

//tracer lexs axes, on  choisi un repère cartésien (0, Ox, Oy)
void tracerAxes(int tailleFenetre) {
	float centre = centreDesAxes();
	glBegin(GL_LINES);
	changerCouleur(1.0F, 0.0F, 0.0F);
	glVertex2f(0, centre - tailleFenetre / 2);
	glVertex2f(0, centre + tailleFenetre / 2);

	glVertex2f(-tailleFenetre / 2, centre);
	glVertex2f(tailleFenetre / 2, centre);
	glEnd();
}

//fonction qui trace le quadrillage en fonction de la taille de la fenêtre
void tracerQuadrillage(int tailleFenetre) {
	float centre = centreDesAxes();
	changerCouleur(0.2F, 0.2F, 0.2F);
	//quadrillage y
	
	for (float x = 2; x >= -2; x-=0.1) {
		glBegin(GL_LINES);
		glVertex2f(x, centre - tailleFenetre / 2);
		glVertex2f(x, centre + tailleFenetre / 2);
		glEnd();
	}

	//quadrillage x
	for (float y = 2; y >= -2; y-=0.1) {
		glBegin(GL_LINES);
		glVertex2f(-tailleFenetre / 2, centre + y);
		glVertex2f(tailleFenetre / 2, centre + y);
		glEnd();
	}
	
}


// FONCTIONS TEST
/**
* myKey
*
* Gestion des touches du clavier
*
* @parma c code ascci definissant une touche du clavier
*
*/
void myKey(int c)
{
	switch (c)
	{
	case 'a':
		bascule ^= 1; /* La bascule passe alternativement de 0 a 1 */
		break;
	}
}

/**
* myDraw
*
* Procédure
*
*/
void myDraw(void)
{
	// Change l'échelle des axes
	glScaled(1.0,1.0,0.0);

	glutSetCursor(GLUT_CURSOR_CROSSHAIR);

	if (bascule)
	{
		/* Trace un rectangle rouge a l'ecran si active
		* par appui de la touche 'a' */
		changerCouleur(1.0F, 0.0F, 0.0F);
		bar(-0.5F, -0.5F, 0.5F, 0.5F);
	}
	
	//changerCouleur(1.0F, 1.0F, 0.0F);
	Tableau courbe = creerListe();
	courbe = tracerGraphiqueListe(courbe);

	//tracerGraphiqueTableau(creertableau());
	//tracerLigne(-1.0, -1.0, 1.0, 1.0);
	tracerQuadrillage(2);
	tracerAxes(2);
	
	freeListe(courbe);

}