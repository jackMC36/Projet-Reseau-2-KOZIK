#ifndef BINAIRE_H
#define BINAIRE_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int puissance(int a, int b);

int Char_vers_ASCII(char l);
int ASCII_vers_Char(int code);

int* ASCII_vers_Binaire(int code);
int Binaire_vers_ASCII(int* binaire);

int** Init_Tableau_Binaire_Vide(int taille);
void Liberer_Tableau_Binaire(int** binaire, int taille);

int** String_vers_Binaire(char* chaine, int taille);
char* Binaire_vers_String(int** binaire, int taille);

void Affichage_Binaire(int** binaire, int taille);
void Affichage_String(char* phrase, int taille);

int** Binaire_Simple_vers_Code_Hamming(int* binaire);
int** Binaire_vers_Code_Hamming(int** binaire, int taille);
int** Code_Hamming_vers_Binaire(int** hamming_code, int taille);
int* Code_Hamming_vers_Binaire_Simple(int** hamming_code);

#endif