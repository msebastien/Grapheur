#ifndef PROJET_H_INCLUDED
#define PROJET_H_INCLUDED

struct Point2D {
    float x;
    float y;
};
typedef Point2D Point;


/**




*/
typedef enum{

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

typedef struct*{
    typelexem lexem;
    typevaleur valeur;
}typejeton;

struct ARBREST{
    typejeton jeton;
    struct ARBREST * fils_gauche;
    struct ARBREST * fils_droit;
};
typedef ARBREST * Arbre;




#endif // PROJET_H_INCLUDED
