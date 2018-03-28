#include "Projet.h"
#include "grapheur.h"

//variable globales, leur utilisation est inévitable pour la gestion des evenements
int deplacementX = 0;
int deplacementY = 0;
float scale_x = 1.0;
float scale_y = 1.0;

int zoomIn = 0, zoomOut = 0;
static int NumeroFenetre;
static int Largeur, Hauteur;
static void(*AppliDessin)(void);
static void(*AppliTouche)(int);


char* convFloatString(float x) {
	char* str = NULL;
	int nombre = (int)(x)+1;
	str = malloc( 20 );

	sprintf_s(str, 20,"%f", x);

	return str;
}

Tableau creerListe() {
	Tableau t;
	t = NULL;
	t = malloc(sizeof(struct TableauSt));

	t->suivant = NULL;
	for (double i = -10; i < 10; i += 0.01) {
		t = insererDansTableau(t, i);
	}

	return t;
}

Tableau insererDansTableau(Tableau t, double i){
	// Nouveau maillon
	Tableau Points;
	Points = malloc(sizeof(struct TableauSt));
		
	// Initialisation de ses champs
	Points->x = i;
	Points->y = cos(i);
		
	// Insertion en tête de liste
	if (t != NULL) {
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
* afficherTexteXY
*
* Cette proc�dure permet d'ecrit une chaine de charact�re s dans une zone de texte d�finie par les coordonn�es x et y
*
* @parma x abscisse du point (coint gauche superieur) de la zone de texte
* @parma y ordonnee du point (coint gauche superieur) de la zone de texte
* @parma s tableau de charcteres
*
*/
void affichertexteXY(const float x, const float y, const char *str)
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
	//glutEstablishOverlay();
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

void tracerPoint(const float x, const float y) {
	glBegin(GL_POINT);
	glVertex2f(x, y);
	glEnd();
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
Tableau tracerGraphiqueListe(Tableau Points) {
	Tableau Ret = Points;

	glBegin(GL_LINE_STRIP);
	glVertex2f(Points->x + deplacementX, Points->y + deplacementY);
	while (Points->suivant != NULL) {
		Points = Points->suivant;
		glVertex2f(Points->x + deplacementX, Points->y + deplacementY);
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
void tracerAxes() {
	glBegin(GL_LINES);
	changerCouleur(1.0F, 0.0F, 0.0F);
	glVertex2f(deplacementX, -1000);
	glVertex2f(deplacementX, 1000);

	glVertex2f(-1000, deplacementY);
	glVertex2f(1000, deplacementY);
	glEnd();
}

//fonction qui trace le quadrillage en fonction de la taille de la fenêtre
void tracerQuadrillage() {
	float centre = centreDesAxes();
	changerCouleur(0.2F, 0.2F, 0.2F);
	//quadrillage y
	
	for (float x = 500; x >= -500; x-=1) {
		glBegin(GL_LINES);
		glVertex2f(x + deplacementX, -500);
		glVertex2f(x + deplacementX, 500);
		glEnd();
	}

	//quadrillage x
	for (float y = 500; y >= -500; y-=1) {
		glBegin(GL_LINES);
		glVertex2f(-500,  y + deplacementY);
		glVertex2f(500,  y - deplacementY);
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
	case 'e':
		zoomIn = 1; /* La bascule passe alternativement de 0 a 1 */
		break;
	case 'a':
		zoomOut = 1;
		break;
	case 'z':
		deplacementY -= 1;
		break;
	case 's':
		deplacementY += 1;
		break;
	case 'q':
		deplacementX -= 1;
		break;
	case 'd':
		deplacementX += 1;
		break;
	case 'r':
		deplacementX = 0;
		deplacementY = 0;
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
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	
	// Change l'échelle des axes
	if (zoomOut && !zoomIn)
	{
		if (scale_x > 0.1 && scale_y > 0.1 ) {
			scale_x -= 0.1;
			scale_y -= 0.1;
		}
		zoomOut = 0;
	}
	else if (zoomIn && !zoomOut) {
		if (scale_x < 4.1 && scale_y < 4.1) {
			scale_x += 0.1;
			scale_y += 0.1;
		}
		zoomIn = 0;
	}
	glScaled(scale_x, scale_y, 0.0);

	


	tracerQuadrillage(deplacementX, deplacementY);
	tracerAxes(deplacementX, deplacementY);

	tracerQuadrillage();
	tracerAxes();

	changerCouleur(0.0F, 0.0F, 1.0F);
	
	Tableau courbe = creerListe();
	courbe = tracerGraphiqueListe(courbe);

	// AFFICHAGE INFOS
	affichertexteXY(-1.0 / scale_x, 0.9 / scale_y, "Scale :");
	affichertexteXY(-0.8/scale_x, 0.9/scale_y, convFloatString(scale_x));

	freeListe(courbe);
}