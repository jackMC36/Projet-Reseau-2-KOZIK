#include "binaire.h"

/// @brief Fonction feur puissance, prend paramètre deux entiers a et b, et renvoie a^b. (créer pour eviter de importer "math.h" et du -lm durant la compilation)
/// @param a 
/// @param b 
/// @return int : a^b
int puissance(int a, int b){
    if(b == 0){
        return 1;
    }
    int z = 1;
    for(int i = 0; i < b; i++){
        z *= a;
    }
    return z;
}

/// @brief Fonction Char_vers_ASCII, prend en paramètre un caractère l, effectue un cast et renvoie son encodage ASCII.
/// @param l : char -> lettre
/// @return int : encodage ASCII
int Char_vers_ASCII(char l){
    return (int)l;
}

/// @brief Fonction ASCII_vers_Char, prend en paramètre un entier représentant un code ASCII, effectue un cast et renvoie le caractère équivalent.
/// @param code : int -> code ASCII 
/// @return char : caractère
char ASCII_vers_Char(int code){
    return (char)code;
}

/// @brief Fonction ASCII_vers_Binaire, prend en paramètre un entier représentant un code ASCII, renvoie sa représentation en binaire sur un octet. 
/// @param code : int -> code ASCII 
/// @return int* : tableau d'entier représentant un nombre binaire
int* ASCII_vers_Binaire(int code){
    int* binaire = malloc(8 * sizeof(int));
    for (int i = 7; i >= 0; i--) {
        binaire[i] = code % 2;
        code = code / 2;
    }
    return binaire;
}

/// @brief Fonction Binaire_vers_ASCII, prend en paramètre un tableau de 8 bits et renvoie le code ASCII équivalent.
/// @param binaire -> liste d'entier représentant un nombre binaire
/// @return int: un code ASCII 
int Binaire_vers_ASCII(int* binaire){
    int ascii = 0;
    for (int i = 0; i < 8; i++) {
        if(binaire[i]==1){
            ascii += puissance(2,7-i);
        }
    }
    return ascii;
}

/// @brief Fonction Init_Tableau_Binaire_Vide, prend en paramètre une taille et renvoie un tableau avec taille*8 case.
/// @param taille -> nombre de caractères d'une phrase
/// @return int** : tableau d'entier taille*8 
int** Init_Tableau_Binaire_Vide(int taille){
    int** binaire = malloc(taille*sizeof(int*));
        for(int i = 0;i<taille;i++){
            binaire[i] = malloc(8*sizeof(int));
        }
    return binaire;
}

/// @brief Procédure Liberer_Tableau_Binaire, prend en paramètre un tableau à 2 dimensions et sa taille et le libère.
/// @param binaire -> tableau à 2 dimensions 
/// @param taille -> nombre de ligne du tableau
void Liberer_Tableau_Binaire(int** binaire, int taille){
    for(int i=0; i<taille; i++){
        free(binaire[i]);
    } 
    free(binaire);
}

/// @brief Fonction String_vers_Binaire, prend en paramètre une chaine de caractères et sa taille et qui renvoie sa représentation binaire.
/// @param chaine -> chaine de caractères 
/// @param taille -> taille de la chaine de caractères
/// @return int** : tableau binaire représentant la chaine de caractères
int** String_vers_Binaire(char* chaine, int taille){
    int** binaire = Init_Tableau_Binaire_Vide(taille); 
    for(int i=0; i<taille;i++){
            int code = Char_vers_ASCII(chaine[i]);
            binaire[i] = ASCII_vers_Binaire(code);
    }
    return binaire;
}

/// @brief Fonction Binaire_vers_String, prend en paramètre un tableau d'entier sous représentation binaire et donne la chaine de caractères éqivalentes (avec la conversion ASCII).
/// @param binaire -> tableau d'entier taille*8 représentant des octets
/// @param taille -> nombre de ligne du tableau d'entier à 2 dimensions
/// @return char* : la chaine de caractères équivalentes.
char* Binaire_vers_String(int** binaire, int taille){
    char* mot = malloc((taille + 1) * sizeof(char));
    
    int ascii;
    for(int i = 0; i < taille; i++){
        ascii = Binaire_vers_ASCII(binaire[i]);
        mot[i] = ASCII_vers_Char(ascii);
    }
    
    mot[taille] = '\0';
    
    return mot;
}

/// @brief Procédure Affichae_Binaire, prend en paramètre un tableau d'octets ainsi qu'une taille, et l'affiche dans le terminal.
/// @param binaire -> tableau d'octet
/// @param taille -> nombre de ligne du tableau
void Affichage_Binaire(int** binaire, int taille){
    for(int i=0;i<taille;i++){
        for(int j=0;j<8;j++){
            printf("%d",binaire[i][j]);
        }
        printf("\n");
    }
}

/// @brief Procédure Affichage_String, prend en paramètre une chaine de caractère ainsi que sa taille et l'affiche dans le teminal.
/// @param phrase -> chaine de caractères 
/// @param taille -> taille de la chaine de caractères
void Affichage_String(char* phrase, int taille){
    for(int i = 0; i<taille;i++){
        printf("%c", phrase[i]);
    }
}

/// @brief Fonction Binaire_Simple_vers_Code_Hamming, prend en paramètre un tableau d'entier binaire et renvoie le code Hamming correspondant.
/// @param binaire -> tableau d'entier binaire
/// @return int** : tableau d'entier représentant le code Hamming
int** Binaire_Simple_vers_Code_Hamming(int* binaire) {
    const int taille = 2;
    int** hamming_code = Init_Tableau_Binaire_Vide(2);

    int d1 = binaire[0];
    int d2 = binaire[1];
    int d3 = binaire[2];
    int d4 = binaire[3];
    int d5 = binaire[4];
    int d6 = binaire[5];
    int d7 = binaire[6];
    int d8 = binaire[7];

    hamming_code[0][2] = d1;
    hamming_code[0][4] = d2;
    hamming_code[0][5] = d3;
    hamming_code[0][6] = d4;

    hamming_code[0][0] = (d1 + d2 + d4) % 2; // P1
    hamming_code[0][1] = (d1 + d3 + d4) % 2; // P2
    hamming_code[0][3] = (d2 + d3 + d4) % 2; // P4
    hamming_code[0][7] = (hamming_code[0][0] + hamming_code[0][1] + hamming_code[0][3] + d1 + d2 + d3 + d4) % 2; // P8 (parité)

    hamming_code[1][2] = d5;
    hamming_code[1][4] = d6;
    hamming_code[1][5] = d7;
    hamming_code[1][6] = d8;

    hamming_code[1][0] = (d5 + d6 + d8) % 2; // P1
    hamming_code[1][1] = (d5 + d7 + d8) % 2; // P2
    hamming_code[1][3] = (d6 + d7 + d8) % 2; // P4
    hamming_code[1][7] = (hamming_code[1][0] + hamming_code[1][1] + hamming_code[1][3] + d5 + d6 + d7 + d8) % 2; // P8 (parité)

    return hamming_code;
}
                

/// @brief Fonction Binaire_vers_Code_Hamming, prend en paramètre un tableau d'entier représentant une chaine de caractères et sa taille et renvoie le code Hamming correspondant.
/// @param binaire -> tableau d'entier représentant une chaine de caractères en binaire
/// @param taille -> taille de la chaine de caractères
/// @return int** : tableau d'entier représentant le code Hamming
int** Binaire_vers_Code_Hamming(int** binaire, int taille) {
    int** hamming_code = Init_Tableau_Binaire_Vide(2 * taille);
    int k;

    for (int i = 0; i < taille; i++) {
        k = 2 * i;

        int d1 = binaire[i][0];
        int d2 = binaire[i][1];
        int d3 = binaire[i][2];
        int d4 = binaire[i][3];
        int d5 = binaire[i][4];
        int d6 = binaire[i][5];
        int d7 = binaire[i][6];
        int d8 = binaire[i][7];

        hamming_code[k][2] = d1;
        hamming_code[k][4] = d2;
        hamming_code[k][5] = d3;
        hamming_code[k][6] = d4;

        hamming_code[k][0] = (d1 + d2 + d4) % 2; // P1
        hamming_code[k][1] = (d1 + d3 + d4) % 2; // P2
        hamming_code[k][3] = (d2 + d3 + d4) % 2; // P4
        hamming_code[k][7] = (hamming_code[k][0] + hamming_code[k][1] + hamming_code[k][3] + d1 + d2 + d3 + d4) % 2; // P8 (parité)

        hamming_code[k + 1][2] = d5;
        hamming_code[k + 1][4] = d6;
        hamming_code[k + 1][5] = d7;
        hamming_code[k + 1][6] = d8;

        hamming_code[k + 1][0] = (d5 + d6 + d8) % 2; // P1
        hamming_code[k + 1][1] = (d5 + d7 + d8) % 2; // P2
        hamming_code[k + 1][3] = (d6 + d7 + d8) % 2; // P4
        hamming_code[k + 1][7] = (hamming_code[k + 1][0] + hamming_code[k + 1][1] + hamming_code[k + 1][3] + d5 + d6 + d7 + d8) % 2; // P8 (parité)
    }

    return hamming_code;
}

/// @brief Fonction Code_Hamming_vers_Binaire, prend en paramètre un tableau d'entier à deux dimensions représentant un code de Hamming et renvoie le tableau binaire initiale.
/// @param hamming_code -> tableau d'entier à deux dimensions représentant un code de Hamming 
/// @param taille -> entier correspondants au nombre de lignes du tableau.
/// @return int** : representation binaire
int** Code_Hamming_vers_Binaire(int** hamming_code, int taille){
    printf("Code_Hamming_vers_Binaire: début avec taille=%d\n", taille);
    
    int** binaire = Init_Tableau_Binaire_Vide(taille/2);

    int k;
    for(int i=0; i<taille/2; i++){
        k = 2*i;
        
        if (k >= taille || k+1 >= taille) {
            printf("Erreur: indice hors limites k=%d (taille=%d)\n", k, taille);
            Liberer_Tableau_Binaire(binaire, taille/2);
            return NULL;
        }
        
        if (i == 0) {
            printf("Premier hamming_code[%d]: ", k);
            for (int j = 0; j < 8; j++) {
                printf("%d ", hamming_code[k][j]);
            }
            printf("\n");
        }
        
        binaire[i][0] = hamming_code[k][2];
        binaire[i][1] = hamming_code[k][4];
        binaire[i][2] = hamming_code[k][5];
        binaire[i][3] = hamming_code[k][6];
        binaire[i][4] = hamming_code[k+1][2];
        binaire[i][5] = hamming_code[k+1][4];
        binaire[i][6] = hamming_code[k+1][5];
        binaire[i][7] = hamming_code[k+1][6];
    }
    
    printf("Code_Hamming_vers_Binaire: décodage réussi\n");
    return binaire;
}

/// @brief Fonction Code_Hamming_vers_Binaire_Simple, prend en paramètre un tableau d'entier 2*8 représentant un code de Hamming et renvoie le tableau binaire initiale.
/// @param hamming_code -> tableau d'entier à deux dimensions (2*8) représentant un code de Hamming 
/// @return int* : tableau binaire
int* Code_Hamming_vers_Binaire_Simple(int** hamming_code){
    int* binaire = malloc(8*sizeof(int));
    binaire[0] = hamming_code[0][2];
    binaire[1] = hamming_code[0][4];
    binaire[2] = hamming_code[0][5];
    binaire[3] = hamming_code[0][6];
    binaire[4] = hamming_code[1][2];
    binaire[5] = hamming_code[1][4];
    binaire[6] = hamming_code[1][5];
    binaire[7] = hamming_code[1][6];
    return binaire;
    }


int binaire_main(){

    // Test
    /*
    int taille = 12;
    char phrase[12] = "Hello World!";
    int** binaire = String_vers_Binaire(phrase,taille);
    int** code_hamming = Binaire_vers_Hamming_Code(binaire,taille);
    Affichage_Binaire(code_hamming,taille*2);

    int** binaire2 = Code_Hamming_vers_Binaire(code_hamming,taille*2);
    char* phrase3 = Binaire_vers_String(binaire2,taille);
    Affichage_String(phrase3,taille);

    Liberer_Tableau_Binaire(binaire,taille);
    */
   
   return 0;
}