#include "raylib.h"
#include "binaire.h"
#include <stdbool.h> 
#include <stdio.h>

int main(void){
	const int BUFF_SIZE = 256;
	char buffer[BUFF_SIZE];
	char input[BUFF_SIZE];

	printf("---\n");
	printf("Souhaitez vous (0) Convertir un message en image ou (1) convertir une image en message?\n");
	printf("---\n");
	fgets(input, BUFF_SIZE, stdin);

	if(input[0]=='0'){
		printf("---\n");
		printf("Quelle texte souhaiter vous transformer?\n");
		printf("---\n");
		fgets(buffer, BUFF_SIZE, stdin);

		printf("Success fgets\n");
		
		bool flag = true;
		int taille_m = 0;
		while(taille_m < BUFF_SIZE-1 && flag) {
			if(buffer[taille_m] == '\n') {
				flag = false;
				buffer[taille_m] = '\0';
				taille_m--;
				}
			taille_m++;
			}
			printf("success buffer\n");
		int** representation_binaire = String_vers_Binaire(buffer,taille_m);
		printf("success representation binaire\n");

		int** representation_binaire_avec_code_hamming = Binaire_vers_Code_Hamming(representation_binaire,taille_m);
		printf("success representation binaire avec code hamming\n");


		int* representation_binaire_taille = ASCII_vers_Binaire(taille_m);
		printf("success representation binaire taille\n");
		int** representation_binaire_taille_avec_code_hamming = Binaire_Simple_vers_Code_Hamming(representation_binaire_taille);
		printf("success representation binaire taille avec code hamming\n");

		const int BIT_MESSAGE = taille_m*2*16;
		printf("BIT MESSAGE: %d \n", BIT_MESSAGE);
		const int BIT_DEPART_ARRIVEE = 3;
		const int BIT_TAILLE = 16;

		const int NOMBRE_DE_BIT = BIT_MESSAGE + BIT_DEPART_ARRIVEE + BIT_TAILLE;
		printf("NOMBRE DE BIT TOTAL: %d \n", NOMBRE_DE_BIT);
		int ScreenSize = 0;
		while((ScreenSize*ScreenSize)<NOMBRE_DE_BIT){
			ScreenSize++;
		}


		const int SCREENWIDTH = ScreenSize*10;
		const int SCREENHEIGHT = (ScreenSize)*10;

		InitWindow(SCREENWIDTH, SCREENHEIGHT, "");

		SetTargetFPS(60);


		
		while (!WindowShouldClose())
		{
				BeginDrawing();
				ClearBackground(RAYWHITE);




				DrawRectangle(0,0,10,10,RED); // le bit suivant est le début du message

				int X=0, Y=1, cpt=1;
				while(cpt<NOMBRE_DE_BIT){
					for(int i=0;i<2;i++){
						for(int j=0;j<8;j++){
							if(Y==ScreenSize){
								Y=0;
								X++;
							}
							if(representation_binaire_taille_avec_code_hamming[i][j]==0){
								DrawRectangle(Y*10, X*10, 10, 10, WHITE);
								DrawRectangleLines(Y*10, X*10, 10, 10, WHITE);
							}
							else{
								DrawRectangle(Y*10, X*10, 10, 10, BLACK);
								DrawRectangleLines(Y*10, X*10, 10, 10, BLACK);
							}
							Y++;
							cpt++;
						}
					}
					if(cpt==BIT_TAILLE+1){
						if(Y==ScreenSize){
							Y=0;
							X++;
						}
						DrawRectangle(Y*10, X*10, 10, 10, GREEN);
						DrawRectangleLines(Y*10, X*10, 10, 10, GREEN);
						Y++;
						cpt++;
					}

					for(int i_tab=0;i_tab<taille_m*2;i_tab++){
						for(int j_tab=0; j_tab<8;j_tab++){
							
							if(Y==ScreenSize){
								Y=0;
								X++;
							}
		
							if(representation_binaire_avec_code_hamming[i_tab][j_tab]==0){
								DrawRectangle(Y*10, X*10, 10, 10, WHITE);
								DrawRectangleLines(Y*10, X*10, 10, 10, WHITE);
							}
							else{
								DrawRectangle(Y*10, X*10, 10, 10, BLACK);
								DrawRectangleLines(Y*10, X*10, 10, 10, BLACK);
							}
		
						Y++;
						cpt++;
						}
					}
					if(Y==ScreenSize){
						Y=0;
						X++;
					}

					DrawRectangle(Y*10, X*10, 10, 10, BLUE);
					DrawRectangleLines(Y*10, X*10, 10, 10, BLUE);

				

				}


				//DrawLine(18, 42, SCREENWIDTH - 18, 42, BLACK);

				DrawRectangleLines(0, 0, SCREENWIDTH, SCREENHEIGHT, BLACK);


			if (IsKeyPressed(KEY_S)) {
				for(int i = 0; i < 5; i++) {
					BeginDrawing();
					EndDrawing();
				} 
				TakeScreenshot("code.png");
				printf("Screenshot taken");
			}




			EndDrawing();
			//----------------------------------------------------------------------------------
		}


		// De-Initialization
		//--------------------------------------------------------------------------------------
		CloseWindow();        // Close window and OpenGL context
		//--------------------------------------------------------------------------------------

		Liberer_Tableau_Binaire(representation_binaire, taille_m);
		Liberer_Tableau_Binaire(representation_binaire_avec_code_hamming,taille_m*2);
		free(representation_binaire_taille);
		Liberer_Tableau_Binaire(representation_binaire_taille_avec_code_hamming,2);
	}
	else{
		printf("---\n");
		printf("Quel est le nom de votre fichier?\n");
		printf("---\n");
		fgets(buffer, BUFF_SIZE, stdin);

		printf("Success fgets\n");
    	bool flag = true;
		int length = 0;
		while(length < BUFF_SIZE-1 && flag) {
			if(buffer[length] == '\n') {
				flag = false;
				buffer[length] = '\0';
			}
			length++;
		}
		
		printf("Loading image: %s\n", buffer);
		
		Image image = LoadImage(buffer);
		int ScreenSize = image.width / 10;
		printf("Image grid size: %d x %d\n", ScreenSize, image.height / 10);
		
		Color startColor = GetImageColor(image, 5, 5);
		printf("Checking for separator at pixel (%d, %d)\n", 5, 5);
		printf("Color values: R=%d G=%d B=%d\n", startColor.r, startColor.g, startColor.b);
		if (!(startColor.r > 200 && startColor.g < 100 && startColor.b < 100)) {
			printf("Start marker not found in the image\n");
			UnloadImage(image);
			return 1;
		}
		else{
			printf("start marker found. red.\n");
		}
		
		int X = 0, Y = 1;
		
		int** taille_code_hamming = Init_Tableau_Binaire_Vide(2);
		for(int i = 0; i < 2; i++) {
			for(int j = 0; j < 8; j++) {
				if(Y >= ScreenSize) {
					Y = 0;
					X++;
				}
				Color pixelColor = GetImageColor(image, Y * 10 + 5, X * 10 + 5);
				
				int brightness = (pixelColor.r + pixelColor.g + pixelColor.b) / 3;
				
				taille_code_hamming[i][j] = (brightness > 127) ? 0 : 1;
				
				Y++;
			}
		}
		
		int* taille_bits = Code_Hamming_vers_Binaire_Simple(taille_code_hamming);
		Affichage_Binaire(taille_code_hamming,2);
		int taille_m = Binaire_vers_ASCII(taille_bits);
		printf("Decoded message length: %d\n", taille_m);

		
		if(Y >= ScreenSize) {
			Y = 0;
			X++;
		}

		Color sepColor = GetImageColor(image, Y * 10 + 5, X * 10 + 5);
		printf("Checking for separator at pixel (%d, %d)\n", Y * 10 + 5, X * 10 + 5);
		printf("Color values: R=%d G=%d B=%d\n", sepColor.r, sepColor.g, sepColor.b);

		if (!(sepColor.g > 180 && sepColor.r < 120 && sepColor.b < 120)) {
			printf("Separator marker not found. Needed green color, got R=%d G=%d B=%d\n", 
				sepColor.r, sepColor.g, sepColor.b);
			
			bool found = false;
			for (int testY = Y-1; testY <= Y+1 && !found; testY++) {
				for (int testX = X-1; testX <= X+1 && !found; testX++) {
					if (testY >= 0 && testX >= 0 && testY < ScreenSize) {
						Color testColor = GetImageColor(image, testY * 10, testX * 10);
						if (testColor.g > 180 && testColor.r < 120 && testColor.b < 120) {
							printf("Found separator nearby at (%d, %d)\n", testY * 10, testX * 10);
							X = testX;
							Y = testY;
							found = true;
						}
					}
				}
			}
			
			if (!found) {
				UnloadImage(image);
				return 1;
			}
		}
		Y++;

		printf("Starting to read message at position (%d,%d)\n", Y, X);

		int** message_bits = (int**)malloc(taille_m * 4 * sizeof(int*));
		if (!message_bits) {
			printf("Memory allocation failed for message_bits\n");
			UnloadImage(image);
			return 1;
		}

		for(int i = 0; i < taille_m * 4; i++) {
			message_bits[i] = (int*)malloc(8 * sizeof(int));
			if (!message_bits[i]) {
				printf("Memory allocation failed for message_bits[%d]\n", i);
				for (int j = 0; j < i; j++) {
					free(message_bits[j]);
				}
				free(message_bits);
				UnloadImage(image);
				return 1;
			}
			
			for(int j = 0; j < 8; j++) {
				if(Y >= ScreenSize) {
					Y = 0;
					X++;
				}
				
				if(X >= ScreenSize) {
					printf("Error: X coordinate (%d) out of bounds\n", X);
					for (int k = 0; k <= i; k++) {
						free(message_bits[k]);
					}
					free(message_bits);
					UnloadImage(image);
					return 1;
				}
				
				Color pixelColor = GetImageColor(image, Y * 10 + 5, X * 10 + 5);
				message_bits[i][j] = (pixelColor.r > 180) ? 0 : 1;
				
				if (i < 2) {
					printf("Reading bit[%d][%d] at (%d,%d): R=%d G=%d B=%d -> %d\n", 
						i, j, Y*10+5, X*10+5, pixelColor.r, pixelColor.g, pixelColor.b, message_bits[i][j]);
				}
				
				Y++;
			}
		}
		
		printf("About to decode %d bits (%d×2 rows of 8 bits each)\n", taille_m * 2 * 8, taille_m);
		printf("First few bits of message_bits:\n");
		for(int i = 0; i < 2 && i < taille_m * 2; i++) {
			printf("Row %d: ", i);
			for(int j = 0; j < 8; j++) {
				printf("%d ", message_bits[i][j]);
			}
			printf("\n");
		}

		printf("Entering Code_Hamming_vers_Binaire with taille_m=%d\n", taille_m);
		int** decoded_message = Code_Hamming_vers_Binaire(message_bits, taille_m*4);

		if (!decoded_message) {
			printf("Error: Code_Hamming_vers_Binaire returned NULL\n");
			Liberer_Tableau_Binaire(taille_code_hamming, 2);
			free(taille_bits);
			Liberer_Tableau_Binaire(message_bits, taille_m * 2);
			UnloadImage(image);
			return 1;
		}
		
		char* result = Binaire_vers_String(decoded_message, taille_m);
		
		printf("Decoded message: %s\n", result);
		
		Liberer_Tableau_Binaire(taille_code_hamming, 2);
		free(taille_bits);
		Liberer_Tableau_Binaire(message_bits, taille_m * 2);
		Liberer_Tableau_Binaire(decoded_message, taille_m);
		free(result);
		UnloadImage(image);
	}
    return 0;
}