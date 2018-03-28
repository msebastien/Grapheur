#ifndef PROJET_H_INCLUDED
#define PROJET_H_INCLUDED

struct Point2D {
    float x;
    float y;
};
typedef struct Point2D Point;


/**




*/
// TO DO : J'ai défini quelques erreurs random pour que mon compilateur arrête de m'afficher des erreurs partout 
//et qu'il puisse enfin compiler le projet. Il faudra donc modifier ce type plus tard au fil du développement.
typedef enum{
    DIV_PAR_ZERO, ERREUR_LEXICALE, ERREUR_SYNTAXE
}typeerreur;

typedef enum{
    REEL,OPERATEUR,FONCTION,ERREUR,FIN,PAR_OUV,PAR_FERM,VARIABLE
}typelexem;

typedef enum{
    PLUS,MOINS,FOIS,DIV,PUISSANCE
}typeoperateur;

typedef enum{
    ABS,SIN,SQRT,LOG,COS,TAN,EXP,ENTIER,VAL_NEG,SINC
}typefonction;

typedef union{
    float reel;
    typefonction fonction;
    typeoperateur operateur;
    typeerreur erreur;
}typevaleur;

typedef struct{
    typelexem lexem;
    typevaleur valeur;
}typejeton;

struct ArbreSt{
    typejeton jeton;
    struct ArbreSt * fils_gauche;
    struct ArbreSt * fils_droit;
};
typedef struct ArbreSt * Arbre;




#endif // PROJET_H_INCLUDED
