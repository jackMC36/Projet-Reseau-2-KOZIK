#include "binaire.h"

int main(){
    int taille = 4;
    int tab[8] = {0, 1, 1, 0, 0, 0, 0, 1};


    char message[4] = "axel";
    int** a = String_vers_Binaire(message,taille);
    Affichage_Binaire(a,taille);
    printf("\n");
    int ** b = Binaire_vers_Code_Hamming(a,taille);
    Affichage_Binaire(b,taille*2);

    int* binaire_taille = ASCII_vers_Binaire(taille);
    int** binaire_taille_hamming = Binaire_Simple_vers_Code_Hamming(binaire_taille);
    int* conversion = Code_Hamming_vers_Binaire_Simple(binaire_taille_hamming);
    int c = Binaire_vers_ASCII(conversion);
    printf("%d", c);
    return 0;
}