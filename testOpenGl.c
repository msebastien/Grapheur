//changer la couleur
void changerCouleur(const float r, const float g, const float b){
	glColor3f(r, g, b);
}

//tracer une ligne entre 2 points
void tracerLigne (const float x1, const float y1, const float x2, const float y2){
	glBegin(GL_LINE);
		glVertex2f(x1, y1);
		glVertex2f(x1, y1);
	glEnd();
}


//tracer une ligne en continu
void tracerLigneContinueDepart (const float x, const float y){
	glBegin(GL_LINE_STRIP);
		glVertex2f(x, y);
}

void tracerLigneContinueSuite (const float x, const float y){
	glVertex2f(x,y);
}

void tracerLigneContinueFin(){
	glEnd();
}

//tracer le graphique de la fonction rentrée
void tracerGraphiqueTableau(point tabeauDesPoints[]){
	changerCouleur (0, 0, 255);
	tracerLigneContinueDepart(tabeauDesPoints[0]->x,tabeauDesPoints[0]->y);
	
	for (int i = 1; i < TAILLE_TABLEAU; i++){//paramètre TAILLE_TABLEAU à définir
		tracerLigneContinueSuite (tabeauDesPoints[i]->x,tabeauDesPoints[i]->y);
	}
	tracerLigneContinueFin();
}
//même chose avec une liste chainée
void tracerGraphiqueListe(point listeDesPoints){
	tracerLigneContinueDepart(listeDesPoints->x,listeDesPoints->y);
	while (listeDesPoints->suivant != NULL){
		listeDesPoints = listeDesPoints->suivant;
	}
	tracerLigneContinueFin();
}

//trouver le centre des axes
float centreDesAxes(){
	float ret = 0;
	if (ordoneeALOrigine < -1 || ordoneeALOrigine > 1){
		ret = ordoneeALOrigine;
	}
	return ret;
} 

//tracer lexs axes, on  choisi un repère cartésien (0, Ox, Oy)
void tracerAxes(int tailleFenetre){
	float centre = centreDesAxes();
	glBegin(GL_LINE);
		changerCouleur(255, 0, 0);
		glVertex2f(0, centre - tailleFenetre/2);
		glVertex2f(0, centre + tailleFenetre/2);
		
		glVertex2f(-tailleFenetre/2, centre);
		glVertex2f(tailleFenetre/2, centre);
	glEnd();
}

//fonction qui trace le quadrillage en fonction de la taille de la fenêtre
void tracerQuadrillage(int tailleFenetre){
	changerCouleur(0, 255, 0);
	//quadrillage y
	glBegin(GL_LINE);
	for (int x = 5; x >= -5; i--){
		glVertex2f(i*tailleFenetre/10, centre - tailleFenetre/2);
		glVertex2f(i*tailleFenetre/10, centre + tailleFenetre/2);
	}

	//quadrillage x
	for (int y = 5; y >= 5; i--){
		glVertex2f(-tailleFenetre/2, centre + i*tailleFenetre/10);
		glVertex2f(tailleFenetre/2, centre + i*tailleFenetre/10);
	}
	glEnd();
}

