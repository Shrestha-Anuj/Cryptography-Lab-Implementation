#include<stdio.h>
#include<string.h>

char plain_text[60] = {}, cipher_text[60] = {}, starting_key[60] = {}, key[60] = {};
int plain_text_value[60] = {}, cipher_text_value[60] = {};
int text_len = 0, key_len = 0; // to get the length of text
int white_space_position[60] = {}; // determine the position of white space in input text
int white_space_len; // length of white space array
int case_status[60] = {}; // flag to check upper case or lower case
char starting_square_elements[26] = {}, square_elements[25] = {};
char square[5][5];
char digraphs[60] = {};
char plain_digraphs[60] = {}; // for containing the cipher character digraphs
int vowel_array_position[5] = {0,4,8,14,20}; // to avoid vowels as a replacement

void getCipherText(void);
void removeWhiteSpace(char[],char[]);
void displayCipherText(void);
void getKey(void);
void removeRedundantCharacter(char[],char[],char[]);
void processSquareElements(char[],char[],char[],char[]);
void createPolybiusSquare();
void displayKey(void);
void createSquareElements(void);
void createDigraphs(void);
void decrypt(void);
void displayPlainText(void);


int main(){
	getCipherText();
	
	text_len = strlen(cipher_text); // length before removing white space
	
	removeWhiteSpace(cipher_text,"text"); // removes all white spaces before the cipher process
	
	text_len = strlen(cipher_text); // length after removing white space
	
	displayCipherText();
	
	getKey();
	
	key_len = strlen(starting_key); // length before removing white space
	
	removeWhiteSpace(starting_key,"key");
	
	removeRedundantCharacter(starting_key, key,"key"); // function to get a non-repetitive key
	
	displayKey();
	
	createSquareElements(); // creates the all characters except 'J' for the polybuis square where I and J are treated as one
	
	processSquareElements(key, starting_square_elements, square_elements, "square"); // to create elements for square that does not contain elements in the key
	
	createPolybiusSquare(); // creates a 5x5 polybius square for playfair cipher
	
	createDigraphs(); // creates digraphs before cipher process
	
	decrypt();
	
	displayPlainText();
	
	return 0;
}

void getCipherText(){
	printf("Enter the Ciphertext:");
	gets(cipher_text);
}

void removeWhiteSpace(char text[60], char name[10]){
	int i, k;
	char temp_text[60] = {};
	char temp_key[60] = {};
	
	if(name == "text"){
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
	else if(name == "key"){
		
		k = 0;
		for(i = 0 ; i < key_len; i++){ // to remove white space from key
			if(text[i] != 32){
				temp_key[k] = text[i];
				k++;
			}
		}
		strcpy(text,temp_key);
	}
}

void displayCipherText(){
	printf("\nCipher text: ");
	puts(cipher_text);
}

void getKey(){
	printf("\nEnter the key in alphabet form:");
	gets(starting_key);
}

void removeRedundantCharacter(char initial_characters[30], char final_characters[30], char name[15]){
	
	int i, j, k = 0;
		
	printf("Initial %s Characters:\n", name);
	puts(initial_characters);
	
	int initial_characters_len = strlen(initial_characters);
		
	int final_characters_len = strlen(final_characters), found;
	
	for(i=0; i<initial_characters_len; i++){
		found = 0;
		
		// 105, 73 ascii value for i,I respectively
		// 106, 74 ascii value for j,J respectively
				
		if(initial_characters[i] == 106){ // converting j to i
			initial_characters[i] = 105;
		}
				
		else if(initial_characters[i] == 74){ // converting J to I
			initial_characters[i] = 73;
		}
		
		for(j=0; j<final_characters_len; j++){	
			if(found == 0){			
				if(initial_characters[i] == final_characters[j]){
					found = 1;
				}
			}	
		}
		
		if(found == 0){ // if identical characters found insert a character in between
			final_characters[k] = initial_characters[i];
			final_characters_len++;
			k++;
		}
	}
	
	printf("\nOld %s Characters:", name);
	puts(initial_characters);
	
	printf("\nNew %s Characters:", name);
	puts(final_characters);
	
	int m,n;
	
	for(m=0; m<final_characters_len;m++){
		for(n=0; n<26; n++){
			if(final_characters[m] == (n+97)){
				final_characters[m] -= 32;
			}
		}	
	}
}

void processSquareElements(char final_key_elements[30], char initial_square[30], char final_square[30], char name[15]){
	int i, j, k = 0;
	
	printf("Initial %s Characters:\n", name);
	puts(initial_square);
	
	int initial_characters_len = strlen(initial_square);
		
	int final_characters_len = strlen(final_key_elements), found;
	
	for(i=0; i<initial_characters_len; i++){
		found = 0;
		
		for(j=0; j<final_characters_len; j++){	
			if(found == 0){
				if((initial_square[i] == final_key_elements[j])){
					found = 1;
				}
			}
		}
		
		if(found == 0){
			final_square[k] = initial_square[i];
			k++;	
		}
	}
	
	printf("\nNew %s Characters:", name);
	puts(final_square);
}

void createPolybiusSquare(){
	int j,k,m = 0,n = 0;
	
	for(j=0;j<5;j++){
		for(k=0;k<5;k++){
			if(m < strlen(key)){
				square[j][k] = key[m];
				m++;
			}
			else{
				square[j][k] = square_elements[n];
				n++;
			}
		}
	}
	printf("\n Polybius Square:\n");
	for(j=0;j<5;j++){
		for(k=0;k<5;k++){
			printf("%c\t",square[j][k]);
		}
		printf("\n");
	}
}
void displayKey(){
	printf("\nKey: ");
	puts(key);
}

void createSquareElements(){
	int i,k = 0;
	
	for(i = 0; i<26; i++){
		if(i != 9){
			starting_square_elements[k] = (i+65);
			k++;
		}
	}
	
	printf("\ninitial square elements:\n");
	puts(starting_square_elements);
}

void createDigraphs(){
	int i,j,k = 0, p,r;
	char temp_ciphertext[60] = {};
	
	printf("\nCreating Digraph.....\n");
	
	// convert all the input to uppercase
	// tracking which character was upper or lower case by using case_status
	for(p = 0; p<strlen(cipher_text); p++){
		for(r = 0; r<26; r++){
			if(cipher_text[p] == (r + 97)){
				temp_ciphertext[p] = cipher_text[p] - 32;
				case_status[p] = 0;  // case_status set to 0 for already upper case
			}
			else if(cipher_text[p] == (r + 65)){
				temp_ciphertext[p] = cipher_text[p];
				case_status[p] = 1;  // case_status set to 1 for already upper case
			}
		}	
	}
	
	strcpy(digraphs,temp_ciphertext);
	
	printf("\nDigraph Completed......\n");
	
	printf("\nDigraph:\n");
	puts(digraphs);
	
	
}

void decrypt(){
	int i,j,k,n;
	int row[60], column[60];
	
	//to check and get the position of each digraph
	for(i = 0; i<strlen(digraphs); i++){
		for(j = 0; j<5; j++){
			for(k = 0; k<5; k++){
				if(digraphs[i] == square[j][k]){
					row[i] = j;
					column[i] = k;
				}
				else if(digraphs[i+1] == square[j][k]){
					row[i+1] = j;
					column[i+1] = k;
				}
			}
		}
		i++;
	}
	
	// playfair algorithm for decryption
	for(n = 0; n<strlen(digraphs); n++){
		
		if(column[n] == column[n+1]){
			plain_digraphs[n] = square[(row[n]+4) % 5][column[n]];
			plain_digraphs[n+1] = square[(row[n+1]+4) % 5][column[n+1]];
		}
		else if(row[n] == row[n+1]){
			plain_digraphs[n] = square[row[n]][(column[n]+4) % 5];
			plain_digraphs[n+1] = square[row[n]][(column[n+1]+4) % 5];
		}
		else{
			plain_digraphs[n] = square[row[n]][column[n+1]];
			plain_digraphs[n+1] = square[row[n+1]][column[n]];
		}
		n++;
	}
	
	printf("\ndecryption complete....\n");
	
	int g = 0, h, t, character_removed = 0;
	int temp_plain_text_value[60] = {};
	int new_case_status[30] = {};
	int case_status_len = strlen(plain_digraphs);
	int c, vowel_found;
	
	// to find and remove the added character between the closest identical character during the encryption in the decrypted output
	for(h=0;h<strlen(plain_digraphs);h++){
		
		vowel_found = 0;
		
		temp_plain_text_value[g] = plain_digraphs[h];
			
			if((h+1) != strlen(plain_digraphs)){
				// if identical characters are found in ith and (i+2)th position then those same letters might exist in same digraphs
				// before encryption
				if(plain_digraphs[h] == plain_digraphs[h+2]){
					
					for(c = 0; c<5; c++){
						if(vowel_found == 0){
							if(plain_digraphs[h+1] == (65 + vowel_array_position[c])){
								/* 	vowel between same identical character shows the identical characters were at different digraphs
									identical characters were not found in same digraphs 
									which do not require to add a random element in between during encryption */
									
								vowel_found = 1; // if it is vowel then nothing was added between the digraph
							}
						}	
					}
					
					if(vowel_found == 0){
						g++;
						temp_plain_text_value[g] = plain_digraphs[h+2]; // replacing the added random character with the successive element
						
						for(t = h+1; t < (case_status_len-character_removed); t++){ // to replace case status of removed character
							case_status[t] = case_status[t+1]; // replacing the case status of preceding character with case status of the following character
						}
						character_removed++;
						h += 2; // h+2 is the end of the digraph so starting of next digraph is h+3 after h+2
					}	
				}
				
				else{
					g++;
					temp_plain_text_value[g] = plain_digraphs[h+1];
					h += 1; // h+2 is not the end of the digraph so starting of next digraph is h+2 after h+1
				}
			}
			g++;
	}
	
	int y;
	for(y=0;y<(case_status_len - character_removed);y++){
		new_case_status[y] = case_status[y];
	}
	
	// changing the case of character in the output according to the input text as maintained by case_status array
	int w = 0;

	while(w < strlen(plain_digraphs)){
		
		if(new_case_status[w] == 0){
			plain_text_value[w] = temp_plain_text_value[w] + 32;
		}
		else{
			plain_text_value[w] = temp_plain_text_value[w];
		}
		w++;
	}
}
	
void displayPlainText(){
	int i, j, k;
	int temp[60] = {};
	
	// getting the position to add the white space
	for(i = 0; i<white_space_len; i++){ 
		temp[white_space_position[i]] = 32; 
	}
	
	
	//placing the white space in the output text
	int m = 0;
	
	for(j = 0; j<(strlen(plain_digraphs) + white_space_len); j++){ 
		if(temp[j] != 32){
			temp[j] = plain_text_value[m];
			m++;
		}
	}
	// transfering the final output text into the array
	for(k=0; k<(strlen(plain_digraphs) + white_space_len); k++){
		plain_text[k] = temp[k];
	}
	
	printf("\n\nPlaintext:");
	puts(plain_text);
}

