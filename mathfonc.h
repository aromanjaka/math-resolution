#ifndef MATHFONC_H
#define MATHFONC_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/// Formulaires pour entrer les données
void integralHtml();
void fonctionHtml();

///Styles pour la mise en forme
void styles();

/// Resolution de l'integrale
float* integraleTrapeze(float a,float b,float eps,int* bor);
float* integraleRectangle(float a,float b,float eps);

/// Fonctions à étudier
float fonction(float x);
float fonc(float x);

/// Méthode tangente
float fprim(float xo);
float pttangente(float xo);
float stangente(float a);

/// Dichotomie
float dichotomie(float a,float b);

/// Méthode sécante
float* coeff(float x1,float y1,float x2,float y2);
float ptSecante(float a, float b);
float ssecante(float a, float b);

/// Affichage de résultats
void integraleresult(char* a, char* b, char* eps);
void fonctionresult(float a,float b,char* method);

#endif
