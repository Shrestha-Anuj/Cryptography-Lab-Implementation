// C Program Encryption using Rail Fence of depth 2
#include<stdio.h>
#include<string.h>

char plain_text[60] = {}, cipher_text[60] = {};
char fence[2][60] = {}; // fence for rail fence cipher
int cipher_text_value[60] = {};
int text_len = 0; // to get the length of text
int cipher_text_value_len = 0; // to get the cipher text array length
int white_space_position[60] = {}; // determine the position of white space in input text
int white_space_len; // length of white space array
int case_status[60] = {}; // flag to check upper case or lower case
int depth = 2; // depth of rail fence


void getPlainText(void);
void removeWhiteSpace(char[]);
void displayPlainText(void);

void encrypt(void);
void displayCipherText(void);


void main(){
	getPlainText();
	
	text_len = strlen(plain_text); // length before removing white space
	
	removeWhiteSpace(plain_text);
	
	text_len = strlen(plain_text); // length after removing white space
	
	displayPlainText();
	
	encrypt();
	
	displayCipherText();
}

void getPlainText(){
	printf("Enter the Plaintext:");
	gets(plain_text);
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

void displayPlainText(){
	printf("\nPlain text: ");
	puts(plain_text);
}

void encrypt(){
	int i, j, k;
	
	for(i =0 ;i<depth; i++){
		for(j = 0; j<text_len; j++){
			if(j % 2 == i){
				fence[i][j] = plain_text[j];
			}
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
	
	// to get the ciphertext
	int z = 0;
	
	for(i = 0; i<depth; i++){
		for(j=0; j<text_len; j++){
			if(j % 2 == i){
				cipher_text_value[z] = fence[i][j];
				z++;
			}	
		}
	}
	cipher_text_value_len = z;
}
	
void displayCipherText(){
	int i, j, k;
	int temp[60] = {};
	
	// getting the position to add the white space
	for(i = 0; i<white_space_len; i++){
		temp[white_space_position[i]] = 32; 
	}
		
	//placing the white space in the output text
	int m = 0;
	
	for(j = 0; j<(cipher_text_value_len + white_space_len); j++){
		if(temp[j] != 32){
			temp[j] = cipher_text_value[m];
			m++;
		}
	}
	
	// transfering the final output text into the array
	for(k=0; k<(cipher_text_value_len + white_space_len); k++){
		cipher_text[k] = temp[k];
	}
	
	printf("\n\nCiphertext:");
	puts(cipher_text);
}

