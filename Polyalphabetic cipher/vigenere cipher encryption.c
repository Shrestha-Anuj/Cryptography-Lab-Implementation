#include<stdio.h>
#include<string.h>

char plain_text[30] = {}, cipher_text[30] = {}, key[30] = {};
int plain_text_value[30] = {}, cipher_text_value[30] = {}, key_value[30] = {};
int text_len = 0, key_len = 0; // to get the length of text and key
int white_space_position[30] = {}; // determine the position of white space in input text
int white_space_len; // length of white space array
int case_status[30]; // flag to check upper case or lower case

void getPlainText(void);

void removeWhiteSpace(char[],char[]);

void displayPlainText(void);

void getKey(void);

void displayKey(void);

void textToValue(char[30], int[30]);

void displayValue(void);

void keyPadding(void);

void encrypt(void);

void displayCipherText(void);

void main(){
	getPlainText();
	
	text_len = strlen(plain_text); // length before removing white space
	
	removeWhiteSpace(plain_text,"text");
	
	text_len = strlen(plain_text); // length after removing white space
	
	displayPlainText();
	
	getKey();
	
	key_len = strlen(key); // length of key before removing white space
	
	removeWhiteSpace(key,"key");
	
	key_len = strlen(key); // length of key after removing white space
	
	displayKey();
	
	textToValue(plain_text,plain_text_value);
	
	textToValue(key,key_value);
	
	displayValue();
	
	if(text_len == key_len){
		printf("\nLength of text and length of key are same so It can be called as a Vernam Encryption\n");
	}
	else if(text_len > key_len){
		keyPadding();
		printf("\n\nAfter Padding  Value becomes:\n");
		displayValue();
	}
	
	encrypt();
	
	displayCipherText();
}

void getPlainText(){
	printf("Enter the Plaintext:");
	gets(plain_text);
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

void displayPlainText(){
	printf("\nPlain text: ");
	puts(plain_text);
}

void getKey(){
	printf("\nEnter the key in alphabet form:");
	gets(key); 
}

void displayKey(){
	printf("\nKey: ");
	puts(key);
}
	
void textToValue(char vector[30], int vector_value[30]){
	int i,j, len;
	
	len = strlen(vector);
	
	for(i=0;i<len;i++){
		for(j=0;j<26;j++){
			if(vector[i] == ' '){
				vector_value[i] = 32; // 32 is an ascii value of white space if need to be dealt in key
			}
			else if(vector[i] == (j+65)){
				vector_value[i] = j;
				
				if(vector == plain_text){
					case_status[i] = 1;
				}
			}
			else if(vector[i] == (j+97)){
				vector_value[i] = j;
				
				if(vector == plain_text){
					case_status[i] = 0;
				}
			}
		}
	}
}

void displayValue(){
	int i, j;
	
	printf("\nPlaintext Value:");
	for(i = 0; i<text_len; i++){
		printf("%d, ", plain_text_value[i]);
	}
	
	printf("\nKey Value:");
	for(i = 0; i<key_len; i++){
		printf("%d, ", key_value[i]);
	}
}

void keyPadding(){
	int i, len_diff;

	len_diff = text_len - key_len;
	
	for(i=0;i<len_diff;i++){
		key_value[key_len + i] = key_value[i];
	}
	key_len = text_len;
}

void encrypt(){
	int i;
	
	for(i = 0; i<text_len; i++){
		if(case_status[i] == 1){
			cipher_text_value[i] = ((plain_text_value[i] + key_value[i]) % 26) + 65;
		}
		
		else if(case_status[i] == 0){
			cipher_text_value[i] = ((plain_text_value[i] + key_value[i]) % 26) + 97;
		}
	}
}
	
void displayCipherText(){
	int i, j, k;
	int temp[30] = {};
	
	for(i = 0; i<white_space_len; i++){
		temp[white_space_position[i]] = 32; 
	}
	
	int m = 0;
	
	for(j = 0; j<(text_len + white_space_len); j++){
		
		if(temp[j] != 32){
			temp[j] = cipher_text_value[m];
			m++;
		}	
	}
		
	for(k=0; k<(text_len + white_space_len); k++){
		cipher_text[k] = temp[k];
	}
	
	printf("\n\nCiphertext:");
	puts(cipher_text);
}

