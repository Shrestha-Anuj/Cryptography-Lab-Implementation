// C Program Encryption using Rail Fence of depth 2
#include<stdio.h>
#include<string.h>

char plain_text[60] = {}, cipher_text[60] = {};
char fence[2][60] = {}; // fence for rail fence cipher
int plain_text_value[60] = {};
int text_len = 0; // to get the length of text
int cipher_text_value_len = 0; // to get the cipher text array length
int white_space_position[60] = {}; // determine the position of white space in input text
int white_space_len; // length of white space array
int case_status[60] = {}; // flag to check upper case or lower case
int depth = 2; // depth of rail fence


void getCipherText(void);
void removeWhiteSpace(char[]);
void displayCipherText(void);

void decrypt(void);
void displayPlainText(void);


void main(){
	getCipherText();
	
	text_len = strlen(cipher_text); // length before removing white space
	
	removeWhiteSpace(cipher_text);
	
	text_len = strlen(cipher_text); // length after removing white space
	
	displayCipherText();
	
	decrypt();
	
	displayPlainText();
}

void getCipherText(){
	printf("Enter the Ciphertext:");
	gets(cipher_text);
}

void removeWhiteSpace(char text[60]){
	int i, k;
	char temp_text[60] = {};
	
	k = 0;
	for(i = 0 ; i < text_len; i++){ // to locate white space
		if(text[i] == 32){
			white_space_position[k] = i;
			k++;
		}
	}
	white_space_len = k;
	
	k = 0;

	for(i = 0 ; i < text_len; i++){ // to remove white space from input text
		if(text[i] != 32){
			temp_text[k] = text[i];
			k++;
		}
	}
	strcpy(text,temp_text);
}

void displayCipherText(){
	printf("\nCipher text: ");
	puts(cipher_text);
}

void decrypt(){
	int i, j, k;
	
	k = 0;
	for(i =0 ;i<depth; i++){
		for(j = i; j<text_len; j++){
			fence[i][j] = cipher_text[k];
			j++;
			k++;
		}
	}
	
	//display fence
	for(i =0 ;i<depth; i++){
		// to make the outer box
		for(k = 0; k<text_len; k++){
			printf("----");
		}
		printf("\n");
		// to make the fence elements
		for(j = 0; j<text_len; j++){

			printf("%c | ",fence[i][j]);
		}
		printf("\n");
	}
	// to make the outer box
	for(k = 0; k<text_len; k++){
		printf("----");
	}
	printf("\n");
	
	// to get the plaintext
	int z = 0;
	
	for(i =0 ;i<text_len; i++){
		for(j = 0; j<depth; j++){
			if(i%2 == j){
				plain_text_value[z] = fence[j][i];
				z++;
			}	
		}
	}
	cipher_text_value_len = z;
}
	
void displayPlainText(){
	int i, j, k;
	int temp[60] = {};
	
	// getting the position to add the white space
	for(i = 0; i<white_space_len; i++){
		temp[white_space_position[i]] = 32; 
	}
		
	// placing the white space in the output text
	int m = 0;
	
	for(j = 0; j<(cipher_text_value_len + white_space_len); j++){
		if(temp[j] != 32){
			temp[j] = plain_text_value[m];
			m++;
		}
	}
	
	// transfering the final output text into the array
	for(k=0; k<(cipher_text_value_len + white_space_len); k++){
		plain_text[k] = temp[k];
	}
	
	printf("\n\nPlaintext:");
	puts(plain_text);
}

